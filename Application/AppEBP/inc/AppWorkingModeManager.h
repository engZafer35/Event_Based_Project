/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppWorkingModeManager.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __APP_WORKING_MODE_MANAGER_H__
#define __APP_WORKING_MODE_MANAGER_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/*
 * @brief set working mode
 * @note  all event producer will set in this function.
 */
RETURN_STATUS appWMSetMode(SYSTEM_WORKING_MODE mode);

#endif /* __APP_WORKING_MODE_MANAGER_H__ */

/********************************* End Of File ********************************/
