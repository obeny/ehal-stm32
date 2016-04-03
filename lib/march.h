/*!
 * \file march.h
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 04.02.2016
 * \version 1
 *
 * \brief Architecture specific definitions.
 */

#ifndef _MARCH_H
#define _MARCH_H

/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

/*!
 * \def __ramfunc
 * \brief attribute for functions that have to be placed in RAM for fast execution
 * \note This works only if RAM_FUNCS is set (see Makefile.cnf).
 */
#ifdef RAM_FUNCS
#define __ramfunc __attribute__((long_call, section(".fastrun"))) __attribute((noinline))
#else
#define  __ramfunc
#endif // RAM_FUNCS

/*!
 * \def WORD_TYPE
 * \brief defines architecture word size
 */
#define WORD_TYPE uint32_t

/*!
 * \def WORD_TYPE
 * \brief defines size of sync_timer tick count type
 */
#define TICK_TYPE uint32_t

/*!
 * \def PROGMEM
 * \brief places static value into .text.progmem section
 * \details Allows to perform convinient flash read/write operations.
 * \note value is always aligned to processor's flash page size
 */
#define PROGMEM __attribute__((section(".progmem")))

/*!
 * \def PROGMEM_ATTR
 * \brief defines attribute indicating location in program memory
 * \note PROGMEM_ATTR and EEPROM_ATTR points to the same section
 */
#define PROGMEM_ATTR PROGMEM

/*!
 * \def EEPROM_ATTR
 * \brief defines attribute indicating location in eeprom memory
 * \note PROGMEM_ATTR and EEPROM_ATTR points to the same section
 */
#define EEPROM_ATTR PROGMEM

#endif // _MARCH_H

// END
