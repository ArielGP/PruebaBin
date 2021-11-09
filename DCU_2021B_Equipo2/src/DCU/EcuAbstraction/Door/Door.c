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

/*Local type def___________________________________________________________*/
typedef uint8 Door_hold_t;

typedef enum
{
    eDOOR_ACTION_UNKNOWN,
    eDOOR_ACTION_IN_PROGRESS,
    eDOOR_ACTION_COMPLETED 
}Door_actionState_t;

/*Local Macro______________________________________________________________*/
#define DOOR_HOLD_THRESHOLD_STATE         ((Door_hold_t) 0x0Au)
#define DOOR_TURN_ON_STATE                 DIO_LOW
#define DOOR_TURN_OFF_STATE                DIO_HIGH

#define DOOR_SW_ACTIVE                     DIO_HIGH
#define DOOR_SW_INACTIVE                   DIO_LOW

/*Local variable____________________________________________________________*/
static DOOR_REQUEST Door_Request;
static DOOR_STATUS  Door_Status;

static DOOR_REQUEST previousDoor_Request;
static Door_hold_t  doorCounter;

/*Local function def________________________________________________________*/
static void Door_StatusDetermination( void );
static void Door_LockDoorActuation  (Door_hold_t * const counterPtr, DOOR_REQUEST * const doorRequestPtr);
static void Door_UnLockDoorActuation(Door_hold_t * const counterPtr, DOOR_REQUEST * const doorRequestPtr)

/* ============================================================================
 * Function Name: Door_Init
 * Description:   This runnable is called during initialization time.
 * Arguments:     None.
 * Return:        None.
 * ========================================================================= */
void Door_Init(void)
{
    Door_Request = DOOR_REQUEST_NONE;
    Door_Status  = DOOR_STATUS_UNKNOWN;

    previousDoor_Request = DOOR_REQUEST_NONE;
    doorCounter = 0x00u;
}

/* ============================================================================
 * Function Name: Door_Run
 * Description:   This Runnable is called every 10 ms.
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
void Door_Run(void)
{

    /* DOOR Actuation */
    if (Door_Request != previousDoor_Request)
    {
        doorCounter = 0x00u;
    }
    
    if (DOOR_REQUEST_LOCK == Door_Request)
    {
        Door_LockDoorActuation(&doorCounter, &Door_Request);
    }
    else if (DOOR_REQUEST_UNLOCK == Door_Request)
    {
        Door_UnLockDoorActuation(&doorCounter, &Door_Request);
    }
    else
    {
        /* Avoid Misra - No action required */
    }

    previousDoor_Request = Door_Request;

    /* DOOR status*/
    Door_StatusDetermination();

    
}

//driver, passenger
/* ============================================================================
 * Function Name: Door_Set_Request
 * Description:   
 * Arguments:     
 * Return:        None
 * ========================================================================= */
void Door_Set_Request(DOOR_REQUEST request)
{
    if ((DOOR_REQUEST_NONE   == request) ||
        (DOOR_REQUEST_LOCK   == request) ||
        (DOOR_REQUEST_UNLOCK == request))
    {
        Door_Request = request;
    }
}

/* ============================================================================
 * Function Name: Door_Get_Status
 * Description:   
 * Arguments:     None
 * Return:        
 * ========================================================================= */
DOOR_STATUS Door_Get_Status(void)
{
    return Door_Status;
}

/* ============================================================================
 * Function Name: Door_StatusDetermination
 * Description:   
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
static void Door_StatusDetermination(void)
{
    PIN_VALUE  UnLock_status = Dio_Read_DoorUnlock();
    PIN_VALUE  Lock_status   = Dio_Read_DoorLock();

    if ((DOOR_SW_ACTIVE == UnLock_status) && (DOOR_SW_INACTIVE == Lock_status))
    {
        Door_Status = DOOR_STATUS_UNLOCKED;
    }
    else if ((DOOR_SW_INACTIVE == UnLock_status) && (DOOR_SW_ACTIVE == Lock_status))
    {
        Door_Status = DOOR_STATUS_LOCKED;
    }
    else
    {
        Door_Status = DOOR_STATUS_ERROR;
    }
}

/* ============================================================================
 * Function Name: Door_LockDoorActuation
 * Description:   
 * Arguments:     
 * Return:        None
 * ========================================================================= */
static void Door_LockDoorActuation(Door_hold_t * const counterPtr, DOOR_REQUEST * const doorRequestPtr)
{
    if (0x00u == counterPtr[0u])
    {
        Dio_Write_DoorUnlock_Led( DOOR_TURN_OFF_STATE );
    }
    
    /* Wait 100ms */
    if (DOOR_HOLD_THRESHOLD_STATE < counterPtr[0u])
    {
        /* DOOR_ACTION_COMPLETED */
        doorRequestPtr[0u] = DOOR_REQUEST_NONE;
        counterPtr[0u]     = 0x00u;
        Dio_Write_DoorLock_Led( DOOR_TURN_ON_STATE );
    }
    else
    {
        /* DOOR_ACTION_IN_PROGRESS */
        counterPtr[0u]++;
    }
}

/* ============================================================================
 * Function Name: Door_UnLockDoorActuation
 * Description:
 * Arguments:     
 * Return:        None 
 * ========================================================================= */
static void Door_LockDoorActuation(Door_hold_t * const counterPtr, DOOR_REQUEST * const doorRequestPtr)
{
    if (0x00u == counterPtr[0u])
    {
        Dio_Write_DoorLock_Led( DOOR_TURN_OFF_STATE );
    }
    
    /* Wait 100ms */
    if (DOOR_HOLD_THRESHOLD_STATE < counterPtr[0u])
    {
        /* DOOR_ACTION_COMPLETED */
        
        doorRequestPtr[0u] = DOOR_REQUEST_NONE;
        counterPtr[0u]     = 0x00u;
        Dio_Write_DoorUnlock_Led( DOOR_TURN_ON_STATE );
    }
    else
    {
        /* DOOR_ACTION_IN_PROGRESS */
        counterPtr[0u]++;
    }
}

/*End of file_______________________________________________________________*/
