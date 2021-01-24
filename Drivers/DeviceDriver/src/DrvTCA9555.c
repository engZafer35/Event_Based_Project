/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : DrvTCA9555.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/

/********************************* INCLUDES ***********************************/
#include "DrvTCA9555.h"
/****************************** MACRO DEFINITIONS *****************************/
#define INPUT_PORT_REG_1        (0x00)
#define INPUT_PORT_REG_2        (0x01)

#define OUTPUT_PORT_REG_1       (0x02)
#define OUTPUT_PORT_REG_2       (0x03)

#define POLARITY_PORT_REG_1     (0x04)
#define POLARITY_PORT_REG_2     (0x05)

#define CONF_PORT_REG_1         (0x06)
#define CONF_PORT_REG_2         (0x07)

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS drvTCA9555Init(const HwReqI2C* hw)
{
    RETURN_STATUS retVal = FAILURE;
    U8 temp;

    if (IS_SAFELY_PTR(hw))
    {
        retVal = hw->i2cReadFunc(hw->devAddr, CONF_PORT_REG_1, &temp, sizeof(U8)); //just read any register, exist?
    }

    return retVal;
}

RETURN_STATUS drvTCA9555SetPortDir(const HwReqI2C* hw, PORTS port, DIRECTION dir)
{
    RETURN_STATUS retVal = SUCCESS;
    U8 regVal;
    U8 regAdr;

    if (IS_SAFELY_PTR(hw))
    {
        regAdr = (EN_PORT_0 == port) ? CONF_PORT_REG_1 : CONF_PORT_REG_2;
        regVal = (EN_OUT == dir) ? 0 : (U8)0XFF; // 0 value output, 1 value input, set 8 pins

        retVal = hw->i2cWriteFunc(hw->devAddr, regAdr, &regVal, sizeof(U8));
    }

    return retVal;
}

RETURN_STATUS drvTCA9555SetPinDir(const HwReqI2C* hw, PORTS port, PINS pin, DIRECTION dir)
{
    RETURN_STATUS retVal = SUCCESS;
    U8 regVal;
    U8 regAdr;

    if (IS_SAFELY_PTR(hw))
    {
        regAdr = (EN_PORT_0 == port) ? CONF_PORT_REG_1 : CONF_PORT_REG_2;

        if (SUCCESS == hw->i2cReadFunc(hw->devAddr, regAdr, &regVal, sizeof(U8)))
        {
            if (EN_OUT == dir)
            {
                regVal &= ~(1 << pin); //set 0 for output direction
            }
            else
            {
                regVal |= (1 << pin); //set 1 for input direction
            }

            retVal = hw->i2cWriteFunc(hw->devAddr, regAdr, &regVal, sizeof(U8));
        }
    }

    return retVal;
}

S32 drvTCA9555ReadPort(const HwReqI2C* hw, PORTS port)
{
    U32 retVal = -1; //failure val
    U8 regVal;
    U8 regAdr;

    if (IS_SAFELY_PTR(hw))
    {
        regAdr = (EN_PORT_0 == port) ? INPUT_PORT_REG_1 : INPUT_PORT_REG_2;

        if (SUCCESS == hw->i2cReadFunc(hw->devAddr, regAdr, &regVal, sizeof(U8)))
        {
            retVal = regVal;
        }
    }

    return retVal;
}

S32 drvTCA9555ReadPin(const HwReqI2C* hw, PORTS port, PINS pin)
{
    S32 retVal = -1;
    U8 regVal;
    U8 regAdr;

    if (IS_SAFELY_PTR(hw))
    {
        regAdr = (EN_PORT_0 == port) ? INPUT_PORT_REG_1 : INPUT_PORT_REG_2;

        if (SUCCESS == hw->i2cReadFunc(hw->devAddr, regAdr, &regVal, sizeof(U8)))
        {
            retVal = CHECK_BIT(regVal, pin);
        }
    }

    return retVal;
}

RETURN_STATUS drvTCA9555WriteOutputPort(const HwReqI2C* hw, PORTS port, U8 val)
{
    RETURN_STATUS retVal = FAILURE;

    if (IS_SAFELY_PTR(hw))
    {
        retVal = hw->i2cWriteFunc(hw->devAddr, (EN_PORT_0 == port) ? OUTPUT_PORT_REG_1 : OUTPUT_PORT_REG_2, &val, sizeof(U8));
    }

    return retVal;
}

RETURN_STATUS drvTCA9555WriteOutputPin(const HwReqI2C* hw, PORTS port, PINS pin, BOOL stat)
{
    RETURN_STATUS retVal = FAILURE;
    U8 regVal;
    U8 regAdr;

    if (IS_SAFELY_PTR(hw))
    {
        regAdr = (EN_PORT_0 == port) ? OUTPUT_PORT_REG_1 : OUTPUT_PORT_REG_2;

        if (SUCCESS == hw->i2cReadFunc(hw->devAddr, regAdr, &regVal, sizeof(U8)))
        {
            if (FALSE == stat)
            {
                regVal &= ~(1 << pin);
            }
            else
            {
                regVal |= (1 << pin);
            }

            retVal = hw->i2cWriteFunc(hw->devAddr, regAdr, &regVal, sizeof(U8));
        }
    }

    return retVal;
}

/******************************** End Of File *********************************/
