/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 15, 2021 - 9:05:66 AM
* #File Name    : DriverCoreIWDT.c 
*******************************************************************************/
/******************************************************************************
* Firstly call init file. After init, wdt can be started with start macro
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG  (DISABLE)
/*********************************INCLUDES*************************************/
#include "DriverCoreIWDT.h"
#include "ProjectConf.h"

/****************************** MACRO DEFINITIONS *****************************/
#define KEY_LOCK_WDT_VAL     ((U16)(0x0000))
#define KEY_UNLOCK_WDT_VAL   ((U16)(0x5555))
#define KEY_RESET_WDT_VAL    ((U16)(0xAAAA))

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/

#ifdef WORKING_PLATFORM_PC
RETURN_STATUS drvIwdtInit(U32 timeMs)
{
    return SUCCESS;
}
#else
/**
 * @brief  init Independent Watchdog Timer
 * @param  wdt timer Ms
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvIwdtInit(U32 timeMs)
{
    RETURN_STATUS retVal = FAILURE;

    /* Check if the system has resumed from IWDG reset */
#if defined(STM32F4xx)
    if (RCC->CSR & RCC_CSR_WDGRSTF) {
#else
    if (RCC->CSR & RCC_CSR_IWDGRSTF) {
#endif
        //Bit 29 IWDGRSTF: Independent watchdog reset flag
        RCC->CSR |= RCC_CSR_RMVF;
    }

    IWDG->KR = KEY_UNLOCK_WDT_VAL; //unlock wdt registers

    if (timeMs < 32000) //mcu support max 32000 ms wdt
    {
        /* check RM0390 Reference document (http://tiny.cc/b0zs6y) for const value */
            if (timeMs < 4000)
            {
          IWDG->PR = 0x03; //set min 1ms wdt, prescaller setted /32
          //while(IWDG->SR) ; // wait until PR set process finis
            }
            else if (timeMs <= 8000)
            {
          IWDG->PR = 0x04;// prescaller setted/64
                    timeMs /= 2;
            }
            else if (timeMs <= 16000)
            {
           IWDG->PR = 0x05; //check table prescaller setted /128
                   timeMs /= 4;
            }
      else if (timeMs <= 32000)
            {
           IWDG->PR = 0x06; //check table, prescaller setted /256
           timeMs /= 8;
            }

            IWDG->RLR = timeMs; //(timeMs/100)=> tolerance.

      IWDG->KR = KEY_RESET_WDT_VAL;
      retVal = SUCCESS;
   }

    return retVal;
}
#endif
/******************************** End Of File *********************************/
