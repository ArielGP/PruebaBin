/*
 * WindowHandler.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
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
}WindowApp_t;

typedef enum
{
    eNOT_WINDOW_ACTUATION,
    eOPEN_WINDOW_ACTUATION,
    eGLOBAL_OPEN_WINDOW_ACTUATION,
    eCLOSE_WINDOW_ACTUATION,
    eGLOBAL_CLOSE_WINDOW_ACTUATION,
    eCANCEL_WINDOW_ACTUATION
}WindowApp_Actuation_t;

/*Local Macro______________________________________________________________*/
#define WINDOW_CTRL_SIGNAL_LEN           (0x03u)

/*Local const_______________________________________________________________*/
const WindowApp_t * const WinCtrlSignal_table [WINDOW_CTRL_SIGNAL_LEN] =
{
    {.SetSignal_WindowControl = Signals_Set_WindowControl_Passenger, 
     .GetButton_WindowOpen    = Button_Get_PassengerWindow_Open,
     .GetButton_WindowClose   = Button_Get_PassengerWindow_Close
    },
    {.SetSignal_WindowControl = Signals_Set_WindowControl_RearLeft, 
     .GetButton_WindowOpen    = Button_Get_RearLeftWindow_Open,
     .GetButton_WindowClose   = Button_Get_RearLeftWindow_Close
    },
    {.SetSignal_WindowControl = Signals_Set_WindowControl_RearRight, 
     .GetButton_WindowOpen    = Button_Get_RearRightWindow_Open,
     .GetButton_WindowClose   = Button_Get_RearRightWindow_Close
    }
};

/*Local variable____________________________________________________________*/
static WINDOW_STATUS    Window_Position;
static WINDOW_OPERATION Window_Operation;
static WINDOW_REQUEST   Window_ReqOperation;


static boolean RearLeftRightOnly;
static WindowApp_Actuation_t Window_Actuation;
static uint8 WinOp_SigVal;


/*Local function def________________________________________________________*/
static WindowApp_Actuation_t WindowApp_ManualMode (void);
static WindowApp_Actuation_t WindowApp_RemoteMode (void);
static WindowApp_Actuation_t WindowApp_GetOpenActuation (BUTTON_STATUS buttonSts);
static WindowApp_Actuation_t WindowApp_GetCloseActuation(BUTTON_STATUS buttonSts);
static void WindowApp_ReportWindowControlSignals(void);
static void WindowApp_ReportRearWindowLockSignal(void);



/* ============================================================================
 * Function Name: WindowApp_Init
 * Description:   This runnable is only called during initalization time.
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
void WindowApp_Init(void)
{
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
    uint8 rearWinLock_SigVal;

    Window_Position  = Window_Get_Status();
    Window_Operation = Window_Get_Operation();

    /* */
    if ((eGLOBAL_CLOSE_WINDOW_ACTUATION != Window_Actuation) && (eGLOBAL_CLOSE_WINDOW_ACTUATION != Window_Actuation))
    {

        Window_Actuation = WindowApp_ManualMode();

        if (eNOT_WINDOW_ACTUATION == Window_Actuation)
        {
            Window_Actuation = WindowApp_RemoteMode();
        }

        if (HWCONFIG_DRIVER == HwConfig_Get())
        {
            WindowApp_ReportWindowControlSignals();
            WindowApp_ReportRearWindowLockSignal();
        }
    }


    /**/
    if ( WINDOW_POSITION_ERROR != Window_Position)
    {
        if (WINDOW_POSITION_OPEN == Window_Position)
        {
            if ((eOPEN_WINDOW_ACTUATION == Window_Actuation) || (eGLOBAL_OPEN_WINDOW_ACTUATION == Window_Actuation))
            {
                Window_Actuation = eCANCEL_WINDOW_ACTUATION;
            }
        }
        else if (WINDOW_POSITION_CLOSED == Window_Position)
        {
            if ((eCLOSE_WINDOW_ACTUATION == Window_Actuation) || (eGLOBAL_CLOSE_WINDOW_ACTUATION == Window_Actuation))
            {
                Window_Actuation = eCANCEL_WINDOW_ACTUATION;
            }
        }
        else
        {
            /* Avoid Misra - No action required */
        }
    }
    else
    {
        Window_Actuation = eCANCEL_WINDOW_ACTUATION;
    }





    switch (Window_Actuation)
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
        {
            WinOp_SigVal        = WINDOWOP_IDLE;
            Window_ReqOperation = WINDOW_REQUEST_IDLE;
        } break;
        default:
            break;
    }

    Window_Set_Request(Window_ReqOperation);
    Signals_Set_WindowOp(&WinOp_SigVal);
}

/* ============================================================================
 * Function Name: WindowApp_ManualMode
 * Description:   
 * Arguments:     None
 * Return:        
 * ========================================================================= */
static WindowApp_Actuation_t WindowApp_ManualMode(void)
{
    BUTTON_STATUS openButtonSts    = Button_Get_Window_Open();
    BUTTON_STATUS closeButtonSts   = Button_Get_Window_Close();
    uint8 rearWinLock_SigVal       = REARWINDOWLOCK_BLOCK;
    WindowApp_Actuation_t retValue = eNOT_WINDOW_ACTUATION;
    
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

    return retValue;
}

/* ============================================================================
 * Function Name: WindowApp_RemoteMode
 * Description:   
 * Arguments:     None
 * Return:        
 * ========================================================================= */
static WindowApp_Actuation_t WindowApp_RemoteMode(void)
{
    uint8 confortCmd_SigVal;
    WindowApp_Actuation_t retValue = eNOT_WINDOW_ACTUATION;

    (void)Signals_Get_ConfortCmd(&confortCmd_SigVal);
    (void)Signals_Get_WindowControl_Passenger(&confortCmd_SigVal);
    (void)Signals_Get_WindowControl_RearLeft(&confortCmd_SigVal);
    (void)Signals_Get_WindowControl_RearRight(&confortCmd_SigVal);

    switch (confortCmd_SigVal)
    {
        case CONFORTCMD_NO:
        {
            retValue = eCANCEL_WINDOW_ACTUATION;
        } break;

        case CONFORTCMD_LOCK:
        {
            retValue = eCLOSE_WINDOW_ACTUATION;

        } break;
    
        case CONFORTCMD_UNLOCK_ALL:
        {
            retValue = eOPEN_WINDOW_ACTUATION;
        } break;

        default:
        {
        } break;
    }

    return retValue;
}

/* ============================================================================
 * Function Name: 
 * Description:   
 * Arguments:     None
 * Return:        
 * ========================================================================= */
static WindowApp_Actuation_t WindowApp_GetOpenActuation(BUTTON_STATUS buttonSts)
{
    WindowApp_Actuation_t retValue = eNOT_WINDOW_ACTUATION;

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
 * Function Name: 
 * Description:   
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
static WindowApp_Actuation_t WindowApp_GetCloseActuation(BUTTON_STATUS buttonSts)
{
    WindowApp_Actuation_t retValue = eNOT_WINDOW_ACTUATION;

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
 * Function Name: 
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
    
    for(index =0x00u; (WINDOW_CTRL_SIGNAL_LEN > index); index++)
    {
        openButtonSts  = WinCtrlSignal_table[index]->GetButton_WindowOpen();
        closeButtonSts = WinCtrlSignal_table[index]->GetButton_WindowClose();

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

        WinCtrlSignal_table[index]->SetSignal_WindowControl(&signalVal);
    }
}

/* ============================================================================
 * Function Name: 
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