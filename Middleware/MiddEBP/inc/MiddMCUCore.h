/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddMCUCore.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_MCU_CORE_H_
#define __MIDD_MCU_CORE_H_
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief init MCU clock
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUClockInit(void);

/**
 * @brief enter sleep mode
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUEnterSleepMode(void);

/**
 * @brief init input and output GPIO
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUGpioInit(void);

 /**
  * @brief init I2C
  * @param void
  * @return if everything is OK, return SUCCES
  *         otherwise return FAILURE
  */
RETURN_STATUS middMCUI2CInit(void);

/**
 * @brief init I2C
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUSPIInit(void);

/**
 * @brief init using timers
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUTimers(void);

/**
* @brief init all UART Channel
* @param void
* @return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS middMCUUartInit(void);

/**
* @brief init all CAN Channel
* @param void
* @return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS middMCUCanInit(void);

/**
* @brief init all ADC Channel
* @param void
* @return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS middMCUADCInit(void);

/**
* @brief init internal RTC
* @param void
* @return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS middMcuRTCInit(void);

 /**
  * @brief init WDT init
  * @param wdt time ms
  * @return if everything is OK, return SUCCES
  *         otherwise return FAILURE
  */
RETURN_STATUS middMCUWdtInit(U32 timeMs);

/**
 * @brief stop WDT
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUWdtStart(void);

/**
 * @brief feed WDT
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUWdtFeed(void);

/**
 * @brief init FMC
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMcuFmcInit(void);

#endif /* __MIDD_MCU_CORE_H_ */

/********************************* End Of File ********************************/
