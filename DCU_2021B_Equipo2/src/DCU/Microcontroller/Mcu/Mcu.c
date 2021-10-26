/*
 * Mcu.c
 *
 *  Created on: 3 ago. 2021
 *      Author: uid87544
 */

#include "BasicTypes.h"
#include "Mcu.h"
#include "sdk_project_config.h"

void Mcu_Init(void)
{
    (void) CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    (void) CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
}

