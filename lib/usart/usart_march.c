/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*!
 * \file usart_march.c
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 03.01.2014
 * \version 1
 *
 * \brief buffered transmission support for usart - architecture specific implementation.
 * \note
 * For detailed description see header file.
 */

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "stm32f10x_gpio.h"

#include "lib_mcu_noarch/usart/usart.h"
#include "lib/usart/usart_march.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

extern usart_cfg_st *usart1_cfg_st;
extern usart_cfg_st *usart2_cfg_st;
extern usart_cfg_st *usart3_cfg_st;

// static functions
static void usart_irq_handler(usart_cfg_st *usart);


/***************************************************************************
 *	FUNCTIONS
 ***************************************************************************/

// --------------------------------------------------------------------------
// irq handlers

// USART1
#ifdef USART_USE1
VOID USART1_IRQHandler(void);
VOID USART1_IRQHandler(void)
{
	usart_irq_handler(usart1_cfg_st);
}
#endif // USART_USE1

// USART2
#ifdef USART_USE2
VOID USART2_IRQHandler(void);
VOID USART2_IRQHandler(void)
{
	usart_irq_handler(usart2_cfg_st);
}
#endif // USART_USE2

// USART3
#ifdef USART_USE3
VOID USART3_IRQHandler(void);
VOID USART3_IRQHandler(void)
{
	usart_irq_handler(usart3_cfg_st);
}
#endif // USART_USE3

// incoming/outgoing data handler
static void usart_irq_handler(usart_cfg_st *usart)
{
	// read status register
	UINT32 ui32_status = ((USART_TypeDef*)usart->usart_if)->SR;

	// handle data transmission
	if (ui32_status & USART_FLAG_TXE)
	{
		if ((usart->usart_tx_tail != usart->usart_tx_head) || usart->b_usart_tx_full)
		{
			((USART_TypeDef*)usart->usart_if)->DR = usart->ac_usart_tx_buff[usart->usart_tx_tail];
			usart->usart_tx_tail++;
			if (usart->usart_tx_tail > (USART_TBUF_SIZE - 1))
				usart->usart_tx_tail = 0;

			usart->b_usart_tx_full = false;
		}
		else
			((USART_TypeDef*)usart->usart_if)->CR1 &= ~USART_FLAG_TXE;
	}

	// handle data receive
	if (ui32_status & USART_FLAG_RXNE)
	{
		if (usart->b_usart_rx_overflow)
		{
			usart->usart_rx_tail++;
			if (usart->usart_rx_tail > (USART_RBUF_SIZE - 1))
				usart->usart_rx_tail = 0;
		}

		// insert byte to ring buffer
		usart->ac_usart_rx_buff[usart->usart_rx_head] = ((USART_TypeDef*)usart->usart_if)->DR;
		usart->usart_rx_head++;
		if (usart->usart_rx_head > (USART_RBUF_SIZE - 1))
			usart->usart_rx_head = 0;

		// indicate buffer overflow
		if (usart->usart_rx_head == usart->usart_rx_tail)
			usart->b_usart_rx_overflow = true;
	}
}

// --------------------------------------------------------------------------
USART_USARTCLOSE_ATTR VOID usartClose(usart_cfg_st *usart)
{
	// flush buffers and disable usart
	usartFlush(usart);
	// AT91F_US_Close(AT91C_BASE_US1);
}

// --------------------------------------------------------------------------
USART_USARTINIT_ATTR VOID usartInit(usart_cfg_st *usart, const UINT16 ui16_baudrate, const BOOL b_two_stop_bits, const UINT8 ui8_parity)
{
	// init status
	USART_InitTypeDef stm_usart;
	GPIO_InitTypeDef stm_gpio;

	usart->usart_rx_head = 0;
	usart->usart_rx_tail = 0;
	usart->usart_tx_head = 0;
	usart->usart_tx_tail = 0;
	usart->b_usart_rx_overflow = false;
	usart->b_usart_tx_full = false;

	RCC_APB2PeriphClockCmd(usart->usart_afio_rcc, ENABLE);
	if (RCC_APB2Periph_USART1 == usart->usart_rcc)
		RCC_APB2PeriphClockCmd(usart->usart_rcc, ENABLE);
	else if ((RCC_APB1Periph_USART2 == usart->usart_rcc) || (RCC_APB1Periph_USART3 == usart->usart_rcc))
		RCC_APB1PeriphClockCmd(usart->usart_rcc, ENABLE);

	RCC_APB2PeriphClockCmd(usart->usart_gpio.gpio_rcc, ENABLE);

	GPIO_StructInit(&stm_gpio);

	stm_gpio.GPIO_Pin = BV(usart->usart_rx_pin);
	stm_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	stm_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init((GPIO_TypeDef*)usart->usart_gpio.gpio, &stm_gpio);

	stm_gpio.GPIO_Pin = BV(usart->usart_tx_pin);
	stm_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	stm_gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init((GPIO_TypeDef*)usart->usart_gpio.gpio, &stm_gpio);

	stm_usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	stm_usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	// set device baudrate
	stm_usart.USART_BaudRate = ui16_baudrate * 100;

	// set frame format: 8 data bits
	stm_usart.USART_WordLength = USART_WordLength_8b ;

	// set frame format: 2 stop bits
	if (b_two_stop_bits)
		stm_usart.USART_StopBits = USART_StopBits_2;
	else
		stm_usart.USART_StopBits = USART_StopBits_1;

	// set frame format: parity
	if (ui8_parity == USART_PARITY_EVEN)
		stm_usart.USART_Parity = USART_Parity_Even;
	else if (ui8_parity == USART_PARITY_ODD)
		stm_usart.USART_Parity = USART_Parity_Odd;
	else
		stm_usart.USART_Parity = USART_Parity_No;

	// configure and enable interrupt
	USART_Init((USART_TypeDef*)usart->usart_if, &stm_usart);
	USART_Cmd((USART_TypeDef*)usart->usart_if, ENABLE);
	USART_ITConfig((USART_TypeDef*)usart->usart_if, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(usart->usart_irq);
}

// --------------------------------------------------------------------------
void march_usartEnableTXEInterrupt(const usart_cfg_st *usart)
{
	((USART_TypeDef*)usart->usart_if)->CR1 |= USART_FLAG_TXE;
}

// END
