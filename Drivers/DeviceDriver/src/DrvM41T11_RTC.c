/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : DrvM4T11_RTC.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/

/********************************* INCLUDES ***********************************/
#include "DrvM41T11_RTC.h"
/****************************** MACRO DEFINITIONS *****************************/
#define RTC_SEC_ADDR       (0x00)
#define RTC_MIN_ADDR       (0x01)
#define RTC_HOUR_ADDR      (0x02)
#define RTC_DAY_ADDR       (0x03)
#define RTC_DATE_ADDR      (0x04)
#define RTC_MONTH_ADDR     (0x05)
#define RTC_YEARS_ADDR     (0x06)
#define RTC_REG_CNT        (7)
#define RTC_CONTROL_ADDR   (0x07)

#ifndef CONFIG_SYS_M41T11_EXT_CENTURY_DATA
#define REG_CNT                     (RTC_REG_CNT+1)
#define CONFIG_SYS_M41T11_BASE_YEAR (2000)
#else
/* we will store extra year info in byte 9*/
#define M41T11_YEAR_DATA   0x8
#define M41T11_YEAR_SIZE   1
#define REG_CNT            (RTC_REG_CNT+1+M41T11_YEAR_SIZE)
#endif

#define I2C_CONN_TIMEOUT    (100
/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static M4T11_I2C gHwI2c;
/***************************** STATIC FUNCTIONS  ******************************/
static U8 bcd2bin (U8 bcd)
{
    return ((((bcd >> 4) & 0x0F) * 10) + (bcd & 0x0F));
}

static U8 bin2bcd (U8 bin)
{
    return (((bin / 10) << 4) | (bin % 10));
}
/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS drvM41T11Init(const M4T11_I2C *i2c)
{
    RETURN_STATUS retVal = FAILURE;

    if (IS_SAFELY_PTR(i2c))
    {
        gHwI2c = *i2c;
        retVal = SUCCESS;
    }
    return retVal;
}
/**
 * @brief  get time
 * @param  M4T11_RTC_STR pointer
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvM41T11GetTime(M4T11_RTC_STR *getTime)
{
    RETURN_STATUS retVal = FAILURE;
    U8 data[RTC_REG_CNT] = {0};

    if (0 != gHwI2c.devAddr)
    {
        if (IS_SAFELY_PTR(getTime))
        {
            if (SUCCESS == gHwI2c.read(gHwI2c.devAddr, RTC_SEC_ADDR, (U8 *)data, RTC_REG_CNT))
            {
                //if 7.bit(ST bit) is 1 RTC, clock not working !!
                if (FALSE == (data[RTC_SEC_ADDR] & 0x80)) //
                {
                    getTime->sec  = bcd2bin (data[RTC_SEC_ADDR]  & 0x7F); //0x7F -> just data bits(for details check datasheet)
                    getTime->min  = bcd2bin (data[RTC_MIN_ADDR]  & 0x7F); //0x7F -> just data bits(for details check datasheet)
                    getTime->hour = bcd2bin (data[RTC_HOUR_ADDR] & 0x3F); //0x3F -> just data bits(for details check datasheet)
                    getTime->wday = bcd2bin (data[RTC_DAY_ADDR]  & 0x07); //0x07 -> just data bits(for details check datasheet)
                    getTime->mday = bcd2bin (data[RTC_DATE_ADDR] & 0x3F); //0x3F -> just data bits(for details check datasheet)
                    getTime->mon  = bcd2bin (data[RTC_MONTH_ADDR]& 0x1F); //0x1F -> just data bits(for details check datasheet)

                    //check CB bit. if it is 1 load 100 year. Because our system using CEB bit. For more details check datasheet
                    getTime->year = CONFIG_SYS_M41T11_BASE_YEAR + bcd2bin(data[RTC_YEARS_ADDR]) + ((data[RTC_HOUR_ADDR] & 0x40) ? 100 : 0);

                    retVal = SUCCESS;
                }
            }
        }
    }

    return retVal;
}

/**
 * @brief  set time
 * @param  M4T11_RTC_STR pointer
 * @return if everything is OK, return SUCCES
 *         otherwise return FAILURE
 */
RETURN_STATUS drvM41T11SetTime(const M4T11_RTC_STR *setTime)
{
    RETURN_STATUS retVal = FAILURE;
    U8 data[RTC_REG_CNT] = {0};

    if (0 != gHwI2c.devAddr)
    {
        if (IS_SAFELY_PTR(setTime))
        {
            //check time values
            if (((setTime->year - CONFIG_SYS_M41T11_BASE_YEAR) < 200) && (setTime->year >= CONFIG_SYS_M41T11_BASE_YEAR) && \
                 (setTime->sec < 60) && (setTime->min < 60) && (setTime->hour < 24) && (setTime->mday < 32) && \
                 (setTime->mon < 13) && (setTime->wday < 8))
            {
                data[RTC_SEC_ADDR]   = bin2bcd(setTime->sec)  & 0x7F; //0x7F -> just data bits(for details check datasheet)
                data[RTC_MIN_ADDR]   = bin2bcd(setTime->min);
                data[RTC_HOUR_ADDR]  = bin2bcd(setTime->hour) & 0x3F; //0x3F -> just data bits(for details check datasheet)
                data[RTC_DATE_ADDR]  = bin2bcd(setTime->mday);
                data[RTC_MONTH_ADDR] = bin2bcd(setTime->mon);
                data[RTC_DAY_ADDR]   = bin2bcd(setTime->wday);
                data[RTC_YEARS_ADDR] = bin2bcd(setTime->year % 100);

                data[RTC_HOUR_ADDR] |= 0x80;  //set century enable bit, with this bit, we can see after 2099 :))

                //dont need to use below line. because related bit(B6) already is 0.
                //data[RTC_HOUR_ADDR] &= (~(0x40)); // set CB bit. if it will be toggled 0 to 1, welcome 3000(2099 finished) :))
                retVal = gHwI2c.write(gHwI2c.devAddr, RTC_SEC_ADDR, (U8 *)data, RTC_REG_CNT);
            }
        }
    }

    return retVal;
}
/******************************** End Of File *********************************/
