/*!
 * \file spi_march.h
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 04.01.2014
 * \version 1
 *
 * \note
 * STM32 architecture implementation of spi_march.c module requires following definitions:
 * - SPI_IF - SPI interface number e.g. SPI1
 * - SPI_GPIO - GPIO which is used by SPI interface
 * - SPI_RCC - RCC clock register used by SPI interface
 * - SPI_MISO - SPI MISO pin number in port
 * - SPI_MOSI - SPI MOSI pin number in port
 * - SPI_SCK - SPI SCK pin number in port
 * 
 * Slave Select pin do not have to be SPI SS, it can be any output pin.
 * - SPI_SS - SPI SS pin number in port
 * - SPI_SS_GPIO - SPI SS GPIO register
 * - SPI_SS_GPIO_RCC - SPI SS RCC clock register for GPIO
 * 
 * - SPI_CLK_DIV - frequency prescaler for SPI
 * All of those definitions are dependent on used mcu type, see datasheet for details.
 *
 * \brief Blocking SPI serial interface handler - architecture specific definitions
 * \warning
 * Depending on MCU architecture additional configuration definitions may be required.
 * Implementation for particular architecture is contained in related version of library in spi_march.c.
 */

#ifndef _SPI_MARCH_H
#define _SPI_MARCH_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "lib_mcu_noarch/global.h"
#include "lib/io.h"
#include "stm32f10x_gpio.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

typedef struct
{
	uint32_t spi_if;
	uint32_t spi_rcc;
	uint32_t spi_afio_rcc;
	gpio_st spi_gpio;
	gpio_st spi_gpio_ss;
	uint8_t spi_sck_pin;
	uint8_t spi_mosi_pin;
	uint8_t spi_miso_pin;
	uint8_t spi_ss_pin;
	uint16_t spi_clk_div;
} spi_cfg_st;

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _SPI_MARCH_H

// END
