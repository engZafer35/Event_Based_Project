/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 15, 2021 - 9:05:66 AM
* #File Name    : DrvPca9535x.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __DRV_PCA9535X_H__
#define __DRV_PCA9535X_H__
/*********************************INCLUDES*************************************/

/******************************MACRO DEFINITIONS*******************************/

/*******************************TYPE DEFINITIONS ******************************/
typedef enum _INPUT_PCA_PORTS
{
    EN_PCA_PORT_1,
    EN_PCA_PORT_2,
}PCA_PORTS;

typedef enum _PCA_PORT_PINS
{
    EN_PCA_PIN_1 = 0,
    EN_PCA_PIN_2,
    EN_PCA_PIN_3,
    EN_PCA_PIN_4,
    EN_PCA_PIN_5,
    EN_PCA_PIN_6,
    EN_PCA_PIN_7,
    EN_PCA_PIN_8,
}PCA_PORT_PINS;

typedef struct _HwReq
{
    int devAddr;
    int (*i2cWriterFunc)(int devAddr, const unsigned char* buff, int bufLeng);
    int (*i2cReadFunc)  (int devAddr, const unsigned char* buff, int bufLeng);
}HwReq;
/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/
int drvPCASetInput(const HwReq* hw, PCA_PORTS port, char mask);

int drvPCASetOutput(const HwReq* hw, PCA_PORTS port, char mask);

int drvPCAWritePort(const HwReq* hw, PCA_PORTS port, char val);

#endif /* __DRV_PCA9535X_H__ */
/********************************* End Of File ********************************/
