/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddKeypad.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_KEYPAD_H__
#define __MIDD_KEYPAD_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
typedef enum _KEYPAD_KEY
{
    EN_KEYPAD_NONE = 0,
	EN_KEYPAD_1 = 1,
	EN_KEYPAD_2,
	EN_KEYPAD_3,
	EN_KEYPAD_A,

	EN_KEYPAD_4,
	EN_KEYPAD_5,
	EN_KEYPAD_6,
	EN_KEYPAD_B,

	EN_KEYPAD_7,
	EN_KEYPAD_8,
	EN_KEYPAD_9,
	EN_KEYPAD_C,

	EN_KEYPAD_X,
	EN_KEYPAD_0,
	EN_KEYPAD_DZ,
	EN_KEYPAD_D,
}KEYPAD_KEY;

typedef void (*KeypadListener)(KEYPAD_KEY key);
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * \brief  init keypad
 * \param  void
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middKeypadInit(void);

/**
 * \brief  listen keypad interrupt
 * \param  callback function pointer,
 *         listener send character of pressed key
 * \param  TRUE for active, FALSE for passive
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS midKeypadListener(KeypadListener cb, BOOL stat);

/**
 * \brief  read key
 * \param  key number
 * \return TRUE key pressed, FALSE key not pressed
 */
//BOOL middKeypadReadKey(KEYPAD_KEY key);

#endif /* __MIDD_KEYPAD_H__ */
/********************************* End Of File ********************************/
