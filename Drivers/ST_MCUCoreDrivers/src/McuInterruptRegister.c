/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : McuInterruptRegister.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/

/********************************* INCLUDES ***********************************/
#include "McuInterruptRegister.h"
#include "ProjectConf.h"
/****************************** MACRO DEFINITIONS *****************************/
#define IS_VALID_ID(x)          (x < EN_INTERRUPT_LIST_MAX_NUM)
#define IS_EMPTY_REGISTER(x)    (NULL == gInterruptCallbackList[x])
#define IS_REGISTERED_CB(x)     (NULL != gInterruptCallbackList[x])
/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
//all interrupt callback function.
static VICallback gInterruptCallbackList[EN_INTERRUPT_LIST_MAX_NUM] ;
/***************************** STATIC FUNCTIONS  ******************************/
static void runCallback(EN_INTERRUPT_LIST intType, int val)
{
    if (IS_REGISTERED_CB(intType))
    {
        gInterruptCallbackList[intType](val);
    }
}

CORE_TIMER_IT_FUNCTION
{
    //for alert timer
    if (TRUE == IS_ALERT_TIMER_IT())
    {
        runCallback(TIMER_ALERT_IT_ID, 0);
    }

    // for events timer
    if (TRUE == IS_EVENT_TIMER_IT())
    {
        runCallback(TIMER_EVENT_IT_ID, 0);
    }

    //dont need to clear IT func for stm32. Check for other MCU
}

UART_RCV_IT_FUNCTION
{
    if (TRUE == IS_LINE1_UART_IT())
    {
        runCallback(LINE_UART1_RX_IT_ID, 1);
    }
    else if (TRUE == IS_LINE2_UART_IT())
    {
        runCallback(LINE_UART2_RX_IT_ID, 2);
    }
    else if (TRUE == IS_LINE6_UART_IT())
    {
        runCallback(LINE_UART6_RX_IT_ID, 6);
    }
}

CORE_EXT_IT_FUNCTION
{
    if (EXT_KEYPAD_Pin == GPIO_Pin)
    {
        runCallback(GPIO_KEYPAD_CHNL, GPIO_Pin);
    }
    else
    {
        runCallback(GPIO_EXT_INT_ID, GPIO_Pin);
    }
}

COM_CAN_RX_IT_FUNC
{
#ifdef CAN1
	runCallback(EN_CAN1_RX0_IRQ, 0);
#elif CAN2
	runCallback(EN_CAN2_RX0_IRQ, 0);
#endif

}
/***************************** PUBLIC FUNCTIONS  ******************************/
/**
 * @brief register for core interrupt
 * @param callback func, interrupt type id
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvIntRegister(VICallback callBackFunc, EN_INTERRUPT_LIST intType)
{
    RETURN_STATUS retVal = FAILURE;

    if (IS_SAFELY_PTR(callBackFunc) && IS_VALID_ID(intType))
    {
        if (IS_EMPTY_REGISTER(intType))
        {
            gInterruptCallbackList[intType] = callBackFunc;
            retVal = SUCCESS;
        }
    }

    return retVal;
}

RETURN_STATUS drvIntUnregister(EN_INTERRUPT_LIST intType)
{
    RETURN_STATUS retVal = FAILURE;

    if (IS_VALID_ID(intType))
    {
        gInterruptCallbackList[intType] = NULL;
        retVal = SUCCESS;
    }

    return retVal;
}
/******************************** End Of File *********************************/
