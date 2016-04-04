/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*!
 * \file init.c
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 04.02.2016
 * \version 1
 *
 * \brief Performs a low level CPU initialization after c-code startup - implementation.
 * \note
 * For detailed description see header file.
 */

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "stm32f10x_flash.h"
#include "stm32f10x_rcc.h"

#include "config.h"
#include "ehal/global.h"

#include "lib/init/init.h"

/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

// --------------------------------------------------------------------------
VOID init(void)
{
	// reset rcc
	RCC_DeInit();

#if (defined MCK_USE_XTAL || defined MCK_USE_PLL)
	// enable external resonator
	RCC_HSEConfig(RCC_HSE_ON);
	// wait for clock stabilisation
	RCC_WaitForHSEStartUp();
#endif

#ifdef MCK_USE_PLL
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	
	// set flash wait state
#if (F_CPU < 24000000UL)
	FLASH_SetLatency(FLASH_Latency_0);
#elif (F_CPU >= 24000000UL) && (F_CPU < 48000000UL)
	FLASH_SetLatency(FLASH_Latency_1);
#elif (F_CPU >= 48000000)
	FLASH_SetLatency(FLASH_Latency_2);
#endif
	
	// HCLK = SYSCLK (use max base speed for )
	RCC_HCLKConfig(RCC_SYSCLK_Div1);

	// PCLK2 = HCLK
	RCC_PCLK2Config(RCC_HCLK_Div1);
	// PCLK1 = HCLK/2
	RCC_PCLK1Config(RCC_HCLK_Div2);

	// config and enable PLL
	RCC_PLLConfig(PLL_RCC_DIV, RCC_PLLMul_9);
	RCC_PLLCmd(ENABLE);

	// wait for PLL ready
	WAIT_FOR(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	// switch system clock source to PLL
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	// wait for PLL as system clock source
	WAIT_FOR(RCC_GetSYSCLKSource() != 0x08);
#endif // MCK_USE_PLL
}

// END
