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

/*Global type def___________________________________________________________*/
typedef uint8 Door_hold_t;

typedef enum
{
    eDOOR_ACTION_UNKNOWN,
    eDOOR_ACTION_IN_PROGRESS,
    eDOOR_ACTION_COMPLETED 
}Door_actionState_t;

/*Global Macro______________________________________________________________*/
#define DOOR_HOLD_THRESHOLD_STATE         ((Door_hold_t) 0x0Au)
#define DOOR_TURN_ON_STATE                 DIO_LOW
#define DOOR_TURN_OFF_STATE                DIO_HIGH

#define DOOR_SW_ACTIVE                     DIO_HIGH
#define DOOR_SW_INACTIVE                   DIO_LOW

/*Local function def________________________________________________________*/
static void Door_StatusDetermination( void );
static Door_actionState_t Door_LockDoorActuation( void );
static Door_actionState_t Door_UnLockDoorActuation( void );

/*Local variable____________________________________________________________*/
static DOOR_REQUEST Door_Request;
static DOOR_STATUS  Door_Status;
static Door_actionState_t actionState;

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
    actionState  = eDOOR_ACTION_UNKNOWN;
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
    if (DOOR_REQUEST_LOCK == Door_Request)
    {
        actionState = Door_LockDoorActuation();
    }
    else if (DOOR_REQUEST_UNLOCK == Door_Request)
    {
        actionState = Door_UnLockDoorActuation();
    }
    else
    {
        /* Avoid Misra - No action required */ 
    }

    if (eDOOR_ACTION_COMPLETED == actionState)
    {
        /* Ready to receive new actuation request */
        Door_Request = DOOR_REQUEST_NONE;
        actionState = eDOOR_ACTION_UNKNOWN;
    }


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
    if ((DOOR_REQUEST_NONE == request) ||
        (DOOR_REQUEST_LOCK == request) ||
        (DOOR_REQUEST_UNLOCK == request))
    {
        /* Request new Door Actuation until finish the current one */
        if (DOOR_REQUEST_NONE == Door_Request)
        {
            Door_Request = request;
        }
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
    PIN_VALUE  Lock_status = Dio_Read_DoorLock();

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
 * Arguments:     None
 * Return:        Enum door action state.
 * ========================================================================= */
static Door_actionState_t Door_LockDoorActuation( void )
{
    static Door_hold_t counter = 0x00u;
    Door_actionState_t ret_value = eDOOR_ACTION_IN_PROGRESS;

    if (0x00u == counter)
    {
        Dio_Write_DoorUnlock_Led( DOOR_TURN_OFF_STATE );
    }
    
    /* Wait 100ms */
    if (DOOR_HOLD_THRESHOLD_STATE < counter)
    {
        Dio_Write_DoorLock_Led( DOOR_TURN_ON_STATE );

        counter = 0x00u;
        ret_value = eDOOR_ACTION_COMPLETED;
    }
    else
    {
        counter++;
    }

    return ret_value;
}

/* ============================================================================
 * Function Name: Door_UnLockDoorActuation
 * Description:
 * Arguments:     
 * Return:        Enum door action state.
 * ========================================================================= */
static Door_actionState_t Door_UnLockDoorActuation( void )
{
    static Door_hold_t counter = 0x00u;
    Door_actionState_t ret_value = eDOOR_ACTION_IN_PROGRESS;

    if (0x00u == counter)
    {
        Dio_Write_DoorLock_Led( DOOR_TURN_OFF_STATE );
    }
    
    /* Wait 100ms */
    if (DOOR_HOLD_THRESHOLD_STATE < counter)
    {
        Dio_Write_DoorUnlock_Led( DOOR_TURN_ON_STATE );

        counter = 0x00u;
        ret_value = eDOOR_ACTION_COMPLETED;
    }
    else
    {
        counter++;
    }

    return ret_value;
}

/*End of file_______________________________________________________________*/
