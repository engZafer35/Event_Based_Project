/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : DrvM4T11_RTC.h
*******************************************************************************/

/******************************************************************************
*                                Pin Table Description
*     Pin
*      1   -   OSCI    -  Oscillator input
*      2   -   OCSO    -  Oscillator output
*      3   -   Vbat    -  Battery supply voltage
*      4   -   Vss     -  Ground
*      5   -   SDA     -  Serial data address input/output
*      6   -   SCL     -  Serial clock
*      7   -   FT/OUT  -  Frequency test/output driver (open drain)
*      8   -   Vcc     -  Supply voltage
*
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __DRV_M41T11_RTC_H__
#define __DRV_M41T11_RTC_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/
 typedef struct M4T_I2C
 {
     U32 devAddr;
     RETURN_STATUS (*write) (U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng);
     RETURN_STATUS (*read)  (U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng);
 }M4T11_I2C;
/*******************************TYPE DEFINITIONS ******************************/
/**
 * @brief m4t11 driver time structure
 */
typedef struct _M4T11_RTC_STR
{
    U8 sec;     /* Seconds parameter, from 00 to 59 */
    U8 min;     /* Minutes parameter, from 00 to 59 */
    U8 hour;    /* Hours parameter, 24Hour mode, 00 to 23 */
    U8 wday;    /* Day in a week, from 1 to 7 */
    U8 mday;    /* Date in a month, 1 to 31 */
    U8 mon;     /* Month in a year, 1 to 12 */
    U16 year;   /* Year parameter, 2000 to 3000 */
}M4T11_RTC_STR;
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

/**
* @brief  init M4T11
* @param  hardware i2c, driver will copy i2c, user can delete own structure
* @return if everything is OK, return SUCCES
*         otherwise return FAILURE
 */
RETURN_STATUS drvM41T11Init(const M4T11_I2C *i2c);

/**
 * @brief  get time
 * @param  M4T11_RTC_STR pointer
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvM41T11GetTime(M4T11_RTC_STR *getTime);

/**
 * @brief  set time
 * @param  M4T11_RTC_STR pointer
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvM41T11SetTime(const M4T11_RTC_STR *setTime);

#endif /* __DRV_M41T11_RTC_H__ */

/********************************* End Of File ********************************/
