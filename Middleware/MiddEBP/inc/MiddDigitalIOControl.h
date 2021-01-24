/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddDigitalIOControl.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_DIGITAL_IO_CONTROL_H__
#define __MIDD_DIGITAL_IO_CONTROL_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
/**
 * @brief show status
 */
enum IO_SHOW_STATUS
{
    EN_IO_POWER_STATUS,
    EN_IO_JOB_STATUS,
    EN_IO_ERROR_STATUS
};

typedef enum _EN_IN_LIST
{
    EN_IN_USER_INPUT_1,
    EN_IN_USER_INPUT_2,
    EN_IN_USER_INPUT_3,
    EN_IN_USER_INPUT_4,

	EN_IN_PCA_EXT_INT,
	EN_IN_KEYPAD_INT,

	EN_IN_MAX_NUM

}EN_IN_LIST;

typedef enum _EN_OUT_LIST
{
    EN_OUT_JOB_STATUS_LED,
    EN_OUT_POWER_LED,

	EN_OUT_KEYPAD_RESET,

}EN_OUT_LIST;

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief  init digital IO
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middIOInit(void);

/**
 * @brief  listen a interrupt input(Check whick input support interrupt)
 * @param  input channel
 * @param  callback function pointer
 * @param  TRUE for active, FALSE for passive
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middIOIntListen(EN_IN_LIST in, VUICallback cb, BOOL stat);

/**
 * @brief  set output
 * @param  output channel list
 * @param  ENABLE active, DISABLE passif
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middIOWrite(EN_OUT_LIST out, BOOL stat);

/**
 * @brief  read input
 * @param  input channel list
 * @return 1 or 0, (TRUE, FALSE)
 */
BOOL middIORead(EN_IN_LIST in);

/**
 * @brief  set output
 * @param  output ID
 * @param  status, enable or disable
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middIOCtrlShowStatusInfo(enum IO_SHOW_STATUS id, BOOL status);

/**
 * @brief  set output
 * @param  output ID
 * @param  status, enable or disable
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middIOCtrlToggleStatusInfo(enum IO_SHOW_STATUS id);

/**
 * @brief  read board ID
 * @param  void
 * @return if everything is OK, return input value
 *         otherwise return (-1)(FAILURE)
 */
S32 middIOCtrlGetBoardID(void);

#endif /* __MIDD_DIGITAL_IO_CONTROL_H__ */

/********************************* End Of File ********************************/
