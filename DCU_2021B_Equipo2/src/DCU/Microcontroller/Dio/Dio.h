/*
 * DIO.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef MICROCONTROLLER_DIO_H_
#define MICROCONTROLLER_DIO_H_


void Dio_Init(void);


typedef boolean PIN_VALUE;
typedef uint32  PIN_VALUES;

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

//driver, passenger
void Dio_Write_DoorUnlock_Led(PIN_VALUE value);
void Dio_Write_DoorLock_Led(PIN_VALUE value);
PIN_VALUE Dio_Read_DoorUnlock(void);
PIN_VALUE Dio_Read_DoorLock(void);


void Dio_Write_Window_Leds(PIN_VALUES values);

PIN_VALUE Dio_Read_Window_Open(void);
PIN_VALUE Dio_Read_Window_Closed(void);

//driver, passenger
PIN_VALUE Dio_Read_DoorLock_Button(void);
PIN_VALUE Dio_Read_DoorUnlock_Button(void);


PIN_VALUE Dio_Read_WindowOpen_Button(void);
PIN_VALUE Dio_Read_WindowClose_Button(void);


//driver
PIN_VALUE Dio_Read_PassengerWindowOpen_Button(void);
PIN_VALUE Dio_Read_PassengerWindowClose_Button(void);
PIN_VALUE Dio_Read_RearLeftWindowOpen_Button(void);
PIN_VALUE Dio_Read_RearLeftWindowClose_Button(void);
PIN_VALUE Dio_Read_RearRightWindowOpen_Button(void);
PIN_VALUE Dio_Read_RearRightWindowClose_Button(void);
PIN_VALUE Dio_Read_RearWindowLock_Button(void);


PIN_VALUE Dio_Read_Jumper0(void);
PIN_VALUE Dio_Read_Jumper1(void);



#endif /* MICROCONTROLLER_DIO_H_ */
