/*
 * WindowDriver.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef ECUABSTRACTION_WINDOWDRIVER_H_
#define ECUABSTRACTION_WINDOWDRIVER_H_

/*Global type def___________________________________________________________*/
typedef uint8 WINDOW_STATUS;
typedef uint8 WINDOW_REQUEST;
typedef uint8 WINDOW_OPERATION;

/*Global Macro______________________________________________________________*/
#define WINDOW_POSITION_OPEN       ((WINDOW_STATUS)0)
#define WINDOW_POSITION_1          ((WINDOW_STATUS)1)
#define WINDOW_POSITION_2          ((WINDOW_STATUS)2)
#define WINDOW_POSITION_3          ((WINDOW_STATUS)3)
#define WINDOW_POSITION_4          ((WINDOW_STATUS)4)
#define WINDOW_POSITION_5          ((WINDOW_STATUS)5)
#define WINDOW_POSITION_6          ((WINDOW_STATUS)6)
#define WINDOW_POSITION_7          ((WINDOW_STATUS)7)
#define WINDOW_POSITION_8          ((WINDOW_STATUS)8)
#define WINDOW_POSITION_9          ((WINDOW_STATUS)9)
#define WINDOW_POSITION_10         ((WINDOW_STATUS)10)
#define WINDOW_POSITION_CLOSED     ((WINDOW_STATUS)11)
#define WINDOW_POSITION_ERROR      ((WINDOW_STATUS)0xFF)

#define WINDOW_REQUEST_IDLE        ((WINDOW_REQUEST)0)
#define WINDOW_REQUEST_UP          ((WINDOW_REQUEST)1)
#define WINDOW_REQUEST_DOWN        ((WINDOW_REQUEST)2)

#define WINDOW_OPERATION_IDLE        ((WINDOW_OPERATION)0)
#define WINDOW_OPERATION_UP          ((WINDOW_OPERATION)1)
#define WINDOW_OPERATION_DOWN        ((WINDOW_OPERATION)2)
#define MPU_TEST

/*Global function def_______________________________________________________*/
extern void Window_Init(void);

extern void Window_Init_Safety(void);

//10 ms
extern void Window_Run(void);

//100 ms
extern void Window_Run_Safety(void);

extern void Window_Set_Request(WINDOW_REQUEST request);

extern WINDOW_STATUS Window_Get_Status(void);

extern WINDOW_OPERATION Window_Get_Operation(void);

#ifdef MPU_TEST
extern void Window_MPU_Test(void);
#endif
#endif /* ECUABSTRACTION_WINDOWDRIVER_H_ */
