/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddSerialComm.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __MIDD_SERIAL_COMM_H__
#define __MIDD_SERIAL_COMM_H__
/*********************************INCLUDES*************************************/
#include "ProjectConf.h"
/******************************MACRO DEFINITIONS*******************************/

#define SERIAL_UART1
#define SERIAL_UART2
#define SERIAL_UART3
//#define SERIAL_UART4
//#define SERIAL_UART5
#define SERIAL_UART6
//#define SERIAL_UART7
//#define SERIAL_UART8

#define MAX_SERIAL_BUFFER_LENG  (128) //byte
#define MAX_HEADER_FILTER_LENG  (8)   //byte

/*******************************TYPE DEFINITIONS ******************************/

/** @brief channel list */
typedef enum _SERIAL_COMM_LINE
{
#ifdef SERIAL_UART1
    EN_SERIAL_LINE_1,
    #define SERIAL_LINE_1   (1)
    #define LINE_1_RX       (ENABLE)         //if not used RX mode set DISABLE,
    #define LINE_1_INTR_ID  (EN_USART1_IRQ) //set correct hw interrupt ID
#endif

#ifdef SERIAL_UART2
    EN_SERIAL_LINE_2,
    #define LINE_2_RX       (ENABLE)       //if not used RX mode set DISABLE,
    #define LINE_2_INTR_ID  (EN_USART2_IRQ) //set correct hw interrupt ID
#endif

#ifdef SERIAL_UART3
    EN_SERIAL_LINE_3,
    #define LINE_3_RX       (DISABLE)       //if not used RX mode set DISABLE,
    #define LINE_3_INTR_ID  (EN_USART3_IRQ) //set correct hw interrupt ID
#endif

#ifdef SERIAL_UART4
    EN_SERIAL_LINE_4,
    #define LINE_4_RX       (ENABLE)      //if not used RX mode set DISABLE,
    #define LINE_4_INTR_ID  (EN_UART4_IRQ) //set correct hw interrupt ID
#endif

#ifdef SERIAL_UART5
    EN_SERIAL_LINE_5,
    #define SERIAL_LINE_5   (5)
    #define LINE_5_RX       (ENABLE)      //if not used RX mode set DISABLE,
    #define LINE_5_INTR_ID  (EN_UART5_IRQ) //set correct hw interrupt ID
#endif

#ifdef SERIAL_UART6
    EN_SERIAL_LINE_6,
    #define LINE_6_RX       (ENABLE)       //if not used RX mode set DISABLE,
    #define LINE_6_INTR_ID  (EN_USART6_IRQ) //set correct hw interrupt ID
#endif

#ifdef SERIAL_UART7
    EN_SERIAL_LINE_7,
    #define LINE_7_RX       (ENABLE)       //if not used RX mode set DISABLE,
    #define LINE_7_INTR_ID  (EN_UART7_IRQ) //set correct hw interrupt ID
#endif

#ifdef SERIAL_UART8
    EN_SERIAL_LINE_8,
    #define LINE_8_RX       (ENABLE)      //if not used RX mode set DISABLE,
    #define LINE_8_INTR_ID  (EN_UART8_IRQ) //set correct hw interrupt ID
#endif

    EN_SERIAL_LINE_MAX_NUM,

}SERIAL_COMM_LINE;

#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)
#define TOTAL_RX_CHN_NUM (1) // how many channel has RX line (LINE_1_RX, LINE_2_RX,LINE_3_RX,LINE_4_RX)
#endif

#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)
/** @brief listener structure */
typedef struct _SerialListener
{
    SERIAL_COMM_LINE line;
    U8 hLeng; //max header filter buffer length MAX_HEADER_FILTER_LENG

    /**
       1- if this value is not NULL listener firstly check received data,
     *     if received message contains this header listener will call the callback
     * 2- if this value is NULL, listener will call your callback when received each data
     *     so in this mode your code should be fast to catch next data
     */
    U8* hFilter;

    VoidCallback cb;
}SerialListener;
#endif
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
 * @brief   int serial communication
 * @param   void
 * @return  if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS middSerialCommInit(void);

#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)
/**
 * @brief  send Data
 * @param  listener structure
 * @param  set active or passive,
 *         To set passive any channel listener,
 *         just set SERIAL_COMM_LINE in SerialListener and set FALSE
 * @note   if you don't want to use filter, set hLeng 0. you will interrupted
 *         when first data received.
 *         Until middSerialCommRcvData() invoked, you wont see interrupt for other data.
 *         After invoked middSerialCommRcvData(), you will again interrupted when first data received
 * @return if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS middSerialCommListener(const SerialListener *lis, BOOL stat);
#endif

/**
 * @brief  send Data
 * @param  line
 * @param  buff pointer
 * @param  buff length
 * @param  timeout
 * @return if everything is OK, return SUCCES, otherwise return FAILURE
 */
RETURN_STATUS middSerialCommSendData(SERIAL_COMM_LINE ln, void *buff, U32 leng, U32 timeout);

#if (LINE_1_RX || LINE_2_RX || LINE_3_RX || LINE_4_RX || LINE5_RX || LINE_6_RX || LINE_7_RX || LINE_8_RX)
/**
 * @brief  receive Data
 * @param  line
 * @param  buff pointer
 * @param  length, It is recommended to use a large length of your frame to get all data.
 * @param  timeout
 * @return return received data length, 0 length means there is no data
 */
U32 middSerialCommRcvData(SERIAL_COMM_LINE ln, void *buff, U32 rcvLeng, U32 timeoutMs);

/**
 * @brief  clear buffer
 * @param  line
 * @return void
 */
void middSerialCommClearBuffer(SERIAL_COMM_LINE ln);

#endif

#endif /* __MIDD_SERIAL_COMM_H__ */

/********************************* End Of File ********************************/
