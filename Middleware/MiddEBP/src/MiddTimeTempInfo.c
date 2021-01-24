/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 17, 2021 - 11:23:41 AM
* #File Name    : MiddTimeTempInfo.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/

/********************************* INCLUDES ***********************************/
#include <string.h>

#include "ProjectConf.h"
#include "MiddTimeTempInfo.h"

#include "DrvM41T11_RTC.h"
#include "DrvLM75B.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

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
/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS middTimeTempInit(void)
{
    RETURN_STATUS retVal = FAILURE;
    M4T11_I2C rtcI2c;
    LM75B_I2C lmI2c;

    rtcI2c.devAddr = M41T11_I2C_ADDR;
    rtcI2c.read    = i2cReadFunc;
    rtcI2c.write   = i2cWriteFunc;

    lmI2c.devAddr = LM75B_I2C_ADDR;
    lmI2c.read    = i2cReadFunc;
    lmI2c.write   = i2cWriteFunc;

    retVal  = drvM41T11Init(&rtcI2c);
    retVal |= drvLM75Init(&lmI2c);

    return retVal;
}

RETURN_STATUS middTimeTempGetTime(RTC_TIME *t)
{
    RETURN_STATUS retVal = FAILURE;
    M4T11_RTC_STR dt;

    if (IS_SAFELY_PTR(t))
    {
        retVal = drvM41T11GetTime(&dt);
        if (SUCCESS == retVal)
        {
            memcpy(t, &dt, sizeof(dt)); //dt and t same size and same members
        }
    }

    return retVal;
}

RETURN_STATUS middTimeTempSetTime(const RTC_TIME *t)
{
    RETURN_STATUS retVal = FAILURE;
    M4T11_RTC_STR dt;

    if (IS_SAFELY_PTR(t))
    {
        memcpy(&dt, t, sizeof(dt)); //dt and t same size and same members
        retVal = drvM41T11SetTime(&dt);
    }

    return retVal;
}

float middTimeTempGetTemp(void)
{
    return drvLM75GetTemp();
}

/******************************** End Of File *********************************/
