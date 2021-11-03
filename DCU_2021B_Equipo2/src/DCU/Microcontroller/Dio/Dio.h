/*
 * DIO.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef MICROCONTROLLER_DIO_H_
#define MICROCONTROLLER_DIO_H_


/*type def__________________________________________________________________*/
typedef boolean PIN_VALUE;
typedef uint32  PIN_VALUES;
/*Global Macros_____________________________________________________________*/
#define DIO_LOW    ((PIN_VALUE)0)
#define DIO_HIGH   ((PIN_VALUE)1)

#define DIO_WINDOW_LED1    ((PIN_VALUES)0x00000002)
#define DIO_WINDOW_LED2    ((PIN_VALUES)0x00000004)
#define DIO_WINDOW_LED3    ((PIN_VALUES)0x00000008)
#define DIO_WINDOW_LED4    ((PIN_VALUES)0x00000010)
#define DIO_WINDOW_LED5    ((PIN_VALUES)0x00000020)
#define DIO_WINDOW_LED6    ((PIN_VALUES)0x00000040)
#define DIO_WINDOW_LED7    ((PIN_VALUES)0x00000080)
#define DIO_WINDOW_LED8    ((PIN_VALUES)0x00000100)
#define DIO_WINDOW_LED9    ((PIN_VALUES)0x00000200)
#define DIO_WINDOW_LED10   ((PIN_VALUES)0x00000400)

extern void Dio_Init(void);

//driver, passenger
extern void Dio_Write_DoorUnlock_Led(PIN_VALUE value);
extern void Dio_Write_DoorLock_Led(PIN_VALUE value);
extern PIN_VALUE Dio_Read_DoorUnlock(void);
extern PIN_VALUE Dio_Read_DoorLock(void);

extern void Dio_Write_Window_Leds(PIN_VALUES values);

extern PIN_VALUE Dio_Read_Window_Open(void);
extern PIN_VALUE Dio_Read_Window_Closed(void);

//driver, passenger
extern PIN_VALUE Dio_Read_DoorLock_Button(void);
extern PIN_VALUE Dio_Read_DoorUnlock_Button(void);

extern PIN_VALUE Dio_Read_WindowOpen_Button(void);
extern PIN_VALUE Dio_Read_WindowClose_Button(void);

//driver
extern PIN_VALUE Dio_Read_PassengerWindowOpen_Button(void);
extern PIN_VALUE Dio_Read_PassengerWindowClose_Button(void);
extern PIN_VALUE Dio_Read_RearLeftWindowOpen_Button(void);
extern PIN_VALUE Dio_Read_RearLeftWindowClose_Button(void);
extern PIN_VALUE Dio_Read_RearRightWindowOpen_Button(void);
extern PIN_VALUE Dio_Read_RearRightWindowClose_Button(void);
extern PIN_VALUE Dio_Read_RearWindowLock_Button(void);

extern PIN_VALUE Dio_Read_Jumper0(void);
extern PIN_VALUE Dio_Read_Jumper1(void);

#endif /* MICROCONTROLLER_DIO_H_ */
