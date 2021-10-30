/*
 * CAN_pal.c
 *
 *  Created on: Oct 6, 2021
 *      Author: Carlos Calvillo
 */

#include "sdk_project_config.h"

#include "BasicTypes.h"
#include "HwConfig.h"
#include "Signals.h"
#include "CANpal.h"

/* "interrupt_manager.h" is required for importing symbols
 * related to interrupt configurations. */
#include "interrupt_manager.h"
#include "sdk_project_config.h"
/* Need to add to the Include Path (-I):
 * ../SDK/platform/drivers/src/flexcan
 * for the compiler to find "flexcan_hw_access.h" and
 * "flexcan_irq.h" */
/* Need to include file flexcan_irq.h for symbol CAN0_ORed_0_15_MB_IRQHandler */
#include "flexcan_irq.h"
/* Need to include flexcan_hw_access.h for symbols CAN_ID_STD_MASK and CAN_ID_STD_SHIFT */
#include "flexcan_hw_access.h"


#define CAN_PAL_RX_BUFFER	0
#define CAN_PAL_TX_BUFFER	1

#define CAN_TX_MSG_DEFAULT_LEN 		8u
#define CAN_TX_MSG_DEFAULT_PAD 		0xffu

#define FLEXCAN_INSTANCE 	can_instance0.instIdx
/* Symbol required for FLEXCAN_SetMsgBuffIntCmd API */
extern CAN_Type * const flexcanBase[];


/* ---------------- */
/* Exported Symbols */
/* ---------------- */
UBaseType_t uxSavedInterruptStatus;
/* Symbol required for FLEXCAN_SetMsgBuffIntCmd API */
CAN_Type * const flexcanBase[] = CAN_BASE_PTRS;

/* Variable to hold current SW variant */
//uint8_t sw_variant = SW_VARIANT_DRIVER;

/* ------------------ */
/*  Imported symbols  */
/* ------------------ */

/* ------------------------------- */
/* Prototypes of private functions */
/* ------------------------------- */
static void CANpal_isr_CAN_MB(void);
static void CANpal_event_callback(uint32_t instance, can_event_t eventType,
							uint32_t objIdx,
							void *driverState);

/* ------------------------------- */
/* Global private data definitions */
/* ------------------------------- */
/* Global variable to hold the received message data from CAN PAL */
can_message_t rx_message;

/* Global variable to hold the last generated event from CAN PAL */
can_event_t can_event_type;

/* Default information for TX messages */
flexcan_data_info_t default_tx_info = {
	.msg_id_type = FLEXCAN_MSG_ID_STD, 	/* Send standard ID messages by default */
	.data_length = 8, 					/* By default assume 8 data bytes.
										 * Needs to change per each transmission. */
#if FEATURE_CAN_HAS_FD
	.fd_enable = false,					/* Assume no FD frame by default */
	.fd_padding = 0,						/* Assume padding of 0x00 by default */
	.enable_brs = false,            /* Disable bit rate switch in CAN FD frame by default */
#endif
	.is_remote = false              /* Assume data frame by default (not remote frame) */
};



/* -------------------- */
/* Function Definitions */
/* -------------------- */
/* ============================================================================
 * Function Name: CANpal_init
 * Description: Initializes CAN driver and CAN Pal
 * Arguments:
 * Return:
 * ========================================================================= */
void CANpal_init(void)
{
	volatile status_t local_status; /* Holds return status of APIs */

	can_buff_config_t can_pal_buff_config = { /* Generic buffer config */
			.enableFD = false,
			.enableBRS = false,
			.fdPadding = 0x00,
			.idType = CAN_MSG_ID_STD,
			.isRemote = false
		};

	/* Initialize CAN Pal  */
	local_status = CAN_Init(&can_instance0, &can_config0);

	/* Initialize CAN Pal Rx Buffer */
	/* Using a dummy ID in the acceptance filter. Later on the filter
	 * will be changed to accept all messages.
	 * Using message buffer (MB) 0 for reception. */
	local_status = CAN_ConfigRxBuff(&can_instance0, CAN_PAL_RX_BUFFER, &can_pal_buff_config, 0x10);

	/* Set Global Acceptance filter (will override individual MB filters).
	 * For this need to use directly CAN driver APIs... */
	/* Filter will accept any incoming message */
	FLEXCAN_DRV_SetRxMaskType(FLEXCAN_INSTANCE, FLEXCAN_RX_MASK_GLOBAL);
	/* Set acceptance filter for Standard IDs */
	FLEXCAN_DRV_SetRxMbGlobalMask(FLEXCAN_INSTANCE,FLEXCAN_MSG_ID_STD,0);

	/* Initialize CAN Pal Tx Buffer */
	/* Will use message buffer (MB) 1 for Transmission */
	local_status = CAN_ConfigTxBuff(&can_instance0,CAN_PAL_TX_BUFFER, &can_pal_buff_config);

	/* Associate CAN event callback */
	/* This callback will be called within ISR context */
	local_status = CAN_InstallEventCallback(&can_instance0,&CANpal_event_callback,NULL);

	/* Install CAN0 MB interrupt handler */
	/* Same interrupt is shared for events on message buffers 0 to 15 */
	/* Using own ISR function */
	INT_SYS_InstallHandler(CAN0_ORed_0_15_MB_IRQn, CANpal_isr_CAN_MB, NULL);
	/* Enable CAN0 MB interrupt handler */
	INT_SYS_EnableIRQ(CAN0_ORed_0_15_MB_IRQn);

	/* To allow calls safe APIs from FreeRTOS, setting interrupt priority to
	be equal to or lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY. */
	INT_SYS_SetPriority(CAN0_ORed_0_15_MB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );

	/* Enable RX/TX interrupts */
	local_status = FLEXCAN_SetMsgBuffIntCmd(flexcanBase[FLEXCAN_INSTANCE],CAN_PAL_RX_BUFFER,true);
	local_status = FLEXCAN_SetMsgBuffIntCmd(flexcanBase[FLEXCAN_INSTANCE],CAN_PAL_TX_BUFFER,true);

	/* Set-up reception of MB 0 (reception message buffer) */
	/* Received data will be put into the global variable rx_message */
	local_status = CAN_Receive(&can_instance0, CAN_PAL_RX_BUFFER, &rx_message);

	(void)local_status; /* Remove warning of unused variable */
}

/* ============================================================================
 * Function Name: CANpal_event_callback
 * Description: This callback is triggered automatically by the CAN Pal layer
 * 				upon a transmission or reception of a CAN msg.
 * Arguments:
 * Return:
 * ========================================================================= */
static void CANpal_event_callback(uint32_t instance, can_event_t eventType,
							uint32_t objIdx,
							void *driverState)
{
	/* Set the received event to a global variable since it will be used
	 * later by the ISR function. */
	can_event_type = eventType;

	/* Check if this callback is due to a reception or a transmission */
	if(eventType == CAN_EVENT_RX_COMPLETE)
	{
		/* Successful reception has been completed */
		/* Data from CAN PAL shall be available at variable rx_message */

		switch(HwConfig_Get())
		{
			case HWCONFIG_DRIVER:
				//can_DCM_DR_HALreceiveMsg(rx_message.id, rx_message.data, rx_message.length);
				break;
			case HWCONFIG_PASSENGER:
				/* call HALreceiveMsg function for DCM_PS */
				break;
			case HWCONFIG_REAR_LEFT:
				/* call HALreceiveMsg function for DCM_RL */
				break;
			case HWCONFIG_REAR_RIGHT:
				/* call HALreceiveMsg function for DCM_RR */
				break;
		}
	}
	else if(eventType == CAN_EVENT_TX_COMPLETE)
	{
		/* Call CAN IL message TX confirmation and TX retry strategy */
		switch(HwConfig_Get())
		{
			case HWCONFIG_DRIVER:
				/* Successful transmission. Confirm TX */
				//can_DCM_DR_HALconfirmTxMsg();
				/* Trigger retry strategy */
				//can_DCM_DR_txRetry();
				break;
			case HWCONFIG_PASSENGER:
				/* Call HALconfirmTxMsg function for DCM_PS */
				/* Call txRetry function for DCM_PS */
				break;
			case HWCONFIG_REAR_LEFT:
				/* Call HALconfirmTxMsg function for DCM_RL */
				/* Call txRetry function for DCM_RL */
				break;
			case HWCONFIG_REAR_RIGHT:
				/* Call HALconfirmTxMsg function for DCM_RR */
				/* Call txRetry function for DCM_RR */
				break;
		}
	}
	else
	{
		/* Nothing to do */
	}
}

/* ============================================================================
 * Function Name: CANpal_isr_CAN_MB
 * Description: Customized ISR for processing CAN RX/TX interrupt
 * Arguments:
 * Return:
 * ========================================================================= */
static void CANpal_isr_CAN_MB(void)
{
	/* This customized ISR is created to allow re-enabling the receive interrupts
	 * after processing the generated IRQ */

	/* CAll generated ISR from CAN driver */
	CAN0_ORed_0_15_MB_IRQHandler();

	/* IRQ disables RX interrupt, re-enable it to have continuous reception. */
	if(can_event_type == CAN_EVENT_RX_COMPLETE){
		CAN_Receive(&can_instance0, CAN_PAL_RX_BUFFER, &rx_message);
	}
}


/* ============================================================================
 * Function Name: CANpal_send_CAN_message
 * Description: Triggers the transmission of a CAN message in the driver
 * Arguments:
 * Return:
 * ========================================================================= */
status_t CANpal_send_CAN_message(uint32_t msg_id, uint8_t length, uint8_t * data)
{
	default_tx_info.data_length = length;
	volatile status_t local_status;

	/* Request msg transmission to CAN driver */
	/* Will use the defined message buffer (1 for TX) */
	local_status = FLEXCAN_DRV_Send(FLEXCAN_INSTANCE,
										CAN_PAL_TX_BUFFER,
										&default_tx_info,
										msg_id,
										data);

	return local_status;
}

/* ============================================================================
 * Function Name: CANpal_get_Txd_Id
 * Description: Get ID of message just transmitted
 * Arguments:
 * Return:
 * ========================================================================= */
uint32_t CANpal_get_Txd_Id(void){
	uint32_t txd_msg_id;

	/* Since the same message buffer CAN_PAL_TX_BUFFER is used for ALL the
	 * nodes (DCM_DR, DCM_PS, DCM_RL, DCM_RR) this same function can be
	 * reused as it is for all the can_<NODEID>_HALgetTxdMsgId functions... */
	volatile uint32_t *flexcan_mb = \
			FLEXCAN_GetMsgBuffRegion(flexcanBase[FLEXCAN_INSTANCE], CAN_PAL_TX_BUFFER);
	volatile uint32_t *flexcan_mb_id   = &flexcan_mb[1];

	txd_msg_id = (*flexcan_mb_id >> CAN_ID_STD_SHIFT) \
			& (CAN_ID_STD_MASK >> CAN_ID_STD_SHIFT);

	return txd_msg_id;
}
