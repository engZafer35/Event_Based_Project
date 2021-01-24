/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppBITManager.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "AppBITManager.h"
#include "MiddMCUCore.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static union
{
    U32 bitErrorList;
    struct
    {
        //1: error 0: no error
        U32 SYSTEM_INIT_ERROR   :1;
        U32 CAN_COMM_ERROR      :1;
        U32 RS422_COMM_ERROR    :1;
        U32 INTERNAL_ERROR      :1;

    };
}gBITErrorList;
/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/
/**
 * @brief  init BIT module
 * @param  void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appBITInit(void)
{
    RETURN_STATUS retVal = SUCCESS;

    retVal = middMCUWdtInit(BIT_TIME + WAIT_3_SEC); //+3sec is offset
    middMCUWdtFeed();

    gBITErrorList.bitErrorList = FALSE; //clear all error list

    return retVal;
}

/**
 * @brief power on BIT. call after all system initialize
 *        After appBitInit() call this func. isPbitOK is TRUE
 *        WDT will begin.
 * @return void
 */
void appBitPBIT(void)
{
    middMCUWdtStart();

    DBG_MSG("-> [E] PBIT system init  ERROR LIST: 0X%04X !!", gBITErrorList.bitErrorList);

    appBitCheck();
}

/**
 * @brief  set error or clear error
 * @param  error ID
 * @param  error status, TRUE or FALSE
 * @return void
 */
void appBitSetError(enum ERROR_LIST error, BOOL status)
{
    if (error < EN_ERR_MAX_NUM)
    {
        if (status) gBITErrorList.bitErrorList |= (1 << error);    //set error
        else        gBITErrorList.bitErrorList &= (~(1 << error)); //clear error
    }
}

/**
 * @brief  Handle error List
 * @param  1: send data, 0: don't send
 * @return if everything is OK, return SUCCES
 *         otherwise return FFFFFFFF
 */
void appBitCheck(void)
{
    BOOL isReset = FALSE;
    static U32 counter = 0;
    static U32 next = 0;

    DBG_MSG(" -> [I] BIT ERROR NO: 0x%04x", gBITErrorList.bitErrorList);

    middMCUWdtFeed(); //clear WDT

    if (FALSE != gBITErrorList.bitErrorList)//check there is a error
    {
        //TODO: !! handle all error ID
        if (gBITErrorList.SYSTEM_INIT_ERROR)
        {
            isReset = TRUE;  // restart the system because of SYSTEM_INIT_ERROR.
        }

        /* if necessary, send error list */
    }

    switch (++next) //check some units or devices
    {
        case 1: /* check X */break;
        case 2: /* check Y */break;
        case 3: /* check Z */break;
        case 4: /* check P */break;
        default: next = 0; break;
    }

    if (TRUE == isReset)
    {
        DBG_MSG(" -> [E] SYSTEM WILL RESTART !!! ERROR NUM: 0x%04x !!!", gBITErrorList.bitErrorList);
        middMCUWdtInit(5);
        middMCUWdtStart();

        while(1) //wait until restart
            ;
    }
    else
    {
        DBG_MSG(" -> [I] WDT FEED OK - Counter: %d", counter++);
    }
}
/******************************** End Of File *********************************/
