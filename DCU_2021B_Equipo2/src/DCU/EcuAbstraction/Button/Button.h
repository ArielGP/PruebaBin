/*
 * ButtonDriver.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef ECUABSTRACTION_BUTTONDRIVER_H_
#define ECUABSTRACTION_BUTTONDRIVER_H_


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
