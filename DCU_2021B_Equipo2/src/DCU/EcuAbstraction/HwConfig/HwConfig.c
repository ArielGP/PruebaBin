/*
 * HwConfig.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */
#include "BasicTypes.h"
#include "HwConfig.h"
#include "Dio.h"

/*
SW Variant Configuration will be done through 2 configuration jumpers.
Depending on the state of the jumpers is the intended behavior of the DCU.
Jumper 0	Jumper 1	Variant Behavior
0	          0	        Driver Door
0	          1	        Passenger Door
1	          0	        RearLeft Door
1	          1	        RearRight Door
*/


HW_CONFIG HwConfig_Get(void)
{
	return HWCONFIG_UNKNOWN;
}


boolean HwConfig_IsAny(HW_CONFIG config, HW_CONFIG config_mask)
{
	(void)config_mask;
	return FALSE;
}
