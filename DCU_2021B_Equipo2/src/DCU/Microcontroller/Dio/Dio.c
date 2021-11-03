/*
 * Dio.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#include "BasicTypes.h"
#include "Dio.h"
#include "sdk_project_config.h"

/*Local Macro_______________________________________________________________*/

/*Local function def________________________________________________________*/
static PIN_VALUE Dio_Get_WindowLED(PIN_VALUES windowLED, PIN_VALUES values);
static PIN_VALUE Dio_Read_Pin(const GPIO_Type * const base, pins_channel_type_t pin);

/* ============================================================================
 * Function Name: Dio_Init
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Dio_Init(void)
{
    /* Init IO HAL */
    PINS_DRV_Init( NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0 );

    Dio_Write_DoorUnlock_Led( DIO_HIGH );
    Dio_Write_DoorLock_Led( DIO_HIGH );
}

/* ============================================================================
 * Function Name:
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Dio_Write_DoorUnlock_Led(PIN_VALUE value)
{
    PINS_DRV_WritePin(DOOR_UNLOCKED_PORT, DOOR_UNLOCKED_PIN, value);
}

/* ============================================================================
 * Function Name:
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Dio_Write_DoorLock_Led(PIN_VALUE value)
{
    PINS_DRV_WritePin(DOOR_LOCKED_PORT, DOOR_LOCKED_PIN, value);
}

/* ============================================================================
 * Function Name: Dio_Write_Window_Leds
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void Dio_Write_Window_Leds(PIN_VALUES values)
{
    PINS_DRV_WritePin(WINDOW_LED1_PORT,  WINDOW_LED1_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED1,  values));
    PINS_DRV_WritePin(WINDOW_LED2_PORT,  WINDOW_LED2_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED2,  values));
    PINS_DRV_WritePin(WINDOW_LED3_PORT,  WINDOW_LED3_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED3,  values));
    PINS_DRV_WritePin(WINDOW_LED4_PORT,  WINDOW_LED4_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED4,  values));
    PINS_DRV_WritePin(WINDOW_LED5_PORT,  WINDOW_LED5_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED5,  values));
    PINS_DRV_WritePin(WINDOW_LED6_PORT,  WINDOW_LED6_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED6,  values));
    PINS_DRV_WritePin(WINDOW_LED7_PORT,  WINDOW_LED7_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED7,  values));
    PINS_DRV_WritePin(WINDOW_LED8_PORT,  WINDOW_LED8_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED8,  values));
    PINS_DRV_WritePin(WINDOW_LED9_PORT,  WINDOW_LED9_PIN,  Dio_Get_WindowLED(DIO_WINDOW_LED9,  values));
    PINS_DRV_WritePin(WINDOW_LED10_PORT, WINDOW_LED10_PIN, Dio_Get_WindowLED(DIO_WINDOW_LED10, values));
}

/* ============================================================================
 * Function Name: Dio_Read_DoorUnlock
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_DoorUnlock(void)
{
    return Dio_Read_Pin(SW_DOOR_UNLOCKED_PORT, SW_DOOR_UNLOCKED_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_DoorLock
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_DoorLock(void)
{
    return Dio_Read_Pin(SW_DOOR_LOCKED_PORT, SW_DOOR_LOCKED_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_Window_Open
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_Window_Open(void)
{
    return Dio_Read_Pin(SW_WINDOW_OPEN_PORT, SW_WINDOW_OPEN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_Window_Closed
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_Window_Closed(void)
{
    return Dio_Read_Pin(SW_WINDOW_CLOSE_PORT, SW_WINDOW_CLOSE_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_DoorLock_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_DoorLock_Button(void)
{
    return Dio_Read_Pin(LOCK_BTN_PORT, LOCK_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_DoorUnlock_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_DoorUnlock_Button(void)
{
    return Dio_Read_Pin(UNLOCK_BTN_PORT, UNLOCK_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_WindowOpen_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_WindowOpen_Button(void)
{
    return Dio_Read_Pin(OPEN_BTN_PORT, OPEN_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_WindowClose_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_WindowClose_Button(void)
{
    return Dio_Read_Pin(CLOSE_BTN_PORT, CLOSE_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_PassengerWindowOpen_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_PassengerWindowOpen_Button(void)
{    
    return Dio_Read_Pin(PASSENGER_OPEN_BTN_PORT, PASSENGER_OPEN_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_PassengerWindowClose_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_PassengerWindowClose_Button(void)
{    
    return Dio_Read_Pin(PASSENGER_CLOSE_BTN_PORT, PASSENGER_CLOSE_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_RearLeftWindowOpen_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_RearLeftWindowOpen_Button(void)
{
    return Dio_Read_Pin(REARLEFT_OPEN_BTN_PORT, REARLEFT_OPEN_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_RearLeftWindowClose_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_RearLeftWindowClose_Button(void)
{    
    return Dio_Read_Pin(REARLEFT_CLOSE_BTN_PORT, REARLEFT_CLOSE_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_RearRightWindowOpen_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_RearRightWindowOpen_Button(void)
{
    return Dio_Read_Pin(REARRIGHT_OPEN_BTN_PORT, REARRIGHT_OPEN_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_RearRightWindowClose_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_RearRightWindowClose_Button(void)
{
    return Dio_Read_Pin(REARRIGHT_CLOSE_BTN_PORT, REARRIGHT_CLOSE_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_RearWindowLock_Button
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_RearWindowLock_Button(void)
{
    return Dio_Read_Pin(REAR_WINDOW_LOCK_BTN_PORT, REAR_WINDOW_LOCK_BTN_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_Jumper0
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_Jumper0(void)
{
    return Dio_Read_Pin(SW_VARIANT_0_PORT, SW_VARIANT_0_PIN);
}

/* ============================================================================
 * Function Name: Dio_Read_Jumper1
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
PIN_VALUE Dio_Read_Jumper1(void)
{
    return Dio_Read_Pin(SW_VARIANT_1_PORT, SW_VARIANT_1_PIN);
}

/* ============================================================================
 * Function Name: Dio_Get_WindowLED
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static PIN_VALUE Dio_Get_WindowLED(PIN_VALUES windowLED, PIN_VALUES values)
{
    PIN_VALUE pinValue = DIO_LOW;
    pinValue = ((values & windowLED) != 0x00u)? DIO_HIGH : DIO_LOW;

    return pinValue;
}

/* ============================================================================
 * Function Name: Dio_Read_Pin
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static PIN_VALUE Dio_Read_Pin(const GPIO_Type * const base, pins_channel_type_t pin)
{
    PIN_VALUE pinValue = DIO_LOW;
    uint16_t portValue = 0x0000UL;

    portValue = PINS_DRV_ReadPins(base);
    pinValue = ((portValue & (1u << pin)) != 0x0000UL)? DIO_HIGH : DIO_LOW;

    return pinValue;
}

/*End of file_______________________________________________________________*/
