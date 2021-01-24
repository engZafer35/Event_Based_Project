/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppEBP.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __APP_EBP_H__
#define __APP_EBP_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
#include "MiddKeypad.h"
#include "MiddKeysCntrl.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
typedef enum _SKP_DO
{
    EN_JOB_EBP_MSG_TIMEOUT,
    EN_JOB_EBP_TEMP_CHECK,

    EN_JOB_EBP_MAX_VALUE
}EBP_DO;
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

RETURN_STATUS appEBPInit(void);

RETURN_STATUS appEBPHandleKeypad(KEYPAD_KEY key);

RETURN_STATUS appEBPHandleKeys(KEYS key);

RETURN_STATUS appEBPHandleSerialMsg(void);

RETURN_STATUS appEBPHandleCanMsg(const U8* msg, U32 len);

RETURN_STATUS appEBPDo(EBP_DO doo);

#endif /* __APP_EBP_H__ */

/********************************* End Of File ********************************/
