/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*!
 * \file adc_march.c
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 04.01.2014
 * \version 1
 *
 * \brief Analog-to-Digital converter control library using polling - architecture specific implementation
 * \note
 * For detailed description see header file.
 */

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"

#include "config.h"
#include "ehal/global.h"
#include "ehal/adc/adc.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

static UINT32 prescaler_reg[] = {RCC_PCLK2_Div2, RCC_PCLK2_Div4, RCC_PCLK2_Div6, RCC_PCLK2_Div8};


/***************************************************************************
 *	FUNCTIONS
 ***************************************************************************/

// --------------------------------------------------------------------------
void adcInit(const UINT8 ui8_reference, const UINT8 ui8_prescaler)
{
	ADC_InitTypeDef adc;

	// suppress compiler complaints
	(void)ui8_reference;

	// configure ADC clock (must not exceed 14MHz)
	RCC_ADCCLKConfig(prescaler_reg[ui8_prescaler]);
	RCC_APB2PeriphClockCmd(ADC_RCC, ENABLE);

	// reset current settings
	ADC_DeInit(ADC_PERIPH);
	
	ADC_StructInit(&adc);
	adc.ADC_Mode = ADC_Mode_Independent;
	adc.ADC_ScanConvMode = DISABLE;
	adc.ADC_ContinuousConvMode = DISABLE;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_NbrOfChannel = 1;
	ADC_Init(ADC_PERIPH, &adc);
	ADC_Cmd(ADC_PERIPH, ENABLE);

	// perform calibration, not needed but it don't hurt
	ADC_ResetCalibration(ADC_PERIPH);
  	WAIT_FOR(ADC_GetResetCalibrationStatus(ADC_PERIPH));
	ADC_StartCalibration(ADC_PERIPH);
	WAIT_FOR(ADC_GetCalibrationStatus(ADC_PERIPH));
}

// --------------------------------------------------------------------------
void adcOff(void)
{
	ADC_Cmd(ADC_PERIPH, DISABLE);
}

// --------------------------------------------------------------------------
void adcSetChannel(const UINT8 ui8_ch)
{
	ADC_RegularChannelConfig(ADC_PERIPH, ui8_ch, 1, ADC_SAMPLE_TIME);
}

// --------------------------------------------------------------------------
void adcStart(void)
{
	ADC_SoftwareStartConvCmd(ADC_PERIPH, ENABLE);
}

// --------------------------------------------------------------------------
BOOL adcConversionIsComplete(void)
{
	return (ADC_GetFlagStatus(ADC_PERIPH, ADC_FLAG_EOC) == RESET);
}

// --------------------------------------------------------------------------
UINT16 adcResult(void)
{
	return (ADC_GetConversionValue(ADC_PERIPH));
}

// END
