/*
 * DoorDriver.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef ECUABSTRACTION_DOORDRIVER_H_
#define ECUABSTRACTION_DOORDRIVER_H_


/*Global type def___________________________________________________________*/
typedef uint8  DOOR_STATUS;
typedef uint8  DOOR_REQUEST;

/*Global Macro______________________________________________________________*/
#define DOOR_STATUS_LOCKED      ((DOOR_STATUS)0)
#define DOOR_STATUS_UNLOCKED    ((DOOR_STATUS)1)
#define DOOR_STATUS_UNKNOWN     ((DOOR_STATUS)2)
#define DOOR_STATUS_ERROR       ((DOOR_STATUS)3)


#define DOOR_REQUEST_NONE        ((DOOR_REQUEST)0)
#define DOOR_REQUEST_LOCK        ((DOOR_REQUEST)1)
#define DOOR_REQUEST_UNLOCK      ((DOOR_REQUEST)2)

/*Global function def_______________________________________________________*/
extern void Door_Init(void);

//10 ms
extern void Door_Run(void);

//driver, passenger
extern void        Door_Set_Request(DOOR_REQUEST request);
extern DOOR_STATUS Door_Get_Status(void);

#endif /* ECUABSTRACTION_DOORDRIVER_H_ */
