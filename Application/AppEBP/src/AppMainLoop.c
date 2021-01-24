/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppMainLoop.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "AppMainLoop.h"

#include "AppSystemVariables.h"
#include "AppEventManager.h"
#include "AppEventHandlers.h"
#include "AppWorkingModeManager.h"

#include "MiddDigitalIOControl.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

/***************************** STATIC FUNCTIONS  ******************************/
static RETURN_STATUS handleEvent(EventStr *event)
{
    RETURN_STATUS retVal = SUCCESS;

    switch(appSysVarGetMode())
    {
        case EN_MODE_WORKING:
        {
            retVal = appEvntHandWorkingMode(event);
            break;
        }
        case EN_MODE_FAILURE:
        {
            retVal = appEvntHandFailureMode(event);
            break;
        }
    }

    return retVal;
}
/***************************** PUBLIC FUNCTIONS  ******************************/

RETURN_STATUS appMLInit(void)
{
    RETURN_STATUS retVal = SUCCESS;

    return retVal;
}

RETURN_STATUS appMLRun(void)
{
    RETURN_STATUS retVal = SUCCESS;
    EventStr *event;

    appWMSetMode(appSysVarGetMode());
    appEventStart();

    DBG_MSG("\n\n\r <---------------------> EBP(Event Based Project <--------------------->\n\n\r");

    while(1)
    {
        event = appEventGet(0, EN_SOURCE_ALL);

        if (NULL != event)
        {
            handleEvent(event);
            appEventClearEvent(event);
        }

        middIOCtrlToggleStatusInfo(EN_IO_JOB_STATUS);
    }

    return retVal;
}
/******************************** End Of File *********************************/
