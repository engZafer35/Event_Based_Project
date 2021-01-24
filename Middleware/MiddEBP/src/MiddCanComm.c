/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddCanComm.c
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include <string.h>

#include "ProjectConf.h"

#include "MiddCanComm.h"
#include "MiddEventTimer.h"
#include "MiddSysTimer.h"

#include "McuInterruptRegister.h"
/****************************** MACRO DEFINITIONS *****************************/
#define DATA_MSG_RTR            (0)
#define REQUEST_MSG_RTR         (1)

#define STANDART_FRAME_IDE      (0)
#define EXTENDED_FRAME_IDE      (4) // 4 for extended frame

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
struct PeriodicMsg
{
    S32 period;
    U32 periodCopy;
    CAN_LINES line;
    CanBusFrame msg;
}perMsg[MAX_PERIODIC_MSG_NUM];

#ifdef CAN_1
U32 index1;
CanBusFrame rcvMsg_1[MAX_MSG_BUFFER_NUM];
VUICallback cb1;
#endif

#ifdef CAN_2
U32 index2;
CanBusFrame rcvMsg_2[MAX_MSG_BUFFER_NUM];
VUICallback cb2;
#endif
/***************************** STATIC FUNCTIONS  ******************************/
static RETURN_STATUS rcvMsg(CAN_LINES ln, CanBusFrame* msg)
{
    RETURN_STATUS retVal = FAILURE;
    DRV_CAN_RX_HEADER rcvHead;

#if defined CAN_2 && defined CAN_1
    if (DRV_RET_SUCCESS == HAL_CAN_GET_RX_MESSAGE((ln == EN_CAN_LINE_1) ? &CAN_LINE1 : &CAN_LINE2, 0, &rcvHead, msg->data))
#elif defined CAN_1
    if (DRV_RET_SUCCESS == HAL_CAN_GET_RX_MESSAGE(&CAN_LINE1, 0, &rcvHead, msg->data))
#elif defined CAN_2
    if (DRV_RET_SUCCESS == HAL_CAN_GET_RX_MESSAGE(&CAN_LINE2, 0, &rcvHead, msg->data))
#endif
    {
    	msg->id  = ((0 != rcvHead.IDE) ? rcvHead.ExtId : rcvHead.StdId);
        msg->rtr = rcvHead.RTR;
        msg->ide = rcvHead.IDE;
        msg->dlc = rcvHead.DLC;

        retVal = SUCCESS;
    }

    return retVal;
}

#ifdef CAN_1
static void cbMsg1(int unused)
{
    if (SUCCESS == rcvMsg(EN_CAN_LINE_1, &rcvMsg_1[index1]))
    {
        if (index1 >= MAX_MSG_BUFFER_NUM)
        {
            index1 = 0;
        }

        if (NULL != cb1)
        {
            cb1(index1); //call app layer callback
        }
    }
}
#endif

#ifdef CAN_2
static void cbMsg2(int unused)
{
	CanBusFrame temp;

    if (SUCCESS == rcvMsg(EN_CAN_LINE_2, &temp))
    {
        if (index2 >= MAX_MSG_BUFFER_NUM)
        {
            index2 = 0;
        }

        if (NULL != cb2)
        {
        	//software filter
//           if ((temp.id == xx) || (temp.id == yy) || (temp.id == xx))
            {
                rcvMsg_2[index2] = temp;
                cb2(index2); //call app layer callback
                index2++;
            }
        }
    }
}
#endif

static void canCallPer(void)
{
    static USS i;

    for (i = 0; i < MAX_PERIODIC_MSG_NUM; i++)
    {
        if (perMsg[i].period > 0)
        {
            perMsg[i].period -= PERIODIC_CAN_MSG_BASE_TIME;

            //timer finished. Send Msg
            if (perMsg[i].period < PERIODIC_CAN_MSG_BASE_TIME)
            {
                perMsg[i].period = perMsg[i].periodCopy; //restart timer

                middCanCommSend(perMsg[i].line, &perMsg[i].msg, 0);
            }
        }
    }
}

/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS MiddCanCommInit(void)
{
    RETURN_STATUS retVal = SUCCESS;
    U32 z;

    for (z = 0; z < MAX_PERIODIC_MSG_NUM; ++z)
    {
        perMsg[z].period = -1; //-1 init value
    }

#ifdef CAN_1
    index1 = 0;
    cb1 = NULL;
    retVal |= drvIntRegister(cbMsg1, EN_CAN1_RX0_IRQ);
#endif

#ifdef CAN_2
    index2 = 0;
    cb2 = NULL;
    retVal |= drvIntRegister(cbMsg2, EN_CAN2_RX0_IRQ);
#endif

    if (PERIODIC_CAN_MSG_BASE_TIME > 0)
    {
        if (SUCCESS == middEventTimerRegister(EN_TIMER_PERIODIC_CAN_MSG, canCallPer, PERIODIC_CAN_MSG_BASE_TIME))
        {
            retVal = middEventTimerStart(EN_TIMER_PERIODIC_CAN_MSG);
        }
    }

    return retVal;
}

RETURN_STATUS middCanCommListener(CAN_LINES line, VUICallback cb, BOOL stat)
{
    RETURN_STATUS retVal = FAILURE;

    if (IS_SAFELY_PTR(cb) && (line < EN_CAN_LINE_MAX_NUM))
    {
#if defined CAN_2 && defined CAN_1
        retVal = SUCCESS;
        if (EN_CAN_LINE_1 == line)
        {
            cb1 = (TRUE == stat) ? cb : NULL;
        }
        else
        {
            cb2 = (TRUE == stat) ? cb : NULL;
        }
#elif defined CAN_1
        if (EN_CAN_LINE_1 == line)
        {
            cb1 = (TRUE == stat) ? cb : NULL;
            retVal = SUCCESS;
        }

#elif defined CAN_2
        if (EN_CAN_LINE_2 == line)
        {
            cb2 = (TRUE == stat) ? cb : NULL;
            retVal = SUCCESS;
        }
#endif
    }

    return retVal;
}

RETURN_STATUS middCanCommLoadPeriodicMsg(CAN_LINES ln, const CanBusFrame* frame, U32 period)
{
    RETURN_STATUS retVal = FAILURE;
    U32 z;

    if (IS_SAFELY_PTR(frame))
    {
        for (z = 0; z < MAX_PERIODIC_MSG_NUM; ++z)
        {
            if (-1 == perMsg[z].period ) //find empty place
            {
                perMsg[z].period     = period;
                perMsg[z].periodCopy = period;
                perMsg[z].line       = ln;
                perMsg[z].msg        = (*frame);

                retVal = SUCCESS;
                break;
            }
        }
    }

    return retVal;
}

RETURN_STATUS midddCanCommUpdatePeriodicMsg(U32 msgCanID, const U8 msgData[8])
{
    RETURN_STATUS retVal = FAILURE;
    U32 z;

    if (IS_SAFELY_PTR(msgData))
    {
        for (z = 0; z < MAX_PERIODIC_MSG_NUM; ++z)
        {
            if (msgCanID == perMsg[z].msg.id)
            {
                memcpy(perMsg[z].msg.data, msgData, sizeof(perMsg[z].msg.data));
                retVal = SUCCESS;
                break;
            }
        }
    }

    return retVal;
}

RETURN_STATUS midddCanCommCancelPeriodicMsg(U32 msgCanID)
{
    RETURN_STATUS retVal = FAILURE;
    U32 z;

    for (z = 0; z < MAX_PERIODIC_MSG_NUM; ++z)
    {
        if (msgCanID == perMsg[z].msg.id)
        {
            perMsg[z].period = -1;
            //dont need to clear other values
            retVal = SUCCESS;
            break;
        }
    }

    return retVal;
}

RETURN_STATUS middCanCommSend(CAN_LINES ln, const CanBusFrame* frame, U32 timeout)
{
    RETURN_STATUS retVal = FAILURE;
    DRV_CAN_TX_HEADER txHeader;

    if (frame->ide)
    {
        txHeader.ExtId = frame->id;
        txHeader.StdId = 0;
    }
    else
    {
        txHeader.StdId = frame->id;
        txHeader.ExtId = 0;
    }

    txHeader.IDE    = 4;//frame->ide;
    txHeader.RTR    = frame->rtr;
    txHeader.DLC    = frame->dlc;
    txHeader.TransmitGlobalTime = DISABLE;
#if defined CAN_2 && defined CAN_1
    if (DRV_RET_SUCCESS == CAN_ADD_TX_MESSAGE((ln == EN_CAN_LINE_1) ? &CAN_LINE1 : &CAN_LINE2, &txHeader, (U8*)frame->data, NULL))
    {
        retVal = SUCCESS;
    }

#elif defined CAN_1
    if (DRV_RET_SUCCESS == CAN_ADD_TX_MESSAGE(&CAN_LINE1, &txHeader, (U8*)frame->data, NULL))
    {
        retVal = SUCCESS;
    }
#elif defined CAN_2
    if (DRV_RET_SUCCESS == CAN_ADD_TX_MESSAGE(&CAN_LINE2, &txHeader, (U8*)frame->data, NULL))
    {
        retVal = SUCCESS;
    }
#endif
    return retVal;
}

RETURN_STATUS middCanCommRcv(CAN_LINES ln, CanBusFrame* frame, U32 bufIndex)
{
    RETURN_STATUS retVal = FAILURE;
    if (IS_SAFELY_PTR(frame))
    {
#if defined CAN_2 && defined CAN_1
        if (EN_CAN_LINE_1 == ln)
        {
        	memcpy(frame, &rcvMsg_1[bufIndex], sizeof(rcvMsg_1[bufIndex]));
        	retVal = SUCCESS;
        }
        else if (EN_CAN_LINE_2 == ln)
        {
        	memcpy(frame, &rcvMsg_2[bufIndex], sizeof(rcvMsg_2[bufIndex]));
        	retVal = SUCCESS;
        }
#elif defined CAN_1
        if (EN_CAN_LINE_1 == ln)
        {
            memcpy(frame, &rcvMsg_1[bufIndex], sizeof(rcvMsg_1[bufIndex]));
            retVal = SUCCESS;
        }
#elif defined CAN_2
        if (EN_CAN_LINE_2 == ln)
        {
            memcpy(frame, &rcvMsg_2[bufIndex], sizeof(rcvMsg_2[bufIndex]));
            retVal = SUCCESS;
        }
#endif
    }

    return retVal;
}

S32 middCanCommGetBuffIndex(CAN_LINES ln)
{
    S32 retIndex = -1;
#if defined CAN_2 && defined CAN_1
    if (EN_CAN_LINE_1 == ln)
    {
        retIndex = index1;
    }
    else if (EN_CAN_LINE_2 == ln)
    {
        retIndex = index2;
    }
#elif defined CAN_1
    if (EN_CAN_LINE_1 == ln)
    {
        retIndex = index1;
    }
#elif defined CAN_2
    if (EN_CAN_LINE_2 == ln)
    {
        retIndex = index2;
    }
#endif

    return retIndex;
}
/******************************** End Of File *********************************/
