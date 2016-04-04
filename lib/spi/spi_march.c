/*!
 * \file spi_march.c
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 09.03.2016
 * \version 2
 *
 * \brief Blocking SPI serial interface handler - architecture specific implementation
 * \note
 * For detailed description see header file.
 */

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "config.h"
#include "lib/io.h"
#include "ehal/spi/spi.h"
#include "lib/spi/spi_march.h"



/***************************************************************************
 *	FUNCTIONS
 ***************************************************************************/

// --------------------------------------------------------------------------
void spiMasterInit(const spi_cfg_st *spi, const e_spiclk_pol_t clk_pol, const e_spiclk_pha_t clk_pha, const e_spiclk_ord_t clk_ord)
{
	GPIO_InitTypeDef stm_gpio;
	SPI_InitTypeDef stm_spi;

	// configure signal lines
	RCC_APB2PeriphClockCmd(spi->spi_afio_rcc, ENABLE);
	RCC_APB2PeriphClockCmd(spi->spi_rcc, ENABLE);
	RCC_APB2PeriphClockCmd(spi->spi_gpio.gpio_rcc, ENABLE);
	RCC_APB2PeriphClockCmd(spi->spi_gpio_ss.gpio_rcc, ENABLE);

	GPIO_StructInit(&stm_gpio);

	stm_gpio.GPIO_Pin = BV(spi->spi_mosi_pin) | BV(spi->spi_sck_pin);
	stm_gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	stm_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init((GPIO_TypeDef*)spi->spi_gpio.gpio, &stm_gpio);

	stm_gpio.GPIO_Pin = BV(spi->spi_miso_pin);
	stm_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init((GPIO_TypeDef*)spi->spi_gpio.gpio, &stm_gpio);

	stm_gpio.GPIO_Pin = BV(spi->spi_ss_pin);
	stm_gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init((GPIO_TypeDef*)spi->spi_gpio_ss.gpio, &stm_gpio);

	// deassert SS selection
	GPIO_SetBits((GPIO_TypeDef*)spi->spi_gpio_ss.gpio, BV(spi->spi_ss_pin));

	// configure SPI controller for master mode
	SPI_StructInit(&stm_spi);
	stm_spi.SPI_Mode = SPI_Mode_Master;
	stm_spi.SPI_NSS = SPI_NSS_Soft;
	stm_spi.SPI_BaudRatePrescaler = spi->spi_clk_div;
	if (clk_pol)
		stm_spi.SPI_CPOL = SPI_CPOL_High;
	if (clk_pha)
		stm_spi.SPI_CPHA = SPI_CPHA_2Edge;
	if (clk_ord)
		stm_spi.SPI_FirstBit = SPI_FirstBit_LSB;
	SPI_Init((SPI_TypeDef*)spi->spi_if, &stm_spi);
	SPI_Cmd((SPI_TypeDef*)spi->spi_if, ENABLE);
}

// --------------------------------------------------------------------------
void spiSendByte(const spi_cfg_st *spi, const BYTE c)
{
	spiTransferByte(spi, c);
}

// --------------------------------------------------------------------------
void spiSendByteStrobeToggle(const spi_cfg_st *spi, const BYTE c)
{
	GPIO_ResetBits((GPIO_TypeDef*)spi->spi_gpio_ss.gpio, BV(spi->spi_ss_pin));
	spiSendByte(spi, c);
	GPIO_SetBits((GPIO_TypeDef*)spi->spi_gpio_ss.gpio, BV(spi->spi_ss_pin));
}

// --------------------------------------------------------------------------
BYTE spiTransferByte(const spi_cfg_st *spi, const BYTE c)
{
	// wait for empty send buffer
	WAIT_FOR(SPI_I2S_GetFlagStatus((SPI_TypeDef*)spi->spi_if, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData((SPI_TypeDef*)spi->spi_if, c);

	// wait for recieved data
	WAIT_FOR(SPI_I2S_GetFlagStatus((SPI_TypeDef*)spi->spi_if, SPI_I2S_FLAG_RXNE) == RESET);

	// return the received data
	return SPI_I2S_ReceiveData((SPI_TypeDef*)spi->spi_if);
}

// --------------------------------------------------------------------------
BYTE spiTransferByteStrobeToggle(const spi_cfg_st *spi, const BYTE c)
{
	BYTE resp;

	GPIO_ResetBits((GPIO_TypeDef*)spi->spi_gpio_ss.gpio, BV(spi->spi_ss_pin));
	resp = spiTransferByte(spi, c);
	GPIO_SetBits((GPIO_TypeDef*)spi->spi_gpio_ss.gpio, BV(spi->spi_ss_pin));

	return resp;
}

// END
