/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddEventTimer.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_EVENT_TIMER_H__
#define __MIDD_EVENT_TIMER_H__

/*********************************INCLUDES*************************************/
#include "ProjectConf.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

RETURN_STATUS middEventTimerInit (void);

RETURN_STATUS middEventTimerRegister(TimerID id, VoidCallback callback, U32 timeMs);

RETURN_STATUS middEventTimerStart(TimerID id);

RETURN_STATUS middEventTimerStop(TimerID id);

RETURN_STATUS middEventTimerStartAll(void);

RETURN_STATUS middEventTimerStopAll(void);

RETURN_STATUS middEventTimerDelete(TimerID id);

RETURN_STATUS middEventTimerDeleteAll(void);

#endif /* __MIDD_EVENT_TIMER_H__ */

/********************************* End Of File ********************************/
