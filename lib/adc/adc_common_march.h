/*!
 * \file adc_common_march.h
 *
 * \author Marcin O'BenY Benka <obeny@obeny.net>
 * \date 03.01.2014
 * \version 1
 *
 * \brief Analog-to-Digital converter handling library - architecture specific definitions.
 * \details
 * Various advanced configurations including differential or amplified channels have to be added
 * manually as additional definitions. See ADC_CH_X and extend this list in config.h.
 * \warning
 * Depending on MCU architecture additional configuration definitions may be required.
 * Implementation for particular architecture is contained in related version of library in adc_march.c.
 */

#ifndef _ADC_MARCH_H
#define _ADC_MARCH_H

/***************************************************************************
 *	INCLUDES
 ***************************************************************************/

#include "ehal/global.h"


/***************************************************************************
 *	DEFINITIONS
 ***************************************************************************/

/*!
 * \def ADC_MUX_MASK
 * \brief mask used internally for filtering channel muxer information
 */
#define ADC_MUX_MASK 0x1F

// --------------------------------------------------------------------------
/*!
 * \def ADC_CH_ADC0
 * \brief value for channel muxer to select ADC0
 */
#define ADC_CH_ADC0 0x00
/*!
 * \def ADC_CH_ADC1
 * \brief value for channel muxer to select ADC1
 */
#define ADC_CH_ADC1 0x01
/*!
 * \def ADC_CH_ADC2
 * \brief value for channel muxer to select ADC2
 */
#define ADC_CH_ADC2 0x02
/*!
 * \def ADC_CH_ADC3
 * \brief value for channel muxer to select ADC3
 */
#define ADC_CH_ADC3 0x03
/*!
 * \def ADC_CH_ADC4
 * \brief value for channel muxer to select ADC4
 */
#define ADC_CH_ADC4 0x04
/*!
 * \def ADC_CH_ADC5
 * \brief value for channel muxer to select ADC5
 */
#define ADC_CH_ADC5 0x05
/*!
 * \def ADC_CH_ADC6
 * \brief value for channel muxer to select ADC6
 */
#define ADC_CH_ADC6 0x06
/*!
 * \def ADC_CH_ADC7
 * \brief value for channel muxer to select ADC7
 */
#define ADC_CH_ADC7 0x07

// --------------------------------------------------------------------------
/*!
 * \def ADC_PRESCALER_DIV2
 * \brief value for select frequency prescaler for ADC (f/2)
 */
#define ADC_PRESCALER_DIV2 0x00
/*!
 * \def ADC_PRESCALER_DIV4
 * \brief value for select frequency prescaler for ADC (f/4)
 */
#define ADC_PRESCALER_DIV4 0x01
/*!
 * \def ADC_PRESCALER_DIV8
 * \brief value for select frequency prescaler for ADC (f/6)
 */
#define ADC_PRESCALER_DIV6 0x02
/*!
 * \def ADC_PRESCALER_DIV16
 * \brief value for select frequency prescaler for ADC (f/8)
 */
#define ADC_PRESCALER_DIV8 0x03

#endif //_ADC_MARCH_H

// END
