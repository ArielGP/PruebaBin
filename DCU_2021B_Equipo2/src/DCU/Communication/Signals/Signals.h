/*
 * Signals.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef ECUABSTRACTION_SIGNALS_H_
#define ECUABSTRACTION_SIGNALS_H_

#include "comgen_CAN_network.h"

extern void Signals_Init(void);

//10 ms
extern void Signals_RunTx(void);


//20 ms
extern void Signals_RunRx(void);


/* --------------------------- */
/* Get timeout flags functions */
/* --------------------------- */
extern boolean Signals_Get_Timeout_BCM_5();
extern boolean Signals_Get_Timeout_BCM_2();
extern boolean Signals_Get_Timeout_BRAKE_2();
extern boolean Signals_Get_Timeout_TRANSM_2();
extern boolean Signals_Get_Timeout_TRANSM_4();

/* CAN Interaction Functions */
extern t_BCM_5_MC Signals_Get_BCM_5_MC();
extern t_SysPwrMode Signals_Get_SysPwrMode();
extern t_BCM_5_CMAC Signals_Get_BCM_5_CMAC();
extern t_BCM_2_MC Signals_Get_BCM_2_MC();
extern t_ConfortCmd Signals_Get_ConfortCmd();
extern t_BCM_2_CMAC Signals_Get_BCM_2_CMAC();
extern t_VehSpeed Signals_Get_VehSpeed();
extern t_BRAKE_2_MC Signals_Get_BRAKE_2_MC();
extern t_BRAKE_2_CRC Signals_Get_BRAKE_2_CRC();
extern t_ShiftLeverPos Signals_Get_ShiftLeverPos();
extern t_TRANSM_2_MC Signals_Get_TRANSM_2_MC();
extern t_TRANSM_2_CRC Signals_Get_TRANSM_2_CRC();
extern t_ShiftLeverEng Signals_Get_ShiftLeverEng();
extern t_TRANSM_4_MC Signals_Get_TRANSM_4_MC();
extern t_TRANSM_4_CRC Signals_Get_TRANSM_4_CRC();

extern void Signals_Set_DCU_1_WindowPos(t_WindowPos value);
extern void Signals_Set_DCU_1_LockingReq(t_LockingReq value);
extern void Signals_Set_DCU_1_WindowOp(t_WindowOp value);
extern void Signals_Set_DCU_1_RearWindowLock(t_RearWindowLock value);
extern void Signals_Set_DCU_1_DoorLockSts(t_DoorLockSts value);
extern void Signals_Set_DCU_1_WdwCtrl_RR(t_WindowControl value);
extern void Signals_Set_DCU_1_WdwCtrl_RL(t_WindowControl value);
extern void Signals_Set_DCU_1_WdwCtrl_Pas(t_WindowControl value);
extern void Signals_Set_DCU_1_MC(t_DCU_1_MC value);
extern void Signals_Set_DCU_1_CRC(t_DCU_1_CRC value);
extern void Signals_Set_DCU_2_WindowPos(t_WindowPos value);
extern void Signals_Set_DCU_2_LockingReq(t_LockingReq value);
extern void Signals_Set_DCU_2_WindowOp(t_WindowOp value);
extern void Signals_Set_DCU_2_DoorLockSts(t_DoorLockSts value);
extern void Signals_Set_DCU_2_MC(t_DCU_2_MC value);
extern void Signals_Set_DCU_2_CRC(t_DCU_2_CRC value);
extern void Signals_Set_DCU_3_WindowPos(t_WindowPos value);
extern void Signals_Set_DCU_3_WindowOp(t_WindowOp value);
extern void Signals_Set_DCU_3_DoorLockSts(t_DoorLockSts value);
extern void Signals_Set_DCU_3_MC(t_DCU_3_MC value);
extern void Signals_Set_DCU_3_CRC(t_DCU_3_CRC value);
extern void Signals_Set_DCU_4_WindowPos(t_WindowPos value);
extern void Signals_Set_DCU_4_WindowOp(t_WindowOp value);
extern void Signals_Set_DCU_4_DoorLockSts(t_DoorLockSts value);
extern void Signals_Set_DCU_4_MC(t_DCU_4_MC value);
extern void Signals_Set_DCU_4_CRC(t_DCU_4_CRC value);

#endif /* ECUABSTRACTION_SIGNALS_H_ */
