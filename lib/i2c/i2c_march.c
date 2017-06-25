/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"

#include "config.h"
#include "ehal/i2c/i2c.h"
#include "ehal/util/util.h"

#include "ehal/debug/debug.h"

/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

#define CHECK_EVENT_TIMEOUT(bus, event, timeout) \
{ \
	timeout_cur = 0; \
	while (I2C_CheckEvent(bus, event) != SUCCESS) { \
		++timeout_cur; \
		if (timeout_cur > timeout) \
			return (false); \
		delayMs(1); \
	} \
}

/***************************************************************************
 *	FUNCTIONS
 ***************************************************************************/

// --------------------------------------------------------------------------
void i2cMasterInit(const i2c_cfg_st *i2c, const BOOL ack)
{
	GPIO_InitTypeDef stm_gpio;
	I2C_InitTypeDef stm_i2c;

	RCC_APB1PeriphClockCmd(i2c->i2c_rcc, ENABLE);
	RCC_APB2PeriphClockCmd(i2c->i2c_gpio.gpio_rcc, ENABLE);

	stm_gpio.GPIO_Pin = BV(i2c->i2c_scl_pin) | BV(i2c->i2c_sda_pin);
	stm_gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	stm_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init((GPIO_TypeDef*)i2c->i2c_gpio.gpio, &stm_gpio);

	I2C_StructInit(&stm_i2c);
	stm_i2c.I2C_Ack = (ack)?(I2C_Ack_Enable):(I2C_Ack_Disable);
	stm_i2c.I2C_ClockSpeed = i2c->i2c_speed;
	I2C_Init((I2C_TypeDef*)i2c->i2c_if, &stm_i2c);
	I2C_Cmd((I2C_TypeDef*)i2c->i2c_if, ENABLE);
}
// --------------------------------------------------------------------------
BOOL i2cMasterTransfer(const i2c_cfg_st *i2c, const BOOL repeated_start, const UINT8 addr, const char* send_buf,
	const UINT8 send_len, char *recv_buf, const UINT8 recv_len, const UINT16 timeout)
{
	char *send_buf_cur = (char *)send_buf;
	char *recv_buf_cur = (char *)recv_buf;
	UINT8 send_cnt = 0;
	UINT8 recv_cnt = 0;
	UINT16 timeout_cur = 0;

	if (send_len > 0) {
		I2C_GenerateSTART((I2C_TypeDef*)i2c->i2c_if, ENABLE);
		CHECK_EVENT_TIMEOUT((I2C_TypeDef*)i2c->i2c_if, I2C_EVENT_MASTER_MODE_SELECT, timeout);

		I2C_Send7bitAddress((I2C_TypeDef*)i2c->i2c_if, 0x40 << 1, I2C_Direction_Transmitter);
		CHECK_EVENT_TIMEOUT((I2C_TypeDef*)i2c->i2c_if, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED, timeout);

		do {
			I2C_SendData((I2C_TypeDef*)i2c->i2c_if, *send_buf_cur);
			CHECK_EVENT_TIMEOUT((I2C_TypeDef*)i2c->i2c_if, I2C_EVENT_MASTER_BYTE_TRANSMITTED, timeout)
			++send_buf_cur;
			++send_cnt;
		} while (send_cnt < send_len);

		if ((!repeated_start) || (0 == recv_len)) {
			I2C_GenerateSTOP((I2C_TypeDef*)i2c->i2c_if, ENABLE);
		}
	}
	
	if (recv_len > 0)
	{
		I2C_GenerateSTART((I2C_TypeDef*)i2c->i2c_if, ENABLE);
		CHECK_EVENT_TIMEOUT((I2C_TypeDef*)i2c->i2c_if, I2C_EVENT_MASTER_MODE_SELECT, timeout);

		I2C_Send7bitAddress((I2C_TypeDef*)i2c->i2c_if, addr << 1, I2C_Direction_Receiver);
		I2C_AcknowledgeConfig((I2C_TypeDef*)i2c->i2c_if, ENABLE);
		CHECK_EVENT_TIMEOUT((I2C_TypeDef*)i2c->i2c_if, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED, timeout);
		do
		{
			if (recv_cnt >= (recv_len - 1))
				I2C_AcknowledgeConfig((I2C_TypeDef*)i2c->i2c_if, DISABLE);
			CHECK_EVENT_TIMEOUT((I2C_TypeDef*)i2c->i2c_if, I2C_EVENT_MASTER_BYTE_RECEIVED, timeout);
			*recv_buf_cur = I2C_ReceiveData((I2C_TypeDef*)i2c->i2c_if);
			++recv_buf_cur;
			++recv_cnt;
		} while (recv_cnt < recv_len);

		I2C_GenerateSTOP((I2C_TypeDef*)i2c->i2c_if, ENABLE);
	}

	return (true);
}

// END
