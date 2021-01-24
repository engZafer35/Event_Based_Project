/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : ProjectConf.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __PROJECT_CONF_H_
#define __PROJECT_CONF_H_
/*********************************INCLUDES*************************************/
#include "GeneralBoardConfig.h"
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/
#define SW_VERSION_MAJOR (0x01)
#define SW_VERSION_MINOR (0x00)
#define SW_VERSION_BUGFX (0x00)

/* ********************** Debug Macros **********************/

#define ALL_DBG_MSG_ACTIVE      (ENABLE)//(DISABLE)//
#include <stdio.h>

#ifndef SHOW_PAGE_DBG_MSG
    #define SHOW_PAGE_DBG_MSG  (ENABLE)
#endif

#if (ALL_DBG_MSG_ACTIVE || SHOW_PAGE_DBG_MSG)

#define DBG_MSG(format, args...) fprintf(stdout, "-> %s():%d: ", __FUNCTION__, __LINE__), \
                                 fprintf(stdout, format , ##args), \
                                 fprintf(stdout, "\n\r")
#else
#define DBG_MSG(format, args...)
#endif

/*-------------- SYSTEM PARAMETERS ----------*/
/**
 * set hw timer period (ms), System need two hardware timer and both period should be same.
 * MIN_TIMER_PERIOD_MS will used in MiddSysTimer and MiddEventTimer
 */
#define MIN_TIMER_PERIOD_MS (10)
#if ((MIN_TIMER_PERIOD_MS  <= 0)) //|| (!(defined MIN_TIMER_PERIOD_MS)))
#error "Hardware timer period is not know. Please set MIN_TIMER_PERIOD_MS macros"
#endif

/*******************************TYPE DEFINITIONS ******************************/
//use for timer event id
typedef enum _TimerID
{
    EN_TIMER_BIT,
    #define BIT_TIME                    (WAIT_1_SEC)

    EN_TIMER_PERIODIC_CAN_MSG,
    #define PERIODIC_CAN_MSG_BASE_TIME  (0) /* !< if not need to send periodically can message, set 0 */

    EN_TIMER_MAX_NUM
}TimerID;

typedef enum _SYSTEM_WORKING_MODE
{
    EN_MODE_WORKING,
    EN_MODE_FAILURE,
}SYSTEM_WORKING_MODE;

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/


#endif /* __PROJECT_CONF_H_ */

/********************************* End Of File ********************************/
