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


	#ifdef TEST
	uint8_t btn_state = 0;
	PIN_VALUE openbtn, closebtn;
	#endif
	#ifdef TEST2
	PIN_VALUES led_data;
	uint8_t leds_state = 0;
	#endif
	#ifdef TEST3
	uint8_t btn_state = 0;
	BUTTON_STATUS openbtn, closebtn;
	#endif

/*Local Macros______________________________________________________________*/
#define app_10ms_TASK_PRIORITY        ( tskIDLE_PRIORITY + 5u )
#define app_100ms_TASK_PRIORITY       ( tskIDLE_PRIORITY + 4u )

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
		Button_Run();

		#ifdef TEST
		switch(btn_state)
		{
			case 0:
			openbtn = Dio_Read_WindowOpen_Button();
			if(openbtn == DIO_HIGH)
			{
				Dio_Write_DoorLock_Led(DIO_HIGH);
				Dio_Write_DoorUnlock_Led(DIO_LOW);
				btn_state = 1;
			}
			else
			{
				Dio_Write_DoorLock_Led(DIO_LOW);
				Dio_Write_DoorUnlock_Led(DIO_HIGH);
			}
			break;

			case 1:
			closebtn = Dio_Read_WindowClose_Button();
			if(closebtn == DIO_HIGH)
			{
				Dio_Write_DoorLock_Led(DIO_LOW);
				Dio_Write_DoorUnlock_Led(DIO_HIGH);
				btn_state = 1;
			}
			break;

			default:
				btn_state = 0;
				break;
		}
		#endif

		#ifdef TEST2
		switch(leds_state)
		{
			case 0:
				led_data = 0x3FF;
				Dio_Write_Window_Leds(led_data);
				leds_state = 1;
				break;

			case 1:

				break;

			default:
				leds_state = 0;
				break;
		}
		#endif
		#ifdef TEST3
		switch(btn_state)
		{
			case 0:
			openbtn = Button_Get_Window_Open();
			if(openbtn == BUTTON_PRESSED)
			{
				Dio_Write_DoorLock_Led(DIO_HIGH);
				btn_state = 1;
			}
			else if(openbtn == BUTTON_LONG_PRESSED)
			{
				Dio_Write_DoorUnlock_Led(DIO_HIGH);
				btn_state = 1;
			}
			break;

			case 1:
			closebtn = Dio_Read_WindowClose_Button();
			if(closebtn == BUTTON_PRESSED)
			{
				Dio_Write_DoorLock_Led(DIO_LOW);
				btn_state = 0;
			}
			if(closebtn == BUTTON_LONG_PRESSED)
			{
				Dio_Write_DoorUnlock_Led(DIO_LOW);
				btn_state = 0;
			}
			break;

			default:
				btn_state = 0;
				break;
		}
		#endif
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, 10 );

	}
}


void Tasks_StartOS(void)
{

	(void) xTaskCreate(app_task_100ms,  "App100ms",         configMINIMAL_STACK_SIZE, NULL,  app_100ms_TASK_PRIORITY, NULL);
	(void) xTaskCreate(app_task_10ms,    "App10ms",         configMINIMAL_STACK_SIZE, NULL,  app_10ms_TASK_PRIORITY,  NULL);

	Mpu_Init();

	vTaskStartScheduler();

}

void init_hook(void) {

    Mcu_Init();

	Wdg_Init();

    Dio_Init();

    Adc_Init();

    Button_Init();

	Tasks_StartOS();
}


