/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppSystemVariables.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __APP_SYSTEM_VARIABLES_H__
#define __APP_SYSTEM_VARIABLES_H__
/*********************************INCLUDES*************************************/
#include "ProjectConf.h"

/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
struct SystemVar
{
    SYSTEM_WORKING_MODE mode;
};

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief  init system variables
 * @param  void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appSysVarInit(void);

/**
 * @brief get system mode
 * @param void
 * @return current system mode
 */
SYSTEM_WORKING_MODE appSysVarGetMode(void);

void appSysVarSetMode(SYSTEM_WORKING_MODE mod);

#endif /* __APP_SYSTEM_VARIABLES_H__ */

/********************************* End Of File ********************************/
