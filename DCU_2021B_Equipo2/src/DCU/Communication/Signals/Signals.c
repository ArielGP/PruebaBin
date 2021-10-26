/*
 * Signals.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#include "sdk_project_config.h"

#include "BasicTypes.h"
#include "HwConfig.h"
#include "Signals.h"
#include "CANpal.h"



void Signals_Init(void)
{
	/* ----------------------- */
	/* Init CAN driver and PAL */
	/* ----------------------- */
	CANpal_init();

	/* ---------------------- */
	/* Init interaction layer */
	/* ---------------------- */

}

//10 ms
void Signals_RunTx(void)
{

	uint8_t test_msg[5]={
			0x01,
			0x02,
			0x03,
			0x04,
			0x05
	};


	CANpal_send_CAN_message(0x02,5,test_msg);


}


//20 ms
void Signals_RunRx(void)
{
	/* Call CAN RX timeout process function */
}


/* --------------------------- */
/* Get timeout flags functions */
/* --------------------------- */
boolean Signals_Get_Timeout_BCM_5()
{
	return TRUE;
}

boolean Signals_Get_Timeout_BCM_2()
{
	return TRUE;
}

boolean Signals_Get_Timeout_BRAKE_2()
{
	return TRUE;
}

boolean Signals_Get_Timeout_TRANSM_2()
{
	return TRUE;
}

boolean Signals_Get_Timeout_TRANSM_4()
{
	return TRUE;
}


/* -------------------- */
/* Get signal functions */
/* -------------------- */

t_BCM_5_MC Signals_Get_BCM_5_MC()
{
	t_BCM_5_MC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_SysPwrMode Signals_Get_SysPwrMode()
{
	t_SysPwrMode value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_BCM_5_CMAC Signals_Get_BCM_5_CMAC()
{
	t_BCM_5_CMAC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_BCM_2_MC Signals_Get_BCM_2_MC()
{
	t_BCM_2_MC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_ConfortCmd Signals_Get_ConfortCmd()
{
	t_ConfortCmd value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_BCM_2_CMAC Signals_Get_BCM_2_CMAC()
{
	t_BCM_2_CMAC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_VehSpeed Signals_Get_VehSpeed()
{
	t_VehSpeed value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_BRAKE_2_MC Signals_Get_BRAKE_2_MC()
{
	t_BRAKE_2_MC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_BRAKE_2_CRC Signals_Get_BRAKE_2_CRC()
{
	t_BRAKE_2_CRC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_ShiftLeverPos Signals_Get_ShiftLeverPos()
{
	t_ShiftLeverPos value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_TRANSM_2_MC Signals_Get_TRANSM_2_MC()
{
	t_TRANSM_2_MC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_TRANSM_2_CRC Signals_Get_TRANSM_2_CRC()
{
	t_TRANSM_2_CRC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_ShiftLeverEng Signals_Get_ShiftLeverEng()
{
	t_ShiftLeverEng value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_TRANSM_4_MC Signals_Get_TRANSM_4_MC()
{
	t_TRANSM_4_MC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

t_TRANSM_4_CRC Signals_Get_TRANSM_4_CRC()
{
	t_TRANSM_4_CRC value;
	CALVOS_CRITICAL_ENTER();
	/* Place code to access signal from buffer */
	CALVOS_CRITICAL_EXIT();

 	return value;
}

/* -------------------- */
/* Set signal functions */
/* -------------------- */

void Signals_Set_DCU_1_WindowPos(t_WindowPos value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_LockingReq(t_LockingReq value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_WindowOp(t_WindowOp value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_RearWindowLock(t_RearWindowLock value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_DoorLockSts(t_DoorLockSts value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_WdwCtrl_RR(t_WindowControl value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_WdwCtrl_RL(t_WindowControl value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_WdwCtrl_Pas(t_WindowControl value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_MC(t_DCU_1_MC value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_1_CRC(t_DCU_1_CRC value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_2_WindowPos(t_WindowPos value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_2_LockingReq(t_LockingReq value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_2_WindowOp(t_WindowOp value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_2_DoorLockSts(t_DoorLockSts value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_2_MC(t_DCU_2_MC value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_2_CRC(t_DCU_2_CRC value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_3_WindowPos(t_WindowPos value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_3_WindowOp(t_WindowOp value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_3_DoorLockSts(t_DoorLockSts value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_3_MC(t_DCU_3_MC value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_3_CRC(t_DCU_3_CRC value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_4_WindowPos(t_WindowPos value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_4_WindowOp(t_WindowOp value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_4_DoorLockSts(t_DoorLockSts value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_4_MC(t_DCU_4_MC value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}

void Signals_Set_DCU_4_CRC(t_DCU_4_CRC value)
{
	CALVOS_CRITICAL_ENTER();
	/* Place code to write value to buffer */
	(void) value;
	CALVOS_CRITICAL_EXIT();
}


