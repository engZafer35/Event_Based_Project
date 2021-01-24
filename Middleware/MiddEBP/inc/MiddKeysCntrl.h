/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddKeysCntrl.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_KEYS_CNTRL_H__
#define __MIDD_KEYS_CNTRL_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
typedef enum _KEYS
{
    EN_KEY_NONE,

    EN_KEY_S1_ON,
    EN_KEY_S1_OFF,

    EN_KEY_S2_ON ,
    EN_KEY_S2_OFF ,

    EN_KEY_S3_ON,
    EN_KEY_S3_OFF,

    EN_KEY_S4_ON,
    EN_KEY_S4_OFF,

    EN_KEY_S5_ON,
    EN_KEY_S5_OFF,

    EN_KEY_S6_ON,
    EN_KEY_S6_OFF,

    EN_KEY_S7_ON,
    EN_KEY_S7_OFF,

    EN_KEY_S8_ON,
    EN_KEY_S8_OFF,

}KEYS;

struct KeyStat
{
    U8 tca1_0;
    U8 tca1_1;
};

typedef void (*KeysListener)(KEYS key);
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * \brief  init keys
 * \param  void
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middKeysInit(void);

/**
 * \brief  listen keypad interrupt
 * \param  callback function pointer
 * \param  TRUE for active, FALSE for passive
 * \return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS midKeysListener(KeysListener cb, BOOL stat);

/**
 * \brief  read key
 * \param  key number
 * \return TRUE key pressed, FALSE key not pressed
 */
RETURN_STATUS middKeyRead(struct KeyStat* ks);

#endif /* __MIDD_KEYS_CNTRL_H__ */

/********************************* End Of File ********************************/
