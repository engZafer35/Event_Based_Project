/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppEventManager.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "AppEventManager.h"

#include "MiddSysTimer.h"
#include <unistd.h>
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static EventStr gEventList[MAX_EVENT_NUMBER];
static USS gIsStart;
/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS appEventInit(void)
{
    RETURN_STATUS retVal = SUCCESS;

    appEventDeleteEvents();
    gIsStart = FALSE;

    return retVal;
}

/**
 * @brief Throw a event. App process loop will catch the event
 * @param event ID
 * @param event priority
 * @note  if needed to load integer value, user can use leng to load integer value.
 *        when used this method user can not use (void *param). So that every time check
 *        param whether NULL
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEventThrowEvent(EVENT event, EVENT_SOURCE source, EVENT_PRIORITY priority, void *param, U32 leng, U32 value)
{
    RETURN_STATUS retVal = FAILURE;
    U32 i;

    if (TRUE == gIsStart)
    {
        for (i = 0; i < MAX_EVENT_NUMBER; ++i)
        {
            if (EN_EVENT_NO_EVENT == gEventList[i].event)
            {
                gEventList[i].event     = event;
                gEventList[i].source    = source;
                gEventList[i].priority  = priority;
                gEventList[i].param     = param;
                gEventList[i].leng      = leng;
                gEventList[i].value     = value;

                retVal = SUCCESS;
                break;
            }
        }
    }

    return retVal;
}

/**
 * @brief Delete all pending events.
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
void appEventDeleteEvents(void)
{
    U32 i;

    for (i = 0; i < MAX_EVENT_NUMBER; ++i)
    {
        gEventList[i].event = EN_EVENT_NO_EVENT; //clear event list
    }

    DBG_MSG("->[I] All events deleted !!!");
}

/**
 * @brief Start to get event
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
void appEventStart(void)
{
    gIsStart = TRUE;
}

/**
 * @brief Stop to set event. But, if there are events before calling this function user can
 * see old events. If you don't want to see any event after call this function,
 * you can call appEventDeleteEvents() function
 * @param void
 * @return void
 */
void appEventStop(void)
{
    gIsStart = FALSE;
}

/**
 * @brief clear related event by event pointer,
 * @note  if return success event pointer loaded NULL
 * @param event ID
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEventClearEvent(EventStr *event)
{
    RETURN_STATUS retVal = FAILURE;
    U32 i;

    for (i = 0; i < MAX_EVENT_NUMBER; ++i)
    {
        if ( event == (gEventList + i)) //find event
        {
            gEventList[i].event = EN_EVENT_NO_EVENT;
            event = NULL;
            retVal = SUCCESS;
            break;
        }
    }

    return retVal;
}

/**
 * @brief get event
 * @param timeout, 0 blocking mode(wait until any event created)
 * @param send a pointer to get events and events priority
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
EventStr* appEventGet(U32 timeoutMs, U32 eventSource)
{
    EventStr* retAddr = NULL;
    S32 maxPri;
    USS timerID;
    U32 i;

    if (FALSE == gIsStart)
    {
        DBG_MSG("->[I] Event Get Stopped !! Don't wait event. Go home and sleep ");
        return retAddr;
    }

    if (0 != timeoutMs)
    {
        timerID = middSysTimerSetTimer(timeoutMs, NULL);
    }

    maxPri  = -1;//negative value for starting

    while(1)
    {
        #ifdef WORKING_PLATFORM_PC
            usleep(10000);
        #endif

        for (i = 0; i < MAX_EVENT_NUMBER; ++i)
        {
            if ((EN_EVENT_NO_EVENT != gEventList[i].event) && (gEventList[i].priority > maxPri) && (eventSource & gEventList[i].source))
            {
                //load event that has high priority
                maxPri  = gEventList[i].priority;
                retAddr = (gEventList + i);
                if (maxPri >= EN_PRIORITY_EMG) //max priority, don't need to look other event
                {
                    break;
                }
            }
        }

        if (NULL != retAddr)
        {
            if (0 != timeoutMs)
            {
                //clear timer
                middSysTimerClearTimer(timerID);
            }
            break;
        }
        else if (0 != timeoutMs)
        {
            if (TRUE == middSysTimerIsTimerOK(timerID))
            {
                //clear timer
                middSysTimerClearTimer(timerID);
                break;
            }
        }

    }

    return retAddr;
}

/******************************** End Of File *********************************/
