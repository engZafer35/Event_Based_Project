/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddTimeTempInfo.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_TIME_TEMP_INFO_H__
#define __MIDD_TIME_TEMP_INFO_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
/**
 * @brief m4t11 driver time structure
 */
typedef struct _RTC
{
    U8 sec;     /* Seconds parameter, from 00 to 59 */
    U8 min;     /* Minutes parameter, from 00 to 59 */
    U8 hour;    /* Hours parameter, 24Hour mode, 00 to 23 */
    U8 wday;    /* Day in a week, from 1 to 7 */
    U8 mday;    /* Date in a month, 1 to 31 */
    U8 mon;     /* Month in a year, 1 to 12 */
    U16 year;   /* Year parameter, 2000 to 3000 */
}RTC_TIME;
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * \brief  init to get system RTC and temperature
 * \param  void
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middTimeTempInit(void);

/**
 * \brief  get system (external RTC) time
 * \param  RTC structure pointer
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middTimeTempGetTime(RTC_TIME *t);

/**
 * \brief  set system (external RTC) time
 * \param  RTC structure pointer
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middTimeTempSetTime(const RTC_TIME *t);

/**
 * \brief  get system temperature (external sensor)
 * \param  void
 * @return if everything is OK, return temperature
 *         otherwise return 0XFFFF;
 */
float middTimeTempGetTemp(void);

#endif /* __MIDD_TIME_TEMP_INFO_H__ */

/********************************* End Of File ********************************/
