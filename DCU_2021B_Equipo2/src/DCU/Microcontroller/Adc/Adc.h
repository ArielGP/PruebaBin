/*
 * ADC.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef MICROCONTROLLER_ADC_H_
#define MICROCONTROLLER_ADC_H_


void Adc_Init(void);

//100 ms
void Adc_Run(void);

typedef uint16 ADC_VALUE;

#define ADC_MIN   ((ADC_VALUE)0)
#define ADC_MAX   ((ADC_VALUE)1023)

ADC_VALUE Adc_Get_AntiPinch_Value(void);

#endif /* MICROCONTROLLER_ADC_H_ */
