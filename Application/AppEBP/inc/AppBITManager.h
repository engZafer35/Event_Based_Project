/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppBITManager.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __APP_BIT_MANAGER_H__
#define __APP_BIT_MANAGER_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
/*
 * @brief error list
 * @note  don't delete or move any item. just add end of list.
 */
enum ERROR_LIST
{
    EN_ERR_SYSTEM_INIT,
    EN_ERR_CAN_COM_ERROR,
    EN_ERR_RS422_COM_ERROR,
    EN_ERR_INTERNAL_ERROR,

    EN_ERR_MAX_NUM
};
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief  init BIT module
 * @param  void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appBITInit(void);

/**
 * @brief power on BIT. call after all system initialize
 *        After appBitInit() call this func. isPbitOK is TRUE
 *        WDT will begin.
 * @return void
 */
void appBitPBIT(void);

/**
 * @brief  set error or clear error
 * @param  error ID
 * @param  error status, TRUE or FALSE
 * @return void
 */
void appBitSetError(enum ERROR_LIST error, BOOL status);

/**
 * @brief check system error and some units
 * @note  the function should be invoked periodical
 */
void appBitCheck(void);

#endif /* __APP_BIT_MANAGER_H__ */

/********************************* End Of File ********************************/
