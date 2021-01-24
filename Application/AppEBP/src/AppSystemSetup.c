/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : AppSystemSetup.c
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "AppSystemSetup.h"
#include "ProjectConf.h"
#include "AppBITManager.h"
#include "AppMainLoop.h"
#include "AppSystemVariables.h"
#include "AppEventManager.h"
#include "AppEBP.h"

#include "MiddMCUCore.h"
#include "MiddSysTimer.h"
#include "MiddEventTimer.h"
#include "MiddDigitalIOControl.h"
#include "MiddCanComm.h"
#include "MiddSerialComm.h"
#include "MiddKeypad.h"
#include "MiddKeysCntrl.h"
#include "MiddLedController.h"
#include "MiddTimeTempInfo.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

/***************************** STATIC FUNCTIONS  ******************************/
/*
 * @brief init all mcu peripherals
 */
static RETURN_STATUS initMcuCore(void)
{
    RETURN_STATUS retVal = SUCCESS;

    retVal |= middMCUClockInit(); //firstly init clock and system
    retVal |= middMCUGpioInit();
    retVal |= middMCUCanInit();
    retVal |= middMCUI2CInit();
    retVal |= middMCUUartInit();
    retVal |= middMCUTimers();
    retVal |= middMCUADCInit();

    DBG_MSG(" ->[I] initMcuCore return: %d", retVal);

    return retVal;
}

static RETURN_STATUS initSWRequirement(void)
{
    RETURN_STATUS retVal = SUCCESS;

    /** !< Firstly init midd layer */
    retVal |= middSysTimerInit();   //init system timer
    retVal |= middEventTimerInit(); //init periodic event timer
    retVal |= middIOInit();
    retVal |= MiddCanCommInit();

    /** don't need to check to set system failure */
    middSerialCommInit();
    middKeypadInit();
    middKeysInit();
    middLedInit(); /** !! MiddLedController module must be init after middKeys */
    middTimeTempInit();

    if (SUCCESS == retVal)
    {
        retVal |= appSysVarInit(); //load all sys var
        retVal |= appBITInit();
        retVal |= appMLInit();
        retVal |= appEventInit();
        retVal |= appEBPInit();
    }

    DBG_MSG(" ->[I] initSWRequirement return value: %d ", retVal);
    return retVal;
}

/*
 * @brief init all device drivers
 */
static RETURN_STATUS initDeviceDrivers(void)
{
    RETURN_STATUS retVal = SUCCESS;
    DBG_MSG(" ->[I] Device Driver Starting");

    /*
     * if you need to init a device driver, handle in this func.
     * use macro to plug in/out device to project. check ProjectConf.h file
     */

    DBG_MSG(" ->[I] Device Driver completed, result %d", retVal);
    return retVal;
}
/***************************** PUBLIC FUNCTIONS  ******************************/
/**
 * @brief initialize all system requirement
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appSystemSetup(void)
{
    RETURN_STATUS retVal = FAILURE;

    if (SUCCESS == initMcuCore())
    {
        //use fprintf to show system info for every time.
        DBG_MSG("\n\r##--- > Board File: %s - Board Name: %s - Board Version: %s Board MCU: %s-%s \n\r", BOARD_FILE_NAME, BOARD_NAME, BOARD_VERSION, MCU_PART_NUM, MCU_CORE);
        DBG_MSG("##--- > SW Version %d.%d.%d \n\r", SW_VERSION_MAJOR, SW_VERSION_MINOR, SW_VERSION_BUGFX);

        if (SUCCESS == initDeviceDrivers())
        {
            retVal = initSWRequirement();
        }

        middIOCtrlShowStatusInfo(EN_IO_POWER_STATUS, ENABLE);
    }

    if (SUCCESS == retVal)
    {
        //system ready, start all hardware timer, set firstly event timer, short circuit method
        if ((DRV_RET_SUCCESS != TIMER_EVENT_START()) || (DRV_RET_SUCCESS != TIMER_ALERT_START()))
        {
            retVal = FAILURE;
        }

        if (DRV_RET_SUCCESS != HAL_CAN_2_START())
        {
//            retVal = FAILURE;//hw not have can IC. closed ==> if HW supports can active this line
            DBG_MSG(" ->[E] !! CANBUS LINE 2 Could not be started !!!!!!!\n\n\r");
        }

        if (DRV_RET_SUCCESS != HAL_CAN_1_START())
        {
//            retVal = FAILURE;//hw not have can IC. closed ==> if HW supports can active this line
            DBG_MSG(" ->[E] !! CANBUS LINE 1 Could not be started !!!!!!!\n\n\r");
        }
    }

    if (FAILURE == retVal)
    {
        appBitSetError(EN_ERR_SYSTEM_INIT, TRUE);
    }

    appBitPBIT(); //wdt will start and all errors will handle

    DBG_MSG(" ->[I] $$$ All System Setup Return: %d $$$", retVal);

    return retVal;
}

/**
 * @brief restart system
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appSystemRestart(void)
{
    RETURN_STATUS retVal = SUCCESS;

    return retVal;
}

/**
 * @brief Up Grade SW
 * @param void
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS appSystemSWUpgrade(void)
{
    RETURN_STATUS retVal = SUCCESS;

    return retVal;
}
/******************************** End Of File *********************************/
