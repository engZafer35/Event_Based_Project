/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : DrvTCA9555.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __DRV_TCA9555_H__
#define __DRV_TCA9555_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
typedef enum _DIRECTION
{
    EN_OUT = 0,
    EN_IN
}DIRECTION;

typedef enum _PORTS
{
    EN_PORT_0,
    EN_PORT_1
}PORTS;

typedef enum _PINS
{
    EN_PIN_0 = 0,
    EN_PIN_1,
    EN_PIN_2,
    EN_PIN_3,
    EN_PIN_4,
    EN_PIN_5,
    EN_PIN_6,
    EN_PIN_7,

    EN_PIN_MAX_NUM
}PINS;

/**
 * \brief load hardware requirement
 * \note  if there more than one tca9555 on the board, all of them can be controlled
 *        easily with HwReqI2C structure. Set related TCA address to devAddr member.
 */
typedef struct _HwReqI2C
{
    U32 devAddr;
    RETURN_STATUS (*i2cWriteFunc) (U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng);
    RETURN_STATUS (*i2cReadFunc)  (U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng);
}HwReqI2C;

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
* \brief  init TCA9555
* \param  HW requirement
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS drvTCA9555Init(const HwReqI2C* hw);

/**
* \brief  set port direction
* \param  HW requirement
* \param  port
* \param  direction
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS drvTCA9555SetPortDir(const HwReqI2C* hw, PORTS port, DIRECTION dir);

/**
* \brief  set pin direction
* \param  HW requirement
* \param  port
* \param  pin number
* \param  direction
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS drvTCA9555SetPinDir(const HwReqI2C* hw, PORTS port, PINS pin, DIRECTION dir);

/**
* \brief  read input port
* \note   all pins of port should be input
* \param  HW requirement
* \param  port
* \return if everything is OK, return port input value(0-0XFF)
*         otherwise return -1
*/
S32 drvTCA9555ReadPort(const HwReqI2C* hw, PORTS port);

/**
* \brief  read input pin
* \note   pin should be input
* \param  HW requirement
* \param  port
* \param  pin
* \return if everything is OK, return 0 or 1
*         otherwise return -1
*/
S32 drvTCA9555ReadPin(const HwReqI2C* hw, PORTS port, PINS pin);

/**
* \brief  set port value
* \note   all pins of port should be output
* \param  HW requirement
* \param  port
* \param  valu, (0-0xFF)
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS drvTCA9555WriteOutputPort(const HwReqI2C* hw, PORTS port, U8 val);

/**
* \brief  set port value
* \note   pins should be output
* \param  HW requirement
* \param  port
* \param  pin
* \param  stat, 1 or 0 (TRUE  or FALSE)
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS drvTCA9555WriteOutputPin(const HwReqI2C* hw, PORTS port, PINS pin, BOOL stat);

/*************************** --- HOW TO USE *******************************
 * STM example HAL_I2C_Mem_Write and HAL_I2C_Mem_Read
#define TCA9555_U7_ADDR     (0X20) //hw I2C addr
#define TCA9555_U8_ADDR     (0X22) //hw I2C addr

//typedef int RETURN_STATUS;
//#define FAILURE (-1)
//#define SUCCESS (0)

#include "i2c.h"
#define I2C_WRITE_FUNC(devAddr, memAddr, buff, leng) (HAL_I2C_Mem_Write(&hi2c1, devAddr, memAddr, I2C_MEMADD_SIZE_8BIT, buff, leng, 300))
#define I2C_READ_FUNC(devAddr, memAddr, buff, leng)  (HAL_I2C_Mem_Read(&hi2c1, devAddr, memAddr, I2C_MEMADD_SIZE_8BIT, buff, leng, 300))

#define I2C_RET_OK  (HAL_OK)
#define I2C_RET_TYPE HAL_StatusTypeDef

static RETURN_STATUS i2cWriteFunc(U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng)
{
    RETURN_STATUS retVal = FAILURE;

    if (I2C_RET_OK == I2C_WRITE_FUNC(devAdr, memAdr, buff, bufLeng))
    {
        retVal = SUCCESS;
    }

    return retVal;
}

static RETURN_STATUS i2cReadFunc(U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng)
{
    RETURN_STATUS retVal = FAILURE;

    if (I2C_RET_OK == I2C_READ_FUNC(devAdr, memAdr, buff, bufLeng))
    {
        retVal = SUCCESS;
    }

    return retVal;
}

int main(void)
{
    HwReqI2C hw;
    int retVal;

    hw.i2cReadFunc  = i2cReadFunc;
    hw.i2cWriteFunc = i2cWriteFunc;
    hw.devAddr      = TCA9555_ADDR;

    retVal = drvTCA9555Init(&hw);

    if (SUCCESS == retVal)
    {
        retVal  = drvTCA9555SetPinDir(&hw, EN_PORT_0, EN_PIN_6, EN_OUT); //just 6. and 7. pins are output
        retVal |= drvTCA9555SetPinDir(&hw, EN_PORT_0, EN_PIN_7, EN_OUT); //just 6. and 7. pins are output
        retVal |= drvTCA9555SetPortDir(&hw, EN_PORT_1, EN_OUT); //port1 all pins output
    }
}
*/

#endif /* __DRV_TCA9555_H__ */

/********************************* End Of File ********************************/
