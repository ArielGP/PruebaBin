/*
 * Mpu.c
 *
 *  Created on: 3 ago. 2021
 *      Author: uid87544
 */
#include "BasicTypes.h"
#include "Mpu.h"



void MemManage_Handler(void) __attribute__((naked));
void BusFault_Handler(void) __attribute__((naked));

static void Mpu_StoreError(uint32 * pulParam);

void MemManage_Handler(void)
{
	while(1);
}


void BusFault_Handler(void)
{
	__asm volatile
	    (
	        #ifndef USE_PROCESS_STACK   /* Code should not be required if a main() is using the process stack. */
	            "	tst lr, #4						\n"
	            "	ite eq							\n"
	            "	mrseq r0, msp					\n"
	            "	mrsne r0, psp					\n"
	        #else
	            "	mrs r0, psp						\n"

	        #endif
	    	   "	bl %0							\n"
	    	   ::"i" (Mpu_StoreError) : "r0", "memory"
	    );

	while(1);
}



void Mpu_Init(void)
{


}



void Mpu_StoreError(uint32 * pulParam)
{


}
