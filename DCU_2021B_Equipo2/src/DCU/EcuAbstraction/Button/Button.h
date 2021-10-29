/*
 * ButtonDriver.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef ECUABSTRACTION_BUTTONDRIVER_H_
#define ECUABSTRACTION_BUTTONDRIVER_H_

#define TOTAL_BUTTONS 11

enum
{
	OPEN_BTN,
	CLOSE_BTN,
	PASSENGER_OPEN_BTN,
	PASSENGER_CLOSE_BTN,
	REARLEFT_OPEN_BTN,
	REARLEFT_CLOSE_BTN,
	REARRIGHT_OPEN_BTN,
	REARRIGHT_CLOSE_BTN,
	REAR_WINDOW_LOCK_BTN,
	LOCK_BTN,
	UNLOCK_BTN
};

void Button_Init(void);


//10 ms
void Button_Run(void);

typedef uint8 BUTTON_STATUS;

#define BUTTON_NOT_PRESSED    ((BUTTON_STATUS)0)
#define BUTTON_PRESSED        ((BUTTON_STATUS)1)
#define BUTTON_LONG_PRESSED   ((BUTTON_STATUS)2)
#define BUTTON_STUCK          ((BUTTON_STATUS)3)


BUTTON_STATUS  Button_Get_Door_Lock(void);

BUTTON_STATUS  Button_Get_Door_Unlock(void);


BUTTON_STATUS  Button_Get_Window_Open(void);

BUTTON_STATUS  Button_Get_Window_Close(void);


//driver
BUTTON_STATUS  Button_Get_PassengerWindow_Open(void);
//driver
BUTTON_STATUS  Button_Get_PassengerWindow_Close(void);

//driver
BUTTON_STATUS  Button_Get_RearLeftWindow_Open(void);
//driver
BUTTON_STATUS  Button_Get_RearLeftWindow_Close(void);

//driver
BUTTON_STATUS  Button_Get_RearRightWindow_Open(void);
//driver
BUTTON_STATUS  Button_Get_RearRightWindow_Close(void);


//driver
BUTTON_STATUS  Button_Get_RearWindow_Lock(void);



#endif /* ECUABSTRACTION_BUTTONDRIVER_H_ */
