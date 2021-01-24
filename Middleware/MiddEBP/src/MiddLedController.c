/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddLedController.c
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include <string.h>
#include "ProjectConf.h"
#include "MiddLedController.h"

#include "DrvTCA9555.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static U8 gLeds[EN_LED_PIN_LED_MAX]; //contains bool value

static union
{
    U8 port;
    struct
    {
        U8 pin_0 :1;
        U8 pin_1 :1;
        U8 pin_2 :1;
        U8 pin_3 :1;
        U8 pin_4 :1;
        U8 pin_5 :1;
        U8 pin_6 :1;
        U8 pin_7 :1;
    };
}gTca1_0, gTca1_0_prev, gTca1_1, gTca1_1_prev;//, gTca2_0, gTca2_0_prev, gTca2_1, gTca2_1_prev;

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

/** very small function and used in a few point, we can use inline .*/
static inline void setPortPinStat(U8* port, U8 pin, BOOL stat)
{
    if (0 == stat)
    {
        (*port) &= ~(1 << pin);
    }
    else
    {
        (*port) |= (1 << pin);
    }
}
/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS middLedInit(void)
{
    RETURN_STATUS retVal;
    HwReqI2C hw;

    hw.i2cReadFunc  = i2cReadFunc;
    hw.i2cWriteFunc = i2cWriteFunc;

    hw.devAddr = TCA9555_I2C_ADDR;
    retVal = drvTCA9555Init(&hw);

    /** Clear firstly output status */
    if (SUCCESS == retVal)
    {
        retVal = middLedCloseAll();
    }

    /** set direction */
    if (SUCCESS == retVal)
    {
        //hw.devAddr = TCA9555_I2C_ADDR; //not need, already adress loaded
        retVal = drvTCA9555SetPortDir(&hw, EN_PORT_1, EN_OUT); //port1 all pins output
    }

    DBG_MSG("->[I] midd Key_Led Init retVal: %d", retVal);

    return retVal;
}

RETURN_STATUS middLedSet(LEDS led, BOOL stat)
{
    RETURN_STATUS retVal = FAILURE;
    HwReqI2C hw;
    PINS pin = EN_PIN_MAX_NUM;
    PORTS pcaPort = -1;

    hw.devAddr = 0; //devAddr=0 will also be used as a flag
    hw.i2cReadFunc  = i2cReadFunc;
    hw.i2cWriteFunc = i2cWriteFunc;

    if (led > EN_LED_PIN_LED_MAX)
    {
        return FAILURE;
    }

    switch (led)
    {
        case EN_LED_LED1:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_0; break;
        case EN_LED_LED2:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_1; break;
        case EN_LED_LED3:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_2; break;
        case EN_LED_LED4:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_3; break;
        case EN_LED_LED5:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_4; break;
        case EN_LED_LED6:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_5; break;
        case EN_LED_LED7:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_6; break;
        case EN_LED_LED8:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_7; break;

#if 0 //example code. need more leds
        case EN_LED_LEDx:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_0; pin = EN_PIN_0; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_0; pin = EN_PIN_1; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_0; pin = EN_PIN_2; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_0; pin = EN_PIN_3; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_0; pin = EN_PIN_4; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_0; pin = EN_PIN_5; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_0; pin = EN_PIN_6; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_I2C_ADDR; pcaPort = EN_PORT_0; pin = EN_PIN_7; break;

        case EN_LED_LEDx:   hw.devAddr = TCA9555_xx_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_0; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_xx_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_1; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_xx_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_2; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_xx_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_3; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_xx_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_4; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_xx_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_5; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_xx_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_6; break;
        case EN_LED_LEDx:   hw.devAddr = TCA9555_xx_ADDR; pcaPort = EN_PORT_1; pin = EN_PIN_7; break;
#endif
        default: retVal = FAILURE; break;
    }

    if (0 != hw.devAddr)
    {
        retVal = drvTCA9555WriteOutputPin(&hw, pcaPort, pin, stat);
    }
    // else retVal = FAILURE; /* !< not need, already retVal = FAILURE */

    if (SUCCESS == retVal)
    {
        if (TCA9555_I2C_ADDR == hw.devAddr)
        {
            if (EN_PORT_0 == pcaPort)
            {
                setPortPinStat(&gTca1_0.port, pin, stat);
                gTca1_0_prev.port = gTca1_0.port;
            }
            else
            {
                setPortPinStat(&gTca1_1.port, pin, stat);
                gTca1_1_prev.port = gTca1_1.port;
            }
        }
#if 0 //example code. need more leds
        else if (TCA9555_xx_ADDR == hw.devAddr)
        {
            if (EN_PORT_0 == pcaPort)
            {
                setPortPinStat(&gTca1_0.port, pin, stat);
                gTca1_0_prev.port = gTca1_0.port;
            }
            else
            {
                setPortPinStat(&gTca2_1.port, pin, stat);
                gTca2_1_prev.port = gTca2_1.port;
            }
        }
#endif

        gLeds[led] = stat;
    }

    return retVal;
}

RETURN_STATUS middLedToggle(LEDS key)
{
    return middLedSet(key, !gLeds[key]);
}

void middLedLoadLedStat(LEDS led, BOOL stat)
{
    if (led > EN_LED_PIN_LED_MAX)
    {
        return;
    }

    switch (led)
    {
        case EN_LED_LED1:   gTca1_1.pin_0 = stat; break;
        case EN_LED_LED2:   gTca1_1.pin_1 = stat; break;
        case EN_LED_LED3:   gTca1_1.pin_2 = stat; break;
        case EN_LED_LED4:   gTca1_1.pin_3 = stat; break;
        case EN_LED_LED5:   gTca1_1.pin_4 = stat; break;
        case EN_LED_LED6:   gTca1_1.pin_5 = stat; break;
        case EN_LED_LED7:   gTca1_1.pin_6 = stat; break;
        case EN_LED_LED8:   gTca1_1.pin_7 = stat; break;

#if 0 //example code. need more leds
        case EN_LED_LEDx:   gTca1_0.pin_0 = stat; break;
        case EN_LED_LEDx:   gTca1_0.pin_1 = stat; break;
        case EN_LED_LEDx:   gTca1_0.pin_2 = stat; break;
        case EN_LED_LEDx:   gTca1_0.pin_3 = stat; break;
        case EN_LED_LEDx:   gTca1_0.pin_4 = stat; break;
        case EN_LED_LEDx:   gTca1_0.pin_5 = stat; break;
        case EN_LED_LEDx:   gTca1_0.pin_6 = stat; break;
        case EN_LED_LEDx:   gTca1_0.pin_7 = stat; break;

        case EN_LED_LEDx:   gTca2_1.pin_0 = stat; break;
        case EN_LED_LEDx:   gTca2_1.pin_1 = stat; break;
        case EN_LED_LEDx:   gTca2_1.pin_2 = stat; break;
        case EN_LED_LEDx:   gTca2_1.pin_3 = stat; break;
        case EN_LED_LEDx:   gTca2_1.pin_4 = stat; break;
        case EN_LED_LEDx:   gTca2_1.pin_5 = stat; break;
        case EN_LED_LEDx:   gTca2_1.pin_6 = stat; break;
        case EN_LED_LEDx:   gTca2_1.pin_7 = stat; break;
#endif
        default: break;
    }
}

RETURN_STATUS middLedFlush(void)
{
    RETURN_STATUS retVal = FAILURE;
    HwReqI2C hw;

    hw.i2cReadFunc  = i2cReadFunc;
    hw.i2cWriteFunc = i2cWriteFunc;

#if 0
    if (gTca1_0.port != gTca1_0_prev.port)
    {
        hw.devAddr = TCA9555_I2C_ADDR; //devAddr=0 will also be used as a flag
        if (SUCCESS == drvTCA9555WriteOutputPort(&hw, EN_PORT_0, gTca1_0.port))
        {
            gTca1_0_prev.port = gTca1_0.port;
        }
        else
        {
            retVal = FAILURE;
        }
    }
#endif

    if (gTca1_1.port != gTca1_1_prev.port)
    {
        hw.devAddr = TCA9555_I2C_ADDR; //devAddr=0 will also be used as a flag
        if (SUCCESS == drvTCA9555WriteOutputPort(&hw, EN_PORT_1, gTca1_1.port))
        {
            gTca1_1_prev.port = gTca1_1.port;
        }
        else
        {
            retVal = FAILURE;
        }
    }

#if 0 //example code. need more leds
    if (gTca1_0.port != gTca1_0_prev.port)
    {
        hw.devAddr = TCA9555_xx_ADDR; //devAddr=0 will also be used as a flag
        if (SUCCESS == drvTCA9555WriteOutputPort(&hw, EN_PORT_0, gTca2_0.port))
        {
            gTca2_0_prev.port = gTca2_0.port;
        }
        else
        {
            retVal = FAILURE;
        }
    }
#endif
    return retVal;
}

S32 middLedGetStat(LEDS key)
{
    return gLeds[key];
}

RETURN_STATUS middLedCloseAll(void)
{
    RETURN_STATUS retVal = SUCCESS;
    HwReqI2C hw;

    hw.i2cReadFunc  = i2cReadFunc;
    hw.i2cWriteFunc = i2cWriteFunc;

    hw.devAddr = TCA9555_I2C_ADDR;
    retVal |= drvTCA9555WriteOutputPort(&hw, EN_PORT_1, FALSE); //clear port 1

    if (SUCCESS == retVal)
    {
        gTca1_1_prev.port = gTca1_1.port = 0;

        memset(gLeds, 0, sizeof(gLeds));
    }

    return retVal;
}
/******************************** End Of File *********************************/
