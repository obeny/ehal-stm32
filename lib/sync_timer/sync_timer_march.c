/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*!
 * \file sync_timer_march.c
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 03.01.2014
 * \version 1
 *
 * \brief Timer for event loop synchronization - architecture specific implementation.
 * \note
 * For detailed description see header file.
 */

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include <string.h>

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "core_cm3.h"

#include "config.h"
#include "lib_mcu_noarch/sync_timer/sync_timer.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

// variables declaration
#ifdef SYNC_TIMER_JIFFIES
volatile UINT32 jiffies;
#endif // SYNC_TIMER_JIFFIES
extern volatile UINT8 ui8_sync_timer_overflow;
extern volatile tick_type_t ticks;
extern volatile UINT16 aui16_timers[];

extern volatile UINT16 ui16_usart0_timeout;
extern volatile UINT16 ui16_usart1_timeout;


/***************************************************************************
 *	FUNCTIONS
 ***************************************************************************/

// --------------------------------------------------------------------------
// timer interrupt handler
VOID SysTick_Handler(void);
VOID SysTick_Handler(void)
{
	// increment systick overflows counter
	++ticks;
#ifdef SYNC_TIMER_JIFFIES
	++jiffies;
#endif // SYNC_TIMER_JIFFIES

#ifdef USART0_USE_TIMER
	++ui16_usart0_timeout;
#endif // USART0_USE_TIMER
#ifdef USART1_USE_TIMER
	++ui16_usart1_timeout;
#endif // USART1_USE_TIMER
#ifdef SYNC_TIMER_EXT_HANDLER
	syncTimerExtHandler(ticks);
#endif // SYNC_TIMER_EXT_HANDLER
}

// --------------------------------------------------------------------------
VOID syncTimerInit(void)
{
	RCC_ClocksTypeDef rcc_clocks;
	RCC_GetClocksFreq(&rcc_clocks);
	SysTick_Config(rcc_clocks.HCLK_Frequency / 1000);

	// ensure that timers were reseted properly
	memset((void*)&aui16_timers[0], 0x00, (sizeof(UINT16) * SYNC_TIMER_TIMERS));
}

// END
