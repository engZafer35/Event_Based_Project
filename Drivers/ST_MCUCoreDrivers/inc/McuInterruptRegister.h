/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 15, 2021 - 9:05:66 AM
* #File Name    : McuInterruptRegister.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MCU_INTERRUPT_REGISTER_H__
#define __MCU_INTERRUPT_REGISTER_H__
/*********************************INCLUDES*************************************/
#include "ProjectConf.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief   register for core interrupt
 * @param   callback func, interrupt type id
 * @return  if everything is OK, return SUCCES
 *           otherwise return FAILURE
 */
RETURN_STATUS drvIntRegister(VICallback callbackFunc, EN_INTERRUPT_LIST intType);

/**
 * @brief   unregister for core interrupt
 * @param   interrupt type id
 * @return  if everything is OK, return SUCCES
 *           otherwise return FAILURE
 */
RETURN_STATUS drvIntUnregister(EN_INTERRUPT_LIST intType);

#endif /* __MCU_INTERRUPT_REGISTER_H__ */

/********************************* End Of File ********************************/
