#ifndef _I2C_MARCH_H
#define _I2C_MARCH_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "ehal/global.h"
#include "lib/io.h"
#include "stm32f10x_gpio.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

typedef struct
{
	uint32_t i2c_if;
	uint32_t i2c_rcc;
	gpio_st i2c_gpio;
	uint8_t i2c_scl_pin;
	uint8_t i2c_sda_pin;
	uint32_t i2c_speed;
} i2c_cfg_st;

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _I2C_MARCH_H

// END
