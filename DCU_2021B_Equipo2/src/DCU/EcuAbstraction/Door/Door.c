/*
 * DoorDriver.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#include "BasicTypes.h"
#include "Dio.h"
#include "HwConfig.h"
#include "Door.h"


void Door_Init(void)
{

}

//10 ms
void Door_Run(void)
{

}


//driver, passenger
void Door_Set_Request(DOOR_REQUEST request)
{
	(void)request;
}

DOOR_STATUS Door_Get_Status(void)
{
    return DOOR_STATUS_UNKNOWN;
}

