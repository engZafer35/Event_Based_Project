/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : MiddKeysCntrl.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
#define SHOW_PAGE_DBG_MSG    (DISABLE)//(ENABLE)//
/********************************* INCLUDES ***********************************/
#include "ProjectConf.h"
#include "MiddKeysCntrl.h"
#include "MiddDigitalIOControl.h"

#include "DrvTCA9555.h"
/****************************** MACRO DEFINITIONS *****************************/

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static KeysListener gCbListener;

static U8 gTca_P0; //PCA U16 port0 value
//static U8 gTca_P1; //PCA U16 port1 value
/***************************** STATIC FUNCTIONS  ******************************/
static U32 findIndex(U32 val)
{
    U32 ret = 0;

    while(val > 0)
    {
        val =  val >> 1;
        ret++;
    }
    return ret;
}

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

/********************************** VARIABLES *********************************/
static HwReqI2C ghw = {
                          .i2cWriteFunc = i2cWriteFunc,
                          .i2cReadFunc  = i2cReadFunc
                      };

static KEYS getPressedKey(U32 devID)
{
    KEYS key = EN_KEY_NONE;
    S32 pv;
    U32 gpioNum;
    U8 ch;

    if (1 == devID) //U16
    {
        ghw.devAddr = TCA9555_I2C_ADDR;
        pv = drvTCA9555ReadPort(&ghw, EN_PORT_0);
        if (-1 != pv)
        {
            ch = gTca_P0 ^ (U8)pv;
            gTca_P0 = (U8)pv; //update new port value
            if (0 != ch)
            {
                gpioNum = findIndex(ch);
                if (pv & ch) //gpio HIGH
                {
                    switch (gpioNum)
                    {
                        case 1: key = EN_KEY_S1_OFF; break;
                        case 2: key = EN_KEY_S2_OFF; break;
                        case 3: key = EN_KEY_S3_OFF; break;
                        case 4: key = EN_KEY_S4_OFF; break;
                        case 5: key = EN_KEY_S5_OFF; break;
                        case 6: key = EN_KEY_S6_OFF; break;
                        case 7: key = EN_KEY_S7_OFF; break;
                        case 8: key = EN_KEY_S8_OFF; break;
                        default: break;
                    }
                }
                else //gpio LOW
                {
                    switch (gpioNum)
                    {
                        case 1: key = EN_KEY_S1_ON; break;
                        case 2: key = EN_KEY_S2_ON; break;
                        case 3: key = EN_KEY_S3_ON; break;
                        case 4: key = EN_KEY_S4_ON; break;
                        case 5: key = EN_KEY_S5_ON; break;
                        case 6: key = EN_KEY_S6_ON; break;
                        case 7: key = EN_KEY_S7_ON; break;
                        case 8: key = EN_KEY_S8_ON; break;
                        default: break;
                    }
                }

                return key; /* just handle one key changed status, don't check other gpio, use case*/
            }
        }

#if 0 //port 1 is output. if need input, enable if block
        pv = drvTCA9555ReadPort(&ghw, EN_PORT_1);
        if (-1 != pv)
        {
            ch = gTca_P1 ^ pv;
            gTca_P1 = pv; //update new port value
            if (0 != ch)
            {
                gpioNum = findIndex(ch);
                if (pv & ch) //gpio HIGH
                {
                    switch (gpioNum)
                    {
                        case 1: key = EN_KEY_xx_OFF; break;
                        case 2: key = EN_KEY_xx_OFF; break;
                        case 3: key = EN_KEY_xx_OFF; break;
                        case 4: key = EN_KEY_xx_OFF; break;
                        case 5: key = EN_KEY_xx_OFF; break;
                        case 6: key = EN_KEY_xx_OFF; break;
                        case 7: key = EN_KEY_xx_OFF; break;
                        case 8: key = EN_KEY_xx_OFF; break;
                        default: break;
                    }
                }
                else //gpio LOW
                {
                    switch (gpioNum)
                    {
                        case 1: key = EN_KEY_xx_ON; break;
                        case 2: key = EN_KEY_xx_ON; break;
                        case 3: key = EN_KEY_xx_ON; break;
                        case 4: key = EN_KEY_xx_ON; break;
                        case 5: key = EN_KEY_xx_ON; break;
                        case 6: key = EN_KEY_xx_ON; break;
                        case 7: key = EN_KEY_xx_ON; break;
                        case 8: key = EN_KEY_xxx_ON; break;
                        default: break;
                    }
                }

                return key; /* just handle one key changed status, don't check other gpio, use case*/
            }
        }
#endif

    }

    return EN_KEY_NONE;
}

static void cbPca(U32 val)
{
    KEYS key;

    key = getPressedKey(1); //1 for PCA U16
    if (EN_KEY_NONE != key)
    {
        gCbListener(key);
    }
}

/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS middKeysInit(void)
{
    RETURN_STATUS retVal;
    S32 temp;

    ghw.devAddr = TCA9555_I2C_ADDR;
    retVal = drvTCA9555Init(&ghw);

    if (SUCCESS == retVal)
    {
        retVal = drvTCA9555SetPortDir(&ghw, EN_PORT_0, EN_IN);
        /** port 0 is input, port 1 output */
    }

    /** !< load button starting value */
    if (SUCCESS == retVal)
    {
        retVal = FAILURE;
        temp = drvTCA9555ReadPort(&ghw, EN_PORT_0);
        if (-1 != temp)
        {
            gTca_P0 = temp;
            retVal = SUCCESS;
        }

      #if 0 //port 1 is output. if need input, enable if block
        if ((SUCCESS == retVal) && (-1 != (temp = drvTCA9555ReadPort(&ghw, EN_PORT_1))))
        {
            gTca_P1 = temp;
        }
        else
        {
            retVal = FAILURE;
        }
      #endif
    }

    DBG_MSG("->[I] midd keys Init retVal: %d", retVal);

    return retVal;
}

RETURN_STATUS midKeysListener(KeysListener cb, BOOL stat)
{
    RETURN_STATUS retVal;

	retVal = middIOIntListen(EN_IN_PCA_EXT_INT, cbPca, stat);

	gCbListener = cb;
	DBG_MSG(" ->[I] midd Keys listener loaded SUCCESS");

    return retVal;
}

RETURN_STATUS middKeyRead(struct KeyStat* ks)
{
    RETURN_STATUS retVal = SUCCESS;
    S32 pv;

    ghw.devAddr = TCA9555_I2C_ADDR;
    pv = ~drvTCA9555ReadPort(&ghw, EN_PORT_0); //pull down so invert data
    if (-1 != pv)
    {
        ks->tca1_0 = pv;
    }
    else
    {
        retVal |= FAILURE;
    }

#if 0 //port 1 is output. if need input, enable if block
    pv = ~drvTCA9555ReadPort(&ghw, EN_PORT_1);//pull down so invert data
    if (-1 != pv)
    {
        ks->tca1_1 = pv;
    }
    else
    {
        retVal |= FAILURE;
    }
#endif

    return retVal;
}

/******************************** End Of File *********************************/
