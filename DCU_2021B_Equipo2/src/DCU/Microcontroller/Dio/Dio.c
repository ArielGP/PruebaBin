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
	PINS_DRV_WritePin(DOOR_UNLOCKED_PORT, DOOR_UNLOCKED_PIN, (uint8_t) value);
}

void Dio_Write_DoorLock_Led(PIN_VALUE value)
{
	PINS_DRV_WritePin(DOOR_LOCKED_PORT, DOOR_LOCKED_PIN, (uint8_t) value);
}

PIN_VALUE Dio_Read_DoorUnlock(void)
{
	//PIN_VALUE drUnlockSts = PINS_DRV_ReadPins(SW_DOOR_UNLOCKED_PORT) >> (31 - SW_DOOR_UNLOCKED_PIN);
	PIN_VALUE drUnlockSts = (PINS_DRV_ReadPins(SW_DOOR_UNLOCKED_PORT) & 0x00000001) >> SW_DOOR_UNLOCKED_PIN;
	return drUnlockSts;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_DoorLock(void)
{
	PIN_VALUE drlockSts = (PINS_DRV_ReadPins(SW_DOOR_LOCKED_PORT) & 0x00000004) >> SW_DOOR_LOCKED_PIN;
	return drlockSts;
	//return DIO_LOW;
}


void Dio_Write_Window_Leds(PIN_VALUES values)
{
	values = values << 1;
	PINS_DRV_WritePin(WINDOW_LED1_PORT, WINDOW_LED1_PIN,  (values & DIO_WINDOW_LED1) >> 1);
	PINS_DRV_WritePin(WINDOW_LED2_PORT, WINDOW_LED2_PIN,  (values & DIO_WINDOW_LED2) >> 2);
	PINS_DRV_WritePin(WINDOW_LED3_PORT, WINDOW_LED3_PIN,  (values & DIO_WINDOW_LED3) >> 3);
	PINS_DRV_WritePin(WINDOW_LED4_PORT, WINDOW_LED4_PIN,  (values & DIO_WINDOW_LED4) >> 4);
	PINS_DRV_WritePin(WINDOW_LED5_PORT, WINDOW_LED5_PIN,  (values & DIO_WINDOW_LED5) >> 5);
	PINS_DRV_WritePin(WINDOW_LED6_PORT, WINDOW_LED6_PIN,  (values & DIO_WINDOW_LED6) >> 6);
	PINS_DRV_WritePin(WINDOW_LED7_PORT, WINDOW_LED7_PIN,  (values & DIO_WINDOW_LED7) >> 7);
	PINS_DRV_WritePin(WINDOW_LED8_PORT, WINDOW_LED8_PIN,  (values & DIO_WINDOW_LED8) >> 8);
	PINS_DRV_WritePin(WINDOW_LED9_PORT, WINDOW_LED9_PIN,  (values & DIO_WINDOW_LED9) >> 9);
	PINS_DRV_WritePin(WINDOW_LED10_PORT, WINDOW_LED10_PIN, (values & DIO_WINDOW_LED10) >> 10);
}



PIN_VALUE Dio_Read_Window_Open(void)
{
	//PIN_VALUE readWinOpen = PINS_DRV_ReadPins(SW_WINDOW_OPEN_PORT) >> (31 - SW_WINDOW_OPEN_PIN);
	PIN_VALUE readWinOpen = (PINS_DRV_ReadPins(SW_WINDOW_OPEN_PORT) & 0x00000040) >> (SW_WINDOW_OPEN_PIN);
	return readWinOpen;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_Window_Closed(void)
{
	//PIN_VALUE readWinClose = PINS_DRV_ReadPins(SW_WINDOW_CLOSE_PORT) >> (31 - SW_WINDOW_CLOSE_PIN);
	PIN_VALUE readWinClose = (PINS_DRV_ReadPins(SW_WINDOW_CLOSE_PORT) & 0x00000080) >> (SW_WINDOW_CLOSE_PIN);
	return readWinClose;
	//return DIO_LOW;
}


PIN_VALUE Dio_Read_DoorLock_Button(void)
{
	//PIN_VALUE drlockBtn = PINS_DRV_ReadPins(LOCK_BTN_PORT) >> (31 - LOCK_BTN_PIN);
	PIN_VALUE drlockBtn = (PINS_DRV_ReadPins(LOCK_BTN_PORT) & 0x00000800) >> (LOCK_BTN_PIN);
	return drlockBtn;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_DoorUnlock_Button(void)
{
	//PIN_VALUE drUnlockBtn = PINS_DRV_ReadPins(UNLOCK_BTN_PORT) >> (31 - UNLOCK_BTN_PIN);
	PIN_VALUE drUnlockBtn = (PINS_DRV_ReadPins(UNLOCK_BTN_PORT) & 0x00020000) >> (UNLOCK_BTN_PIN);
	return drUnlockBtn;
	//return DIO_LOW;
}


PIN_VALUE Dio_Read_WindowOpen_Button(void)
{
	//PIN_VALUE winOpenBtn = PINS_DRV_ReadPins(OPEN_BTN_PORT) >> (31 - OPEN_BTN_PIN);
	PIN_VALUE winOpenBtn = (PINS_DRV_ReadPins(OPEN_BTN_PORT) & 0x00001000) >> (OPEN_BTN_PIN);
	return winOpenBtn;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_WindowClose_Button(void)
{
	//PIN_VALUE winOpenBtn = PINS_DRV_ReadPins(CLOSE_BTN_PORT) >> (31 - CLOSE_BTN_PIN);
	PIN_VALUE winCloseBtn = (PINS_DRV_ReadPins(CLOSE_BTN_PORT) & 0x00002000) >> (CLOSE_BTN_PIN);
	return winCloseBtn;
	//return DIO_LOW;
}



PIN_VALUE Dio_Read_PassengerWindowOpen_Button(void)
{
	//PIN_VALUE btn = PINS_DRV_ReadPins(PASSENGER_OPEN_BTN_PORT) >> (31 - PASSENGER_OPEN_BTN_PIN);
	PIN_VALUE btn = (PINS_DRV_ReadPins(PASSENGER_OPEN_BTN_PORT) & 0x00004000) >> (PASSENGER_OPEN_BTN_PIN);
	return btn;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_PassengerWindowClose_Button(void)
{
	//PIN_VALUE btn = PINS_DRV_ReadPins(PASSENGER_CLOSE_BTN_PORT) >> (31 - PASSENGER_CLOSE_BTN_PIN);
	PIN_VALUE btn = (PINS_DRV_ReadPins(PASSENGER_CLOSE_BTN_PORT) & 0x00008000) >> (PASSENGER_CLOSE_BTN_PIN);
	return btn;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_RearLeftWindowOpen_Button(void)
{
	//PIN_VALUE btn = PINS_DRV_ReadPins(REARLEFT_OPEN_BTN_PORT) >> (31 - REARLEFT_OPEN_BTN_PIN);
	PIN_VALUE btn = (PINS_DRV_ReadPins(REARLEFT_OPEN_BTN_PORT) & 0x00000001) >> REARLEFT_OPEN_BTN_PIN;
	return btn;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_RearLeftWindowClose_Button(void)
{
	//PIN_VALUE btn = PINS_DRV_ReadPins(REARLEFT_CLOSE_BTN_PORT) >> (31 - REARLEFT_CLOSE_BTN_PIN);
	PIN_VALUE btn = (PINS_DRV_ReadPins(REARLEFT_CLOSE_BTN_PORT) & 0x00000200) >> (REARLEFT_CLOSE_BTN_PIN);
	return btn;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_RearRightWindowOpen_Button(void)
{
	//PIN_VALUE btn = PINS_DRV_ReadPins(REARRIGHT_OPEN_BTN_PORT) >> (31 - REARRIGHT_OPEN_BTN_PIN);
	PIN_VALUE btn = (PINS_DRV_ReadPins(REARRIGHT_OPEN_BTN_PORT) & 0x00000020) >> (REARRIGHT_OPEN_BTN_PIN);
	return btn;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_RearRightWindowClose_Button(void)
{
	//PIN_VALUE btn = PINS_DRV_ReadPins(REARRIGHT_CLOSE_BTN_PORT) >> (31 - REARRIGHT_CLOSE_BTN_PIN);
	PIN_VALUE btn = (PINS_DRV_ReadPins(REARRIGHT_CLOSE_BTN_PORT) & 0x000010000) >> (REARRIGHT_CLOSE_BTN_PIN);
	return btn;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_RearWindowLock_Button(void)
{
	//PIN_VALUE btn = PINS_DRV_ReadPins(REAR_WINDOW_LOCK_BTN_PORT) >> (31 - REAR_WINDOW_LOCK_BTN_PIN);
	PIN_VALUE btn = (PINS_DRV_ReadPins(REAR_WINDOW_LOCK_BTN_PORT) & 0x00020000) >> (REAR_WINDOW_LOCK_BTN_PIN);
	return btn;
	//return DIO_LOW;
}


PIN_VALUE Dio_Read_Jumper0(void)
{
	//PIN_VALUE jmp = PINS_DRV_ReadPins(SW_VARIANT_0_PORT) >> (31 - SW_VARIANT_0_PIN);
	PIN_VALUE jmp = (PINS_DRV_ReadPins(SW_VARIANT_0_PORT) & 0x00000002) >> (SW_VARIANT_0_PIN);
	return jmp;
	//return DIO_LOW;
}

PIN_VALUE Dio_Read_Jumper1(void)
{
	//PIN_VALUE jmp = PINS_DRV_ReadPins(SW_VARIANT_1_PORT) >> (31 - SW_VARIANT_1_PIN);
	PIN_VALUE jmp = (PINS_DRV_ReadPins(SW_VARIANT_1_PORT) & 0x00000008) >> (SW_VARIANT_1_PIN);
	return jmp;
	//return DIO_LOW;
}


