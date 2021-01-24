/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : DrvPca9535x.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/

/********************************* INCLUDES ***********************************/
#include "DrvPca9535x.h"
/****************************** MACRO DEFINITIONS *****************************/
#define COMMAND_INPUT_P1        (0)
#define COMMAND_INPUT_P2        (1)
#define COMMAND_OUTPUT_P1       (2)
#define COMMAND_OUTPUT_P2       (3)
#define COMMAND_POLARIITY_P1    (4)
#define COMMAND_POLARIITY_P2    (5)
#define COMMAND_CONFIG_P1       (6)
#define COMMAND_CONFIG_P2       (7)
/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/

/***************************** STATIC FUNCTIONS  ******************************/

/***************************** PUBLIC FUNCTIONS  ******************************/
int drvPCASetInput (const HwReq* hw, PCA_PORTS port, char mask)
{
    unsigned char confBuff[2];

    confBuff[0] = (port == EN_PCA_PORT_1) ? COMMAND_CONFIG_P1 : COMMAND_CONFIG_P2;
    confBuff[1] = mask;

    return hw->i2cWriterFunc(hw->devAddr, confBuff, 2);
}

int drvPCASetOutput(const HwReq* hw, PCA_PORTS port, char mask)
{
    unsigned char confBuff[2];

    confBuff[0] = (port == EN_PCA_PORT_1) ? COMMAND_CONFIG_P1 : COMMAND_CONFIG_P2;
    confBuff[1] = mask;

    return hw->i2cWriterFunc(hw->devAddr, confBuff, 2);
}

int drvPCAWritePort(const HwReq* hw, PCA_PORTS port, char val)
{
    unsigned char confBuff[2];

    confBuff[0] = (port == EN_PCA_PORT_1) ? COMMAND_OUTPUT_P1 : COMMAND_OUTPUT_P2;
    confBuff[1] = val;

    return hw->i2cWriterFunc(hw->devAddr, confBuff, 2);
}




/******************************** End Of File *********************************/
