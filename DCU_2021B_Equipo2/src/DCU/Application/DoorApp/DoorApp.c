/*
 * DoorHandler.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */
#include "BasicTypes.h"
#include "DoorApp.h"
#include "Signals.h"
#include "Button.h"
#include "Door.h"
#include "HwConfig.h"


static BUTTON_STATUS doorunlock_btn_status;
static BUTTON_STATUS doorlock_btn_status;

static DOOR_STATUS door_status;

static DOOR_REQUEST door_request;

const uint8_t autolock_speed_threshold = 20;

static uint8_t loq_request;

static uint8_t CAN_status_report;

static uint8_t confort_cmd;


static void Remote_Operation(void)
{

	uint8_t remote_request_driver;
	uint8_t remote_request_passenger;

	Signals_Get_LockingReq_Driver(&remote_request_driver);
	Signals_Get_LockingReq_Passenger(&remote_request_passenger);

	/*reads remote request from driver and passenger for lock */
	if((remote_request_driver == LOCKINGREQ_LOCK) || (remote_request_passenger == LOCKINGREQ_LOCK))
	{
		if (DOOR_STATUS_LOCKED != Door_Get_Status())
		{

			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}


	/*reads remote request from driver and passenger for unlock */
	else if((remote_request_driver == LOCKINGREQ_UNLOCK) || (remote_request_passenger == LOCKINGREQ_UNLOCK))
	{

		if (DOOR_STATUS_UNLOCKED != Door_Get_Status())
		{

			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}
	else
	{
		Door_Set_Request(DOOR_REQUEST_NONE);

		CAN_status_report = DOOR_STATUS_UNKNOWN;
		Signals_Set_DoorLockSts(&CAN_status_report);
	}

}

static void Autolock_driving(void)
{


	uint8_t PS_door_lockstatus;
	uint8_t System_PwrMode;
	uint8_t vehicle_speed;

	/*reads doorlockstatus by CAN*/
	Signals_Get_Passenger_DoorLockSts(&PS_door_lockstatus);
	//Signals_Get_RearLeft_DoorLockSts(&RL_door_lockstatus);
	//Signals_Get_RearRight_DoorLockSts(&RR_door_lockstatus);

	Signals_Get_SysPwrMode(&System_PwrMode);

	Signals_Get_VehSpeed(&vehicle_speed);

	/*
	if((( door_status || PS_door_lockstatus || RL_door_lockstatus || RR_door_lockstatus) == DOOR_STATUS_UNLOCKED) &&
			((System_PwrMode == SYSPWRMODE_RUN) && (vehicle_speed >=autolock_speed_threshold)))

	 */
	if(PS_door_lockstatus == LOCKINGREQ_UNLOCK)
	{
		/*check byte 2 del bcm for confort comd value*/

		Door_Set_Request(DOOR_REQUEST_LOCK);

		loq_request = LOCKINGREQ_LOCK;
		Signals_Set_LockingReq(&loq_request);
		/*
		if((Signals_Get_ConfortCmd(&confort_cmd))==(CONFORTCMD_UNLOCK_DRIVER || CONFORTCMD_UNLOCK_ALL))
		{
			Door_Set_Request(DOOR_REQUEST_UNLOCK);
			door_status = CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);

		}

		*/

	}

}

//pasenger,driver
static void Manual_Mode(void)
{

	if (BUTTON_PRESSED == Button_Get_Door_Lock())
	{

		loq_request =LOCKINGREQ_LOCK;
		Signals_Set_LockingReq(&loq_request);



		if (DOOR_STATUS_LOCKED != Door_Get_Status())
		{

			Door_Set_Request(DOOR_REQUEST_LOCK);



			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}
	else if (BUTTON_PRESSED == Button_Get_Door_Unlock())
	{
		loq_request = LOCKINGREQ_UNLOCK;
		Signals_Set_LockingReq(&loq_request);

		if (DOOR_STATUS_UNLOCKED != Door_Get_Status())
		{
			Door_Set_Request(DOOR_REQUEST_UNLOCK);



			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}

	else if ((BUTTON_PRESSED == Button_Get_Door_Unlock()) && (BUTTON_PRESSED == Button_Get_Door_Lock()))
	{
		Door_Set_Request(DOOR_REQUEST_NONE);
		loq_request = LOCKINGREQ_NO;
		Signals_Set_LockingReq(&loq_request);

	}

	else{
		loq_request =LOCKINGREQ_NO;
		Signals_Set_LockingReq(&loq_request);
	}


}


void DoorApp_Init(void)
{
	doorunlock_btn_status = BUTTON_NOT_PRESSED;
	doorlock_btn_status = BUTTON_NOT_PRESSED;

	door_status = DOOR_STATUS_UNKNOWN;

	door_request = DOOR_REQUEST_NONE;

	loq_request = LOCKINGREQ_NO;

	confort_cmd = CONFORTCMD_NO;

}

//50 ms
void DoorApp_Run(void)
{
	switch (HwConfig_Get())
	{
	case HWCONFIG_DRIVER:
	{
		Signals_Get_ConfortCmd(&confort_cmd);


			if(confort_cmd == CONFORTCMD_LOCK)
			{
				Door_Set_Request(DOOR_REQUEST_LOCK);

			    CAN_status_report = DOORLOCKSTS_LOCK;
				Signals_Set_DoorLockSts(&CAN_status_report);

				confort_cmd = CONFORTCMD_NO;

			}
			else if(confort_cmd == CONFORTCMD_UNLOCK_ALL)

				confort_cmd = CONFORTCMD_NO;




		  else if(confort_cmd == CONFORTCMD_UNLOCK_DRIVER)
		  {
				Door_Set_Request(DOOR_REQUEST_UNLOCK);

			    CAN_status_report = DOORLOCKSTS_UNLOCK;
				Signals_Set_DoorLockSts(&CAN_status_report);
				confort_cmd = CONFORTCMD_NO;

	       }


			else if(confort_cmd == CONFORTCMD_NO)
			{
		        Autolock_driving();

		          Manual_Mode();
		  }




	}break;
	case HWCONFIG_PASSENGER:
	{
		Manual_Mode();


	}break;
	case HWCONFIG_REAR_LEFT:
	{
		Remote_Operation();

	}break;
	case HWCONFIG_REAR_RIGHT:
	{

		Remote_Operation();

	}break;
	default:
	{
		/* Avoid Misra - No action required */
	}break;
	}


}

