/*
 * WindowDriver.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */



#include "BasicTypes.h"
#include "Dio.h"
#include "Window.h"
#include "Adc.h"

void Window_Init(void)
{

}


void Window_Init_Safety(void)
{

}

//10 ms
void Window_Run(void)
{

}

//100 ms
void Window_Run_Safety(void)
{

}

void  Window_Set_Request(WINDOW_REQUEST request)
{
	(void)request;
}

WINDOW_STATUS Window_Get_Status(void)
{
    return WINDOW_POSITION_OPEN;
}

WINDOW_OPERATION Window_Get_Operation(void)
{
    return WINDOW_OPERATION_IDLE;
}
