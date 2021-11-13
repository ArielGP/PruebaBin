/*
 * DoorHandler.c
 *
 *  Created on: 2 ago. 2021
 *      Author: jose garibay
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

static uint8_t power_mode_previous1;
static uint8_t power_mode_current1;

static uint8_t power_mode_previous2;
static uint8_t power_mode_current2;

static void (*ptr_function)(void);



static void Remote_Operation(void) {

	uint8_t remote_request_driver;
	uint8_t remote_request_passenger;

	Signals_Get_LockingReq_Driver(&remote_request_driver);
	Signals_Get_LockingReq_Passenger(&remote_request_passenger);

	/*reads remote request from driver and passenger for lock */
	if ((remote_request_driver == LOCKINGREQ_LOCK)
			|| (remote_request_passenger == LOCKINGREQ_LOCK)) {
		if (DOOR_STATUS_LOCKED != Door_Get_Status()) {

			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}

	/*reads remote request from driver and passenger for unlock */
	else if ((remote_request_driver == LOCKINGREQ_UNLOCK)
			|| (remote_request_passenger == LOCKINGREQ_UNLOCK)) {

		if (DOOR_STATUS_UNLOCKED != Door_Get_Status()) {

			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}
	/*
	 else {
	 Door_Set_Request(DOOR_REQUEST_NONE);

	 CAN_status_report = DOOR_STATUS_UNKNOWN;
	 Signals_Set_DoorLockSts(&CAN_status_report);
	 }
	 */

}

//pasenger
static void Remote_Operation_rqst_driver(void) {

	uint8_t remote_request_driver;

	Signals_Get_LockingReq_Driver(&remote_request_driver);

	/*reads remote request from driver and passenger for lock */
	if (remote_request_driver == LOCKINGREQ_LOCK) {
		if (DOOR_STATUS_LOCKED != Door_Get_Status()) {

			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}

	/*reads remote request from driver and passenger for unlock */
	else if (remote_request_driver == LOCKINGREQ_UNLOCK) {

		if (DOOR_STATUS_UNLOCKED != Door_Get_Status()) {

			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}
	/*else {
	 Door_Set_Request(DOOR_REQUEST_NONE);

	 CAN_status_report = DOOR_STATUS_UNKNOWN;
	 Signals_Set_DoorLockSts(&CAN_status_report);
	 }
	 */

}

//pasenger
static void Remote_Operation_rqst_passenger(void) {

	uint8_t remote_request_passenger;

	Signals_Get_LockingReq_Passenger(&remote_request_passenger);

	/*reads remote request from driver and passenger for lock */
	if (remote_request_passenger == LOCKINGREQ_LOCK) {
		if (DOOR_STATUS_LOCKED != Door_Get_Status()) {

			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}

	/*reads remote request from driver and passenger for unlock */
	else if (remote_request_passenger == LOCKINGREQ_UNLOCK) {

		if (DOOR_STATUS_UNLOCKED != Door_Get_Status()) {

			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}
	/*
	 else {
	 Door_Set_Request(DOOR_REQUEST_NONE);

	 CAN_status_report = DOOR_STATUS_UNKNOWN;
	 Signals_Set_DoorLockSts(&CAN_status_report);
	 }
	 */

}

static void Autolock_driving(void) {
	uint8_t PS_door_lockstatus;
	uint8_t System_PwrMode;
	uint8_t vehicle_speed;

	/*reads doorlockstatus by CAN*/
	Signals_Get_Passenger_DoorLockSts(&PS_door_lockstatus);

	Signals_Get_SysPwrMode(&System_PwrMode);

	Signals_Get_VehSpeed(&vehicle_speed);

	if ((PS_door_lockstatus == LOCKINGREQ_UNLOCK)
			&& (vehicle_speed > autolock_speed_threshold)
			&& (System_PwrMode == SYSPWRMODE_RUN)) {
		/*check byte 2 del bcm for confort comd value*/

		if (DOOR_STATUS_LOCKED != Door_Get_Status()){


		Door_Set_Request(DOOR_REQUEST_LOCK);

		CAN_status_report = DOORLOCKSTS_LOCK;
		Signals_Set_DoorLockSts(&CAN_status_report);}
	}

	else
		(*ptr_function)();


}

//pasenger
static void Manual_Mode(void) {


	if (BUTTON_PRESSED == Button_Get_Door_Lock()) {

		loq_request = LOCKINGREQ_LOCK;
		Signals_Set_LockingReq(&loq_request);

		if (DOOR_STATUS_LOCKED != Door_Get_Status()) {

			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	} else if (BUTTON_PRESSED == Button_Get_Door_Unlock()) {
		loq_request = LOCKINGREQ_UNLOCK;
		Signals_Set_LockingReq(&loq_request);

		if (DOOR_STATUS_UNLOCKED != Door_Get_Status()) {
			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}

	else if ((BUTTON_PRESSED == Button_Get_Door_Unlock())
			&& (BUTTON_PRESSED == Button_Get_Door_Lock())) {
		Door_Set_Request(DOOR_REQUEST_NONE);
		loq_request = LOCKINGREQ_NO;
		Signals_Set_LockingReq(&loq_request);

	}

	else if (BUTTON_STUCK == Button_Get_Door_Unlock()) {
		Signals_Get_SysPwrMode(&power_mode_current1);
		if ((power_mode_current1 == SYSPWRMODE_RUN)
				&& (power_mode_previous1 == SYSPWRMODE_OFF)) {
			Button_Consume_Stuck(BUTTON_UNLOCK_BTN_IDX);
			power_mode_previous1 = SYSPWRMODE_SNA;
			power_mode_current1 = SYSPWRMODE_SNA;
		}

		else
			power_mode_previous1 = power_mode_current1;

	}

	else if (BUTTON_STUCK == Button_Get_Door_Lock()) {
		Signals_Get_SysPwrMode(&power_mode_current2);
		if ((power_mode_current2 == SYSPWRMODE_RUN)
				&& (power_mode_previous2 == SYSPWRMODE_OFF)) {
			Button_Consume_Stuck(BUTTON_LOCK_BTN_IDX);
			power_mode_previous2 = SYSPWRMODE_SNA;
			power_mode_current2 = SYSPWRMODE_SNA;
		}

		else
			power_mode_previous2 = power_mode_current2;

	}


	else {
		loq_request = LOCKINGREQ_NO;
		Signals_Set_LockingReq(&loq_request);
	}

}


static void Manual_Mode_Driver(void) {

	uint8_t PS_door_lockstatus;
		uint8_t System_PwrMode;
		uint8_t vehicle_speed;
		/*reads doorlockstatus by CAN*/
		Signals_Get_Passenger_DoorLockSts(&PS_door_lockstatus);

		Signals_Get_SysPwrMode(&System_PwrMode);

		Signals_Get_VehSpeed(&vehicle_speed);





	if (BUTTON_PRESSED == Button_Get_Door_Lock()) {

		loq_request = LOCKINGREQ_LOCK;
		Signals_Set_LockingReq(&loq_request);

		if (DOOR_STATUS_LOCKED != Door_Get_Status()) {

			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	} else if (BUTTON_PRESSED == Button_Get_Door_Unlock()) {
		loq_request = LOCKINGREQ_UNLOCK;
		Signals_Set_LockingReq(&loq_request);

		if (DOOR_STATUS_UNLOCKED != Door_Get_Status()) {
			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
		}
	}

	else if ((BUTTON_PRESSED == Button_Get_Door_Unlock())
			&& (BUTTON_PRESSED == Button_Get_Door_Lock())) {
		Door_Set_Request(DOOR_REQUEST_NONE);
		loq_request = LOCKINGREQ_NO;
		Signals_Set_LockingReq(&loq_request);

	}

	else if (BUTTON_STUCK == Button_Get_Door_Unlock()) {
		Signals_Get_SysPwrMode(&power_mode_current1);
		if ((power_mode_current1 == SYSPWRMODE_RUN)
				&& (power_mode_previous1 == SYSPWRMODE_OFF)) {
			Button_Consume_Stuck(BUTTON_UNLOCK_BTN_IDX);
			power_mode_previous1 = SYSPWRMODE_SNA;
			power_mode_current1 = SYSPWRMODE_SNA;
		}

		else
			power_mode_previous1 = power_mode_current1;

	}

	else if (BUTTON_STUCK == Button_Get_Door_Lock()) {
		Signals_Get_SysPwrMode(&power_mode_current2);
		if ((power_mode_current2 == SYSPWRMODE_RUN)
				&& (power_mode_previous2 == SYSPWRMODE_OFF)) {
			Button_Consume_Stuck(BUTTON_LOCK_BTN_IDX);
			power_mode_previous2 = SYSPWRMODE_SNA;
			power_mode_current2 = SYSPWRMODE_SNA;
		}

		else
			power_mode_previous2 = power_mode_current2;

	}


	else if((PS_door_lockstatus == LOCKINGREQ_UNLOCK)
			&& (vehicle_speed > autolock_speed_threshold)
			&& (System_PwrMode == SYSPWRMODE_RUN))
	{
				/*check byte 2 del bcm for confort comd value*/

				if (DOOR_STATUS_LOCKED != Door_Get_Status()){


				Door_Set_Request(DOOR_REQUEST_LOCK);

				CAN_status_report = DOORLOCKSTS_LOCK;
				Signals_Set_DoorLockSts(&CAN_status_report);
				PS_door_lockstatus = LOCKINGREQ_NO;
				}
	}


	else {
		loq_request = LOCKINGREQ_NO;
		Signals_Set_LockingReq(&loq_request);
	}

}
void DoorApp_Init(void) {
	doorunlock_btn_status = BUTTON_NOT_PRESSED;
	doorlock_btn_status = BUTTON_NOT_PRESSED;

	door_status = DOOR_STATUS_UNKNOWN;

	door_request = DOOR_REQUEST_NONE;

	loq_request = LOCKINGREQ_NO;

	confort_cmd = CONFORTCMD_NO;

	ptr_function = &Manual_Mode;
}

//50 ms
void DoorApp_Run(void) {
	switch (HwConfig_Get()) {
	case HWCONFIG_DRIVER: {
		Signals_Get_ConfortCmd(&confort_cmd); //MODIFICACION PARA CONFORR

		if (confort_cmd == CONFORTCMD_LOCK) {



			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);

			confort_cmd = CONFORTCMD_NO;



		} else if (confort_cmd == CONFORTCMD_UNLOCK_ALL)

		{
			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
			confort_cmd = CONFORTCMD_NO;
		}

		else if (confort_cmd == CONFORTCMD_UNLOCK_DRIVER) {



			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
			confort_cmd = CONFORTCMD_NO;

			//(*ptr_function)();              //apuntador a funcion manual mode





		}

		else {

			//Autolock_driving();

			Remote_Operation_rqst_passenger();

			Manual_Mode_Driver();

		}

	}
		break;
	case HWCONFIG_PASSENGER: {
		Signals_Get_ConfortCmd(&confort_cmd);

		if (confort_cmd == CONFORTCMD_LOCK) {
			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);

			confort_cmd = CONFORTCMD_NO;

		} else if (confort_cmd == CONFORTCMD_UNLOCK_DRIVER)

			confort_cmd = CONFORTCMD_NO;

		else if (confort_cmd == CONFORTCMD_UNLOCK_ALL) {
			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
			confort_cmd = CONFORTCMD_NO;

		}

		else {

			Remote_Operation_rqst_driver();

			Manual_Mode();

		}

	}
		break;
	case HWCONFIG_REAR_LEFT: {
		Signals_Get_ConfortCmd(&confort_cmd);

		if (confort_cmd == CONFORTCMD_LOCK) {
			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);

			confort_cmd = CONFORTCMD_NO;

		} else if (confort_cmd == CONFORTCMD_UNLOCK_DRIVER)

			confort_cmd = CONFORTCMD_NO;

		else if (confort_cmd == CONFORTCMD_UNLOCK_ALL) {
			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
			confort_cmd = CONFORTCMD_NO;

		} else
			Remote_Operation();

	}
		break;
	case HWCONFIG_REAR_RIGHT: {
		Signals_Get_ConfortCmd(&confort_cmd);

		if (confort_cmd == CONFORTCMD_LOCK) {
			Door_Set_Request(DOOR_REQUEST_LOCK);

			CAN_status_report = DOORLOCKSTS_LOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);

			confort_cmd = CONFORTCMD_NO;

		} else if (confort_cmd == CONFORTCMD_UNLOCK_ALL) {
			Door_Set_Request(DOOR_REQUEST_UNLOCK);

			CAN_status_report = DOORLOCKSTS_UNLOCK;
			Signals_Set_DoorLockSts(&CAN_status_report);
			confort_cmd = CONFORTCMD_NO;

		}

		else if (confort_cmd == CONFORTCMD_UNLOCK_DRIVER) {

			confort_cmd = CONFORTCMD_NO;
		}

		else
			Remote_Operation();

	}
		break;
	default: {
		/* Avoid Misra - No action required */
	}
		break;
	}

}

