/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppEventProducers.h
*******************************************************************************/

/******************************************************************************
* Note: appEvntProdPerTimer is not good function. So that Asis should handle file
*       in future. appEvntProdPerTimer function breaks open-closed design rule.
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __APP_EVENT_PRODUCERS_H__
#define __APP_EVENT_PRODUCERS_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
#include "AppEventManager.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief  set digital IO event producer.
 * @param  TRUE for receive event, FALSE is stop
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntProdDigitalIO(BOOL stat, EVENT_PRIORITY prio);

/**
 * @brief  set keypad event producer.
 * @param  TRUE for receive event, FALSE is stop
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntProdKeypad(BOOL stat, EVENT_PRIORITY prio);

/**
 * @brief  set keys event producer.
 * @param  TRUE for receive event, FALSE is stop
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntProdKeys(BOOL stat, EVENT_PRIORITY prio);

/**
 * @brief  set external board(Can-Bus) communication event
 * @param  TRUE for receive event, FALSE is stop
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntProdCanComm(BOOL stat, EVENT_PRIORITY prio);

/**
 * @brief  set serial comm event
 * @param  TRUE for receive event, FALSE is stop
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntProdSerialComm(BOOL stat, EVENT_PRIORITY prio);

/**
 * @brief  set periodic timer event
 * @param  TRUE for receive event, FALSE is stop
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntProdPerTimer(TimerID tmid, U32 time, BOOL status, EVENT_PRIORITY prio);

/**
 * @brief  stop all event producers
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntProdStopAll(void);

#endif /* __APP_EVENT_PRODUCERS_H__ */

/********************************* End Of File ********************************/
