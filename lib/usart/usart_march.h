/*!
 * \file usart1_march.h
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 08.02.2016
 * \version 1
 *
 * \brief buffered transmission support for usart1 - architecture specific definitions.
 * \note
 * For detailed description see usart.h header file.
 */

#ifndef _USART_MARCH_H
#define _USART_MARCH_H

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "config.h"
#include "lib/io.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

#ifdef USART_BIG_BUFFERS
typedef UINT32 usart_bufsize_t;
#else
typedef UINT8 usart_bufsize_t;
#endif // USART_BIG_BUFFERS

typedef struct
{
	uint32_t usart_if;
	uint32_t usart_rcc;
	uint32_t usart_afio_rcc;
	gpio_st usart_gpio;
	uint8_t usart_rx_pin;
	uint8_t usart_tx_pin;
	uint8_t usart_irq;

	// rx/tx buffers
	volatile usart_bufsize_t usart_rx_head, usart_rx_tail;
	volatile usart_bufsize_t usart_tx_head, usart_tx_tail;
	// buffer indexes
	volatile BYTE ac_usart_rx_buff[USART_RBUF_SIZE];
	volatile BYTE ac_usart_tx_buff[USART_TBUF_SIZE];
	// usart status
	volatile BOOL b_usart_rx_overflow;
	volatile BOOL b_usart_tx_full;

} usart_cfg_st;

/***************************************************************************
 *	FUNCTIONS
 ***************************************************************************/

// enable TX empty interrupt
void march_usartEnableTXEInterrupt(const usart_cfg_st *usart);

#endif // _USART_MARCH_H

// END
