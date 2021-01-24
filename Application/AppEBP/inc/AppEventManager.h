/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppEventManager.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __APP_EVENT_MANAGER_H__
#define __APP_EVENT_MANAGER_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/
#define MAX_EVENT_NUMBER    (32) // max event buffer
/*******************************TYPE DEFINITIONS ******************************/
/** \brief Events ID */
typedef enum _EVENTS
{
    EN_EVENT_NO_EVENT,

    EN_EVENT_BIT,
    EN_EVENT_KEYPAD,
	EN_EVENT_KEYS,
    EN_EVENT_CAN_COMM_MSG, //can line message received
    EN_EVENT_SERIAL_COMM,
    EN_EVENT_SERIAL_COMM_TIMEOUT,
    EN_EVENT_CAN_COMM_TIMEOUT,
    EN_EVENT_CHECK_TEMP

}EVENT;

/** @brief Event Priority */
typedef enum _EVENT_PRIORITY
{
    EN_PRIORITY_LOW,
    EN_PRIORITY_MED,
    EN_PRIORITY_HIG,
    EN_PRIORITY_EMG
}EVENT_PRIORITY;

/** \brief Event Source */
typedef enum _EVENT_SOURCE
{
    EN_SOURCE_PER_TIMER     = 0001, //periodic timer
    EN_SOURCE_ONE_TIMER     = 0x02, //one-shot timer
    EN_SOURCE_INTERNAL      = 0x04,
    EN_SOURCE_COMM_LINE     = 0x08,
    EN_SOURCE_CAN_COMM_LINE = 0x10,
    EN_SOURCE_USER_INPUT    = 0x20,
    EN_SOURCE_DIGITAL_INPUT = 0x40,

    EN_SOURCE_ALL = 0X3FF //max 10 bit

}EVENT_SOURCE;

typedef struct _EventStr
{
    U32             event     :10;    // 10 bit
    EVENT_SOURCE    source    :10;    // 10 bit
    U32             leng      :10;    // 10 bit
    EVENT_PRIORITY  priority  :2;     // 2 bit

    U32             value;
    void*           param;

}EventStr;

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief This function init Event Manager
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEventInit(void);

/**
 * @brief Throw a event. App process loop will catch the event
 * @param event ID
 * @param event priority
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEventThrowEvent(EVENT event, EVENT_SOURCE source, EVENT_PRIORITY priority, void *param, U32 leng, U32 value);

/**
 * @brief Delete all pending events.
 * @param void
 * @return void
 */
void appEventDeleteEvents(void);

/**
 * @brief Start to get event
 * @param void
 * @return void
 */
void appEventStart(void);

/**
 * @brief Stop to set event. But, if there are events before calling this function user can
 * see old events. If you don't want to see any event after call this function,
 * you can call appEventDeleteEvents() function
 * @param void
 * @return void
 */
void appEventStop(void);

/**
 * @brief clear related event by event pointer
 * @note  if return success event pointer loaded NULL
 * @param event ID
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEventClearEvent(EventStr *event);

/**
 * @brief get event
 * @param timeout, 0 blocking mode(wait until any event created)
 * @param send a pointer to get events and events priority
 * @return if everything is OK, return event addr
 *         otherwise return NULL addr
 */
EventStr* appEventGet(U32 timeoutMs, U32 eventSource);

#if 0
/**
 * @brief Start event loop thread
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEventThreadStart(void);

/**
 * @brief Pause event loop thread. If use this function you will not get new events.
 *        Also thread still lives
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEventThreadStop(void);

/**
 * @brief delete loop thread.
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEventLoopThreadDelete(void);
#endif //#if 0

#endif /* __APP_EVENT_MANAGER_H__ */

/********************************* End Of File ********************************/
