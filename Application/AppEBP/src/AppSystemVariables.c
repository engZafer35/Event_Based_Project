/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppSystemVariables.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "AppSystemVariables.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static struct SystemVar gSystemValues;

/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS appSysVarInit(void)
{
    RETURN_STATUS retVal = SUCCESS;

    //todo load gSystemValues from eeprom

    DBG_MSG("->[I] Starting Sys Value List:\n\r"      \
            "->[I] Sys Mode: %d\n\r"                  \
            ,gSystemValues.mode
            );

    return retVal;
}

/**
 * @brief get system mode
 * @param void
 * @return current system mode
 */
SYSTEM_WORKING_MODE appSysVarGetMode(void)
{
    return gSystemValues.mode;
}

void appSysVarSetMode(SYSTEM_WORKING_MODE mod)
{
    gSystemValues.mode = mod;
}

/******************************** End Of File *********************************/
