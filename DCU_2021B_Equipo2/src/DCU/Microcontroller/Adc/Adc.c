/*
 * ADC.c
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#include "BasicTypes.h"
#include "Adc.h"


ASIL_A_VAR_NOINIT static ADC_VALUE  Adc_AntiPinch;

void Adc_Init(void)
{
	Adc_AntiPinch = ADC_MIN;
}

//100 ms
void Adc_Run(void)
{

}


ADC_VALUE Adc_Get_AntiPinch_Value(void)
{
	return Adc_AntiPinch;
}


