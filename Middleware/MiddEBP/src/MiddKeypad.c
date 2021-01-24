/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddKeypad.c
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "MiddKeypad.h"
#include "McuInterruptRegister.h"
#include "MiddDigitalIOControl.h"

#include "DrvTCA8418.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static KeypadListener gCbListener;
/***************************** STATIC FUNCTIONS  ******************************/
static RETURN_STATUS i2cWriteFunc(U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng)
{
    RETURN_STATUS retVal = FAILURE;

    if (DRV_RET_SUCCESS == I2C_WRITE(I2C_LINE_1, devAdr, memAdr, buff, bufLeng))
    {
        retVal = SUCCESS;
    }

    return retVal;
}

static RETURN_STATUS i2cReadFunc(U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng)
{
    RETURN_STATUS retVal = FAILURE;

    if (DRV_RET_SUCCESS == I2C_READ(I2C_LINE_1, devAdr, memAdr, buff, bufLeng))
    {
        retVal = SUCCESS;
    }

    return retVal;
}


static void cbKeypad(U32 key)
{
    if (key & 0x80) //key pressed event
    {
        key = key & 0x7F; //clear event bit
        gCbListener(key);
    }
}

/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS middKeypadInit(void)
{
    RETURN_STATUS retVal = FAILURE;
    HwI2C i2c;

    i2c.devAddr  = TCA8418_I2C_ADDR;
    i2c.write = i2cWriteFunc;
    i2c.read  = i2cReadFunc;


    if (SUCCESS == drvTca8418Init(&i2c))
    {
        retVal = drvSetKeypad(4, 4); //4x4 keypad
    }

    DBG_MSG("->[I] midd keypad Init retVal: %d", retVal);
    return retVal;
}

RETURN_STATUS midKeypadListener(KeypadListener cb, BOOL stat)
{
	drvTca8418CbListener(cbKeypad, stat);
	gCbListener = cb;

    return SUCCESS;
}

BOOL middKeypadReadKey(KEYPAD_KEY key)
{
    BOOL retVal = SUCCESS;

    //TODO: read key from keypad IC
    return retVal;
}

/******************************** End Of File *********************************/
