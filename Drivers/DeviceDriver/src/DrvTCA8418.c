/******************************************************************************
* #Author       : Zafer Satilmis
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : DrvTCA8418.c 
*******************************************************************************/
/******************************************************************************
*
*
*******************************************************************************/

/********************************* INCLUDES ***********************************/
#include "DrvTCA8418.h"
#include "McuInterruptRegister.h"
/****************************** MACRO DEFINITIONS *****************************/
/* TCA8418 register map */
#define REG_CFG             (0x01)
#define REG_INT_STAT        (0x02)
#define REG_KEY_LCK_EC      (0x03)
#define REG_KEY_EVENT_A     (0x04)
#define REG_KEY_EVENT_B     (0x05)
#define REG_KEY_EVENT_C     (0x06)
#define REG_KEY_EVENT_D     (0x07)
#define REG_KEY_EVENT_E     (0x08)
#define REG_KEY_EVENT_F     (0x09)
#define REG_KEY_EVENT_G     (0x0A)
#define REG_KEY_EVENT_H     (0x0B)
#define REG_KEY_EVENT_I     (0x0C)
#define REG_KEY_EVENT_J     (0x0D)
#define REG_KP_LCK_TIMER    (0x0E)
#define REG_UNLOCK1         (0x0F)
#define REG_UNLOCK2         (0x10)
#define REG_GPIO_INT_STAT1  (0x11)
#define REG_GPIO_INT_STAT2  (0x12)
#define REG_GPIO_INT_STAT3  (0x13)
#define REG_GPIO_DAT_STAT1  (0x14)
#define REG_GPIO_DAT_STAT2  (0x15)
#define REG_GPIO_DAT_STAT3  (0x16)
#define REG_GPIO_DAT_OUT1   (0x17)
#define REG_GPIO_DAT_OUT2   (0x18)
#define REG_GPIO_DAT_OUT3   (0x19)
#define REG_GPIO_INT_EN1    (0x1A)
#define REG_GPIO_INT_EN2    (0x1B)
#define REG_GPIO_INT_EN3    (0x1C)
#define REG_KP_GPIO1        (0x1D)
#define REG_KP_GPIO2        (0x1E)
#define REG_KP_GPIO3        (0x1F)
#define REG_GPI_EM1         (0x20)
#define REG_GPI_EM2         (0x21)
#define REG_GPI_EM3         (0x22)
#define REG_GPIO_DIR1       (0x23)
#define REG_GPIO_DIR2       (0x24)
#define REG_GPIO_DIR3       (0x25)
#define REG_GPIO_INT_LVL1   (0x26)
#define REG_GPIO_INT_LVL2   (0x27)
#define REG_GPIO_INT_LVL3   (0x28)
#define REG_DEBOUNCE_DIS1   (0x29)
#define REG_DEBOUNCE_DIS2   (0x2A)
#define REG_DEBOUNCE_DIS3   (0x2B)
#define REG_GPIO_PULL1      (0x2C)
#define REG_GPIO_PULL2      (0x2D)
#define REG_GPIO_PULL3      (0x2E)


/* TCA8418 bit definitions */
#define CFG_AI              0x80
#define CFG_GPI_E_CFG       0x40
#define CFG_OVR_FLOW_M      0x20
#define CFG_INT_CFG         0x10
#define CFG_OVR_FLOW_IEN    0x08
#define CFG_K_LCK_IEN       0x04
#define CFG_GPI_IEN         0x02
#define CFG_KE_IEN          0x01

#define INT_STAT_CAD_INT 0x10
#define INT_STAT_OVR_FLOW_INT 0x08
#define INT_STAT_K_LCK_INT 0x04
#define INT_STAT_GPI_INT 0x02
#define INT_STAT_K_INT 0x01

/* TCA8418 register masks */
#define KEY_LCK_EC_KEC 0x7
#define KEY_EVENT_CODE 0x7f
#define KEY_EVENT_VALUE 0x80

/* TCA8418 Rows and Columns */
#define ROW0 (0x01)
#define ROW1 (0x02)
#define ROW2 (0x04)
#define ROW3 (0x08)
#define ROW4 (0x10)
#define ROW5 (0x20)
#define ROW6 (0x40)
#define ROW7 (0x80)

#define COL0 (0x0001)
#define COL1 (0x0002)
#define COL2 (0x0004)
#define COL3 (0x0008)
#define COL4 (0x0010)
#define COL5 (0x0020)
#define COL6 (0x0040)
#define COL7 (0x0080)
#define COL8 (0x0100)
#define COL9 (0x0200)

/*************************** FUNCTION PROTOTYPES ******************************/

/******************************* TYPE DEFINITIONS *****************************/

/********************************** VARIABLES *********************************/
static VUICallback cbListener;
static HwI2C gHwI2c;
/***************************** STATIC FUNCTIONS  ******************************/
static void cbGpioExtInt(int pin)
{
    U8 reg;
    U32 keyInfo; //7.bit key event, press or release

    if (0 == gHwI2c.devAddr) //0 address is not correct, not initialized hwI2c
    {
        return;
    }

    if (SUCCESS == gHwI2c.read(TCA8418_I2C_ADDR, REG_INT_STAT, &reg, sizeof(U8))) //read int register
    {
        if (reg & INT_STAT_K_INT) //check keypad interrupt
        {
            if (SUCCESS == gHwI2c.read(TCA8418_I2C_ADDR, REG_KEY_EVENT_A, &reg, sizeof(U8))) //read new key
            {
                if (NULL != cbListener)
                {
                    /* convert key value to enum KEY */
                    keyInfo = reg & 0x80; //get key event(press or release)
                    reg = reg & 0x7F; //clear event bit
                    keyInfo |= ((reg % 10) + ((reg / 10)*4)); //find key value from 4x4 table

                    cbListener(keyInfo);
                }
            }
        }

        reg = 0XFF;
        gHwI2c.write(TCA8418_I2C_ADDR, REG_INT_STAT, &reg, sizeof(U8)); //clear interrupt flag
    }
    else
    {
        drvTca8418FlushFifo();
    }
}
/***************************** PUBLIC FUNCTIONS  ******************************/
RETURN_STATUS drvTca8418Init(const HwI2C *hwI2c)
{
    RETURN_STATUS retVal = FAILURE;
    U8 reg;

    if (IS_SAFELY_PTR(hwI2c))
    {
        gHwI2c = *hwI2c;

        //check connecting, read any readable register, REG_KEY_LCK_EC
        if (SUCCESS == gHwI2c.read(TCA8418_I2C_ADDR, REG_KEY_LCK_EC, &reg, sizeof(U8)))
        {
            retVal = drvIntRegister(cbGpioExtInt, GPIO_KEYPAD_CHNL); //listen interrupt
            drvTca8418FlushFifo();
        }

        cbListener = NULL;
    }

    return retVal;
}

RETURN_STATUS drvSetKeypad(U32 rowNumber, U32 colNumber)
{
    RETURN_STATUS retVal = SUCCESS;;
    U32 regVal;
    U8  temp;

    if ((rowNumber > TCA8418_MAX_ROWS) || (colNumber > TCA8418_MAX_COLS))
    {
        return FAILURE;
    }

    if (0 == gHwI2c.devAddr) //0 address is not correct, not initialized hwI2c
    {
        return FAILURE;
    }

    regVal  =  ~(~0 << rowNumber);
    regVal += (~(~0 << colNumber)) << 8;

    /************* Write keypad registers */
    temp   = (U8)(regVal);
    retVal = gHwI2c.write(TCA8418_I2C_ADDR, REG_KP_GPIO1, &temp, sizeof(U8));

    temp    = (U8)(regVal >> 8);
    retVal |= gHwI2c.write(TCA8418_I2C_ADDR, REG_KP_GPIO2, &temp, sizeof(U8));

    temp    = (U8)(regVal >> 16);
    retVal |= gHwI2c.write(TCA8418_I2C_ADDR, REG_KP_GPIO3, &temp, sizeof(U8));

    /************* Write debounce registers */
    temp    = (U8)(regVal);
    retVal |= gHwI2c.write(TCA8418_I2C_ADDR, REG_DEBOUNCE_DIS1, &temp, sizeof(U8));

    temp    = (U8)(regVal >> 8);
    retVal |= gHwI2c.write(TCA8418_I2C_ADDR, REG_DEBOUNCE_DIS2, &temp, sizeof(U8));

    temp    = (U8)(regVal >> 16);
    retVal |= gHwI2c.write(TCA8418_I2C_ADDR, REG_DEBOUNCE_DIS3, &temp, sizeof(U8));

    /************* Write conf register */
    temp    = (/*CFG_INT_CFG | CFG_OVR_FLOW_IEN | */CFG_KE_IEN); // CFG_KE_IEN => keypad interrupt enable value
    retVal |= gHwI2c.write(TCA8418_I2C_ADDR, REG_CFG, &temp, sizeof(U8));

    return retVal;
}

RETURN_STATUS drvSetGpio(PIN_MODE pm, PINS pin)
{
    return SUCCESS;
}

void drvTca8418CbListener(VUICallback cb, BOOL stat)
{
    cbListener = cb;
}

RETURN_STATUS drvTca8418FlushFifo(void)
{
    RETURN_STATUS retVal = FAILURE;
    U32 i;
    U8 reg;

    if (0 != gHwI2c.devAddr) //0 address is not correct, not initialized hwI2c
    {
        for (i = 0; i < 10; ++i) //max buffer number 10
        {
            retVal = gHwI2c.read(TCA8418_I2C_ADDR, REG_KEY_EVENT_A, &reg, sizeof(U8));
            if ((FAILURE == retVal) || (0 == reg))//reg = 0 =>no data found, end of register
            {
                break;
            }
        }

        reg = 0XFF;
        retVal |= gHwI2c.write(TCA8418_I2C_ADDR, REG_INT_STAT, &reg, sizeof(U8)); //clear interrupt flag
    }

    return retVal;
}

/******************************** End Of File *********************************/
