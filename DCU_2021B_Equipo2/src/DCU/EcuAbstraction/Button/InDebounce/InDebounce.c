/*
 * Debounce.c
 *
 *  Created on: Jul 15, 2015
 *      Author: Carlos Calvillo
 */

#include "stddef.h"
#include "InDebounce.h"

ButtonRetStat_t Debounce_Process(Button_t * button, uint8_t inputState);
/* ------------------------------------------------
 * Definitions for button debouncing
 --------------------------------------------------*/
 
/* Processing Function, call cyclically and pass the pointer to the
 * button to be processed. */
ButtonRetStat_t Debounce_Process(Button_t * button, uint8_t inputState){
	ButtonRetStat_t retVal = kStatOk;
	
	/* Execute state chart */
	switch(button->state){
		case kButtonNotDebounced:
			if(inputState){
				button->debounceCounter++;
				if(button->debounceCounter > button->threshold1){
					button->state = kButtonDebouncedAt1;
#if BTTN_CFG_REACH_FLAGS
					button->reached1 = kTrue;
#endif
#if BTTN_CFG_REACH_CALLBACKS
					/* Call callback only if it is different than NULL */
					if(button->reached1Callback != NULL){
						button->reached1Callback();
					}
#endif
				}
			} else {
				/* Reset debounce counter */
				button->debounceCounter = 0;
			}
		break;
		case kButtonDebouncedAt1:
			if(inputState){
				button->debounceCounter++;
				if(button->debounceCounter > button->threshold2){
					button->state = kButtonDebouncedAt2;
#if BTTN_CFG_REACH_FLAGS
					button->reached2 = kTrue;
#endif
#if BTTN_CFG_REACH_CALLBACKS
					if(button->reached2Callback != NULL){
						button->reached2Callback();
					}
#endif
				}
			} else {
				/* Reset debounce counter */
				button->debounceCounter = 0;
				button->state = kButtonNotDebounced;
#if BTTN_CFG_RELEASE_FLAGS
				button->releasedAt1 = kTrue;
#endif
#if BTTN_CFG_RELEASE_CALLBACKS
				if(button->released1Callback != 0){
					button->released1Callback();
				}
#endif
			}
		break;
		case kButtonDebouncedAt2:
			if(!inputState){
				button->debounceCounter = 0;
				button->state = kButtonNotDebounced;
#if BTTN_CFG_RELEASE_FLAGS
				button->releasedAt2 = kTrue;
#endif
#if BTTN_CFG_RELEASE_CALLBACKS
				if(button->released2Callback != 0){
					button->released2Callback();
				}
#endif
			}
		break;
		default:
			retVal = kStatNotOk;
	}
	
	return(retVal);
}

/* -------- End Of Button Definitions -------------*/
