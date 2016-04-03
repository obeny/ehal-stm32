/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*
	STM32F10X microcontrollers familly C-startup file for GNU compiler toolchain.

	NOTE:
	CPP_SUPPORT - enable C++ support
	VECTORS_RAM - symbol defined causes remapping of memory and places vectors in RAM
	RAM_FUNCS - functions can be copied to ram and exected from there

	Written by Marcin OBenY Benka <obeny@obeny.net>
*/

/**********************************************************************************************************************
	DEFINITIONS
**********************************************************************************************************************/

/* Check configuration-options and map to "assembler symbols". */
#ifdef CPP_SUPPORT
.set _CPP_SUPP, 1
#else
.set _CPP_SUPP, 0
#endif /* CPP_SUPPORT */

#ifdef VECTORS_RAM
.set _VECT_RAM, 1
#else
.set _VECT_RAM, 0
#endif /* VECTORS_RAM */

#ifdef RAM_FUNCS
.set _RAM_FUNCS, 1
#else
.set _RAM_FUNCS, 0
#endif /* RAM_FUNCS */

#ifdef BUILD_DEBUG
.set _BUILD_DEBUG, 1
#else
.set _BUILD_DEBUG, 0
#endif /* BUILD_DEBUG */

/* Stack fill pattern */
.global STACK_FILL
.equ	STACK_FILL, 0xAAAAAAAA

/* external functions */
.extern exit
.extern init
.extern main

.text
.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

/* Info section */
.if (_RAM_FUNCS)
.print "INFO: support for functions executed from RAM enabled"
.else
.print "INFO: support for functions executed from RAM disabled"
.endif /* _RAM_FUNCS */


/**********************************************************************************************************************
	STARTUP
**********************************************************************************************************************/

/*
	STARTUP ROUTINE
	Preparation of stacks for each operating mode, copying .data to ram, .bss initialization, ram remapping
	and running C++ constructors. Finally branching to C main() routine.
*/

/* Reset_Handler initializes MCU after reset condition */
.section	.text.Reset_Handler, "ax"
.weak		Reset_Handler
.type		Reset_Handler, %function

Reset_Handler:

/* Workaround for debugger - allows to break at startup. */
.if (_BUILD_DEBUG)
.print "INFO: delay loop for debug -> enabled"

	mov		r0, #0x1000
_init_wait:
	sub		r0, #1
	cmp		r0, #0
	bgt		_init_wait
.endif /* _BUILD_DEBUG */

.global	_startup
.func	_startup
_startup:
/*
	Relocate .data section (Copy from ROM to RAM).
	This will also copy the .vectram and .fastrun.
*/
/*
	registers used:
	r0 -> offset
	r1 -> variables init values from flash
	r2 -> variables target in ram
	r3 -> variables section end in ram
	
	r4 -> word to process
	r5 -> current address in ram
*/
	movs	r0, #0x00
	ldr		r1, =_etext
	ldr		r2, =_data
	ldr		r3, =_edata
	b		LoopCopyDataInit

CopyDataInit:
	ldr		r4, [r1, r0]
	str		r4, [r2, r0]
	adds	r0, r0, #4

LoopCopyDataInit:
	adds	r5, r2, r0
	cmp		r5, r3
	bcc		CopyDataInit

/* Clear .bss section (Zero init) */
/*
	registers used:
	r0 -> zero
	r1 -> bss word address
	r2 -> bss end
*/
	ldr		r1, =__bss_start__
	ldr		r2, =__bss_end__
	movs	r0, #0x00
	b		LoopZeroInit

ZeroInit:
	str		r0, [r1], #4
    
LoopZeroInit:
	cmp  r1, r2
	bcc  ZeroInit

/* Fill the .stack section */
/*
	registers used:
	r0 -> fill value
	r1 -> bss word address
	r2 -> bss end
*/
	ldr		r1, =__stack_start__
	ldr		r2, =__stack_end__
	ldr		r0, =STACK_FILL
	b		LoopStackFill

StackFill:
	str		r0, [r1], #4

LoopStackFill:
	cmp		r1, r2
	bcc		StackFill


/* Perform low level processor initialization */
	bl		init

.if (_CPP_SUPP)
.print "INFO: C++ constructors in global scope enabled"
/* Call C++ constructors (for objects in "global scope") */
	bl		__libc_init_array
.endif /* _CPP_SUPP */

/* Do additional initializations here */
_user_init:
.include "ext/conf_init.inc.s"

/* Enter the C/C++ code */
_enter_main:
	mov		r0, #0			/* no arguments (argc = 0) */
	mov		r1, r0
	mov		r2, r0
	mov		r3, r0
	mov		r4, r0
	mov		r5, r0
	mov		fp, r0			/* null frame pointer */
	mov		r7, r0			/* null frame pointer for thumb */
	ldr		lr, =_exit		/* handle main() return */
	b		main			/* enter main() */
.size	_startup, . - _startup
.endfunc
.size	Reset_Handler, . - Reset_Handler

/* Include exit() function implementation - required by newlib */
.include "ext/conf_impl_exit.inc.s"
