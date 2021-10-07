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



void Button_Init(void)
{


}


//10 ms
void Button_Run(void)
{

}

BUTTON_STATUS  Button_Get_Door_Lock(void)
{
    return BUTTON_NOT_PRESSED;
}

BUTTON_STATUS  Button_Get_Door_Unlock(void)
{
	return BUTTON_NOT_PRESSED;
}


BUTTON_STATUS  Button_Get_Window_Open(void)
{
	return BUTTON_NOT_PRESSED;
}

BUTTON_STATUS  Button_Get_Window_Close(void)
{
	return BUTTON_NOT_PRESSED;
}


//driver
BUTTON_STATUS  Button_Get_PassengerWindow_Open(void)
{
	return BUTTON_NOT_PRESSED;
}
//driver
BUTTON_STATUS  Button_Get_PassengerWindow_Close(void)
{
	return BUTTON_NOT_PRESSED;
}

//driver
BUTTON_STATUS  Button_Get_RearLeftWindow_Open(void)
{
	return BUTTON_NOT_PRESSED;
}
//driver
BUTTON_STATUS  Button_Get_RearLeftWindow_Close(void)
{
	return BUTTON_NOT_PRESSED;
}

//driver
BUTTON_STATUS  Button_Get_RearRightWindow_Open(void)
{
	return BUTTON_NOT_PRESSED;
}
//driver
BUTTON_STATUS  Button_Get_RearRightWindow_Close(void)
{
	return BUTTON_NOT_PRESSED;
}



//driver
BUTTON_STATUS  Button_Get_RearWindow_Lock(void)  //switch
{
	return BUTTON_NOT_PRESSED;
}



