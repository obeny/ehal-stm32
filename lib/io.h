/*!
 * \file io.h
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 08.02.2016
 * \version 1 (20130208)
 *
 * \brief Collection of basic I/O routines and definitions
 */

#ifndef _IO_H
#define _IO_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "ehal/global.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

typedef struct
{
	uint32_t gpio;
	uint32_t gpio_rcc;
} gpio_st;


/***************************************************************************
 *	FUNCTIONS
 ***************************************************************************/

/*!
 * \fn initIo
 * \brief initializes I/O ports
 * \note this function have to be implemented by user for specific hardware configuration
 */
VOID initIo(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _IO_H
// END
