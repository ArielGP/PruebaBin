/*============================================================================*/
/*                           calvOS Project                                   */
/*============================================================================*/
/** \file		USER_comgen_CAN_DCM_DR_callbacks.h                            */
/** \brief     	Header file for CAN callbacks.
 *  \details   	Contains declarations of CAN callback functions.
 *  \author    	Carlos Calvillo
 *  \version   	1.0
 *  \date      	2020-11-15
 *  \copyright 	2020 Carlos Calvillo.
 */
/*============================================================================*/
/*  This file is part of calvOS project <https://github.com/calcore-io/calvos>.
 *
 *  calvOS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  calvOS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with calvOS.  If not, see <https://www.gnu.org/licenses/>. */
/*============================================================================*/
/*-----------------------------------------------------------------------------
 * This file was generated on (yyyy.mm.dd::hh:mm:ss): 2021.10.31::12:48:32
 * Generated from following source(s):
 *     Network file: "/home/efren/Documents/2_Courses/2_CUCEI/2_Diplomado_Conti/..
                      0_Git/Equipo2/DCU_2021B_Equipo2/src/DCU/Communication/..
                      Calvos/Calvos_GenData/usr_in/..
                      template - CAN Network Definition.ods"
 *     Network name: "CAN-B"
 *     Network id: "B"
 *     Network date: "12/Mar/2021"
 *     Network version: "2"
 -----------------------------------------------------------------------------*/
#ifndef USER_COMGEN_CAN_DCM_DR_CALLBACKS_H
#define USER_COMGEN_CAN_DCM_DR_CALLBACKS_H

#include "calvos.h"
#include "comgen_CAN_common.h"
#include "comgen_CAN_DCM_DR_node_network.h"


/* --------------------------- */
/* Message reception callbacks */
/* --------------------------- */
extern void can_DCM_DR_BCM_5_rx_callback(void);
extern void can_DCM_DR_BCM_2_rx_callback(void);
extern void can_DCM_DR_BRAKE_2_rx_callback(void);
extern void can_DCM_DR_TRANSM_2_rx_callback(void);
extern void can_DCM_DR_TRANSM_4_rx_callback(void);
extern void can_DCM_DR_DCU_2_rx_callback(void);

/* ------------------------- */
/* Message timeout callbacks */
/* ------------------------- */
extern void can_DCM_DR_BCM_5_timeout_callback(void);
extern void can_DCM_DR_BCM_2_timeout_callback(void);
extern void can_DCM_DR_BRAKE_2_timeout_callback(void);
extern void can_DCM_DR_TRANSM_2_timeout_callback(void);
extern void can_DCM_DR_TRANSM_4_timeout_callback(void);
extern void can_DCM_DR_DCU_2_timeout_callback(void);

/* ------------------------------ */
/* Message transmission callbacks */
/* ------------------------------ */
extern void can_DCM_DR_DCU_1_tx_callback(void);


#endif /* USER_COMGEN_CAN_DCM_DR_CALLBACKS_H */
