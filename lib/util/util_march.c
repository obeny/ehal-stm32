/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*!
 * \file util_march.c
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 08.02.2016
 * \version 1
 *
 * \brief Utilities package - implementation
 * \note
 * For detailed description see header file.
 */

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "stm32f10x.h"
#include "core_cm3.h"

#include "config.h"

#include "lib_mcu_noarch/util/util.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

extern UINT32 __stack_end__;
extern UINT32 _stack_size;
extern UINT32 STACK_FILL;


/***************************************************************************
 *	FUNCTIONS
 ***************************************************************************/

// --------------------------------------------------------------------------
BOOL checkStack(UINT16 range)
{
	UINT32 stack_end = (UINT32)&__stack_end__;
	UINT32 stack_size = (UINT32)&_stack_size;
	UINT32 *stack_ptr;

	if (0 == range)
		stack_ptr = (UINT32*)(stack_end - stack_size);
	else
		stack_ptr = (UINT32*)(stack_end - range);

	return ((UINT32)&STACK_FILL != *stack_ptr);
}

// --------------------------------------------------------------------------
void __naked delayUs(volatile UINT32 us)
{
	UINT32 rep = (2 * F_CPU) / (8000000UL);

	register UINT32 r1 __asm__("r1");
	register UINT32 r2 __asm__("r2");
	register UINT32 r3 __asm__("r3");

	(void)us;
	(void)r1;
	(void)r2;
	(void)r3;

	__asm__ __volatile__("mov r2, %0" : : "r" (rep));

	__asm__ __volatile__(
		"mov r1, #0\n" \
		"mov r3, #0\n" \
		"outer_loop:\n" \
		"mov r3, #0\n" \
		"inner_loop:\n" \
		"add r3, #1\n" \
		"cmp r3, r2\n" \
		"bcc inner_loop\n" \
		"add r1, #1\n"
		"cmp r1, r0\n" \
		"bcc outer_loop\n" \
		"bx lr\n"
	);
}

// --------------------------------------------------------------------------
void delayMs(UINT16 ms)
{
	delayUs(ms * (1000UL));
}

// --------------------------------------------------------------------------
__no_return UTIL_SOFTRESET_ATTR void softReset(void)
{
	// disable interrupts
	__disable_irq();

	// perform processor reset
	NVIC_SystemReset();

	while(1);
}

// END
