/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddCanComm.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_COMM_H__
#define __MIDD_COMM_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"

/******************************MACRO DEFINITIONS*******************************/
/** Max periodic can message number */
#define MAX_PERIODIC_MSG_NUM	(4)

/** can circular buffer max index */
#define MAX_MSG_BUFFER_NUM      (64)

/** Active used lines */
#define CAN_1
//#define CAN_2

#if !defined(CAN_1) && !defined(CAN_2)
#error "Both CAN_1 and CAN_2 undefined."
#endif
/*******************************TYPE DEFINITIONS ******************************/
typedef enum _CAN_LINES
{
#ifdef CAN_1
    EN_CAN_LINE_1,
    #define CAN_1_INTR_ID  (EN_CAN1_RX0_IRQ) //set correct hw interrupt ID
#endif

#ifdef CAN_2
    EN_CAN_LINE_2,
    #define CAN_2_INTR_ID  (EN_CAN2_RX0_IRQ) //set correct hw interrupt ID
#endif
    EN_CAN_LINE_MAX_NUM,
}CAN_LINES;

typedef struct _CanBusFrame
{
    U32 id; /** !< can bus message identify, supports can-bus CAN2.0B */
    U32 rtr;  /** !< 0 for data message, 1 for request message */
    U32 ide;  /** !< 0 for CAN2.0A (11 bit ide), 1 for CAN2.0B(29 bit ide) */
    U8  data[8];
    U8  dlc; /** data leng it can get max 8 */
}CanBusFrame;
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

/**
 * \brief init Can comm
 * \return if everything is OK, return SUCCES, otherwise return FAILURE
 * \note: can device is not be init here. So for use MiddCanComm, user should
 *        init can line before.
 */
RETURN_STATUS MiddCanCommInit(void);

/**
 * \brief can line msg listener
 * \param line
 * \param callback
 * \param status, 1:listen, 0:cancel listen. not matter cb when stat is 0
 * \return if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS middCanCommListener(CAN_LINES line, VUICallback cb, BOOL stat);

/**
 * \brief  send Data
 * \param  line
 * \param  can bus frame pointer
 * \param  timeout
 * \return if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS middCanCommSend(CAN_LINES ln, const CanBusFrame* frame, U32 timeout);

/**
 * \brief  get latest index number
 * \param  line
 * \return if everything is OK, return index number,
 *         otherwise return FAILURE(-1)
 */
S32 middCanCommGetBuffIndex(CAN_LINES ln);

/**
 * \brief  receive Data
 * \param  line
 * \param  can bus frame pointer
 * \param  buff index
 * \return if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS middCanCommRcv(CAN_LINES ln, CanBusFrame* msg, U32 bufIndex);

/**
 * \brief send periodic message
 * \param line
 * \param can bus frame pointer.
 * \return if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS middCanCommLoadPeriodicMsg(CAN_LINES ln, const CanBusFrame* frame, U32 period);

/**
 * \brief update periodic message
 * \param can bus frame pointer
 * \return if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS midddCanCommUpdatePeriodicMsg(U32 msgCanID, const U8 msgData[8]);

/**
 * \brief cancel periodic can message
 * \param canbus msg id. For standart msg, msgID is 11 bit, for extended msg, msgID is 29 bit
 * \return if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS midddCanCommCancelPeriodicMsg(U32 msgCanID);

#endif /* __MIDD_COMM_H__ */
/********************************* End Of File ********************************/
