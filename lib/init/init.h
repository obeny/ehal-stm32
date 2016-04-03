/*!
 * \file init.h
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 04.02.2016
 * \version 1
 *
 * \brief Performs a low level CPU initialization after c-code startup - definitions.
 * \details
 * Initializes CPU. Enables selected clock source, changes flash waitstates,
 * assigns default interrupt handlers.
 *
 * \note
 * This library need to set following constants in config.h to work:
 * - F_CPU - CPU frequency (template of config.h file contains appropriate macros for
 * computation of frequency according to MCK_USE_* definitions.
 * - XTAL_FREQ - crystal oscillator frequency
 * - MCK_USE_PLL | MCK_USE_XTAL | MCK_USE_INTOSC - selection of clock source set during initialization
 * \note If MCK_USE_PLL is set, following constants have to be defined:
 * - PLL_DIV - PLL divider
 * - PLL_MUL - PLL multiplier
 * - PLL_PRESCALER_DIV - PLL prescaler (according to AT91C_PMC_PRES_CLK_* values)
 */

#ifndef _INIT_H
#define _INIT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "lib_mcu_noarch/global.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

/*!
 * \fn init
 * \brief initializes CPU after c-startup
 * \note This function is called before main and can't rely on any initializations.
 */
VOID init(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _INIT_H

// END
