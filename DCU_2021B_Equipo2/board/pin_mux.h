#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "pins_driver.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*! @brief Definitions/Declarations for BOARD_InitPins Functional Group */
/*! @brief User definition pins */
#define DOOR_UNLOCKED_PORT    PTD
#define DOOR_UNLOCKED_PIN     16U
#define DOOR_LOCKED_PORT    PTD
#define DOOR_LOCKED_PIN     15U
#define WINDOW_LED6_PORT    PTC
#define WINDOW_LED6_PIN     0U
#define REARLEFT_CLOSE_BTN_PORT    PTE
#define REARLEFT_CLOSE_BTN_PIN     9U
#define REARLEFT_OPEN_BTN_PORT    PTE
#define REARLEFT_OPEN_BTN_PIN     0U
#define REARRIGHT_OPEN_BTN_PORT    PTC
#define REARRIGHT_OPEN_BTN_PIN     5U
#define OPEN_BTN_PORT    PTC
#define OPEN_BTN_PIN     12U
#define CLOSE_BTN_PORT    PTC
#define CLOSE_BTN_PIN     13U
#define SW_WINDOW_CLOSE_PORT    PTD
#define SW_WINDOW_CLOSE_PIN     7U
#define LOCK_BTN_PORT    PTA
#define LOCK_BTN_PIN     10U
#define SW_DOOR_LOCKED_PORT    PTD
#define SW_DOOR_LOCKED_PIN     2U
#define SW_DOOR_UNLOCKED_PORT    PTD
#define SW_DOOR_UNLOCKED_PIN     0U
#define REAR_WINDOW_LOCK_BTN_PORT    PTC
#define REAR_WINDOW_LOCK_BTN_PIN     17U
#define SW_VARIANT_1_PORT    PTD
#define SW_VARIANT_1_PIN     3U
#define SW_VARIANT_0_PORT    PTD
#define SW_VARIANT_0_PIN     1U
#define SW_WINDOW_OPEN_PORT    PTD
#define SW_WINDOW_OPEN_PIN     6U
#define WINDOW_LED1_PORT    PTD
#define WINDOW_LED1_PIN     4U
#define WINDOW_LED2_PORT    PTB
#define WINDOW_LED2_PIN     12U
#define WINDOW_LED3_PORT    PTB
#define WINDOW_LED3_PIN     0U
#define WINDOW_LED4_PORT    PTB
#define WINDOW_LED4_PIN     1U
#define WINDOW_LED5_PORT    PTA
#define WINDOW_LED5_PIN     6U
#define WINDOW_LED7_PORT    PTE
#define WINDOW_LED7_PIN     2U
#define WINDOW_LED8_PORT    PTE
#define WINDOW_LED8_PIN     6U
#define WINDOW_LED9_PORT    PTA
#define WINDOW_LED9_PIN     15U
#define WINDOW_LED10_PORT    PTA
#define WINDOW_LED10_PIN     16U
#define ANTIPINCH_SIGNAL_PORT    PTC
#define ANTIPINCH_SIGNAL_PIN     14U
#define CAN_RX_PORT    PTE
#define CAN_RX_PIN     4U
#define CAN_TX_PORT    PTE
#define CAN_TX_PIN     5U
#define PASSENGER_OPEN_BTN_PORT    PTB
#define PASSENGER_OPEN_BTN_PIN     14U
#define UNLOCK_BTN_PORT    PTB
#define UNLOCK_BTN_PIN     17U
#define PASSENGER_CLOSE_BTN_PORT    PTB
#define PASSENGER_CLOSE_BTN_PIN     15U
#define REARRIGHT_CLOSE_BTN_PORT    PTB
#define REARRIGHT_CLOSE_BTN_PIN     16U
/*! @brief User number of configured pins */
#define NUM_OF_CONFIGURED_PINS0 34
/*! @brief User configuration structure */
extern pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0];


#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

