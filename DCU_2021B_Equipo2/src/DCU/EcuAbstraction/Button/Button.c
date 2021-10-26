/*
 * ButtonDriver.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */





#include "BasicTypes.h"
#include "Dio.h"
#include "HwConfig.h"
#include "Button.h"

#include "InDebounce.h"

Button_t ButtonList[TOTAL_BUTTONS];

PIN_VALUE getDigitalInput(int index);

void Button_Init(void)
{
	for(int i = 0; i < TOTAL_BUTTONS; i++)
	{
		memset(&ButtonList[i], 0, sizeof(ButtonList[i]));
		ButtonList[i].threshold1 = 5;
		ButtonList[i].threshold2 = 50;
	}


}


//10 ms
void Button_Run(void)
{
	PIN_VALUE button_pin_value;
	for(int i = 0; i < TOTAL_BUTTONS; i++)
	{
		button_pin_value = getDigitalInput(i);
		Debounce_Process(&ButtonList[i], button_pin_value);
	}
}

BUTTON_STATUS  Button_Get_Door_Lock(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[LOCK_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[LOCK_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
    //return BUTTON_NOT_PRESSED;
}

BUTTON_STATUS  Button_Get_Door_Unlock(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[UNLOCK_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[UNLOCK_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}


BUTTON_STATUS  Button_Get_Window_Open(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[OPEN_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[OPEN_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}

BUTTON_STATUS  Button_Get_Window_Close(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[CLOSE_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[CLOSE_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}


//driver
BUTTON_STATUS  Button_Get_PassengerWindow_Open(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[PASSENGER_OPEN_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[PASSENGER_OPEN_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}
//driver
BUTTON_STATUS  Button_Get_PassengerWindow_Close(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[PASSENGER_CLOSE_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[PASSENGER_CLOSE_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}

//driver
BUTTON_STATUS  Button_Get_RearLeftWindow_Open(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[REARLEFT_OPEN_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[REARLEFT_OPEN_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}
//driver
BUTTON_STATUS  Button_Get_RearLeftWindow_Close(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[REARLEFT_CLOSE_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[REARLEFT_CLOSE_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}

//driver
BUTTON_STATUS  Button_Get_RearRightWindow_Open(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[REARRIGHT_OPEN_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[REARRIGHT_OPEN_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}
//driver
BUTTON_STATUS  Button_Get_RearRightWindow_Close(void)
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[REARRIGHT_CLOSE_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[REARRIGHT_CLOSE_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}



//driver
BUTTON_STATUS  Button_Get_RearWindow_Lock(void)  //switch
{
	BUTTON_STATUS btn_value = BUTTON_NOT_PRESSED;
	if(ButtonList[REAR_WINDOW_LOCK_BTN].releasedAt1)
	{
		btn_value = BUTTON_PRESSED;
	}
	else if(ButtonList[REAR_WINDOW_LOCK_BTN].releasedAt2)
	{
		btn_value = BUTTON_LONG_PRESSED;
	}
	return btn_value;
	//return BUTTON_NOT_PRESSED;
}

PIN_VALUE getDigitalInput(int index)
{
	PIN_VALUE button_pin_value;
	switch(index)
	{
		case OPEN_BTN:
			button_pin_value = Dio_Read_WindowOpen_Button();
			break;

		case CLOSE_BTN:
			button_pin_value = Dio_Read_WindowClose_Button();
			break;

		case PASSENGER_OPEN_BTN:
			button_pin_value = Dio_Read_PassengerWindowOpen_Button();
			break;

		case PASSENGER_CLOSE_BTN:
			button_pin_value = Dio_Read_PassengerWindowClose_Button();
			break;

		case REARLEFT_OPEN_BTN:
			button_pin_value = Dio_Read_RearLeftWindowOpen_Button();
			break;

		case REARLEFT_CLOSE_BTN:
			button_pin_value =  Dio_Read_RearLeftWindowClose_Button();
			break;

		case REARRIGHT_OPEN_BTN:
			button_pin_value = Dio_Read_RearRightWindowOpen_Button();
			break;

		case REARRIGHT_CLOSE_BTN:
			button_pin_value = Dio_Read_RearRightWindowClose_Button();
			break;

		case REAR_WINDOW_LOCK_BTN:
			button_pin_value = Dio_Read_RearWindowLock_Button();
			break;

		case LOCK_BTN:
			button_pin_value = Dio_Read_DoorLock_Button();
			break;

		case UNLOCK_BTN:
			button_pin_value = Dio_Read_DoorUnlock_Button();
			break;

	}

	return button_pin_value;
}

