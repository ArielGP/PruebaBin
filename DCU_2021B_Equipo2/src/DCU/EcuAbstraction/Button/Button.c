/*
 * ButtonDriver.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#include <string.h>
#include "BasicTypes.h"
#include "Dio.h"
#include "HwConfig.h"
#include "Button.h"
#include "InDebounce.h"

/*Local Macro_______________________________________________________________*/
#define BUTTON_THRESHOLD1             ((ButtonData_t) 0x05u)
#define BUTTON_THRESHOLD2             ((ButtonData_t) 0x32u)
#define BUTTON_THRESHOLD3             ((ButtonData_t) 0x3E8u)
/*Local variables___________________________________________________________*/
static Button_t ButtonList[BUTTON_LIST_LENGTH];

/*Local function def________________________________________________________*/
static BUTTON_STATUS Button_GetButtonStatus(uint8_t index);
static PIN_VALUE getDigitalInput(uint8_t index);

/* ============================================================================
 * Function Name: Button_Init
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Button_Init(void)
{
	uint8_t index = 0x00u;

	(void) memset(ButtonList, 0x00u, sizeof(ButtonList));

	for(index = 0x00u; (BUTTON_LIST_LENGTH > index); index++)
	{
		ButtonList[index].threshold1 = BUTTON_THRESHOLD1;
		ButtonList[index].threshold2 = BUTTON_THRESHOLD2;
		ButtonList[index].threshold3 = BUTTON_THRESHOLD3;
	}
}

//10 ms
/* ============================================================================
 * Function Name: Button_Run
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Button_Run(void)
{
	uint8_t index = 0x00u;
	PIN_VALUE button_pin_value = DIO_LOW;
	
	for (index = 0x00u; (BUTTON_LIST_LENGTH > index); index++)
	{
		button_pin_value = getDigitalInput(index);
		(void) Debounce_Process(&ButtonList[index], button_pin_value);
	}
}

/* ============================================================================
 * Function Name: Button_Get_Door_Lock
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_Door_Lock(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_LOCK_BTN_IDX);

	return return_status;
}

/* ============================================================================
 * Function Name: Button_Get_Door_Unlock
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_Door_Unlock(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_UNLOCK_BTN_IDX);

	return return_status;
}

/* ============================================================================
 * Function Name: Button_Get_Window_Open
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_Window_Open(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_OPEN_BTN_IDX);

	return return_status;
}

/* ============================================================================
 * Function Name: Button_Get_Window_Close
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_Window_Close(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_CLOSE_BTN_IDX);

	return return_status;
}


//driver
/* ============================================================================
 * Function Name: Button_Get_PassengerWindow_Open
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_PassengerWindow_Open(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_PASSENGER_OPEN_BTN_IDX);

	return return_status;
}

//driver
/* ============================================================================
 * Function Name: Button_Get_PassengerWindow_Close
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_PassengerWindow_Close(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_PASSENGER_CLOSE_BTN_IDX);

	return return_status;
}

//driver
/* ============================================================================
 * Function Name: Button_Get_RearLeftWindow_Open
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_RearLeftWindow_Open(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_REARLEFT_OPEN_BTN_IDX);

	return return_status;
}
//driver
/* ============================================================================
 * Function Name: Button_Get_RearLeftWindow_Close
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_RearLeftWindow_Close(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_REARLEFT_CLOSE_BTN_IDX);

	return return_status;
}

//driver
/* ============================================================================
 * Function Name: Button_Get_RearRightWindow_Open
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_RearRightWindow_Open(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_REARRIGHT_OPEN_BTN_IDX);

	return return_status;
}

//driver
/* ============================================================================
 * Function Name: Button_Get_RearRightWindow_Close
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_RearRightWindow_Close(void)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_REARRIGHT_CLOSE_BTN_IDX);

	return return_status;
}

//driver
/* ============================================================================
 * Function Name: Button_Get_RearWindow_Lock
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
BUTTON_STATUS  Button_Get_RearWindow_Lock(void)  //switch
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	return_status = Button_GetButtonStatus(BUTTON_REAR_WINDOW_LOCK_BTN_IDX);

	return return_status;
}

/* ============================================================================
 * Function Name: Button_GetButtonStatus
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static BUTTON_STATUS Button_GetButtonStatus(uint8_t index)
{
	BUTTON_STATUS return_status = BUTTON_NOT_PRESSED;

	if (kTrue == ButtonList[index].releasedAt1)
	{
		return_status = BUTTON_PRESSED;
		ButtonList[index].releasedAt1 = kFalse;
	}
	else if (kTrue == ButtonList[index].releasedAt2)
	{
		return_status = BUTTON_LONG_PRESSED;
		ButtonList[index].releasedAt2 = kFalse;
	}
	else if (kTrue == ButtonList[index].reached3)
	{
		return_status = BUTTON_STUCK;
	}
	else
	{
		/*Avoid Misra - No action required */
	}

	return return_status;
}

/* ============================================================================
 * Function Name: getDigitalInput
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static PIN_VALUE getDigitalInput(uint8_t index)
{
	PIN_VALUE button_pin_value = DIO_LOW; //pin initialization value

	switch (index)
	{
		case BUTTON_OPEN_BTN_IDX:
			button_pin_value = Dio_Read_WindowOpen_Button();
			break;

		case BUTTON_CLOSE_BTN_IDX:
			button_pin_value = Dio_Read_WindowClose_Button();
			break;

		case BUTTON_PASSENGER_OPEN_BTN_IDX:
			button_pin_value = Dio_Read_PassengerWindowOpen_Button();
			break;

		case BUTTON_PASSENGER_CLOSE_BTN_IDX:
			button_pin_value = Dio_Read_PassengerWindowClose_Button();
			break;

		case BUTTON_REARLEFT_OPEN_BTN_IDX:
			button_pin_value = Dio_Read_RearLeftWindowOpen_Button();
			break;

		case BUTTON_REARLEFT_CLOSE_BTN_IDX:
			button_pin_value =  Dio_Read_RearLeftWindowClose_Button();
			break;

		case BUTTON_REARRIGHT_OPEN_BTN_IDX:
			button_pin_value = Dio_Read_RearRightWindowOpen_Button();
			break;

		case BUTTON_REARRIGHT_CLOSE_BTN_IDX:
			button_pin_value = Dio_Read_RearRightWindowClose_Button();
			break;

		case BUTTON_REAR_WINDOW_LOCK_BTN_IDX:
			button_pin_value = Dio_Read_RearWindowLock_Button();
			break;

		case BUTTON_LOCK_BTN_IDX:
			button_pin_value = Dio_Read_DoorLock_Button();
			break;

		case BUTTON_UNLOCK_BTN_IDX:
			button_pin_value = Dio_Read_DoorUnlock_Button();
			break;

		default:
			/* Avoid Misra -No action required */
			break;
	}

	return button_pin_value;
}

/* ============================================================================
 * Function Name: Button_Consume_Stuck
 * Description:
 * Arguments: index
 * Return:
 * ========================================================================= */
void Button_Consume_Stuck(uint8 index)
{
	ButtonList[index].reached3 = kFalse;
	ButtonList[index].reached1 = kFalse;
	ButtonList[index].reached2 = kFalse;
	ButtonList[index].debounceCounter = 0;
	ButtonList[index].state =kButtonNotDebounced;

}

/*End of file_______________________________________________________________*/
