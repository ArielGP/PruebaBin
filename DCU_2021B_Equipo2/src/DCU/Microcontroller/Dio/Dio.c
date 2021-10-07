/*
 * Dio.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#include "BasicTypes.h"
#include "Dio.h"

#include "sdk_project_config.h"


void Dio_Init(void)
{

	/* Init IO HAL */
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0,g_pin_mux_InitConfigArr0);
}


void Dio_Write_DoorUnlock_Led(PIN_VALUE value)
{

}

void Dio_Write_DoorLock_Led(PIN_VALUE value)
{

}

PIN_VALUE Dio_Read_DoorUnlock(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_DoorLock(void)
{
	return DIO_LOW;
}


void Dio_Write_Window_Leds(PIN_VALUES values)
{

}



PIN_VALUE Dio_Read_Window_Open(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_Window_Closed(void)
{
	return DIO_LOW;
}


PIN_VALUE Dio_Read_DoorLock_Button(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_DoorUnlock_Button(void)
{
	return DIO_LOW;
}


PIN_VALUE Dio_Read_WindowOpen_Button(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_WindowClose_Button(void)
{
	return DIO_LOW;
}



PIN_VALUE Dio_Read_PassengerWindowOpen_Button(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_PassengerWindowClose_Button(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_RearLeftWindowOpen_Button(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_RearLeftWindowClose_Button(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_RearRightWindowOpen_Button(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_RearRightWindowClose_Button(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_RearWindowLock_Button(void)
{
	return DIO_LOW;
}


PIN_VALUE Dio_Read_Jumper0(void)
{
	return DIO_LOW;
}

PIN_VALUE Dio_Read_Jumper1(void)
{
	return DIO_LOW;
}


