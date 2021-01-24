/******************************************************************************
* #Author 		: Zafer Satılmış
* #Revision		: 1.0
* #Date			: Jan 15, 2021 - 9:05:66 AM
* #File Name	: DriverSTM32_ADC.h
*******************************************************************************/

/******************************************************************************
*          ADC1   ADC2   ADC3
*0         PA0    PA0    PA0
*1         PA1    PA1    PA1
*2         PA2    PA2    PA2
*3         PA3    PA3    PA3
*4         PA4    PA4    PF6
*5         PA5    PA5    PF7
*6         PA6    PA6    PF8
*7         PA7    PA7    PF9
*8         PB0    PB0    PF10
*9         PB1    PB1    PF3
*10        PC0    PC0    PC0
*11        PC1    PC1    PC1
*12        PC2    PC2    PC2
*13        PC3    PC3    PC3
*14        PC4    PC4    PF4
*15        PC5    PC5    PF5
*
*How To Use: User firstly init ADC BUS. For that firstly call drvADCInitBus() 
*            after that invoke drvADCInitChannel() with same bus number. If initialize
*            steps are SUCCESSFULY, drvADCRead() can be used.
*
******************************************************************************/
/******************************IFNDEF ï¿½ DEFINE********************************/
#ifndef __DRIVER_STM32_ADC_H__
#define __DRIVER_STM32_ADC_H__

/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
#include "ProjectConf.h"
/******************************MACRO DEFINITIONS*******************************/

/*
 * Select which channel need to use
*/
#define USE_BUS_1   (1) // 1: ENABLE, 0: DISABLE
#define USE_BUS_2   (0) // 1: ENABLE, 0: DISABLE
#define USE_BUS_3   (0) // 1: ENABLE, 0: DISABLE

#define ADC_REF_VOLTAGE (3300) //not used, just mcu vref info


//-------- Default Bus Values ----------//
#define CLOCK_PRESCALLER    (ADC_CLOCK_SYNC_PCLK_DIV4)
#define RESOLUTION          (ADC_RESOLUTION_12B) 
#define SCAN_CONV_MODE      (DISABLE)                       //ScanConvMode
#define CON_CONV_MODE       (ENABLE)                        //ContinuousConvMode
#define DIS_CONT_CONV_MODE  (DISABLE)                       //DiscontinuousConvMode
#define EXT_TRIG_CONV_EDGE  (ADC_EXTERNALTRIGCONVEDGE_NONE) //ExternalTrigConvEdge
#define EXT_TRIG_CONV       (ADC_EXTERNALTRIGCONV_T1_CC1)   // ExternalTrigConv
#define DATA_ALIGN          (ADC_DATAALIGN_RIGHT)           //DataAlign
#define DMA_CONTIN_REQUEST  (DMAContinuousRequests)         //DMAContinuousRequests
#define EOC_SELECTION       (EOCSelection)                  //EOCSelection
#define NBR_OF_CONVERSION   (1)                             //set using channel number


#if (CURRENT_BOARD == BOARD_STM_010101)
#define SAMPLING_TIME       (ADC_SAMPLETIME_480CYCLES)
#elif (CURRENT_BOARD == BOARD_STM_LP_010101)
#define SAMPLING_TIME    (ADC_SAMPLETIME_640CYCLES_5)
#endif

/*******************************TYPE DEFINITIONS ******************************/
typedef enum _EN_ADC_CHANNEL
{
	EN_ADC_CHANNEL_0,  
	EN_ADC_CHANNEL_1, 
	EN_ADC_CHANNEL_2,  
	EN_ADC_CHANNEL_3,
#if CURRENT_BOARD == BOARD_STM_LP_010101
	EN_ADC_CHANNEL_4 = ADC_CHANNEL_4,
#elif CURRENT_BOARD == BOARD_STM_010101
	EN_ADC_CHANNEL_4,
#endif
	EN_ADC_CHANNEL_5,  
	EN_ADC_CHANNEL_6,  
	EN_ADC_CHANNEL_7,  
	EN_ADC_CHANNEL_8,  
	EN_ADC_CHANNEL_9,  
	EN_ADC_CHANNEL_10, 
	EN_ADC_CHANNEL_11, 
	EN_ADC_CHANNEL_12, 
	EN_ADC_CHANNEL_13, 
	EN_ADC_CHANNEL_14, 
	EN_ADC_CHANNEL_15, 
     
    EN_ADC_CHANNEL_MAX_NUM
    
}EN_ADC_CHANNEL;

typedef enum _EN_ADC_BUS
{
#if (USE_BUS_1 == 1)
    EN_ADC_BUS_1, //ADC1 
#endif
#if (USE_BUS_2 == 1)    
    EN_ADC_BUS_2, //ADC2 
#endif    
#if (USE_BUS_3 == 1)    
    EN_ADC_BUS_3, //ADC3 
#endif
    EN_ADC_BUSS_MAX_NUM
}EN_ADC_BUS;
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

/**
 * @brief  init ADC Bus. Func will handle ADC1, ADC2, ADC3
 * @note   First of all call this function
 * @param  Bus ID
 * @param  if hAdcX is NULL, func will use default values
 *         if hAdcX is not NULL, func will create ADC_HandleTypeDef value so user dont 
 *         need to keep this value.
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvADCInitBus(EN_ADC_BUS busID, ADC_HandleTypeDef *hAdcX);

/**
 * @brief  init ADC Channel.
 * @note   Firstly drvADCInitBus() should be call. 
 * @param  Bus ID 
 * @pram   channel ID
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvADCInitChannel(EN_ADC_BUS busID, EN_ADC_CHANNEL chnlID);

/**
 * @brief   read adc
 * @note    Firstly drvADCInitAdcBus() and drvADCInitAdcChannel() should be call. 
 * @param   Bus ID
 * @pram    Channel ID
 * @return  if everything is OK, return adc value
 *          otherwise return -1(FAILURE)
 */
int drvADCRead(EN_ADC_BUS busID, EN_ADC_CHANNEL chnlID);


#endif /* __DRIVER_STM32_ADC_H__ */

/********************************* End Of File ********************************/
