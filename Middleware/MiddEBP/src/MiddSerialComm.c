/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddSerialComm.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG  (DISABLE)
/********************************* INCLUDES ***********************************/
#include <string.h>

#include "ProjectConf.h"
#include "MiddSerialComm.h"
#include "MiddSysTimer.h"

#include "McuInterruptRegister.h"

/****************************** MACRO DEFINITIONS *****************************/
#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)
#define LINE(x) gLineBuffers[x]
#endif
/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)

static struct _LineBuffers
{
    U8  buff[MAX_SERIAL_BUFFER_LENG];
    U8  hFilter[MAX_HEADER_FILTER_LENG]; //+1 is contains user header leng
    U32 hFilterLeng;
    BOOL isInformed;
    VoidCallback cb;
    U16 counter;
    U8  chr;

}gLineBuffers[EN_SERIAL_LINE_MAX_NUM];
#endif

/***************************** STATIC FUNCTIONS  ******************************/
#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)
void cbLine(SERIAL_COMM_LINE ln, UART_LINE_OBJ_TYPE* hwLine)  //hardware line object, depends mcu type(stm, ti, nxp, ..)
{
    UART_CLR_RX_INT_FLAG(hwLine);
    U32 i;

    LINE(ln).buff[LINE(ln).counter++] = LINE(ln).chr;

    if((0 != LINE(ln).hFilterLeng) && (LINE(ln).hFilterLeng == LINE(ln).counter)) //first data received
    {
        for (i = 0; i < LINE(ln).hFilterLeng; ++i) //hFilterLeng contains leng
        {
            if (LINE(ln).buff[i] != LINE(ln).hFilter[1+i]) break; // +1 ship size info,  not correct header,
        }

        if (i == LINE(ln).hFilterLeng) //header correct
        {
            if (TRUE == IS_SAFELY_PTR(LINE(ln).cb))
            {
                LINE(ln).cb(); // invoke callback
            }
        }
        else
        {
            LINE(ln).counter = 0; // data is not correct
        }
    }
    else if ((0 ==  LINE(ln).hFilterLeng) && (FALSE == LINE(ln).isInformed)) // not used filter and first data received, inform user
    {
        if (TRUE == IS_SAFELY_PTR(LINE(ln).cb))
        {
            LINE(ln).isInformed = TRUE;
            LINE(ln).cb(); // invoke callback
        }
    }

    if (LINE(ln).counter >= MAX_SERIAL_BUFFER_LENG) LINE(ln).counter = 0;

    UART_RCV_IT(hwLine, &LINE(ln).chr, 1);
}
#endif

#if (LINE_1_RX)
void cbLine_1(int x)
{
    if (NULL != gLineBuffers[EN_SERIAL_LINE_1].cb) //0 first channel index
    {
        cbLine(EN_SERIAL_LINE_1, &UART_HW_LINE_1); //number starting from 1,
    }
}
#endif

#if (LINE_2_RX)
void cbLine_2(int x)
{
    if (NULL != gLineBuffers[EN_SERIAL_LINE_2].cb) //1 second channel index
    {
        cbLine(EN_SERIAL_LINE_2, &UART_HW_LINE_2); //number starting from 1,
    }
}
#endif

#if (LINE_3_RX)
void cbLine_3(int x)
{
    if (NULL != gLineBuffers[EN_SERIAL_LINE_3].cb) //2 third channel index
    {
        cbLine(EN_SERIAL_LINE_3, &UART_HW_LINE_3); //number starting from 1,
    }
}
#endif

#if (LINE_4_RX)
void cbLine_4(int x)
{
    if (NULL != gLineBuffers[EN_SERIAL_LINE_4].cb)
    {
        cbLine(EN_SERIAL_LINE_4, &UART_HW_LINE_4);
    }
}
#endif

#if (LINE_5_RX)
void cbLine_5(int x)
{
    if (NULL != gLineBuffers[EN_SERIAL_LINE_5].cb)
    {
        cbLine(EN_SERIAL_LINE_5, &UART_HW_LINE_5);
    }
}
#endif

#if (LINE_6_RX)
void cbLine_6(int x)
{
    if (NULL != gLineBuffers[EN_SERIAL_LINE_6].cb)
    {
        cbLine(EN_SERIAL_LINE_6, &UART_HW_LINE_6);
    }
}
#endif

#if (LINE_7_RX)
void cbLine_7(int x)
{
    if (NULL != gLineBuffers[EN_SERIAL_LINE_7].cb)
    {
        cbLine(EN_SERIAL_LINE_7, &UART_HW_LINE_7);
    }
}
#endif

#if (LINE_8_RX)
void cbLine_8(int x)
{
    if (NULL != gLineBuffers[EN_SERIAL_LINE_8].cb)
    {
        cbLine(EN_SERIAL_LINE_8, &UART_HW_LINE_8);
    }
}
#endif
/***************************** PUBLIC FUNCTIONS  ******************************/

RETURN_STATUS middSerialCommInit(void)
{
    RETURN_STATUS retVal = SUCCESS;

    return retVal;
}

#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)
RETURN_STATUS middSerialCommListener(const SerialListener *lis, BOOL stat)
{
    RETURN_STATUS     retVal;
    VICallback        cb;
    EN_INTERRUPT_LIST intID;
    UART_LINE_OBJ_TYPE* hwLine; //hardware line object, depends mcu type(stm, ti, nxp, ..)

    if (TRUE == IS_NULL_PTR(lis))
    {
        return FAILURE;
    }

    switch(lis->line)
    {
        #if (LINE_1_RX)
          case EN_SERIAL_LINE_1:
          {
              hwLine = &UART_LINE_1;
              cb     = cbLine_1;
              intID  = LINE_1_INTR_ID;
              break;
          }
        #endif
        #if (LINE_2_RX)
          case EN_SERIAL_LINE_2:
          {
              hwLine = &UART_LINE_2;
              cb     = cbLine_2;
              intID  = LINE_2_INTR_ID;
              break;
          }
        #endif
        #if (LINE_3_RX)
          case EN_SERIAL_LINE_3:
          {
              hwLine = &UART_LINE_3;
              cb     = cbLine_3;
              intID  = LINE_3_INTR_ID;
              break;
          }
        #endif
        #if (LINE_4_RX)
          case EN_SERIAL_LINE_4:
          {
              hwLine = &UART_HW_LINE_4;
              cb     = cbLine_4;
              intID  = LINE_4_INTR_ID;
              break;
          }
        #endif
        #if (LINE_5_RX)
          case EN_SERIAL_LINE_5:
          {
              hwLine = &UART_HW_LINE_5;
              cb     = cbLine_5;
              intID  = LINE_5_INTR_ID;
              break;
          }
        #endif
        #if (LINE_6_RX)
          case EN_SERIAL_LINE_6:
          {
              hwLine = &UART_HW_LINE_6;
              cb     = cbLine_6;
              intID  = LINE_6_INTR_ID;
              break;
          }
        #endif
        #if (LINE_7_RX)
          case EN_SERIAL_LINE_7:
          {
              hwLine = &UART_HW_LINE_7;
              cb     = cbLine_7;
              intID  = LINE_7_INTR_ID;
              break;
          }
        #endif
        #if (LINE_8_RX)
          case EN_SERIAL_LINE_8:
          {
              hwLine = &UART_HW_LINE_8;
              cb     = cbLine_8;
              intID  = LINE_8_INTR_ID;
              break;
          }
        #endif

         default: return FAILURE; //error case
    }

    LINE(lis->line).counter = 0; //clear receive Int buffer counter, fist data should be insert first index

    if(TRUE == stat)
    {
        LINE(lis->line).cb          = lis->cb; //copy callback address
        LINE(lis->line).hFilterLeng = lis->hLeng; //copy filter leng

        memcpy(LINE(lis->line).hFilter, lis->hFilter, lis->hLeng); //copy filter

        retVal = drvIntRegister(cb, intID); //register our interrupt map

        UART_RX_IT_ENABLE(hwLine); //normally this func. should be in drvIntRegister. But this way code is becoming more portable
        UART_RCV_IT(hwLine, &LINE(lis->line).chr, 1); //set interrupt buffer
    }
    else //stop receiving data, stop interrupt
    {
        UART_RX_IT_DISABLE(hwLine);
        retVal = drvIntUnregister(intID);
        LINE(lis->line).hFilterLeng = 0; //clear filter buffer length
        LINE(lis->line).cb = NULL;
    }

    return retVal;
}
#endif

RETURN_STATUS middSerialCommSendData(SERIAL_COMM_LINE ln, void *buff, U32 leng, U32 timeout)
{
    RETURN_STATUS retVal = SUCCESS;
    UART_LINE_OBJ_TYPE* hwLine; //hardware line object, depends mcu type(stm, ti, nxp, ..)

    switch(ln)
    {
        #ifdef SERIAL_UART1
          case EN_SERIAL_LINE_1: hwLine = &UART_HW_LINE_1; break;
        #endif
        #ifdef SERIAL_UART2
          case EN_SERIAL_LINE_2: hwLine = &UART_HW_LINE_2; break;
        #endif
        #ifdef SERIAL_UART3
          case EN_SERIAL_LINE_3: hwLine = &UART_HW_LINE_3; break;
        #endif
        #ifdef SERIAL_UART4
          case EN_SERIAL_LINE_4: hwLine = &UART_HW_LINE_4; break;
        #endif

        #ifdef SERIAL_UART5
          case EN_SERIAL_LINE_5: hwLine = &UART_HW_LINE_5; break;
        #endif
        #ifdef SERIAL_UART6
          case EN_SERIAL_LINE_6: hwLine = &UART_HW_LINE_6; break;
        #endif
        #ifdef SERIAL_UART7
          case EN_SERIAL_LINE_7: hwLine = &UART_HW_LINE_7; break;
        #endif
        #ifdef SERIAL_UART8
          case EN_SERIAL_LINE_8: hwLine = &UART_HW_LINE_8; break;
        #endif
         default: return FAILURE; //error case
    }

    if (DRV_RET_SUCCESS != UART_SEND(hwLine, buff, leng, timeout))
    {
        retVal = FAILURE;
    }

    return retVal;
}

#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)
U32 middSerialCommRcvData(SERIAL_COMM_LINE ln, void *buff, U32 rcvLeng, U32 timeoutMs)
{
    U32 retLen = 0;
    USS timerID = 0;

    if (0 != timeoutMs)
    {
        timerID = middSysTimerSetTimer(timeoutMs, NULL);
    }

    while(1)
    {
        if (LINE(ln).counter)
        {
            /**
             * data comes one by one from UART line,
             * so small waiting may be helpful to receive all data
             */
            DELAY_MS(1); //wait all data, Test it.

            if (LINE(ln).counter/* >= rcvLeng*/) // data is ready
            {
                if (0 != timeoutMs)
                {
                    middSysTimerClearTimer(timerID); //clear timer
                }
                break;
            }
        }

        if (0 != timeoutMs)
        {
            if (TRUE == middSysTimerIsTimerOK(timerID))
            {
                //clear timer
                middSysTimerClearTimer(timerID);
                break;
            }
        }
    }

    if (LINE(ln).counter)
    {
        UART_LINE_OBJ_TYPE* hwLine; //hardware line object, depends mcu type(stm, ti, nxp, ..)
        switch(ln)
        {
            #if (LINE_1_RX)
              case EN_SERIAL_LINE_1:  hwLine = &UART_HW_LINE_1; break;
            #endif
            #if (LINE_2_RX)
              case EN_SERIAL_LINE_2:  hwLine = &UART_HW_LINE_2; break;
            #endif
            #if (LINE_3_RX)
              case EN_SERIAL_LINE_3:  hwLine = &UART_HW_LINE_3; break;
            #endif
            #if (LINE_4_RX)
              case EN_SERIAL_LINE_4:  hwLine = &UART_HW_LINE_4; break;
            #endif
            #ifdef SERIAL_UART5
              case EN_SERIAL_LINE_5:  hwLine = &UART_HW_LINE_5; break;
            #endif
            #ifdef SERIAL_UART6
              case EN_SERIAL_LINE_6:  hwLine = &UART_HW_LINE_6; break;
            #endif
            #ifdef SERIAL_UART7
              case EN_SERIAL_LINE_7:  hwLine = &UART_HW_LINE_7; break;
            #endif
            #ifdef SERIAL_UART8
              case EN_SERIAL_LINE_8:  hwLine = &UART_HW_LINE_8; break;
            #endif

              default: return 0; //error case
        }

        /************************************************************************************************************/
        UART_RX_IT_DISABLE(hwLine); //disable RX interrupt before copy data

        if (LINE(ln).counter > 0)
        {
            if (LINE(ln).counter > rcvLeng) //buffered data size bigger than wanted size
            {
                memcpy(buff, LINE(ln).buff, rcvLeng); //just copy wanted size
                retLen = rcvLeng;

                LINE(ln).counter -= rcvLeng; //calculate remaining data size
                memcpy(LINE(ln).buff, &LINE(ln).buff[rcvLeng], LINE(ln).counter); //Move the remaining data to beginning of LINE(ln).buff
            }
            else // LINE(ln).counter < rcvLeng, so give all received data
            {
                memcpy(buff, LINE(ln).buff, LINE(ln).counter);
                retLen = LINE(ln).counter;
                LINE(ln).counter = 0; //all data copied, set buff index to beginning point
            }

            LINE(ln).isInformed = FALSE; //user will informed with next coming byte

            /*** Debug Codes - Print received data  ****/
              #if ((ENABLE == SHOW_PAGE_DBG_MSG) || (ENABLE == ALL_DBG_MSG_ACTIVE))
                fprintf(stdout, "\n\r");
                for (int i = 0; i < retLen; i++)
                {
                    fprintf(stdout, "%02x+", ((U8 *)buff)[i] );
                    if ((i != 0) && (0 == (i % 16))) fprintf(stdout, "\n\r");
                }
                fprintf(stdout, "\n\r");
              #endif
        }

        UART_RX_IT_ENABLE(hwLine); //enable RX interrupt again
        /************************************************************************************************************/
    }

    return retLen;
}

void middSerialCommClearBuffer(SERIAL_COMM_LINE ln)
{
    LINE(ln).counter = 0;
}

#endif
/******************************** End Of File *********************************/
