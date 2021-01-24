/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppSKP.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include <string.h>
#include "ProjectConf.h"
#include "AppEBP.h"
#include "AppEventManager.h"

#include "MiddSerialComm.h"
#include "MiddKeysCntrl.h"
#include "MiddKeypad.h"
#include "MiddLedController.h"
#include "MiddSysTimer.h"
#include "MiddTimeTempInfo.h"
/****************************** MACRO DEFINITIONS *****************************/
#define MSG_ID_TIME_REQ    (0X01)
#define MSG_ID_TEMP_REQ    (0X02)
#define MSG_ID_SET_TIME    (0X03)
/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static union
{
    U32 allLedStat;
    struct
    {
        U32 led1    :1;
        U32 led2    :1;
        U32 led3    :1;
        U32 led4    :1;
        U32 led5    :1;
        U32 led6    :1;
        U32 led7    :1;
        U32 led8    :1;
    };
}gLedStatus;

static struct KeyStr
{
    U32 key1    :1;
    U32 key2    :1;
    U32 key3    :1;
    U32 key4    :1;
    U32 key5    :1;
    U32 key6    :1;
    U32 key7    :1;
    U32 key8    :1;

    U32 keypad  :8; //keypad

}gKeyStatus;

static U32 msgTimeoutTimerID;
static U32 msgTimeout;
/***************************** STATIC FUNCTIONS  ******************************/

static RETURN_STATUS updateLedStatus(void)
{
    RETURN_STATUS retVal;

    middLedLoadLedStat(EN_LED_LED1, gLedStatus.led1);
    middLedLoadLedStat(EN_LED_LED2, gLedStatus.led2);
    middLedLoadLedStat(EN_LED_LED3, gLedStatus.led3);
    middLedLoadLedStat(EN_LED_LED4, gLedStatus.led4);
    middLedLoadLedStat(EN_LED_LED5, gLedStatus.led5);
    middLedLoadLedStat(EN_LED_LED6, gLedStatus.led6);
    middLedLoadLedStat(EN_LED_LED7, gLedStatus.led7);
    middLedLoadLedStat(EN_LED_LED8, gLedStatus.led8);

    retVal = middLedFlush();

    return retVal;
}

void msgTimeoutCb(void) //this function is in timer interrupt. if any problem, it can move AppEventHandler.
{
    middSysTimerClearTimer(msgTimeoutTimerID);
    msgTimeoutTimerID = 0xFFFFFFFF; //clear timerID

    appEventThrowEvent(EN_EVENT_SERIAL_COMM_TIMEOUT, EN_SOURCE_INTERNAL, EN_PRIORITY_MED, NULL, 0, 0);
}

static RETURN_STATUS loadKeyStatus(struct KeyStr* keys)
{
    RETURN_STATUS retVal = FAILURE;
    struct KeyStat ks;

    if (SUCCESS == middKeyRead(&ks))
    {
        gKeyStatus.key1 = ks.tca1_0 & 0x01;
        gKeyStatus.key2 = !!(ks.tca1_0 & 0x02);
        gKeyStatus.key3 = !!(ks.tca1_0 & 0x04);
        gKeyStatus.key4 = !!(ks.tca1_0 & 0x08);
        gKeyStatus.key5 = !!(ks.tca1_0 & 0x10);
        gKeyStatus.key6 = !!(ks.tca1_0 & 0x20);
        gKeyStatus.key6 = !!(ks.tca1_0 & 0x40);
        gKeyStatus.key6 = !!(ks.tca1_0 & 0x80);

        retVal = SUCCESS;
    }

    return retVal;
}
/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS appEBPInit(void)
{
    msgTimeout = WAIT_20_SEC; //default timeout 20sec
    msgTimeoutTimerID = middSysTimerSetTimer(msgTimeout, msgTimeoutCb);

    return loadKeyStatus(&gKeyStatus);
}

RETURN_STATUS appEBPHandleKeypad(KEYPAD_KEY key)
{
	U8 chr = 0;

	if (EN_KEYPAD_NONE == key)
	{
	    chr = 0;
	}
	else if (key == EN_KEYPAD_A)
	{
	    chr = 'A';
	}
    else if (key == EN_KEYPAD_B)
    {
        chr = 'B';
    }
    else if (key == EN_KEYPAD_C)
    {
        chr = 'C';
    }
    else if (key == EN_KEYPAD_D)
    {
        chr = 'D';
    }
	else if ((key >= EN_KEYPAD_1) && (key <= EN_KEYPAD_A))
	{
	    chr = key + '0';
	}
    else if ((key >= EN_KEYPAD_4) && (key <= EN_KEYPAD_B))
    {
        chr = key + '0' -1; //skip 'A'
    }
    else if ((key >= EN_KEYPAD_7) && (key <= EN_KEYPAD_C))
    {
        chr = key + '0' -2; //skip 'B'
    }
	else if (EN_KEYPAD_0 == key)
	{
	    chr = '0';
	}
	else if (EN_KEYPAD_X == key)
	{
	    chr = '*';
	}
	else if (EN_KEYPAD_DZ == key)
	{
	    chr = '#';
	}

	gKeyStatus.keypad = chr;

	DBG_MSG(" ->[I] Keypad Key: %c", chr);

	return SUCCESS;
}

#if 1 //!!!!!!!!!! test !!!!!!!!
#include "MiddCanComm.h"
void canCb(U32 bufIndex)
{
    CanBusFrame frm;
#ifdef CAN1
    middCanCommRcv(EN_CAN_LINE_1, &frm, bufIndex);
    middCanCommSend(EN_CAN_LINE_1, &frm, 300);
#elif CAN2
    middCanCommRcv(EN_CAN_LINE_2, &frm, bufIndex);
    middCanCommSend(EN_CAN_LINE_2, &frm, 300);
#endif


}

RETURN_STATUS appEBPHandleKeys(KEYS key)  //!!!!!!!!!! test function !!!!!!!!
{
    RETURN_STATUS retVal = SUCCESS;
    static int test = 0;

    if (0 == test)
    {
        test = 1;
#ifdef CAN1
        middCanCommListener(EN_CAN_LINE_1, canCb, TRUE);
#elif CAN2
        middCanCommListener(EN_CAN_LINE_2, canCb, TRUE);
#endif

    }

    DBG_MSG(" ->[I] Keys: %02d", key);

    switch(key)
    {
        case EN_KEY_S1_ON:  middLedSet(EN_LED_LED1, TRUE);  break;
        case EN_KEY_S1_OFF: middLedSet(EN_LED_LED1, FALSE); break;

        case EN_KEY_S2_ON:  middLedSet(EN_LED_LED2, TRUE);  break;
        case EN_KEY_S2_OFF: middLedSet(EN_LED_LED2, FALSE); break;

        case EN_KEY_S3_ON:  middLedSet(EN_LED_LED3, TRUE);  break;
        case EN_KEY_S3_OFF: middLedSet(EN_LED_LED3, FALSE); break;

        case EN_KEY_S4_ON:  middLedSet(EN_LED_LED4, TRUE);  break;
        case EN_KEY_S4_OFF: middLedSet(EN_LED_LED4, FALSE); break;

        case EN_KEY_S5_ON:  middLedSet(EN_LED_LED5, TRUE);  break;
        case EN_KEY_S5_OFF: middLedSet(EN_LED_LED5, FALSE); break;

        case EN_KEY_S6_ON:  middLedSet(EN_LED_LED6, TRUE);  break;
        case EN_KEY_S6_OFF: middLedSet(EN_LED_LED6, FALSE); break;

        case EN_KEY_S7_ON:  middLedSet(EN_LED_LED7, TRUE);  break;
        case EN_KEY_S7_OFF: middLedSet(EN_LED_LED7, FALSE); break;

        case EN_KEY_S8_ON:  middLedSet(EN_LED_LED8, TRUE);  break;
        case EN_KEY_S8_OFF: middLedSet(EN_LED_LED8, FALSE); break;

        default: retVal = FAILURE; break;
    }

    CanBusFrame frm;

    frm.id = 0xFFAA;
    frm.rtr = 0;
    frm.ide = 1; //extended frame
    frm.dlc = 8;

    frm.data[0] = 0;
    frm.data[1] = 2;
    frm.data[2] = 4;
    frm.data[3] = 6;
    frm.data[4] = 8;
    frm.data[5] = 10;
    frm.data[6] = 12;
    frm.data[7] = 14;

#ifdef CAN1
    middCanCommSend(EN_CAN_LINE_1, &frm, 300);
#elif CAN2
    middCanCommSend(EN_CAN_LINE_2, &frm, 300);
#endif


    return retVal;
}
#else
RETURN_STATUS appEBPHandleKeys(KEYS key)
{
	RETURN_STATUS retVal = SUCCESS;

	DBG_MSG(" ->[I] Keys: %02d", key);

	switch(key)
	{
        case EN_KEY_S1_ON:  gKeyStatus.key1 = TRUE;  break;
        case EN_KEY_S1_OFF: gKeyStatus.key1 = FALSE; break;

        case EN_KEY_S2_ON:  gKeyStatus.key2  = TRUE;  break;
        case EN_KEY_S2_OFF: gKeyStatus.key2  = FALSE; break;

        case EN_KEY_S3_ON:  gKeyStatus.key3 = TRUE;  break;
        case EN_KEY_S3_OFF: gKeyStatus.key3 = FALSE; break;

        case EN_KEY_S4_ON:  gKeyStatus.key4 = TRUE;  break;
        case EN_KEY_S4_OFF: gKeyStatus.key4 = FALSE; break;

        case EN_KEY_S5_ON:  gKeyStatus.key5 = TRUE;  break;
        case EN_KEY_S5_OFF: gKeyStatus.key5 = FALSE; break;

        case EN_KEY_S6_ON:  gKeyStatus.key6 = TRUE; break;
        case EN_KEY_S6_OFF: gKeyStatus.key6 = FALSE; break;

        case EN_KEY_S7_ON:  gKeyStatus.key7 = TRUE; break;
        case EN_KEY_S7_OFF: gKeyStatus.key7 = FALSE; break;

        case EN_KEY_S8_ON:  gKeyStatus.key8 = TRUE; break;
        case EN_KEY_S8_OFF: gKeyStatus.key8 = FALSE; break;

        default: retVal = FAILURE; break;
	}

	return retVal;
}
#endif

RETURN_STATUS appEBPHandleSerialMsg(void)
{
	RETURN_STATUS retVal = FAILURE;
    U8 buff[MAX_SERIAL_BUFFER_LENG];
    U32 msgLeng;
    
    #if CURRENT_BOARD == BOARD_STM_010101
    msgLeng = middSerialCommRcvData(EN_SERIAL_LINE_6, buff, sizeof(buff), WAIT_20_MS);
    #elif CURRENT_BOARD == BOARD_STM_LP_010101
    msgLeng = middSerialCommRcvData(EN_SERIAL_LINE_1, buff, sizeof(buff), WAIT_20_MS);
    #endif
    if (2 < msgLeng)
    {
        if (0 != msgTimeout)
        {
            if (0xFFFFFFFF != msgTimeoutTimerID)
            {
                //msg received, refresh timeout timer
                middSysTimerClearTimer(msgTimeoutTimerID);
            }

            msgTimeoutTimerID = middSysTimerSetTimer(msgTimeout, msgTimeoutCb);
        }

        //TODO: handle uart message according to Uart Message Frame
        switch(buff[1])
        {
            case (U8)MSG_ID_TIME_REQ:
            {
                //todo send time info - middTimeTempGetTime
                break;
            }
            case (U8)MSG_ID_TEMP_REQ:
            {
                //todo send temperature info - middTimeTempGetTemp()
                break;
            }
            case (U8)MSG_ID_SET_TIME:
            {
                //todo get time and set system time - middTimeTempSetTime()
                break;
            }

        }

        DBG_MSG(" ->[I] Serial Comm Message Parsed ");
    }
    else
    {
        DBG_MSG(" ->[E] MSG size is less than 3 byte. Incorrect message length %d ", msgLeng);
    }

	return retVal;
}

RETURN_STATUS appEBPHandleCanMsg(const U8* msg, U32 len)
{
    RETURN_STATUS retVal = SUCCESS;

    //TODO: parse and handle canbus message

    return retVal;
}

RETURN_STATUS appEBPDo(EBP_DO doo)
{
    RETURN_STATUS retVal = FAILURE;

    switch (doo)
    {
        case EN_JOB_EBP_MSG_TIMEOUT:
        {
            /*not received msg, set HIGH all led */
            gLedStatus.allLedStat = 0XFFFFFFFF;
            retVal = updateLedStatus();
            break;
        }
        case EN_JOB_EBP_TEMP_CHECK:
        {
            if (70 < middTimeTempGetTemp())
            {
                //todo start fan
            }
            break;
        }
        default: break;
    }

    return retVal;
}

/******************************** End Of File *********************************/
