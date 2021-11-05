/*
 * WindowDriver.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */



#include "BasicTypes.h"
#include "Dio.h"
#include "Signals.h"
#include "Window.h"
#include "Adc.h"


typedef enum
{
    eNOT_WINDOW_ACTUATION,
    eOPEN_WINDOW_ACTUATION,
    eGLOBAL_OPEN_WINDOW_ACTUATION,
    eCLOSE_WINDOW_ACTUATION,
    eGLOBAL_CLOSE_WINDOW_ACTUATION,
    eCANCEL_WINDOW_ACTUATION
}Window_Actuation_t;


#define WINDOW_DELAY_500MS        (50u)

#define WINDOW_SW_ACTIVE          DIO_HIGH
#define WINDOW_SW_INACTIVE        DIO_LOW

#define WINDOW_INIT_LEDS         ((PIN_VALUES)0x00)


static uint8_t Window_delay_conter;
static WINDOW_REQUEST   Window_request;
static WINDOW_STATUS    Window_status;
static WINDOW_STATUS    Window_position;
static WINDOW_OPERATION Window_operation;

static Window_pin_t     Window_pin;
static Window_Actuation_t Window_actuation_state;

PIN_VALUES pins_value = 0x00;

static void Window_Actuation(void);
static void Window_Status_Process(void);
/* ============================================================================
 * Function Name: Window_Init
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Window_Init(void)
{

    Window_actuation_state = eNOT_WINDOW_ACTUATION;

    Window_request = WINDOW_REQUEST_IDLE;
    
    Window_operation = WINDOW_OPERATION_IDLE;

    Window_delay_conter = 0u;

    Window_status = WINDOW_POSITION_OPEN;
    Window_position = WINDOW_POSITION_1;

    Dio_Write_Window_Leds(WINDOW_INIT_LEDS);
}

/* ============================================================================
 * Function Name: Window_Init_Safety
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Window_Init_Safety(void)
{

}

//10 ms
/* ============================================================================
 * Function Name: Window_Runstatic void Window_Status_Process(void)
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Window_Run(void)
{
# if(0)
    Signals_Set_WindowPos();
# endif

    /* */
    Window_Status_Process();
    
    /**/
    Window_Actuation();

    /* Sets Window Operation */
    Signals_Set_WindowOp(Window_operation);
    
}

//100 ms
/* ============================================================================
 * Function Name: Window_Run_Safety
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Window_Run_Safety(void)
{

}

/* ============================================================================
 * Function Name: Window_Set_Request
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Window_Set_Request(WINDOW_REQUEST request)
{
    if ((WINDOW_REQUEST_IDLE == request) || 
        (WINDOW_REQUEST_UP == request) ||
        (WINDOW_REQUEST_DOWN == request))
    {
        Window_request = request;
    }
}

/* ============================================================================
 * Function Name: Window_Get_Status
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
WINDOW_STATUS Window_Get_Status(void)
{
    return Window_status;
}

/* ============================================================================
 * Function Name: Window_Get_Operation
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
WINDOW_OPERATION Window_Get_Operation(void)
{    
    return Window_operation;
}

/* ============================================================================
 * Function Name: 
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static void Window_Status_Process(void)
{
    PIN_VALUE Window_pinOpen  = Dio_Read_Window_Open();
    PIN_VALUE Window_pinClose = Dio_Read_Window_Closed();

    if (WINDOW_SW_INACTIVE == Window_pinOpen)
    {
        Window_status = (WINDOW_SW_INACTIVE == Window_pinOpen)? WINDOW_POSITION_OPEN : WINDOW_POSITION_ERROR;
    }
    else
    /* WINDOW_SW_ACTIVE == Window_pinOpen */
    {
        Window_status = (WINDOW_SW_ACTIVE == Window_pinClose)? WINDOW_POSITION_CLOSED : Window_position;
    }
}

/* ============================================================================
 * Function Name: 
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static void Window_Actuation(void)
{
    if (WINDOW_DELAY_500MS > Window_delay_conter)
    {
        Window_delay_conter = 0x00u;

        if ((WINDOW_POSITION_OPEN != Window_status) && (WINDOW_POSITION_ERROR != Window_status))
        {
            Window_actuation_state = eOPEN_WINDOW_ACTUATION;
        }
        else if ((WINDOW_POSITION_CLOSED != Window_status) && (WINDOW_POSITION_ERROR != Window_status))
        {
            Window_actuation_state = eCLOSE_WINDOW_ACTUATION;
        }
        else if (((WINDOW_POSITION_CLOSED == Window_status) && (eGLOBAL_CLOSE_WINDOW_ACTUATION == Window_actuation_state)) ||
                ((WINDOW_POSITION_OPEN == Window_status) && (eGLOBAL_OPEN_WINDOW_ACTUATION == Window_actuation_state)))
        {
            Window_actuation_state = eCANCEL_WINDOW_ACTUATION;
        }

    }
    else
    {
        Window_delay_conter++;
    }


    switch (Window_actuation_state)
    {
        case eNOT_WINDOW_ACTUATION:
        case eCANCEL_WINDOW_ACTUATION:
        {
            Window_operation = WINDOW_OPERATION_IDLE;
        } break;

        case eOPEN_WINDOW_ACTUATION:
        case eGLOBAL_OPEN_WINDOW_ACTUATION:
        {
            Window_operation = WINDOW_OPERATION_DOWN;
        } break;

        case eCLOSE_WINDOW_ACTUATION:
        case eGLOBAL_CLOSE_WINDOW_ACTUATION:
        {
            Window_operation = WINDOW_OPERATION_UP;
        }
        default:
        {
            /* Avoid Misra - No action required */
        } break;
    }
}

/* ============================================================================
 * Function Name: 
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static void Window_Actuation_Open(void)
{
    Window_position = (WINDOW_POSITION_OPEN == Window_position)? WINDOW_POSITION_1 : Window_position;

    pins_value |= (0x01u << Window_position);
    
    Dio_Write_Window_Leds(pins_value);

    Window_position++;

    Window_position = (WINDOW_POSITION_10 <= Window_position)? WINDOW_POSITION_10 : Window_position;
    }
}

/* ============================================================================
 * Function Name: 
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static void Window_Actuation_Close(void)
{
    Window_position = (WINDOW_POSITION_10 <= Window_position)? WINDOW_POSITION_10 : Window_position;

    pins_value &= ~(0x01u << Window_position);
    
    Dio_Write_Window_Leds(pins_value);

    Window_position--;

    Window_position = (WINDOW_POSITION_OPEN <= Window_position)? WINDOW_POSITION_OPEN : Window_position;
    }
}
/*End of file_______________________________________________________________*/
