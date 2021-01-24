/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddKeyLedController.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_LED_CONTROLLER_H__
#define __MIDD_LED_CONTROLLER_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
typedef enum _LEDS
{
    //*** TCA -P1 */
    EN_LED_LED1 = 1,
    EN_LED_LED2,
    EN_LED_LED3,
    EN_LED_LED4,
    EN_LED_LED5,
    EN_LED_LED6,
    EN_LED_LED7,
    EN_LED_LED8,

    EN_LED_PIN_LED_MAX
}LEDS;

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * \brief  init keyLed
 * \param  void
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middLedInit(void);

/**
 * \brief  load led status value, this function doesn't effect GPIO output
 *         call flushLed() to write hardware
 * \param  led id
 * \param  led status (TRUE, FALSE)
 */
void middLedLoadLedStat(LEDS led, BOOL stat);

/**
 * \brief  flush led value to hardware, call before midKeyLedLoadLedStat()
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middLedFlush(void);

/**
 * \brief  set led status
 * \param  led id
 * \param  led status (TRUE, FALSE)
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middLedSet(LEDS led, BOOL stat);

/**
 * \brief  Toggle led status
 * \param  led id
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middLedToggle(LEDS led);

/**
 * \brief  get led status
 * \param  led id
 * \return if everything is OK, return Led status(TRUE(active), FALSE(passive)
 *         otherwise return -1(FAILURE)
 */
S32 middLedGetStat(LEDS led);

/**
 * \brief  close all led
 * \param  void
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middLedCloseAll(void);

#endif /* __MIDD_KEY_LED_CONTROLLER_H__ */

/********************************* End Of File ********************************/
