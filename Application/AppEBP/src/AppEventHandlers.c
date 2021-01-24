/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppEvntHandlers.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "AppEventHandlers.h"
#include "AppWorkingModeManager.h"
#include "AppBITManager.h"
#include <AppEBP.h>

#include "MiddDigitalIOControl.h"
#include "MiddLedController.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/

RETURN_STATUS appEvntHandWorkingMode(const EventStr *event)
{
    RETURN_STATUS retVal = FAILURE;
    switch(event->event)
    {
        case EN_EVENT_BIT:
        {
            DBG_MSG(" ->[I] event::EN_EVENT_BIT");
            appBitCheck();
            printf("\n\n\n------ADC------->\n\n\n\n %d  \n\n\n\n\n\n", _ADC_READ_X_SENSOR());
            break;
        }
        case EN_EVENT_CAN_COMM_MSG:
        {
            DBG_MSG(" ->[I] Working::event::EN_EVENT_CAN_COMM_MSG");
            break;
        }
        case EN_EVENT_SERIAL_COMM:
        {
            DBG_MSG(" ->[I] Working::event::EN_EVENT_SERIAL_COMM");
            retVal = appEBPHandleSerialMsg();
            break;
        }
        case EN_EVENT_KEYPAD:
        {
            DBG_MSG(" ->[I] Working::event::EN_EVENT_KEYPAD");
            retVal = appEBPHandleKeypad((KEYPAD_KEY)event->value);
            break;
        }
        case EN_EVENT_KEYS:
        {
            DBG_MSG(" ->[I] Working::event::EN_EVENT_KEYS");
            retVal = appEBPHandleKeys((KEYS)event->value);
            break;
        }
        case EN_EVENT_SERIAL_COMM_TIMEOUT:
        {
            DBG_MSG(" ->[I] Working::event::EN_EVENT_SERIAL_COMM_TIMEOUT");
            retVal = appEBPDo(EN_JOB_EBP_MSG_TIMEOUT);
            break;
        }
        case EN_EVENT_CHECK_TEMP:
        {
            DBG_MSG(" ->[I] Working::event::EN_EVENT_CHECK_TEMP");
            //Todo
            break;
        }
    }
    return retVal;
}

RETURN_STATUS appEvntHandMaintenanceMode(const EventStr *event)
{
    RETURN_STATUS retVal = FAILURE;
    switch(event->event)
    {
        case EN_EVENT_BIT:
        {
            DBG_MSG("->[I] event::EN_EVENT_BIT");
            appBitCheck();
            break;
        }

        default:
            break;
    }
    return retVal;
}

RETURN_STATUS appEvntHandFailureMode(const EventStr *event)
{
    RETURN_STATUS retVal = FAILURE;
    switch(event->event)
    {
        case EN_EVENT_BIT:
        {
            DBG_MSG("->[I] event::EN_EVENT_BIT");
            appBitCheck();
            break;
        }
        default: break;
    }

    return retVal;
}

/******************************** End Of File *********************************/
