/*
 * Signals.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef ECUABSTRACTION_SIGNALS_H_
#define ECUABSTRACTION_SIGNALS_H_

#include "..\Calvos\comgen_CAN_network.h"

extern void Signals_Init(void);

//10 ms
extern void Signals_RunTx(void);

//20 ms
extern void Signals_RunRx(void);

typedef uint8 SIGNAL_ERROR;

#define SIGNAL_ERROR_NO                ((SIGNAL_ERROR)0)
#define SIGNAL_ERROR_NEVER_RECEIVED    ((SIGNAL_ERROR)1)
#define SIGNAL_ERROR_TIMEOUT           ((SIGNAL_ERROR)2)
#define SIGNAL_ERROR_ERROR             ((SIGNAL_ERROR)3)


#define SYSPWRMODE_SNA    ((uint8)0)
#define SYSPWRMODE_OFF    ((uint8)1)
#define SYSPWRMODE_ACC    ((uint8)2)
#define SYSPWRMODE_RUN    ((uint8)3)
#define SYSPWRMODE_CRANK  ((uint8)4)

//500 ms
SIGNAL_ERROR Signals_Get_SysPwrMode(uint8 * value);



#define CONFORTCMD_NO            ((uint8)0)
#define CONFORTCMD_LOCK          ((uint8)1)
#define CONFORTCMD_UNLOCK_ALL    ((uint8)2)
#define CONFORTCMD_UNLOCK_DRIVER ((uint8)3)

//500 ms
SIGNAL_ERROR Signals_Get_ConfortCmd(uint8 * value);

#define VEHSPEED_MIN            ((uint16)0)
#define VEHSPEED_MAX            ((uint16)1023)


//100 ms 0.25 kph/bit
SIGNAL_ERROR Signals_Get_VehSpeed(uint8 * value);

#define SHIFTLEVERPOS_PARK       ((uint8)0)
#define SHIFTLEVERPOS_DRIVE_1    ((uint8)1)
#define SHIFTLEVERPOS_DRIVE_2    ((uint8)2)
#define SHIFTLEVERPOS_DRIVE_3    ((uint8)3)
#define SHIFTLEVERPOS_NEUTRAL    ((uint8)4)
#define SHIFTLEVERPOS_MANUAL     ((uint8)5)
#define SHIFTLEVERPOS_REVERSE    ((uint8)6)
#define SHIFTLEVERPOS_SNA        ((uint8)7)


//20 ms
SIGNAL_ERROR Signals_Get_ShiftLeverPos(uint8 * value);



#define SHIFTLEVERENG_NOT_ENGAGED   ((uint8)0)
#define SHIFTLEVERENG_ENGAGED       ((uint8)1)

SIGNAL_ERROR Signals_Get_ShiftLeverEng(uint8* value);



#define WINDOWPOS_IN_BETWEEN         ((uint8)0)
#define WINDOWPOS_COMPLETELY_OPEN    ((uint8)1)
#define WINDOWPOS_COMPLETELY_CLOSE   ((uint8)2)
#define WINDOWPOS_ERROR              ((uint8)3)


//100 ms driver, passenger, rear
void Signals_Set_WindowPos(const uint8 *value);


#define LOCKINGREQ_NO        ((uint8)0)
#define LOCKINGREQ_LOCK      ((uint8)1)
#define LOCKINGREQ_UNLOCK    ((uint8)2)

//100 ms, driver, passenger
void Signals_Set_LockingReq(const uint8 *value);

//100 ms passenger, rear
SIGNAL_ERROR Signals_Get_LockingReq_Driver(uint8 * value);
//100 ms rear
SIGNAL_ERROR Signals_Get_LockingReq_Passenger(uint8 * value);


#define WINDOWOP_IDLE    ((uint8)0)
#define WINDOWOP_UP      ((uint8)1)
#define WINDOWOP_DOWN    ((uint8)2)


//100 ms, driver, passenger, rear
void Signals_Set_WindowOp(const uint8 *value);


#define REARWINDOWLOCK_UNBLOCK   ((uint8)0)
#define REARWINDOWLOCK_BLOCK     ((uint8)1)


//100 ms, driver
void Signals_Set_RearWindowLock(const uint8 *value);

SIGNAL_ERROR Signals_Get_RearWindowLock(uint8 *value);


#define DOORLOCKSTS_LOCK        ((uint8)0)
#define DOORLOCKSTS_UNLOCK      ((uint8)1)
#define DOORLOCKSTS_UNKNOWN     ((uint8)2)
#define DOORLOCKSTS_ERROR       ((uint8)3)


//100 ms driver, passenger, rear
void Signals_Set_DoorLockSts(const uint8 *value);

//100 ms driver
SIGNAL_ERROR Signals_Get_Passenger_DoorLockSts(uint8 * value);
SIGNAL_ERROR Signals_Get_RearLeft_DoorLockSts(uint8 * value);
SIGNAL_ERROR Signals_Get_RearRight_DoorLockSts(uint8 * value);


#define WINDOWCONTROL_NO_REQ    ((uint8)0)
#define WINDOWCONTROL_UP_REQ    ((uint8)1)
#define WINDOWCONTROL_DOWN_REQ  ((uint8)2)


//100 ms driver
void Signals_Set_WindowControl_Passenger(const uint8 *value);
void Signals_Set_WindowControl_RearLeft(const uint8 *value);
void Signals_Set_WindowControl_RearRight(const uint8 *value);

//100 ms passenger
SIGNAL_ERROR Signals_Get_WindowControl_Passenger(uint8 *value);

//100 ms rear left
SIGNAL_ERROR Signals_Get_WindowControl_RearLeft(uint8 *value);

//100 ms rear right
SIGNAL_ERROR Signals_Get_WindowControl_RearRight(uint8 *value);


#endif /* ECUABSTRACTION_SIGNALS_H_ */
