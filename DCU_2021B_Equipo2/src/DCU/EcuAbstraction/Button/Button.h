/*
 * ButtonDriver.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef ECUABSTRACTION_BUTTONDRIVER_H_
#define ECUABSTRACTION_BUTTONDRIVER_H_

/*Global Macro______________________________________________________________*/
#define BUTTON_OPEN_BTN_IDX                 (0x00u)
#define BUTTON_CLOSE_BTN_IDX                (0x01u)
#define BUTTON_PASSENGER_OPEN_BTN_IDX       (0x02u)
#define BUTTON_PASSENGER_CLOSE_BTN_IDX      (0x03u)
#define BUTTON_REARLEFT_OPEN_BTN_IDX        (0x04u)
#define BUTTON_REARLEFT_CLOSE_BTN_IDX       (0x05u)
#define BUTTON_REARRIGHT_OPEN_BTN_IDX       (0x06u)
#define BUTTON_REARRIGHT_CLOSE_BTN_IDX      (0x07u)
#define BUTTON_REAR_WINDOW_LOCK_BTN_IDX     (0x08u)
#define BUTTON_LOCK_BTN_IDX                 (0x09u)
#define BUTTON_UNLOCK_BTN_IDX               (0x0Au)
#define BUTTON_LIST_LENGTH                  (0x0Bu)

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
