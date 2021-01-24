/******************************************************************************
* #Author 		: Zafer Satılmış
* #Revision		: 1.0
* #Date			: Jan 27, 2021 - 9:05:66 AM
* #File Name	: DriverLM75B_DigitalTemp.h
*******************************************************************************/

/******************************************************************************
*                       Table Pin Description
*    Symbol     Pin                   Description
*    SDA     -   1      -     Digital I/O. I2C-bus serial bidirectional data line; open-drain.
*    SCL     -   2      -     Digital input. I2C-bus serial clock input.
*    OS      -   3      -     Over temperature Shutdown output; open-drain.
*    GND     -   4      -     Ground. To be connected to the system ground.
*    A2      -   5      -     Digital input. User-defined address bit 2.
*    A1      -   6      -     Digital input. User-defined address bit 1.
*    A0      -   7      -     Digital input. User-defined address bit 0.
*    VCC     -   8      -     Power supply
*
*            |------>Pin_3, OS Output, open-drain.
*  IC OUT----|
*            |---|
*               _|_ 
*              |___|  
*
*******************************************************************************/
/******************************IFNDEF ï¿½ DEFINE********************************/
#ifndef __DRV_LM75B_DIGITAL_TEMP_H__
#define __DRV_LM75B_DIGITAL_TEMP_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/

 /**
  * \brief load hardware requirement
  */
 typedef struct _I2C_Func
 {
     U32 devAddr;
     RETURN_STATUS (*write) (U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng);
     RETURN_STATUS (*read)  (U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng);
 }LM75B_I2C;
/************************* OPTIMIZATION *********************/
/*
 * If you dont need to change some value or status in run time, 
 * you can use OPTIMIZATION macro to reduce the code size. 
 *
 * If you set OPTIMIZATION macro, you should check each
 * default value or status and select correct value.
 *
 ************************************************************/
 
#define OPTIMIZATION    (1) //1: code optimization active, 0: pasive

#if (OPTIMIZATION == 1)
    #define OVERTEMPERATURE_VALUE     (60) //Centigrade
    #define HYSTERESIS_TEMP_VALUE     (50) //Centigrade
#endif
/**
 * @brief LM75 has 2 working mode. In periodic measure mode, device measure temp 
 *        each 100ms. Device update temp resgister to write new temp about 10ms.
*/
typedef enum _LM75_WORKING_MODE
{ 
    EN_LM75_WORK_MODE_PERIODIC_MEASURE = 0,   //0b00000000  //device update temp register each 100 ms
    EN_LM75_WORK_MODE_SHUTDOWN         = 0x01,//0b00000001 //device in idle(no update temp register)        

#if (OPTIMIZATION == 1)    
  #define DF_LM75_WORKING_MODE (EN_LM75_WORK_MODE_PERIODIC_MEASURE)
#endif    
    
}LM75_WORKING_MODE;

/**
 * @brief OS output working mode. For more deteail check datasheet.
*/
typedef enum _OS_WORKING_MODE
{
    EN_OS_WORKING_COMPARATOR = 0,   //0b00000000
    EN_OS_WORKING_INTERRUPT  = 0x02,//0b00000010
        
#if (OPTIMIZATION == 1)
  #define DF_OS_WORKING_MODE   (EN_OS_WORKING_COMPARATOR)   
 // #define USE_INTERRUPT //if using interrupt mode, uncomment USE_INTERRUPT macro    
#endif       
    
}OS_WORKING_MODE;

/**
 * @brief If Temp value overs the threshold temp value, device toggle OS pin.
 *         User can select default status of OS pin. 
*/
typedef enum _OS_POLARITY
{  
    EN_OS_POLARITY_LOW  = 0,    //0b00000000
    EN_OS_POLARITY_HIGH = 0x04, //0b00000100

#if (OPTIMIZATION == 1)    
  #define DF_OS_POLARITY   (EN_OS_POLARITY_HIGH)  
#endif
        
}OS_POLARITY;

/**
 * @brief Fault num is used as a counter. If number of overtemperature exceed the 
 *        fault number, OS output will be active.
*/
typedef enum _OS_FAULT_NUM
{
    EN_OS_FAULT_NUM_1 = 0x00, //0b00000000
    EN_OS_FAULT_NUM_2 = 0x08, //0b00001000
    EN_OS_FAULT_NUM_4 = 0x10, //0b00010000
    EN_OS_FAULT_NUM_6 = 0x18, //0b00011000
    
#if (OPTIMIZATION == 1)    
  #define DF_OS_FAULT_NUM (EN_OS_FAULT_NUM_1)
#endif    
        
}OS_FAULT_NUM;

/*******************************TYPE DEFINITIONS ******************************/

#if (OPTIMIZATION == 0)
typedef struct _LM75_CONF_REG
{
    LM75_WORKING_MODE workingMode;    
    OS_POLARITY       osPolarity;
    OS_WORKING_MODE   osWorkingMode;    
    OS_FAULT_NUM      osFaultNum;    
}LM75_CONF_REG;

typedef struct _LM75_INIT_STR
{
    LM75_CONF_REG   confReg;
    U16             overTemp;
    U16             hysTemp;
    
}LM75_INIT_STR;
#endif

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

#if (OPTIMIZATION == 1)
/**
 * @brief init LM75 temperature sensor with default value
* \param  hardware i2c, driver will copy i2c, user can delete own struct
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
 */
RETURN_STATUS drvLM75Init(const LM75B_I2C *i2c);
#endif

/**
 * @brief  read temperature
 * @param  void
 * @return if everything is OK, return SUCCES
 *         otherwise return 0XFFFF
 */
float drvLM75GetTemp(void);

#if ((OPTIMIZATION == 0) || (defined USE_INTERRUPT))
/**
 * @brief  clear LM75B interrupt output
 * @note   if you select interrupt mode for os_working mode 
 *         you can use this func to clear os output status
 * @param  void 
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75ClrInterrupt(void);
#endif

#if (OPTIMIZATION == 0)
/**
 * @brief  init LM75 temperature sensor. 
 * @param  init struct. If NULL func will use default value
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75Init(const LM75_INIT_STR *intStr, const LM75B_I2C *i2c);

/**
 * @brief  set threshold and hysteresis temperature value
 * @param  threshold value (Centigrade)
 * @param  hysteresis value (Centigrade)
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetTohAndThyr(U16 toh, U16 hys);


/**
 * @brief  set OS working mode
 * @param  mode
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetOsWorkingMode(OS_WORKING_MODE mode);

/**
 * @brief  set sensor(LM75) working mode
 * @param  mode
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetL75WorkingMode(LM75_WORKING_MODE mode);

/**
 * @brief  set os polarity
 * @param  mode
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetOsPolarity(OS_POLARITY mode);

/**
 * @brief  set fault number
 * @param  mode
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75SetFaultNum(OS_FAULT_NUM fault);

/**
 * @brief  read Toh and Thyr
 * @param  mode
 * @param  hysteresis
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75ReadTohAndThyr(float *toh, float *hys);

/**
 * @brief  read conf. register
 * @param  mode
 * @param  hysteresis
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75ReadConf(LM75_CONF_REG *confReg);

/**
 * @brief  clear LM75B interrupt output
 * @note   if you select interrupt mode for os_working mode 
 *         you can use this func to clear os output status
 * @param  void 
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvLM75ClrInterrupt(void);
#endif //#if (OPTIMIZATION == 0)

#endif /* __DRV_LM75B_DIGITAL_TEMP_H__ */

/********************************* End Of File ********************************/
