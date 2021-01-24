/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddMCUCore.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/

/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "MiddMCUCore.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/
/**
 * @brief init MCU clock
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUClockInit(void)
{
    MCU_CORE_INIT();
    CONF_MCU_CLOCK();

    return SUCCESS;
}

/**
 * @brief enter sleep mode
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUClockEnterSleepMode(void)
{
    return SUCCESS;
}
/**
 * @brief init input and output GPIO
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUGpioInit(void)
{
    GPIO_INIT();
    return SUCCESS;
}

 /**
  * @brief init I2C
  * @param void
  * @return if everything is OK, return SUCCES
  *         otherwise return FAILURE
  */
RETURN_STATUS middMCUI2CInit(void)
{
    I2C1_INIT();
    I2C2_INIT();
    return SUCCESS;
}

/**
 * @brief init I2C
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUSPIInit(void)
{
   SPI_INIT();
   return SUCCESS;
}
/**
 * @brief init using timers
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUTimers(void)
{
    TIMER_ALERT_INIT();       //10ms for alert timer
    TIMER_EVENT_INIT();       //10ms for event timer

    return SUCCESS;
}

/**
 * @brief init all UART Channel
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUUartInit(void)
{
    UART_DEBUG_INIT();  //for debug, and bootloader, uart1
    UART_COMM_INIT(); //for mfd comm, uart2

    return SUCCESS;
}


/**
* @brief init all CAN Channel
* @param void
* @return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS middMCUCanInit(void)
{
    CAN_INIT();

    return SUCCESS;
}

/**
* @brief init all ADC Channel
* @param void
* @return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS middMCUADCInit(void)
{
    RETURN_STATUS retVal;

    retVal  = ADC_BOARD_MEASURE_BUS_INIT(); // ! adc retval SUCCESS OR FAILURE
    retVal |= ADC_CHNL_MEASURE_INIT();

    return retVal;
}

/**
* @brief init internal RTC
* @param void
* @return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS middMcuRTCInit(void)
{
    return SUCCESS;
}
 /**
  * @brief init WDT init
  * @param wdt time ms
  * @return if everything is OK, return SUCCES
  *         otherwise return FAILURE
  */
RETURN_STATUS middMCUWdtInit(U32 timeMs)
{
    return WDT_INIT(timeMs);
}

/**
 * @brief stop WDT
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUWdtStart(void)
{
    WDT_START();
    return SUCCESS;
}

/**
 * @brief feed WDT
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS middMCUWdtFeed(void)
{
    WDT_FEED();
    return SUCCESS;
}

/******************************** End Of File *********************************/
