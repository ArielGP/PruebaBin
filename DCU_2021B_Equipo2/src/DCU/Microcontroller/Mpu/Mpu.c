/*
 * Mpu.c
 *
 *  Created on: 3 ago. 2021
 *      Author: uid87544
 */
#include "BasicTypes.h"
#include "Mpu.h"
#include "mpu_driver.h"
#include "peripherals_mpu_pal_config_1.h"

#define MPU_NUMBER_OF_SLAVES  4

MPU_ERROR_VAR_NOINIT static mpu_access_err_info_t Mpu_ErrorInfo[MPU_NUMBER_OF_SLAVES];
MPU_ERROR_VAR_NOINIT uint32 MPU_CodeSourceAddress;

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

	S32_SCB->ACTLR |= S32_SCB_ACTLR_DISDEFWBUF_MASK;

	/*enable MemFault Handler and BusFault handler exceptions */
	S32_SCB->SHCSR |= (S32_SCB_SHCSR_MEMFAULTENA_MASK | S32_SCB_SHCSR_BUSFAULTENA_MASK);
    /*set priorities     reserved : Usage : BusFault: MemFault */
	S32_SCB->SHPR1 = 0x00020100;

	MPU_DRV_Init(0, MPU_PAL_CONFIG_1_REGION_CFG_CNT0, MPU_Cfg0);


	AIPS->PACRB    |= (AIPS_PACRB_SP5_MASK | AIPS_PACRB_WP5_MASK); // MPU only accessed in supervisor mode
	AIPS->OPACR[3] |= (AIPS_OPACR_SP3_MASK);                       // ADC0 only accessed in supervisor mode
	AIPS->OPACR[5] |= (AIPS_OPACR_SP5_MASK);                       // PORTE only accessed in supervisor mode
	AIPS->OPACR[6] |= (AIPS_OPACR_SP2_MASK);                       // WDOG only accessed in supervisor mode
	AIPS->OPACR[8] |= (AIPS_OPACR_SP4_MASK | AIPS_OPACR_WP4_MASK); // SCG only accessed in supervisor mode
	AIPS->OPACR[8] |= (AIPS_OPACR_SP5_MASK | AIPS_OPACR_WP5_MASK); // PCC only accessed in supervisor mode
	AIPS->OPACR[11] |= (AIPS_OPACR_SP5_MASK | AIPS_OPACR_WP5_MASK); // PMC only accessed in supervisor mode
	AIPS->OPACR[11] |= (AIPS_OPACR_SP6_MASK | AIPS_OPACR_WP6_MASK); // SMC only accessed in supervisor mode
	AIPS->OPACR[11] |= (AIPS_OPACR_SP7_MASK );                      // RCM only accessed in supervisor mode


}



void Mpu_StoreError(uint32 * pulParam)
{
	uint8 slave;

	/* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR */
	MPU_CodeSourceAddress = pulParam[6];

	for(slave = 0; slave < MPU_NUMBER_OF_SLAVES; slave++)
	{
	    MPU_DRV_GetDetailErrorAccessInfo(0, slave, &Mpu_ErrorInfo[slave]);
	}

}
