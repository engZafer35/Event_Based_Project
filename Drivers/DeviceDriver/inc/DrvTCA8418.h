/*****************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : DrvTCA8418.h
******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __DRV_TCA8418_H__
#define __DRV_TCA8418_H__
/*********************************INCLUDES*************************************/
#include "GlobalDefinitions.h"
/******************************MACRO DEFINITIONS*******************************/
#define TCA8418_MAX_ROWS	(8)
#define TCA8418_MAX_COLS 	(10)

/*******************************TYPE DEFINITIONS ******************************/
 typedef enum _PINS
 {
     EN_ROW_1, EN_ROW_2, EN_ROW_3, EN_ROW_4, \
     EN_ROW_5, EN_ROW_6, EN_ROW_7, EN_ROW_8, \

     EN_COL_1, EN_COL_2, EN_COL_3, EN_COL_4, \
     EN_COL_5, EN_COL_6, EN_COL_7, EN_COL_8, \
     EN_COL_9, EN_COL_10,
 }PINS;

 typedef enum _PIN_MODE
 {
     EN_PIN_OUT,
     EN_PIN_IN,
 }PIN_MODE;

 /**
  * \brief load hardware requirement
  */
 typedef struct _HwI2C
 {
     U32 devAddr;
     RETURN_STATUS (*write) (U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng);
     RETURN_STATUS (*read)  (U32 devAdr, U32 memAdr, U8* buff, U32 bufLeng);
 }HwI2C;
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
/**
* \brief  init TCA8418
* \param  hardware i2c, driver will copy hwI2c, user can delete own struct
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS drvTca8418Init(const HwI2C *hwI2c);

/**
* \brief  set keypad rows and columns
* \param  total row number     - TCA8418_MAX_ROWS (8)
* \param  total columns number - TCA8418_MAX_COLS (10)
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS drvSetKeypad(U32 rowNumber, U32 colNumber);

/**  !! not implemented !!
* \brief  set gpio to use input or output
* \param  pin mode, input or output
* \param  pin
* \return if everything is OK, return SUCCES
*         otherwise return FAILURE
*/
RETURN_STATUS drvSetGpio(PIN_MODE pm, PINS pin);

/**
* \brief  callback for interrupt pin
* \param  callback function
* \param  listen mode enable or disable
*/
void drvTca8418CbListener(VUICallback cb, BOOL stat);

/**
* \brief  clear FIFO
* \param  void
*/
RETURN_STATUS drvTca8418FlushFifo(void);

#endif /* __DRV_TCA8418_H__ */
/********************************* End Of File ********************************/
