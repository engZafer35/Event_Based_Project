/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddSysTimer.h
*******************************************************************************/

/******************************************************************************
* When you need timer alert you can use this file. Also you can use this file
* to set timeout.
* Firstly you should invoke middSysTimerInit() function. Also be sure to invoke
* middTimer3Init() function in middMCUCoreInit.c file. After initialize you can
* use middSysTimerSetTimer() to set timer alert. This function return timer ID.
* Don't lose the timerID. You can check whether your time end or not with
* middSysTimerIsTimerOK() function. After used timer, clear timer with
* middSysTimerClearTimer() function. Don't forget to clear
* 
* middSysTimerDelayMs() can be used for delay. Your can get system tick counter
* with middSysTimerGetTick() function.
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_SYS_TIMER_H__
#define __MIDD_SYS_TIMER_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

#define MAX_ALERT_TIMER (32)
/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief Init system Timer.
 * @param void
 * @return if timer flag active return TRUE,
 *         otherwise return FALSE
 *
 */
RETURN_STATUS middSysTimerInit(void);

/**
 * @brief Delay ms
 * @param time ms
 * @return void
 */
void middSysTimerDelayMs(U32 timeMs);

/**
 * @brief Get system tick counter value
 * @param void
 * @return current system tick counter value
 */
U32 middSysTimerGetTick(void);

/**
 * @brief Set alert timer ms
 * @param time ms
 * @return if SUCCES return timerID
 *         otherwise return (-1)(FAILURE)
 */
USS middSysTimerSetTimer(U32 timerMs, VoidCallback cb);

/**
 * @brief Clear alert flag
 * @param  alert timerID
 * @return void
 */
void middSysTimerClearTimer(USS timerID);

/**
 * @brief Get timer alert flag active
 * @param  alert timerID
 * @return if timer flag active return TRUE,
 *         otherwise return FALSE
 */
BOOL middSysTimerIsTimerOK(USS timerID);

#endif /* __MIDD_SYS_TIMER_H__ */

/********************************* End Of File ********************************/
