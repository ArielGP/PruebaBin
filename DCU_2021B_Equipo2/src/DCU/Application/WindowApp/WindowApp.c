/*
 * WindowHandler.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 *
 *      History
 *      Date        Version     Author               Comment
 *      (YYMMDD)    vX.X.X
 *
 *      211109      v1.0.0      Efren Del Real       WindowApp SWC implemented
 */
#include "BasicTypes.h"
#include "WindowApp.h"
#include "Signals.h"
#include "HwConfig.h"
#include "Button.h"
#include "Window.h"

/*Local type def___________________________________________________________*/
typedef void (*Signal_set_t)(const uint8 *value);
typedef BUTTON_STATUS (*Button_Get_t) (void);

typedef struct 
{
    Signal_set_t SetSignal_WindowControl;
    Button_Get_t GetButton_WindowOpen;
    Button_Get_t GetButton_WindowClose;
}WinApp_WinCtrlDoor_t;

typedef enum
{
    eNOT_WINDOW_ACTUATION,
    eOPEN_WINDOW_ACTUATION,
    eGLOBAL_OPEN_WINDOW_ACTUATION,
    eCLOSE_WINDOW_ACTUATION,
    eGLOBAL_CLOSE_WINDOW_ACTUATION,
    eCANCEL_WINDOW_ACTUATION
}WinApp_Actuation_t;

/*Local Macro______________________________________________________________*/
#define BCM_2_CONFORCMD_TIME_REACH       (0x05u)
#define WINDOW_CTRL_DOOR_LEN             (0x03u)

/*Local const_______________________________________________________________*/
const WinApp_WinCtrlDoor_t WinCtrlDoor_table [WINDOW_CTRL_DOOR_LEN] =
{
    {
        .SetSignal_WindowControl = Signals_Set_WindowControl_Passenger,
        .GetButton_WindowOpen    = Button_Get_PassengerWindow_Open,
        .GetButton_WindowClose   = Button_Get_PassengerWindow_Close
    },
    {
        .SetSignal_WindowControl = Signals_Set_WindowControl_RearLeft,
        .GetButton_WindowOpen    = Button_Get_RearLeftWindow_Open,
        .GetButton_WindowClose   = Button_Get_RearLeftWindow_Close
    },
    {
        .SetSignal_WindowControl = Signals_Set_WindowControl_RearRight,
        .GetButton_WindowOpen    = Button_Get_RearRightWindow_Open,
        .GetButton_WindowClose   = Button_Get_RearRightWindow_Close
    }
};

/*Local variable____________________________________________________________*/
static WINDOW_REQUEST   Window_ReqOperation;

static boolean RearLeftRightOnly;
static uint8 WinOp_SigVal;
static uint8 BCM_2_Counter;

/*Local function def________________________________________________________*/
static WinApp_Actuation_t WindowApp_ManualMode (void);
static WinApp_Actuation_t WindowApp_RemoteOperation (void);
static WinApp_Actuation_t WindowApp_GetOpenActuation (BUTTON_STATUS buttonSts);
static WinApp_Actuation_t WindowApp_GetCloseActuation(BUTTON_STATUS buttonSts);
static void WindowApp_ReportWindowControlSignals(void);
static void WindowApp_ReportRearWindowLockSignal(void);
static void WindowApp_ValidateWindowActuation(WinApp_Actuation_t * const winActuationPtr);



/* ============================================================================
 * Function Name: WindowApp_Init
 * Description:   This runnable is only called during initalization time.
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
void WindowApp_Init(void)
{
    WinOp_SigVal        = WINDOWOP_IDLE;
    Window_ReqOperation = WINDOW_REQUEST_IDLE;
    BCM_2_Counter = 0x00u;

    RearLeftRightOnly = ((HWCONFIG_REAR_LEFT == HwConfig_Get()) || (HWCONFIG_REAR_RIGHT == HwConfig_Get()))? TRUE : FALSE;
}

/* ============================================================================
 * Function Name: WindowApp_Run
 * Description:   This runnable is called every 100ms.
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
void WindowApp_Run(void)
{
    static WinApp_Actuation_t prevWinActuation = eNOT_WINDOW_ACTUATION;
    WinApp_Actuation_t winActuation = eNOT_WINDOW_ACTUATION;
    
    /* */
     winActuation = WindowApp_ManualMode();

    /* */
     if (eNOT_WINDOW_ACTUATION == winActuation)
    {
        winActuation = WindowApp_RemoteOperation();
    }

    if ((eGLOBAL_CLOSE_WINDOW_ACTUATION == prevWinActuation) || (eGLOBAL_CLOSE_WINDOW_ACTUATION == prevWinActuation))
    {
        /* 
         *Global actuation will stop whether window is considered either COMPLETY_OPEN or COMPLETY_CLOSE 
        */
        winActuation = prevWinActuation;
    }

    WindowApp_ValidateWindowActuation(&winActuation);

    switch (winActuation)
    {
        case eOPEN_WINDOW_ACTUATION:
        case eGLOBAL_OPEN_WINDOW_ACTUATION:
        {
            WinOp_SigVal        = WINDOWOP_DOWN;
            Window_ReqOperation = WINDOW_REQUEST_DOWN;
        } break;
        
        case eCLOSE_WINDOW_ACTUATION:
        case eGLOBAL_CLOSE_WINDOW_ACTUATION:
        {
            WinOp_SigVal        = WINDOWOP_UP;
            Window_ReqOperation = WINDOW_REQUEST_UP;

        } break;

        case eCANCEL_WINDOW_ACTUATION:
        case eNOT_WINDOW_ACTUATION:
        {
            WinOp_SigVal        = WINDOWOP_IDLE;
            Window_ReqOperation = WINDOW_REQUEST_IDLE;
        } break;
        default:
            break;
    }

    prevWinActuation = winActuation;

    Window_Set_Request(Window_ReqOperation);
    Signals_Set_WindowOp(&WinOp_SigVal);
}

/* ============================================================================
 * Function Name: WindowApp_ManualMode
 * Description:   All Doors are allowed to execute manual Window Control from 
 *                its corresponding OPEN_BTN and CLOSE_BTN states.
 * 
 * Arguments:     None
 * Return:        
 * ========================================================================= */
static WinApp_Actuation_t WindowApp_ManualMode(void)
{
    BUTTON_STATUS openButtonSts    = Button_Get_Window_Open();
    BUTTON_STATUS closeButtonSts   = Button_Get_Window_Close();
    uint8 rearWinLock_SigVal       = REARWINDOWLOCK_BLOCK;
    WinApp_Actuation_t retValue = eNOT_WINDOW_ACTUATION;
    
    if (TRUE == RearLeftRightOnly)
    {
        (void)Signals_Get_RearWindowLock(&rearWinLock_SigVal);
    }

    if (BUTTON_NOT_PRESSED != openButtonSts)
    {
        if (FALSE == RearLeftRightOnly)
        {
            retValue = WindowApp_GetOpenActuation(openButtonSts);
        }
        else /* TRUE == RearLeftRightOnly */
        {
            if (REARWINDOWLOCK_UNBLOCK == rearWinLock_SigVal)
            {
                retValue = WindowApp_GetOpenActuation(openButtonSts);
            }
        }
    }
    else if (BUTTON_NOT_PRESSED != closeButtonSts)
    {
        if (FALSE == RearLeftRightOnly)
        {
            retValue = WindowApp_GetCloseActuation(closeButtonSts);
        }
        else /* TRUE == RearLeftRightOnly */
        {
            if (REARWINDOWLOCK_UNBLOCK == rearWinLock_SigVal)
            {
                retValue = WindowApp_GetCloseActuation(closeButtonSts);
            }
        }
    }
    else
    {
        /* Avoid Misra - No action required */
    }


    if (HWCONFIG_DRIVER == HwConfig_Get())
    {
        WindowApp_ReportWindowControlSignals();
        WindowApp_ReportRearWindowLockSignal();
    }

    return retValue;
}

/* ============================================================================
 * Function Name: WindowApp_RemoteOperation
 * Description:    
 * Arguments:     None
 * Return:        
 * ========================================================================= */
static WinApp_Actuation_t WindowApp_RemoteOperation(void)
{
    static uint8 prevConfortCmd_SigVal = CONFORTCMD_NO;
    uint8 confortCmd_SigVal;
    uint8 winCtrl_SigVal = WINDOWCONTROL_NO_REQ;
    WinApp_Actuation_t retValue = eNOT_WINDOW_ACTUATION;

    (void)Signals_Get_ConfortCmd(&confortCmd_SigVal);

    if (CONFORTCMD_NO == confortCmd_SigVal)
    {
        retValue = eCANCEL_WINDOW_ACTUATION;
        BCM_2_Counter = 0x00u;
    }
    else
    {
        if ((CONFORTCMD_LOCK == confortCmd_SigVal) || (CONFORTCMD_UNLOCK_ALL == confortCmd_SigVal))
        {
            if (prevConfortCmd_SigVal != confortCmd_SigVal)
            {
                BCM_2_Counter = 0x00u;
            }

            if (BCM_2_CONFORCMD_TIME_REACH < BCM_2_Counter)
            {
                retValue = (CONFORTCMD_UNLOCK_ALL == confortCmd_SigVal)? eOPEN_WINDOW_ACTUATION : eCLOSE_WINDOW_ACTUATION;
                BCM_2_Counter = 0x00u;
            }
            else
            {
                BCM_2_Counter++;
            }

            prevConfortCmd_SigVal = confortCmd_SigVal;
        }
        else /* CONFORTCMD_UNLOCK_DRIVER == confortCmd_SigVal*/
        {
            BCM_2_Counter = 0x00u;
        }
    }

    
    if (eNOT_WINDOW_ACTUATION == retValue)
    {
        switch (HwConfig_Get())
        {
            case HWCONFIG_PASSENGER:
            {
                (void)Signals_Get_WindowControl_Passenger(&winCtrl_SigVal);
            } break;

            case HWCONFIG_REAR_LEFT:
            {
                (void)Signals_Get_WindowControl_RearLeft(&winCtrl_SigVal);
            } break;

            case HWCONFIG_REAR_RIGHT:
            {
                (void)Signals_Get_WindowControl_RearRight(&winCtrl_SigVal);
            } break;

            default:
            {
                /* Avoid Misra - No action required */
            } break;
        }

        switch (winCtrl_SigVal)
        {
            case WINDOWCONTROL_NO_REQ:
            {
                retValue = eCANCEL_WINDOW_ACTUATION;
            } break;

            case WINDOWCONTROL_UP_REQ:
            {
                retValue = eCLOSE_WINDOW_ACTUATION;
            } break;

            case WINDOWCONTROL_DOWN_REQ:
            {
                retValue = eOPEN_WINDOW_ACTUATION;
            } break;
        
            default:
            {
                /* Avoid Misra - No action required */
            } break;
        }
    }

    return retValue;
}

/* ============================================================================
 * Function Name: WindowApp_GetOpenActuation
 * Description:   
 * Arguments:     None
 * Return:        
 * ========================================================================= */
static WinApp_Actuation_t WindowApp_GetOpenActuation(BUTTON_STATUS buttonSts)
{
    WinApp_Actuation_t retValue = eNOT_WINDOW_ACTUATION;

    switch (buttonSts)
    {
        case BUTTON_PRESSED:
        {
            retValue = eGLOBAL_OPEN_WINDOW_ACTUATION;
        } break;

        case BUTTON_LONG_PRESSED:
        {
            retValue = eOPEN_WINDOW_ACTUATION;
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return retValue;
}


/* ============================================================================
 * Function Name: WindowApp_GetCloseActuation
 * Description:   
 * Arguments:     
 * Return:        None
 * ========================================================================= */
static WinApp_Actuation_t WindowApp_GetCloseActuation(BUTTON_STATUS buttonSts)
{
    WinApp_Actuation_t retValue = eNOT_WINDOW_ACTUATION;

    switch (buttonSts)
    {
        case BUTTON_PRESSED:
        {
            retValue = eGLOBAL_CLOSE_WINDOW_ACTUATION;
        } break;

        case BUTTON_LONG_PRESSED:
        {
            retValue = eCLOSE_WINDOW_ACTUATION;
        } break;

        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }

    return retValue;
}

/* ============================================================================
 * Function Name: WindowApp_ReportWindowControlSignals
 * Description:   
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
static void WindowApp_ReportWindowControlSignals(void)
{
    BUTTON_STATUS  openButtonSts;
    BUTTON_STATUS  closeButtonSts;
    uint8 signalVal;
    uint8 index;
    
    for(index =0x00u; (WINDOW_CTRL_DOOR_LEN > index); index++)
    {
        openButtonSts  = WinCtrlDoor_table[index].GetButton_WindowOpen();
        closeButtonSts = WinCtrlDoor_table[index].GetButton_WindowClose();

        if ((BUTTON_PRESSED == openButtonSts) || (BUTTON_LONG_PRESSED == openButtonSts))
        {
            signalVal = WINDOWCONTROL_UP_REQ;
        }
        else if ((BUTTON_PRESSED == closeButtonSts) || (BUTTON_LONG_PRESSED == closeButtonSts))
        {
            signalVal = WINDOWCONTROL_DOWN_REQ;
        }
        else
        {
            signalVal = WINDOWCONTROL_NO_REQ;
        }

        WinCtrlDoor_table[index].SetSignal_WindowControl(&signalVal);
    }
}

/* ============================================================================
 * Function Name: WindowApp_ReportRearWindowLockSignal
 * Description:   
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
static void WindowApp_ReportRearWindowLockSignal(void)
{
    BUTTON_STATUS  ButtonSts = Button_Get_RearWindow_Lock();
    uint8 signalVal = REARWINDOWLOCK_UNBLOCK;

    if (BUTTON_PRESSED == ButtonSts)
    {
        signalVal = REARWINDOWLOCK_BLOCK;
    }

    Signals_Set_RearWindowLock(&signalVal);
}

/* ============================================================================
 * Function Name: WindowApp_ValidateWindowActuation
 * Description:   
 * Arguments:     
 * Return:        None
 * ========================================================================= */
static void WindowApp_ValidateWindowActuation(WinApp_Actuation_t * const winActuationPtr)
{
    WINDOW_STATUS winPosition = Window_Get_Status();

    if ( WINDOW_POSITION_ERROR != winPosition)
    {
        if (WINDOW_POSITION_OPEN == winPosition)
        {
            if ((eOPEN_WINDOW_ACTUATION == winActuationPtr[0]) || (eGLOBAL_OPEN_WINDOW_ACTUATION == winActuationPtr[0]))
            {
                winActuationPtr[0] = eCANCEL_WINDOW_ACTUATION;
            }
        }
        else if (WINDOW_POSITION_CLOSED == winPosition)
        {
            if ((eCLOSE_WINDOW_ACTUATION == winActuationPtr[0]) || (eGLOBAL_CLOSE_WINDOW_ACTUATION == winActuationPtr[0]))
            {
                winActuationPtr[0] = eCANCEL_WINDOW_ACTUATION;
            }
        }
        else
        {
            /* Avoid Misra - No action required */
        }
    }
    else
    {
        winActuationPtr[0] = eCANCEL_WINDOW_ACTUATION;
    }
}

/*End of file_______________________________________________________________*/
