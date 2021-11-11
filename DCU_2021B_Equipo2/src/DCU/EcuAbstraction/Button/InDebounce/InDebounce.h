/*
 * app_button.h
 *
 *  Created on: Jul 15, 2015
 *      Author: Carlos Calvillo
 */

#ifndef INDEBOUNCE_H_
#define INDEBOUNCE_H_


#include <stdint.h>

#define kFalse	0
#define kTrue	1

typedef enum{
	kStatOk,
	kStatNotOk
} ButtonRetStat_t;

/* ------------------------------------------------
 * Definitions for button debouncing
 --------------------------------------------------*/
#define BTTN_CFG_REACH_CALLBACKS			1
#define BTTN_CFG_REACH_FLAGS				1
#define BTTN_CFG_RELEASE_CALLBACKS			1
#define BTTN_CFG_RELEASE_FLAGS				1

typedef void(*ButtonCallback_t)(void);
typedef uint32_t ButtonData_t;

typedef enum{
	kButtonNotDebounced,
	kButtonDebouncedAt1,
	kButtonDebouncedAt2,
	kButtonDebouncedAt3,
}ButtonState_t;

typedef struct{
	ButtonData_t threshold1;
	ButtonData_t threshold2;
	ButtonData_t threshold3;
	ButtonData_t debounceCounter;	
#if BTTN_CFG_REACH_CALLBACKS
	ButtonCallback_t reached1Callback;
	ButtonCallback_t reached2Callback;
#endif	
#if BTTN_CFG_REACH_FLAGS
	uint8_t reached1;
	uint8_t reached2;
	uint8_t reached3;
#endif
#if BTTN_CFG_RELEASE_CALLBACKS
	ButtonCallback_t released1Callback;
	ButtonCallback_t released2Callback;
#endif
#if BTTN_CFG_RELEASE_FLAGS
	uint8_t releasedAt1;
	uint8_t releasedAt2;
#endif
	ButtonState_t state;
}Button_t;

extern ButtonRetStat_t Debounce_Process(Button_t * button, uint8_t currentValue);
extern void Debounce_Init(void);

/* -------- End Of Button Definitions -------------*/

#endif /* INDEBOUNCE_H_ */
