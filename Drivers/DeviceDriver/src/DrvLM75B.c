/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : DrvLM75B_DigitalTemp.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/
/*********************************INCLUDES*************************************/
#include "DrvLM75B.h"
#include "ProjectConf.h"

/****************************** MACRO DEFINITIONS *****************************/
#define TEMP_REGISTER_ADD   (0x00) //tempeture register add
#define CONF_REGISTER_ADD   (0x01) //configuration register add
#define THYS_REG_ADD        (0x02) //hysteresis register add
#define TOH_REG_ADD         (0x03) //threshold temp register add

#define SIZEOF_TEMP_REG     (2)
#define SIZEOF_CONF_REG     (1)
#define SIZEOF_THYS_REG     (2)
#define SIZEOF_TOH_REG      (2)

#define I2C_CONN_TIMEOUT	(100)

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

static LM75B_I2C gI2c;
/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/
/**
 * @brief  read tempetarature
 * @param  void
 * @return if everything is OK, return temperature
 *         otherwise return 0XFFFF;
 */
float drvLM75GetTemp(void)
{
    float retTemp = 0XFFFF;
    U8 buff[SIZEOF_TEMP_REG];

    if (0 != gI2c.devAddr)
    {
        if (SUCCESS == gI2c.read(gI2c.devAddr, TEMP_REGISTER_ADD, (U8 *)buff, SIZEOF_TEMP_REG))
        {
            retTemp =  (buff[0] << 8) + buff[1];
            retTemp =  retTemp/256;
        }
    }
    
    return retTemp;
}

#if (OPTIMIZATION == 1)
/**
 * @brief  init LM75 temperature sensor with default value
 * @param  init struct. 
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75Init(const LM75B_I2C *i2c)
{
    RETURN_STATUS retVal = FAILURE;
    U8 buff[2]; //max register 2 byte

    if (IS_SAFELY_PTR(i2c))
    {
        gI2c = *i2c;

        buff[0] = OVERTEMPERATURE_VALUE & 0x00FF;
        buff[1] = OVERTEMPERATURE_VALUE & 0xFF00;

        if (SUCCESS == gI2c.write(gI2c.devAddr, TOH_REG_ADD, (uint8_t *)buff, SIZEOF_TOH_REG))
        {
            buff[0] = HYSTERESIS_TEMP_VALUE & 0x00FF;
            buff[1] = HYSTERESIS_TEMP_VALUE & 0xFF00;
            if (SUCCESS == gI2c.write(gI2c.devAddr, THYS_REG_ADD, (uint8_t *)buff, SIZEOF_THYS_REG))
            { 
                //load conf register data
                buff[0] = DF_LM75_WORKING_MODE + DF_OS_WORKING_MODE + DF_OS_POLARITY + DF_OS_FAULT_NUM;

                if (SUCCESS == gI2c.write(gI2c.devAddr, CONF_REGISTER_ADD, (uint8_t *)buff, SIZEOF_CONF_REG))
                {
                    retVal = SUCCESS;
                }
            }
        }
    }
      
    return retVal;

}
#endif

#if ((OPTIMIZATION == 0) || (defined USE_INTERRUPT))
/**
 * @brief  clear LM75B interrupt output
 * @note   if you select interrupt mode for os_working mode 
 *         you can use this func to clear os output status
 * @param  void 
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75ClrInterrupt(void)
{
    RETURN_STATUS retVal = FAILURE;

    if (0 != gI2c.devAddr)
    {
        if (0XFFFF != drvLM75GetTemp())
        {
            retVal = SUCCESS;
        }
    }

    return retVal;
}
#endif


#if (OPTIMIZATION == 0)
/**
 * @brief  init LM75 temperature sensor. 
 * @param  init struct. 
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75Init(const LM75_INIT_STR *intStr, const LM75B_I2C *i2c)
{
    RETURN_STATUS retVal = FAILURE;
    U8 configReg; //max register 2 byte
    
    if (IS_SAFELY_PTR(intStr) && IS_SAFELY_PTR(i2c))
    {        
        gI2c = *i2c;

        if (SUCCESS == drvLM75SetTohAndThyr(intStr->overTemp, intStr->hysTemp))
        {
            //load conf register data
            configReg = intStr->confReg.osWorkingMode + intStr->confReg.osPolarity + intStr->confReg.osWorkingMode + intStr->confReg.osFaultNum;                                
            
            retVal = gI2c.write(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&configReg, SIZEOF_CONF_REG);
        }              
    } 
      
    return retVal;
}

/**
 * @brief  set threshold and hysteresis temperature value
 * @param  threshold value (Centigrade)
 * @param  hysteresis value (Centigrade)
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetTohAndThyr(U16 toh, U16 hys)
{
    RETURN_STATUS retVal = FAILURE;
    U8 buff[2]; //max register 2 byte
 
    if (0 != gI2c.devAddr)
    {
        buff[0] = toh & 0x00FF;
        buff[1] = (toh >> 8) & 0x00FF;

        if (SUCCESS == gI2c.write(gI2c.devAddr, TOH_REG_ADD, (U8 *)buff, SIZEOF_TOH_REG))
        {
            buff[0] = hys & 0x00FF;
            buff[1] = (hys >>8) & 0x00FF;

           retVal = gI2c.write(gI2c.devAddr, THYS_REG_ADD, (U8 *)buff, SIZEOF_THYS_REG);
        }
    }

    return retVal;
}

/**
 * @brief  set OS working mode
 * @param  mode
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetOsWorkingMode(OS_WORKING_MODE mode)
{
    RETURN_STATUS retVal = FAILURE;
    U8 temp;

    if (0 != gI2c.devAddr)
    {
        if (SUCCESS == gI2c.read(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&temp, SIZEOF_CONF_REG))
        {
            temp &= 0xFD; //clear os working bit
            temp |= mode;

            retVal = gI2c.write(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&temp, SIZEOF_CONF_REG);
        }
    }

    return retVal;
}

/**
 * @brief  set sensor(LM75) working mode
 * @param  mode
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetL75WorkingMode(LM75_WORKING_MODE mode)
{
    RETURN_STATUS retVal = FAILURE;
    U8 temp;

    if (0 != gI2c.devAddr)
    {
        if (SUCCESS == gI2c.read(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&temp, SIZEOF_CONF_REG))
        {
            temp &= 0xFE; //clear LM75 working mode bit
            temp |= mode;

            retVal = gI2c.write(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&temp, SIZEOF_CONF_REG);
        }
    }

    return retVal;
}

/**
 * @brief  set sensor(LM75) working mode
 * @param  mode
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetOsPolarity(OS_POLARITY mode)
{
    RETURN_STATUS retVal = FAILURE;
    U8 temp;

    if (0 != gI2c.devAddr)
    {
        if (SUCCESS == gI2c.read(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&temp, SIZEOF_CONF_REG))
        {
            temp &= 0xFB; //clear os polarity bit
            temp |= mode;

            retVal = gI2c.write(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&temp, SIZEOF_CONF_REG);
        }
    }
    return retVal;
}

/**
 * @brief  set fault number
 * @param  mode
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetFaultNum(OS_FAULT_NUM fault)
{
    RETURN_STATUS retVal = FAILURE;
    U8 temp;
    
    if (0 != gI2c.devAddr)
    {
        if (SUCCESS == gI2c.read(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&temp, SIZEOF_CONF_REG))
        {
            temp &= 0xE7; //clear os polarity bit
            temp |= fault;

            retVal = gI2c.write(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&temp, SIZEOF_CONF_REG);
        }
    }
    return retVal;
}

/**
 * @brief  read Toh and Thyr
 * @param  Toh set add
 * @param  hysteresis set add
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75ReadTohAndThyr(float *toh, float *hys)
{
    RETURN_STATUS retVal = FAILURE;
    U8 buff[SIZEOF_THYS_REG];
    
    if (0 != gI2c.devAddr)
    {
        if (IS_SAFELY_PTR(toh) && IS_SAFELY_PTR(hys))
        {
            if (SUCCESS == gI2c.read(gI2c.devAddr, TOH_REG_ADD, (U8 *)buff, SIZEOF_TOH_REG))
            {
                (*toh) = (buff[0] << 8) + buff[1];
                (*toh) = (*toh)/256;

                buff[0] = buff[1] = 0;
                if (SUCCESS == gI2c.read(gI2c.devAddr, THYS_REG_ADD, (U8 *)buff, SIZEOF_THYS_REG))
                {
                    (*hys) = (buff[0]<<8) + buff[1];
                    (*hys) = (*hys)/256;
            
                    retVal = SUCCESS;
                }
            }
        }
    }

    return retVal;
}

/**
 * @brief  read conf. register
 * @param  mode
 * @param  hysteresis
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75ReadConf(LM75_CONF_REG *confReg)
{
    RETURN_STATUS retVal = FAILURE;
    U8 conf;
   
    if (0 != gI2c.devAddr)
    {
       if(IS_SAFELY_PTR(confReg))
       {
            if (SUCCESS == gI2c.read(gI2c.devAddr, CONF_REGISTER_ADD, (U8 *)&conf, SIZEOF_CONF_REG))
            {
                confReg->workingMode    = (LM75_WORKING_MODE)(conf & 0x01);
                confReg->osWorkingMode  = (OS_WORKING_MODE)(conf & 0x02);
                confReg->osPolarity     = (OS_POLARITY)(conf & 0x04);
                confReg->osFaultNum     = (OS_FAULT_NUM)(conf & 0x18);

                retVal = SUCCESS;
            }
        }
    }

    return retVal;
}

#endif //#if (OPTIMIZATION == 0)
/******************************** End Of File *********************************/
