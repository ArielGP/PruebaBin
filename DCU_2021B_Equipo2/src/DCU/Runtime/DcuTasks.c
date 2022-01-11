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
#include "adc.h"
#include "Adc.h"
#include "Dio.h"
#include "DcuTasks.h"
#include "..\Communication\Signals\Signals.h"
#include "HwConfig.h"
#include "pins_driver.h"


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

int g_counter=0;
int g_counter2=0;
/*Local Macros______________________________________________________________*/

# if (0)
#    define ACT_3_5
#    define ACT_3_7
# endif

# if (0)
#    define ECU_DOOR_WINDOW_TEST
# endif

#define app_10ms_TASK_PRIORITY      ( tskIDLE_PRIORITY + 3u )
#define app_20ms_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2u )
#define app_100ms_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1u )

#define app_10ms_STACK_SIZE         ( configMINIMAL_STACK_SIZE + 10u )
#define app_20ms_STACK_SIZE         ( configMINIMAL_STACK_SIZE + 10u )
#define app_100ms_STACK_SIZE        ( configMINIMAL_STACK_SIZE +  0u )

#ifdef ACT_3_5
#define ACT_3_5_ANTIPINCH_LIMIT     (500UL)
#endif

/* Local Function Prototypes */
static void Tasks_StartOS(void);

static void app_task_10ms( void *pvParameters );
static void app_task_20ms( void *pvParameters );
static void app_task_100ms( void *pvParameters );
static void app_task_100ms_Safety( void *pvParameters );


void Tasks_StartOS(void)
{
	(void) xTaskCreate(app_task_10ms,    "App10ms",    app_10ms_STACK_SIZE +100,  NULL,  app_10ms_TASK_PRIORITY,  NULL);
	(void) xTaskCreate(app_task_20ms,    "App20ms",    app_20ms_STACK_SIZE,  NULL,  app_20ms_TASK_PRIORITY,  NULL);
	(void) xTaskCreate(app_task_100ms,   "App100ms",   app_100ms_STACK_SIZE, NULL,  app_100ms_TASK_PRIORITY, NULL);
	(void) xTaskCreate(app_task_100ms_Safety,   "App100ms_Safety",   app_100ms_STACK_SIZE, NULL,  3 | portPRIVILEGE_BIT, NULL);

	Mpu_Init();

	vTaskStartScheduler();
}

void init_hook(void) 
{

	Mcu_Init();

	Wdg_Init();

	Dio_Init();

	Adc_Init();
	
	Hw_Config_Init();

	Button_Init();

	Signals_Init();

    /* */
    Door_Init();

    /* */
    Window_Init();
    Window_Init_Safety();

	/* */
	WindowApp_Init();
	/* */
	DoorApp_Init();

	Tasks_StartOS();
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

		Signals_RunTx();

		Button_Run();

		/* */
        Door_Run();

        /* */
        Window_Run();

		/*
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
				btn_state = 0;
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
				//led_data = 0x3FF;
				led_data = 0x0000001F;
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
		 */
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
			else if(openbtn == BUTTON_STUCK)
			{
				Dio_Write_Window_Leds((PIN_VALUES) 0x3FF);
			}
			break;

		case 1:
			closebtn = Button_Get_Window_Close();
			if(closebtn == BUTTON_PRESSED)
			{
				Dio_Write_DoorLock_Led(DIO_LOW);
				btn_state = 0;
			}
			else if(closebtn == BUTTON_LONG_PRESSED)
			{
				Dio_Write_DoorUnlock_Led(DIO_LOW);
				btn_state = 0;
			}
			else if(closebtn == BUTTON_STUCK)
			{
				Dio_Write_Window_Leds((PIN_VALUES) 0x3FF);
			}
			break;

		default:
			btn_state = 0;
			break;
		}
#endif

		/*CAN running*/

		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, pdMS_TO_TICKS( 10u ) );

	}
}

/* ============================================================================
 * Function Name:app_task_20ms
 * Description:It is a periodic task task that runs each 20ms
 * Arguments: void *pvParameters
 * Return:void
 * ========================================================================= */
void app_task_20ms( void *pvParameters )
{
	TickType_t xNextWakeTime;

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/*CAN running*/
		Signals_RunRx();


		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, pdMS_TO_TICKS( 20u ) );

	}
}



/* ============================================================================
 * Function Name:app_task_100ms_Safety
 * Description:It is a periodic task task that runs each 100ms
 * Arguments: void *pvParameters
 * Return:void
 * ========================================================================= */
void app_task_100ms( void *pvParameters )
{
	TickType_t xNextWakeTime;

# ifdef ACT_3_5
    PIN_VALUE  DoorUnlockPin_value;
# endif

# ifdef ACT_3_7
	SIGNAL_ERROR error_code;
	uint8_t signal_value;
# endif

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		Adc_Run();

        /* */
        Window_Run_Safety();

		/* */
		WindowApp_Run();


		DoorApp_Run();


# ifdef ECU_DOOR_WINDOW_TEST

	/* NOTE: below code is just fort test */
		if (BUTTON_PRESSED == Button_Get_Window_Open())
		{
			/* test window */
			if (WINDOW_OPERATION_DOWN != Window_Get_Operation())
			{
				Window_Set_Request(WINDOW_REQUEST_DOWN);
			}
			else
			{
				Window_Set_Request(WINDOW_REQUEST_IDLE);
			}

			/* test Door */
			if (DOOR_STATUS_LOCKED != Door_Get_Status())
			{
				Door_Set_Request(DOOR_REQUEST_LOCK);
			}
		}
		else if (BUTTON_PRESSED == Button_Get_Window_Close())
		{
			/* test window */
			if (WINDOW_OPERATION_UP != Window_Get_Operation())
			{
				Window_Set_Request(WINDOW_REQUEST_UP);
			}
			else
			{
				Window_Set_Request(WINDOW_REQUEST_IDLE);
			}

			/* test Door */
			if (DOOR_STATUS_UNLOCKED != Door_Get_Status())
			{
				Door_Set_Request(DOOR_REQUEST_UNLOCK);
			}
		}
# endif



# ifdef ACT_3_5
		if (ACT_3_5_ANTIPINCH_LIMIT <= Adc_Get_AntiPinch_Value())
		{
			/* Toogle Green LED */
			DoorUnlockPin_value ^= DIO_HIGH;
		}
		else
		{
			/* Turn off Green LED */
			DoorUnlockPin_value = DIO_HIGH;
		}

		Dio_Write_DoorUnlock_Led(DoorUnlockPin_value);
# endif


# ifdef ACT_3_7
		error_code = Signals_Get_SysPwrMode(&signal_value);

		if ((SIGNAL_ERROR_NO == error_code) && (SYSPWRMODE_SNA != signal_value))
		{
			Signals_Set_WindowOp(&signal_value);
		}
# endif

		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, pdMS_TO_TICKS( 100u ) );
	}
}



/* ============================================================================
 * Function Name:app_task_100ms_Safety
 * Description:It is a periodic task task that runs each 100ms
 * Arguments: void *pvParameters
 * Return:void
 * ========================================================================= */
void app_task_100ms_Safety( void *pvParameters )
{
	TickType_t xNextWakeTime;


	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{

		g_counter++;
		g_counter2++;


		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, pdMS_TO_TICKS( 100u ) );
	}
}
