/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppSystemSetupAndManager.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __APP_SYSTEM_SETUP_AND_MANAGER_H__
#define __APP_SYSTEM_SETUP_AND_MANAGER_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief initialize all system requirement
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appSystemSetup(void);

/**
 * @brief restart system
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appSystemRestart(void);

/**
 * @brief Up Grade SW
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appSystemSWUpgrade(void);

#endif /* APPLICATION_APPCP_INC_APPSYSTEMSETUPANDMANAGER_H_ */

/********************************* End Of File ********************************/
