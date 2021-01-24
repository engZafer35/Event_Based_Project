/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppWorkingModeManager.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "AppWorkingModeManager.h"
#include "AppEventProducers.h"
#include "AppEventManager.h"
#include "AppSystemVariables.h"

#include "MiddMCUCore.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

/***************************** STATIC FUNCTIONS  ******************************/
static RETURN_STATUS setWorkingMode(void)
{
    RETURN_STATUS retVal;

    retVal = appEvntProdStopAll();

    appEventDeleteEvents(); //delete all pending events

    retVal |= appEvntProdDigitalIO( TRUE, EN_PRIORITY_MED);
    retVal |= appEvntProdSerialComm(TRUE, EN_PRIORITY_HIG);
    retVal |= appEvntProdKeypad(    TRUE, EN_PRIORITY_MED);
    retVal |= appEvntProdKeys(      TRUE, EN_PRIORITY_MED);
    /* Can Comm not used*/

    middMCUWdtFeed(); //before set BIT timer, clear wdt !!
    retVal |= appEvntProdPerTimer(EN_TIMER_BIT, BIT_TIME, TRUE, EN_PRIORITY_EMG);  //for periodic timer event

    DBG_MSG("->[I] Set Working Mode retval %d !!!", retVal);
    return retVal;
}

static RETURN_STATUS setFailureMode(void)
{
    RETURN_STATUS retVal;

    retVal = appEvntProdStopAll();

    appEventDeleteEvents(); //delete all pending events

    retVal |= appEvntProdDigitalIO(TRUE, EN_PRIORITY_MED);
    retVal |= appEvntProdSerialComm(TRUE,EN_PRIORITY_HIG);
    retVal |= appEvntProdKeypad(FALSE,    EN_PRIORITY_MED);
    retVal |= appEvntProdKeys(FALSE,     EN_PRIORITY_MED);

    middMCUWdtFeed();
    retVal |= appEvntProdPerTimer(EN_TIMER_BIT, BIT_TIME, TRUE, EN_PRIORITY_EMG);  //for periodic timer event

    DBG_MSG("->[I] Set Failure Mode retval %d !!!", retVal);
    return retVal;
}

/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS appWMSetMode(SYSTEM_WORKING_MODE mode)
{
    RETURN_STATUS retVal = SUCCESS;

    switch(mode)
    {
        case EN_MODE_WORKING:
        {
            retVal = setWorkingMode();
            if (SUCCESS == retVal)
            {
                appSysVarSetMode(EN_MODE_WORKING);
            }
            break;
        }
        case EN_MODE_FAILURE:
        {
            retVal = setFailureMode();
            if (SUCCESS == retVal)
            {
                appSysVarSetMode(EN_MODE_FAILURE);
            }
            break;
        }
    }

    return retVal;
}
/******************************** End Of File *********************************/
