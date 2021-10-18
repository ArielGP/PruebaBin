/*
 * Tasks.c
 *
 *  Created on: 8 sep. 2021
 *      Author: uid87544
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* SDK includes. */
#include "sdk_project_config.h"


#include "BasicTypes.h"
#include "Window.h"
#include "Door.h"
#include "Button.h"
#include "DoorApp.h"
#include "WindowApp.h"
#include "Wdg.h"
#include "Mcu.h"
#include "Mpu.h"
#include "Adc.h"
#include "Dio.h"
#include "DcuTasks.h"

/* Local Function Prototypes */
void Tasks_StartOS(void);


/* ============================================================================
 * Function Name:app_task_100ms
 * Description:It is a periodic task task that runs each 100ms
 * Arguments: void *pvParameters
 * Return:void
 * ========================================================================= */
void app_task_100ms( void *pvParameters )
{
	TickType_t xNextWakeTime;

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{

		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, 100 );

	}
}

/* ============================================================================
 * Function Name:app_task_10ms
 * Description:It is a periodic task task that runs each 10ms
 * Arguments: void *pvParameters
 * Return:void
 * ========================================================================= */
void app_task_10ms( void *pvParameters )
{
	TickType_t xNextWakeTime;

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{

		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, 10 );

	}
}


void Tasks_StartOS(void)
{

	xTaskCreate(app_task_100ms,        "App100ms",         configMINIMAL_STACK_SIZE, NULL,  5, NULL);
	xTaskCreate(app_task_10ms,          "App10ms",         configMINIMAL_STACK_SIZE, NULL,  5, NULL);

	Mpu_Init();

	vTaskStartScheduler();

}

void init_hook(void) {

    Mcu_Init();

	Wdg_Init();

    Dio_Init();

    Adc_Init();

	Tasks_StartOS();
}
