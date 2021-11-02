/*
 * Signals.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#include "sdk_project_config.h"

#include "BasicTypes.h"
#include "HwConfig.h"
#include "Signals.h"
#include "CANpal.h"
#include "comgen_CAN_includes.h"

/*Global Macro______________________________________________________________*/


/*Local variables____________________________________________________________*/


/* ============================================================================
 * Function Name: Signals_Init
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Signals_Init(void)
{
    /* ----------------------- */
    /* Init CAN driver and PAL */
    /* ----------------------- */
    CANpal_init();

    /* ---------------------- */
    /* Init interaction layer */
    /* ---------------------- */
    switch (HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            can_DCM_DR_coreInit();
        }break;
        case HWCONFIG_PASSENGER:
        {
            can_DCM_PS_coreInit();
        }break;
        case HWCONFIG_REAR_LEFT:
        {
            can_DCM_RL_coreInit();
        }break;
        case HWCONFIG_REAR_RIGHT:
        {
            can_DCM_RR_coreInit();
        }break;
        default:
        {
            /* Avoid Misra - No action required */
        }break;
    }

}

//10 ms
/* ============================================================================
 * Function Name: Signals_RunTx
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Signals_RunTx(void)
{
    switch (HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            can_DCM_DR_txRetry();
            can_task_10ms_DCM_DR_txProcess();
        }break;
        case HWCONFIG_PASSENGER:
        {
            can_DCM_PS_txRetry();
            can_task_10ms_DCM_PS_txProcess();
        }break;
        case HWCONFIG_REAR_LEFT:
        {
            can_DCM_RL_txRetry();
            can_task_10ms_DCM_RL_txProcess();
        }break;
        case HWCONFIG_REAR_RIGHT:
        {
            can_DCM_RR_txRetry();
            can_task_10ms_DCM_RR_txProcess();
        }break;
        default:
        {
            /* Avoid Misra - No action required */
        }break;
    }
}

//20 ms
/* ============================================================================
 * Function Name: Signals_RunRx
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Signals_RunRx(void)
{
    /* Call CAN RX timeout process function */

    switch (HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            can_task_20ms_DCM_DR_rxProcess();
        }break;
        case HWCONFIG_PASSENGER:
        {
           can_task_20ms_DCM_PS_rxProcess();
        }break;
        case HWCONFIG_REAR_LEFT:
        {
            can_task_20ms_DCM_RL_rxProcess();
        }break;
        case HWCONFIG_REAR_RIGHT:
        {
            can_task_20ms_DCM_RR_rxProcess();
        }break;
        default:
        {
            /* Avoid Misra - No action required */
        }break;
    }
}

SIGNAL_ERROR Signals_Get_SysPwrMode(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_SysPwrMode();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_SysPwrMode();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_SysPwrMode();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_SysPwrMode();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_ConfortCmd(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_ConfortCmd();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_ConfortCmd();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_ConfortCmd();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_ConfortCmd();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_VehSpeed(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_VehSpeed();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_VehSpeed();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_VehSpeed();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_VehSpeed();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_ShiftLeverPos(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_ShiftLeverPos();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_ShiftLeverPos();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_ShiftLeverPos();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_ShiftLeverPos();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_ShiftLeverEng(uint8* value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_ShiftLeverEng();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_ShiftLeverEng();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_ShiftLeverEng();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_ShiftLeverEng();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

void Signals_Set_WindowPos(const uint8 *value)
{
    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_DR_update_direct_DCU_1_WindowPos(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_PS_update_direct_DCU_2_WindowPos(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_RL_update_direct_DCU_3_WindowPos(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_RR_update_direct_DCU_4_WindowPos(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

void Signals_Set_LockingReq(const uint8 *value)
{
    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_DR_update_direct_DCU_1_LockingReq(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_PS_update_direct_DCU_2_LockingReq(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        case HWCONFIG_REAR_RIGHT:
        {

        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

SIGNAL_ERROR Signals_Get_LockingReq_Driver(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_DCU_1_LockingReq();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_DCU_1_LockingReq();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_DCU_1_LockingReq();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_DCU_1_LockingReq();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_LockingReq_Passenger(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_DCU_2_LockingReq();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_DCU_2_LockingReq();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_DCU_2_LockingReq();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_DCU_2_LockingReq();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

void Signals_Set_WindowOp(const uint8* value)
{
    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_DR_update_direct_DCU_1_WindowOp(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_PS_update_direct_DCU_2_WindowOp(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_RL_update_direct_DCU_3_WindowOp(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_RR_update_direct_DCU_4_WindowOp(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

void Signals_Set_RearWindowLock(const uint8 *value)
{
    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_DR_update_direct_DCU_1_RearWindowLock(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        case HWCONFIG_REAR_LEFT:
        case HWCONFIG_REAR_RIGHT:
        {

        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

SIGNAL_ERROR Signals_Get_RearWindowLock(uint8 *value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_DCU_1_RearWindowLock();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_DCU_1_RearWindowLock();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_DCU_1_RearWindowLock();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_DCU_1_RearWindowLock();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

void Signals_Set_DoorLockSts(const uint8 *value)
{
    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_DR_update_direct_DCU_1_DoorLockSts(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_PS_update_direct_DCU_2_DoorLockSts(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_RL_update_direct_DCU_3_DoorLockSts(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_RR_update_direct_DCU_4_DoorLockSts(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

SIGNAL_ERROR Signals_Get_Passenger_DoorLockSts(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_DCU_2_DoorLockSts();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_DCU_2_DoorLockSts();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_DCU_2_DoorLockSts();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_DCU_2_DoorLockSts();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_RearLeft_DoorLockSts(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_DCU_3_DoorLockSts();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_DRIVER:
        case HWCONFIG_PASSENGER:
        case HWCONFIG_REAR_RIGHT:
        {

        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_RearRight_DoorLockSts(uint8 * value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        case HWCONFIG_PASSENGER:
        case HWCONFIG_REAR_LEFT:
        {

        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_DCU_4_DoorLockSts();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

void Signals_Set_WindowControl_Passenger(const uint8 *value)
{
    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_DR_update_direct_DCU_1_WdwCtrl_Pas(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        case HWCONFIG_REAR_LEFT:
        case HWCONFIG_REAR_RIGHT:
        {

        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

void Signals_Set_WindowControl_RearLeft(const uint8 *value)
{
    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_DR_update_direct_DCU_1_WdwCtrl_RL(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        case HWCONFIG_REAR_LEFT:
        case HWCONFIG_REAR_RIGHT:
        {

        } break;
        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

void Signals_Set_WindowControl_RearRight(const uint8 *value)
{
    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                CAN_DCM_DR_update_direct_DCU_1_WdwCtrl_RR(value[0]);
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        case HWCONFIG_REAR_LEFT:
        case HWCONFIG_REAR_RIGHT:
        {

        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

SIGNAL_ERROR Signals_Get_WindowControl_Passenger(uint8 *value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_DCU_1_WdwCtrl_Pas();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_DCU_1_WdwCtrl_Pas();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_DCU_1_WdwCtrl_Pas();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_DCU_1_WdwCtrl_Pas();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_WindowControl_RearLeft(uint8 *value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_DCU_1_WdwCtrl_RL();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_DCU_1_WdwCtrl_RL();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_DCU_1_WdwCtrl_RL();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_DCU_1_WdwCtrl_RL();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}

SIGNAL_ERROR Signals_Get_WindowControl_RearRight(uint8 *value)
{
    SIGNAL_ERROR return_value;

    value[0] = 0; // Dummy sentence to assign some value for missing switch cases
    return_value = SIGNAL_ERROR_NO; // Assuming signal is always valid for now (no timeout strategy yet in place)

    switch(HwConfig_Get())
    {
        case HWCONFIG_DRIVER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_DR_get_direct_DCU_1_WdwCtrl_RR();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_PASSENGER:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_PS_get_direct_DCU_1_WdwCtrl_RR();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_LEFT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RL_get_direct_DCU_1_WdwCtrl_RR();
            CALVOS_CRITICAL_EXIT();
        } break;

        case HWCONFIG_REAR_RIGHT:
        {
            CALVOS_CRITICAL_ENTER();
                value[0] = CAN_DCM_RR_get_direct_DCU_1_WdwCtrl_RR();
            CALVOS_CRITICAL_EXIT();
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return return_value;
}
