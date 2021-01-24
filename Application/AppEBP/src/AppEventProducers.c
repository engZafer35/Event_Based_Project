/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppEventProducers.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "AppEventProducers.h"

#include "MiddEventTimer.h"
#include "MiddSerialComm.h"
#include "MiddDigitalIOControl.h"
#include "MiddKeypad.h"
#include "MiddKeysCntrl.h"
#include "MiddCanComm.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static union
{
    U32 prioVal;
    struct
    {
        EVENT_PRIORITY  bitPrio         :2;     // 2 bit
        EVENT_PRIORITY  commMsgPrio     :2;     // 2 bit
        EVENT_PRIORITY  digitalIOPrio   :2;     // 2 bit
        EVENT_PRIORITY  keypadPrio      :2;     // 2 bit
        EVENT_PRIORITY  keysPrio 	    :2;     // 2 bit
        EVENT_PRIORITY  uartCommPrio    :2;     // 2 bit
    };
}gEventPriority;
/***************************** STATIC FUNCTIONS  ******************************/
/**
 * @brief feed wdt callback func.
 */
static void cbBIT(void)
{
    appEventThrowEvent(EN_EVENT_BIT, EN_SOURCE_PER_TIMER, gEventPriority.bitPrio, NULL, 0, 0);
}

static void cbCommLine(U32 msgBufIndex)
{
    appEventThrowEvent(EN_EVENT_CAN_COMM_MSG, EN_SOURCE_COMM_LINE, gEventPriority.digitalIOPrio, NULL, 0, msgBufIndex);
}

static void cbKeypad(KEYPAD_KEY key)
{
    appEventThrowEvent(EN_EVENT_KEYPAD, EN_SOURCE_USER_INPUT, gEventPriority.keypadPrio, NULL, 0, key);
}

void cbKeys(KEYS key)
{
	appEventThrowEvent(EN_EVENT_KEYS, EN_SOURCE_USER_INPUT, gEventPriority.keysPrio, NULL, 0, key);
}

void cbSerialComm(void)
{
	appEventThrowEvent(EN_EVENT_SERIAL_COMM, EN_SOURCE_COMM_LINE, gEventPriority.uartCommPrio, NULL, 0, 0);
}

/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS appEvntProdDigitalIO(BOOL stat, EVENT_PRIORITY prio)
{
    RETURN_STATUS retVal = SUCCESS;

    gEventPriority.digitalIOPrio = prio;  /* if stat is FALSE we don't need to clear priority */

    DBG_MSG("->[I] EXT Digital IO Event Producer Status: %d Priority: %d retVal: %d", stat, prio, retVal);
    return retVal;
}

RETURN_STATUS appEvntProdKeypad(BOOL stat, EVENT_PRIORITY prio)
{
    RETURN_STATUS retVal = SUCCESS;

    gEventPriority.keypadPrio = prio; /* if stat is FALSE we don't need to clear priority */
    retVal = midKeypadListener(cbKeypad, stat);

    DBG_MSG("->[I] Keypad Event Producer Status: %d Priority: %d retVal: %d", stat, prio, retVal);
    return retVal;
}

RETURN_STATUS appEvntProdKeys(BOOL stat, EVENT_PRIORITY prio)
{
    RETURN_STATUS retVal = SUCCESS;

    gEventPriority.keysPrio = prio; /* if stat is FALSE we don't need to clear priority */
    retVal = midKeysListener(cbKeys, stat);

    DBG_MSG("->[I] Keys Event Producer Status: %d Priority: %d retVal: %d", stat, prio, retVal);
    return retVal;
}

RETURN_STATUS appEvntProdCanComm(BOOL stat, EVENT_PRIORITY prio)
{
    RETURN_STATUS retVal;

    gEventPriority.commMsgPrio = prio; /* if stat is FALSE we don't need to clear priority */
#ifdef CAN1
    retVal = middCanCommListener(EN_CAN_LINE_1, cbCommLine, stat);
#elif CAN2
    retVal = middCanCommListener(EN_CAN_LINE_2, cbCommLine, stat);
#endif


    DBG_MSG("->[I] EXT Board Comm Event Producer Status: %d Priority: %d retVal: %d", stat, prio, retVal);
    return retVal;
}

RETURN_STATUS appEvntProdSerialComm(BOOL stat, EVENT_PRIORITY prio)
{
    RETURN_STATUS retVal;
    SerialListener lis;
//    U8 filter[] = {0xAA};

    lis.cb 	    = cbSerialComm;
    lis.hFilter = NULL;//filter;
    lis.hLeng	= 0;//sizeof(filter);
    #if CURRENT_BOARD == BOARD_STM_010101
    lis.line    = EN_SERIAL_LINE_6;
    #elif CURRENT_BOARD == BOARD_STM_LP_010101
    lis.line    = EN_SERIAL_LINE_1;
    #endif
    

    gEventPriority.uartCommPrio = prio; /* if stat is FALSE we don't need to clear priority */
    retVal = middSerialCommListener(&lis, stat);

    DBG_MSG("->[I] EXT Board Comm Event Producer Status: %d Priority: %d retVal: %d", stat, prio, retVal);
    return retVal;
}

RETURN_STATUS appEvntProdPerTimer(TimerID tmid, U32 time, BOOL status, EVENT_PRIORITY prio)
{
    RETURN_STATUS retVal = FAILURE;
    VoidCallback cb;

    if (TRUE == status)
    {
        switch(tmid)
        {
            case EN_TIMER_BIT: cb = cbBIT; gEventPriority.bitPrio = prio; break;

            default:
                return FAILURE;
        }

        if (SUCCESS == middEventTimerRegister(tmid, cb, time))
        {
            retVal = middEventTimerStart(tmid);
        }
    }
    else
    {
        /* if stat is FALSE we don't need to clear priority */
        retVal = middEventTimerStop(tmid);
    }

    DBG_MSG("->[I] Periodic Timer Event Producer TimerID: %d Time: %d Status: %d Priority: %d retVal: %d", tmid, time, status, prio, retVal);

    return retVal;
}

RETURN_STATUS appEvntProdStopAll(void)
{
    RETURN_STATUS retVal = SUCCESS;

    gEventPriority.prioVal = 0; //clear all event priority value

    retVal |= appEvntProdDigitalIO(FALSE, EN_PRIORITY_LOW);
    retVal |= appEvntProdCanComm(FALSE,   EN_PRIORITY_LOW);
    retVal |= appEvntProdKeypad(FALSE,    EN_PRIORITY_LOW);
    retVal |= appEvntProdKeys(FALSE,      EN_PRIORITY_LOW);

    retVal |= middEventTimerDeleteAll(); //delete all periodic timer event

    DBG_MSG("->[W] All event producer stoped retval: %d", retVal);
    return retVal;
}
/******************************** End Of File *********************************/
