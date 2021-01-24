/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddSysTimer.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "MiddSysTimer.h"
#include "ProjectConf.h"
#include "McuInterruptRegister.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static struct
{
    U32 time;
    U32 alert;
    VoidCallback cb;
}gAlertTime[MAX_ALERT_TIMER];

/***************************** STATIC FUNCTIONS  ******************************/
/* timerCallback is linked to HW timer,
 * so don't do big job in this callback function
 */
static void timerCallback(int x)
{
    USS i;

    for (i = 0; i < MAX_ALERT_TIMER; i++)
    {
        if (gAlertTime[i].time > 0)
        {
            gAlertTime[i].time -= MIN_TIMER_PERIOD_MS;

            if (gAlertTime[i].time < MIN_TIMER_PERIOD_MS)
            {
                gAlertTime[i].alert = TRUE;
                if (NULL != gAlertTime[i].cb)
                {
                    gAlertTime[i].cb();
                }
            }
        }
    }
}
#ifdef WORKING_PLATFORM_PC
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
static void testThread(void)
{
    printf("\n      #> middEvent TestThread Running ... <# \n");
    while(1)
    {
        usleep(10000);
        timerCallback(0);
    }
}
#endif
/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS middSysTimerInit()
{
    RETURN_STATUS retVal;

    //global alert struct 0.  not need to clear

    retVal = drvIntRegister(timerCallback, TIMER_ALERT_IT_ID);

    DBG_MSG("-> [I]middSysTimerInit return %d", retVal);

#ifdef WORKING_PLATFORM_PC
    pthread_t thread_id;
    if (0 == pthread_create(&thread_id, NULL, testThread, NULL))
    {
        printf("---- SYSTEM TIMER Test Thread Created ..... \n");
    }
#endif
    return retVal;
}

void middSysTimerDelayMs(U32 timeMs)
{
    DELAY_MS(timeMs);
}

U32 middSysTimerGetTick(void)
{
    U32 sysTick = 666;
    //TODO:
    return sysTick;
}

USS middSysTimerSetTimer(U32 timerMs, VoidCallback cb)
{
    USS timerID = -1; //error value
    USS i;
    USS ru;

    //round up
    ru = (timerMs % MIN_TIMER_PERIOD_MS);
    if (0 != ru)
    {
        timerMs += MIN_TIMER_PERIOD_MS - ru;
    }

    for (i = 0; i < MAX_ALERT_TIMER; i++)
    {
        if (0 == gAlertTime[i].time)
        {
            timerID = i;
            gAlertTime[i].time  = timerMs;
            gAlertTime[i].alert = FALSE;
            gAlertTime[i].cb    = cb;
            break;
        }
    }

    return timerID;
}

void middSysTimerClearTimer(USS timerID)
{
    if (timerID < MAX_ALERT_TIMER)
    {
        gAlertTime[timerID].time  = 0;
        gAlertTime[timerID].alert = FALSE;
        gAlertTime[timerID].cb    = NULL;
    }
}

BOOL middSysTimerIsTimerOK(USS timerID)
{
    if ((gAlertTime[timerID].time == 0) && (timerID < MAX_ALERT_TIMER))
    {
        return gAlertTime[timerID].alert;
    }

    return FALSE;
}

/******************************** End Of File *********************************/
