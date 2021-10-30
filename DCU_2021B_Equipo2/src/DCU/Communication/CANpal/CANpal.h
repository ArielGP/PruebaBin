/*
 * CAN_pal.h
 *
 *  Created on: Oct 6, 2021
 *      Author: Carlos Calvillo
 */
#ifndef DCU_COMMUNICATION_CAN_PAL_CAN_PAL_H_
#define DCU_COMMUNICATION_CAN_PAL_CAN_PAL_H_

#include "sdk_project_config.h"

extern void CANpal_init(void);
extern status_t CANpal_send_CAN_message(uint32_t msg_id, uint8_t length, uint8_t * data);
extern uint32_t CANpal_get_Txd_Id(void);

#endif /* DCU_COMMUNICATION_CAN_PAL_CAN_PAL_H_ */
