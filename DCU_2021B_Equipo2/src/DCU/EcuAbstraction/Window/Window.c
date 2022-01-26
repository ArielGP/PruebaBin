/*
 * WindowDriver.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */



#include "BasicTypes.h"
#include "Dio.h"
#include "Window.h"
#include "Adc.h"


/*Local Macro______________________________________________________________*/
#define WINDOW_ADC_COUNTS_THRESHOLD   ((ADC_VALUE)0x334)
#define WINDOW_DELAY_500MS            (50u)

#define WINDOW_SW_ACTIVE              DIO_HIGH
#define WINDOW_SW_INACTIVE            DIO_LOW

#define WINDOW_INIT_LEDS              ((PIN_VALUES)0x00u)


/*Local variable____________________________________________________________*/
static WINDOW_STATUS    Window_Status;
static WINDOW_STATUS    Window_Position;
static WINDOW_OPERATION Window_Operation;

static PIN_VALUES pins_Value = 0x00;

/*Local function def________________________________________________________*/
static void Window_Actuation(void);
static void Window_StatusDetermination(void);
static void Window_Actuation_Open(void);
static void Window_Actuation_Close(void);

/* ============================================================================
 * Function Name: Window_Init
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Window_Init(void)
{
    Window_Operation = WINDOW_OPERATION_IDLE;
    Window_Status    = WINDOW_POSITION_OPEN;
    Window_Position  = WINDOW_POSITION_OPEN;

    Dio_Write_Window_Leds( WINDOW_INIT_LEDS );
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

/* ============================================================================
 * Function Name: Window_Run
 * Description:   This runnable is execute every 10ms.
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
void Window_Run(void)
{
    /**/
    Window_Actuation();

    /* */
    Window_StatusDetermination();
}

/* ============================================================================
 * Function Name: Window_Run_Safety
 * Description:   This runnable is execute every 100ms.
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
void Window_Run_Safety(void)
{
# if (0)
    static ADC_VALUE Previous_AntiPinch_Val = 0x00u;
    ADC_VALUE AntiPinch_Val = 0x00u;

    AntiPinch_Val = Adc_Get_AntiPinch_Value();
    
    if ((WINDOW_ADC_COUNTS_THRESHOLD < AntiPinch_Val) &&
        (WINDOW_ADC_COUNTS_THRESHOLD > Previous_AntiPinch_Val))
    {
            
    }
    Previous_AntiPinch_Val = AntiPinch_Val;
# endif   
}

/* ============================================================================
 * Function Name: Window_Set_Request
 * Description:
 * Arguments:
 * Return:        None
 * ========================================================================= */
void Window_Set_Request(WINDOW_REQUEST request)
{
    if ((WINDOW_REQUEST_IDLE == request) || 
        (WINDOW_REQUEST_UP   == request) ||
        (WINDOW_REQUEST_DOWN == request))
    {
        Window_Operation = (WINDOW_OPERATION) request;
    }
}

/* ============================================================================
 * Function Name: Window_Get_Status
 * Description:   
 * Arguments:     None
 * Return:        
 * ========================================================================= */
WINDOW_STATUS Window_Get_Status(void)
{
    return Window_Status;
}

/* ============================================================================
 * Function Name: Window_Get_Operation
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
WINDOW_OPERATION Window_Get_Operation(void)
{    
    return Window_Operation;
}

/* ============================================================================
 * Function Name: Window_StatusDetermination
 * Description:
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
static void Window_StatusDetermination(void)
{
    PIN_VALUE Open_PinVal  = Dio_Read_Window_Open();
    PIN_VALUE Close_PinVal = Dio_Read_Window_Closed();

    if (WINDOW_SW_INACTIVE == Open_PinVal)
    {
        Window_Status = (WINDOW_SW_INACTIVE == Close_PinVal)? WINDOW_POSITION_OPEN : WINDOW_POSITION_ERROR;
    }
    else /* WINDOW_SW_ACTIVE == Open_PinVal */
    {
        Window_Status = (WINDOW_SW_ACTIVE == Close_PinVal)? WINDOW_POSITION_CLOSED : Window_Position;
    }
}

/* ============================================================================
 * Function Name: Window_Actuation
 * Description:   
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
static void Window_Actuation(void)
{
    static uint8 Delay_Counter = 0x00u;

    if (WINDOW_REQUEST_IDLE != Window_Operation)
    {
        if (WINDOW_DELAY_500MS <= Delay_Counter)
        {
            if (WINDOW_REQUEST_DOWN == Window_Operation)
            {
                Window_Actuation_Open();
            }
            else /* WINDOW_REQUEST_UP == Window_Operation */
            {
                Window_Actuation_Close();
            }

            /* 
             * Window operation is complete. 
             * Reset the conditions to the next request.
             * */
            Window_Operation = WINDOW_OPERATION_IDLE;
            Delay_Counter = 0x00u;
        }
        else
        {
            Delay_Counter++;
        }
    }
    else
    {
        Delay_Counter = 0x00u;
    }
}

/* ============================================================================
 * Function Name: Window_Actuation_Open
 * Description:   
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
static void Window_Actuation_Open(void)
{
    if ((WINDOW_POSITION_OPEN < Window_Position) && (WINDOW_POSITION_10 >= Window_Position))
    {
        pins_Value &= ~(0x01u << Window_Position);
        Dio_Write_Window_Leds( pins_Value );

        Window_Position--;
    }
}

/* ============================================================================
 * Function Name: Window_Actuation_Close
 * Description:
 * Arguments:     None
 * Return:        None
 * ========================================================================= */
static void Window_Actuation_Close(void)
{
    if ((WINDOW_POSITION_OPEN <= Window_Position) && (WINDOW_POSITION_10 > Window_Position))
    {
        Window_Position++;

        pins_Value |= (0x01u << Window_Position);
        Dio_Write_Window_Leds( pins_Value );
    }
}

/*End of file_______________________________________________________________*/