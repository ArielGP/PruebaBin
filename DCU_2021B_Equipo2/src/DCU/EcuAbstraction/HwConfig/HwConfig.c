/*
 * HwConfig.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */
#include "BasicTypes.h"
#include "HwConfig.h"
#include "Dio.h"

#include "sdk_project_config.h"

/*
SW Variant Configuration will be done through 2 configuration jumpers.
Depending on the state of the jumpers is the intended behavior of the DCU.
Jumper 0	Jumper 1	Variant Behavior
0	          0	        Driver Door
0	          1	        Passenger Door
1	          0	        RearLeft Door
1	          1	        RearRight Door
*/

//Variable de HwConfig
HW_CONFIG Hw_Config = HWCONFIG_UNKNOWN;

void HwConfig_Init(void)
{
	volatile uint8_t sw_variant_1_value, sw_variant_0_value;
	sw_variant_1_value = (PINS_DRV_ReadPins(SW_VARIANT_1_PORT) >> SW_VARIANT_1_PIN) & 1u;
	sw_variant_0_value = (PINS_DRV_ReadPins(SW_VARIANT_0_PORT) >> SW_VARIANT_0_PIN) & 1u;
	if(sw_variant_1_value == 0 && sw_variant_0_value == 0)
	{
		Hw_Config = HWCONFIG_DRIVER;
	}
	if(sw_variant_1_value == 1 && sw_variant_0_value == 0)
	{
		Hw_Config = HWCONFIG_PASSENGER;
	}
	if(sw_variant_1_value == 0 && sw_variant_0_value == 1)
	{
		Hw_Config = HWCONFIG_REAR_LEFT;
	}
	if(sw_variant_1_value == 0 && sw_variant_0_value == 1)
	{
		Hw_Config = HWCONFIG_REAR_RIGHT;
	}
}

HW_CONFIG HwConfig_Get(void)
{
	return Hw_Config;
}


boolean HwConfig_IsAny(HW_CONFIG config, HW_CONFIG config_mask)
{
	(void)config_mask;
	return FALSE;
}

