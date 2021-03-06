/***********************************************************************************************************************
 * This file was generated by the S32 Configuration Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Configuration Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v9.0
processor: S32K144
package_id: S32K144_LQFP100
mcu_data: s32sdk_s32k1xx_rtm_402
processor_version: 0.0.0
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 33afab84-3987-42cd-bca4-67126556733a
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "peripherals_wdog_config_1.h"

/*******************************************************************************
 * wdog_config_1 initialization code
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'wdog_config_1'
- type: 'wdog'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'wdog'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'WDOG'
- config_sets:
  - wdog:
    - WDOGConfig:
      - 0:
        - name: 'WDOG_Cfg0'
        - readonly: 'true'
        - clkSource: 'WDOG_SOSC_CLOCK'
        - wait: 'false'
        - stop: 'false'
        - debug: 'false'
        - prescalerEnable: 'true'
        - updateEnable: 'false'
        - intEnable: 'false'
        - winEnable: 'false'
        - windowValue: '0'
        - timeoutValue: '6250'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variables will be used in other source files in application code.
 *
 */

    /* WDOG user configuration 0 */
const wdog_user_config_t WDOG_Cfg0 = {
    .clkSource = WDOG_SOSC_CLOCK,
    .opMode = {
        false,                   /* Wait Mode         */
        false,                   /* Stop Mode         */
        false                    /* Debug Mode        */
    },
    .updateEnable = false,
    .intEnable = false,
    .winEnable = false,
    .windowValue = 0U,
    .timeoutValue = 6250U,
    .prescalerEnable = true     /* WDOG prescaler             */
};


