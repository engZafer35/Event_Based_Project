/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 15, 2021 - 9:05:66 AM
* #File Name    : DriverCoreIWDT.H
*******************************************************************************/

/******************************************************************************
* How To Use: You can control mcu iwdt(Independent watchdog) with this file.
* For mor detail check RM0390 Reference document (http://tiny.cc/b0zs6y)
**                                   DOWNCOUNTER
*                  Table 121. Min/max IWDG timeout period at 32kHz(LSI)
*
*        rescaler divider | PR[2:0] bits | Min Timeout(ms) | Max Timeout(ms)
*                         |              |      RL = 0     |  RL = 0xFFF
*             /4          |     0        |      0.125      |    512
*             /8          |     1        |      0.25       |    1024
*             /16         |     2        |      0.5        |    2048
*             /32         |     3        |      1          |    4096
*             /64         |     4        |      2          |    8192
*             /128        |     5        |      4          |    16384
*             /256        |     6        |      8          |    32768
*
******************************************************************************/
/******************************IFNDEF ï¿½ DEFINE******************************/
#ifndef __DRIVER_CORE_IWDT_H__
#define __DRIVER_CORE_IWDT_H__

/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/*************************** GLOBAL FUNC-LIKE-MACRO ***************************/
#if defined (__linux)
#define drvIwdtStart() DBG_MSG("-> [I] WDT STARTED !")
#define drvIwdtFeed() DBG_MSG("-> [I] WDT FEDDED !")
#else

/**
 * @brief start the wdt. Firstly call Init function
 * @note  function like macro
 * @param none
 *
 * @return none
 *
 */
#define drvIwdtStart() (IWDG->KR = ((U16)(0xCCCC)))

/**
 * @brief feed the wdt. Firstly call Init function
 * @note  function like macro
 * @param none
 *
 * @return none
 *
 */
#define drvIwdtFeed()   (IWDG->KR = ((U16)(0xAAAA)))
#endif
/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief  init Independent Watchdog Timer. Max 32000ms, min 1ms
 * @param  wdt timer ms
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvIwdtInit(U32 timeMs);

#endif /* __DRIVER_CORE_IWDT_H__ */

/********************************* End Of File ********************************/
