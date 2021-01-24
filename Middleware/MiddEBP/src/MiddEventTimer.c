/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddEventTimer.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG  (DISABLE)
/*********************************INCLUDES*************************************/
#include "MiddEventTimer.h"
#include "McuInterruptRegister.h"
/****************************** MACRO DEFINITIONS *****************************/
#define IS_VALID_TIMER_ID(x)    (x < EN_TIMER_MAX_NUM)
/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/
typedef struct _TimerStr
{
    U32 timeout;
    VoidCallback callback;
    U32 timeoutCopy;

}TimerStr;
/********************************** VARIABLES *********************************/
static volatile TimerStr timerCallBackList[EN_TIMER_MAX_NUM] = {{0},};

/***************************** STATIC FUNCTIONS  ******************************/

/*
 * Check user timer, İf the time reached timer call callback function
 * And than start again
 */
static void timerEventCallback(int x)
{
    static USS i;

    for (i = 0; i < EN_TIMER_MAX_NUM; i++)
    {
        if (timerCallBackList[i].timeout > 0)
        {
            if (IS_SAFELY_PTR(timerCallBackList[i].callback))
            {
                timerCallBackList[i].timeout -= MIN_TIMER_PERIOD_MS;

                //timer finished. invoke callback func
                if (timerCallBackList[i].timeout < MIN_TIMER_PERIOD_MS)
                {
                    timerCallBackList[i].timeout = timerCallBackList[i].timeoutCopy; //restart timer
                    timerCallBackList[i].callback();
                }
            }
        }
    }
}

#ifdef WORKING_PLATFORM_PC
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
static void testThread(void)
{
    printf("\n#>middEvent TestThread Running ... \n");
    while(1)
    {
        usleep(10000);
        timerEventCallback(0);
    }
}
#endif
/***************************** PUBLIC FUNCTIONS  ******************************/

RETURN_STATUS middEventTimerInit(void)
{
    RETURN_STATUS retVal;
    USS i = 0;

    //clear callback list
    for (i = 0; i < EN_TIMER_MAX_NUM; i++)
    {
        timerCallBackList[i].timeout = 0;
        timerCallBackList[i].callback = NULL;
    }

    retVal = drvIntRegister(timerEventCallback, TIMER_EVENT_IT_ID);
    DBG_MSG("-> [I]middEventTimerInit return: %d", retVal);

#ifdef WORKING_PLATFORM_PC
    pthread_t thread_id;
    if (0 == pthread_create(&thread_id, NULL, testThread, NULL))
    {
        printf("----EVENT TIMER Test Thread Created ..... \n");
    }
#endif

    return retVal;
}

RETURN_STATUS middEventTimerRegister(TimerID id, VoidCallback callback, U32 timeMs)
{
    RETURN_STATUS retVal = FAILURE;
    U32 ru;

    if (IS_VALID_TIMER_ID(id) && IS_SAFELY_PTR(callback))
    {
        //round up
        ru = (timeMs % MIN_TIMER_PERIOD_MS);
        if (0 != ru)
        {
            timeMs += MIN_TIMER_PERIOD_MS - ru;
        }

        timerCallBackList[id].callback    = callback;
        timerCallBackList[id].timeout     = 0;
        timerCallBackList[id].timeoutCopy = timeMs;

        retVal = SUCCESS;
    }

    return retVal;
}

RETURN_STATUS middEventTimerStart(TimerID id)
{
    RETURN_STATUS retVal = FAILURE;

    if (IS_VALID_TIMER_ID(id))
    {
        timerCallBackList[id].timeout = timerCallBackList[id].timeoutCopy;
        retVal = SUCCESS;
    }

    return retVal;
}

RETURN_STATUS middEventTimerStop(TimerID id)
{
    int retVal = FAILURE;

    if (IS_VALID_TIMER_ID(id))
    {
        timerCallBackList[id].timeout = 0;
        retVal = SUCCESS;
    }

    return retVal;
}

RETURN_STATUS middEventTimerStartAll(void)
{
    USS i;
    for(i = 0; i < EN_TIMER_MAX_NUM; i++)
    {
        timerCallBackList[i].timeout = timerCallBackList[i].timeoutCopy;
    }
    return SUCCESS;
}

RETURN_STATUS middEventTimerStopAll(void)
{
    USS i;
    for(i = 0; i < EN_TIMER_MAX_NUM; i++)
    {
        timerCallBackList[i].timeout = 0;
    }

    return SUCCESS;
}

RETURN_STATUS middEventTimerDelete(TimerID id)
{
    RETURN_STATUS retVal = FAILURE;

    if (IS_VALID_TIMER_ID(id))
    {
        timerCallBackList[id].timeout = 0;
        timerCallBackList[id].timeoutCopy = 0;
        timerCallBackList[id].callback = NULL;
        retVal = SUCCESS;
    }

    return retVal;
}

RETURN_STATUS middEventTimerDeleteAll(void)
{
    USS i;
    for(i = 0; i < EN_TIMER_MAX_NUM; i++)
    {
        timerCallBackList[i].timeout = 0;
        timerCallBackList[i].timeoutCopy = 0;
        timerCallBackList[i].callback = NULL;
    }

    return SUCCESS;
}


/******************************** End Of File *********************************/
