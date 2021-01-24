/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppEventHandlers.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __APP_EVNT_HANDLERS_H__
#define __APP_EVNT_HANDLERS_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
#include "AppEventManager.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief handle event in working mode
 * @param event pointer
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntHandWorkingMode(const EventStr *event);

/**
 * @brief handle event when device closed
 * @param event pointer
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntHandClosedMode(const EventStr *event);

/**
 * @brief handle event in working mode
 * @param event pointer
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntHandMaintenanceMode(const EventStr *event);

/**
 * @brief handle event in working mode
 * @param event pointer
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appEvntHandFailureMode(const EventStr *event);
#endif /* __APP_EVNT_HANDLERS_H__ */

/********************************* End Of File ********************************/
