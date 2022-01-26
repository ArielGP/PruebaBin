/*
 * Wdg.c
 *
 *  Created on: 10 ago. 2021
 *      Author: uid87544
 */

#include "BasicTypes.h"
#include "Wdg.h"
#include "wdog_driver.h"
#include "peripherals_wdog_config_1.h"


void Wdg_Init(void)
{
	WDOG_DRV_Init(WDOG_CONFIG_1_INST,&WDOG_Cfg0);
}

void Wdg_Feed(uint8 check_point)
{
    (void)check_point;

    WDOG_DRV_Trigger(WDOG_CONFIG_1_INST);
}
