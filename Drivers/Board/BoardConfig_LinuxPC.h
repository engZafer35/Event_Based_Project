/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : BoardConfig_LinuxPC.h
* #File Path    : /Driver/Board/BoardConfig_LinuxPC.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __BOARDCONFIG_LINUXPC_H__
#define __BOARDCONFIG_LINUXPC_H__

/*********************************INCLUDES*************************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/
#define BOARD_NAME            "EBP_QT_010101"
#define BOARD_VERSION         "V1.0"
#define BOARD_FILE_NAME       "BoardConfig_LinuxPC.h"
#define WORKING_PLATFORM_PC   (202007)
#define _WORKING_PLATFORM     WORKING_PLATFORM_PC
#define _PLATFORM_NAME        "LINUX-QT"
#define _MCU_BIT_SIZE         (64)
#define MCU_CORE              "Linux-PC"
#define MCU_PART_NUM          "Linux-PC"

/******************************MACRO DEFINITIONS*******************************/
typedef enum _DRV_RET
{
    EN_DRV_RET_OK,
    EN_DRV_RET_ERROR,
    EN_DRV_RET_BUSY,
    EN_DRV_RET_TIMEOUT
}DRV_RET;
typedef DRV_RET _DRV_RET_TYPE;
#define _DRV_RET_OK         (EN_DRV_RET_OK)
#define _DRV_RET_ERROR      (EN_DRV_RET_ERROR)
#define _DRV_RET_BUSY       (EN_DRV_RET_BUSY)
#define _DRV_RET_TIMEOUT    (EN_DRV_RET_TIMEOUT)

#define _EXT_MEMORY_TYPE_FRAM    (1)
#define _EXT_MEMORY_TYPE_EEPROM  (2)

#define _EXT_MEMORY_1_SIZE       (8000)  // kbyte   (best size 256kbyte)
#define _EXT_MEMORY_2_SIZE       (32000) // kbyte   (best size 256kbyte)
#define _EXT_MEMORY_1_I2C_ADDR   (0XAE)  // fram
#define _EXT_MEMORY_2_I2C_ADDR   (0XAC)  // eeprom

/** @brief select ext memory type. conf, error, reset value will record in this memory */
#define _EXT_MEMORY_1_TYPE  (_EXT_MEMORY_TYPE_FRAM) // _EXT_MEMORY_TYPE_EEPROM
/** @brief select ext memory type. current and volt value will record in this memory */
#define _EXT_MEMORY_2_TYPE  (_EXT_MEMORY_TYPE_EEPROM) //(_EXT_MEMORY_TYPE_FRAM)

// Warning if EEPROM memory is using, eeprom page size must be defined
#if (_EXT_MEMORY_1_TYPE == _EXT_MEMORY_TYPE_EEPROM) || (_EXT_MEMORY_2_TYPE == _EXT_MEMORY_TYPE_EEPROM)
 #define _EEPROM_PAGE_SIZE_BYTE   (64)
#endif

enum _EXT_MEMORY_NUM
{
    EN_EXT_MEM_NUM_1,
    EN_EXT_MEM_NUM_2,

    EN_EXT_MEM_MAX_NUM
};

/* -------- MCU_CORE_STM32F Interrupt List --------*/
/*
 * You can comment unused interrupt. But don't move position of EN_INTERRUPT_LIST_MAX_NUM
 * It must be on end of list.
 */
typedef enum _EN_INTERRUPT_LIST
{
//    EN_WWDG_IRQ,
//    EN_PVD_IRQ,
//    EN_TAMP_STAMP_IRQ,
//    EN_RTC_WKUP_IRQ,
//    EN_FLASH_IRQ,
//    EN_RCC_IRQ,
    EN_EXTI0_IRQ,
//    EN_EXTI1_IRQ,
//    EN_EXTI2_IRQ,
//    EN_EXTI3_IRQ,
    EN_EXTI4_IRQ,
//    EN_DMA1_Stream0_IRQ,
//    EN_DMA1_Stream1_IRQ,
//    EN_DMA1_Stream2_IRQ,
//    EN_DMA1_Stream3_IRQ,
//    EN_DMA1_Stream4_IRQ,
//    EN_DMA1_Stream5_IRQ,
//    EN_DMA1_Stream6_IRQ,
//    EN_ADC_IRQ,
//    EN_CAN1_TX_IRQ,
    EN_CAN1_RX0_IRQ,
//    EN_CAN1_RX1_IRQ,
    EN_CAN1_SCE_IRQ,
//    EN_EXTI9_5_IRQ,
//    EN_TIM1_BRK_TIM9_IRQ,
    EN_TIM1_UP_TIM10_IRQ,
//    EN_TIM1_TRG_COM_TIM11_IRQ,
//    EN_TIM1_CC_IRQ,
    EN_TIM2_IRQ,
//    EN_TIM3_IRQ,
//    EN_TIM4_IRQ,
//    EN_I2C1_EV_IRQ,
//    EN_I2C1_ER_IRQ,
//    EN_I2C2_EV_IRQ,
//    EN_I2C2_ER_IRQ,
//    EN_SPI1_IRQ,
//    EN_SPI2_IRQ,
    EN_USART1_IRQ,
    EN_USART2_IRQ,
    EN_USART3_IRQ,
    EN_EXTI15_10_IRQ,
//    EN_RTC_Alarm_IRQ,
//    EN_OTG_FS_WKUP_IRQ,
//    EN_TIM8_BRK_TIM12_IRQ,
//    EN_TIM8_UP_TIM13_IRQ,
//    EN_TIM8_TRG_COM_TIM14_IRQ,
//    EN_TIM8_CC_IRQ,
//    EN_DMA1_Stream7_IRQ,
//    EN_FMC_IRQ,
//    EN_SDIO_IRQ,
//    EN_TIM5_IRQ,
//    EN_SPI3_IRQ,
//    EN_UART4_IRQ,
//    EN_UART5_IRQ,
    EN_TIM6_DAC_IRQ,
    EN_TIM7_IRQ,
//    EN_DMA2_Stream0_IRQ,
//    EN_DMA2_Stream1_IRQ,
//    EN_DMA2_Stream2_IRQ,
//    EN_DMA2_Stream3_IRQ,
//    EN_DMA2_Stream4_IRQ,
//    EN_CAN2_TX_IRQ,
    EN_CAN2_RX0_IRQ,
    EN_CAN2_RX1_IRQ,
//    EN_CAN2_SCE_IRQ,
//    EN_OTG_FS_IRQ,
//    EN_DMA2_Stream5_IRQ,
//    EN_DMA2_Stream6_IRQ,
//    EN_DMA2_Stream7_IRQ,
//    EN_USART6_IRQ,
//    EN_I2C3_EV_IRQ,
//    EN_I2C3_ER_IRQ,
//    EN_OTG_HS_EP1_OUT_IRQ,
//    EN_OTG_HS_EP1_IN_IRQ,
//    EN_OTG_HS_WKUP_IRQ,
//    EN_OTG_HS_IRQ,
//    EN_DCMI_IRQ,
//    EN_FPU_IRQ,
//    EN_SPI4_IRQ,
//    EN_SAI1_IRQ,
//    EN_SAI2_IRQ,
//    EN_QUADSPI_IRQ,
//    EN_CEC_IRQ,
//    EN_SPDIF_RX_IRQ,
//    EN_I2C4_Event_IRQ,
//    EN_I2C4_Error_IRQ,

    EN_INTERRUPT_LIST_MAX_NUM, // dont move this line
}_EN_INTERRUPT_LIST;


typedef void (*InterruptCallback)(_EN_INTERRUPT_LIST intList);

/********************* BOARD MCU CLOCK CONTROL **************/
#define _MCU_CORE_INIT()
#define _CONF_MCU_CLOCK()
#include <unistd.h>
#define _DELAY_MS(x)    usleep(x*1000)

/********************* BOARD GPIO CONTROL ******************/
#define _GPIO_INIT()

#define _WRITE_GPIO(port, pin, status)  hwWriteGpio(port, pin, status)
#define _GPIO_TOGGLE(port, pin)         hwToggleGpio(port, pin)
#define _GPIO_READ(port, pin)           hwReadGpio(port, pin)

#define _LED_1(x)                       _WRITE_GPIO(1, 24, x)
#define _LED_2(x)                       _WRITE_GPIO(1, 25, x)
#define _LED_3(x)                       _WRITE_GPIO(1, 26, x)

#define _TOGGLE_LED_1()                 _GPIO_TOGGLE(1, 24)
#define _TOGGLE_LED_2()                 _GPIO_TOGGLE(1, 26)
#define _TOGGLE_LED_3()                 _GPIO_TOGGLE(1, 26)

#define _VOUT_2_CTRL(x)                 _WRITE_GPIO(1, 1, x)
#define _VOUT_1_CTRL(x)                 _WRITE_GPIO(1, 1, x)
#define _VOLT_3V3_CTRL_1(x)             _WRITE_GPIO(1, 1, x)
#define _VOLT_3V3_CTRL_2(x)             _WRITE_GPIO(1, 1, x)

#define _LIN_EN(x)                      _WRITE_GPIO(1, 1, x) //Lin
#define _LIN_WAKE(x)                    _WRITE_GPIO(1, 1, x) //Lin wake
#define _KLO_EN(x)                      _WRITE_GPIO(1, 1, x) // K Line

#define _BUZZER()                       _WRITE_GPIO(1, 1, x)
#define _RESET_DISP()                   _WRITE_GPIO(1, 1, x)

#define _GPIO_EXT_INT_ID                EN_EXTI4_IRQ
#define _GPIO5_9_EXT_INT_ID             EN_EXTI9_5_IRQ


#define _CORE_EXT_IT_FUNCTION      		void hwGpioExtInt(int pin) // pin4 external interrupt

/********************* BOARD I2C CONTROL ******************/
#define _I2C_LINE_1
#define _I2C_LINE_3

#define _OUTPUT_EXP_1_DEV_ADDR                                      (0x42)
#define _OUTPUT_EXP_2_DEV_ADDR                                      (0x40)

#define _I2C1_INIT()
#define _I2C2_INIT()

#define _I2C_IS_DEVICE_READY(line, deviceAdr, try, timeout)         (EN_DRV_RET_OK)

#define _I2C_WRITE(line, deviceAdr, buff, leng)                     (EN_DRV_RET_OK)

#define _I2C_READ(line, deviceAdr, buff, leng)                      (EN_DRV_RET_OK)
/** output expander 1*/
#define _I2C_WRITE_OUTPUT_EXP_1(buff, leng)                         (EN_DRV_RET_OK)
#define _I2C_READ_OUTPUT_EXP_1( buff, leng)                         (EN_DRV_RET_OK)
/** output expander 2*/
#define _I2C_WRITE_OUTPUT_EXP_2(buff, leng)                         (EN_DRV_RET_OK)
#define _I2C_READ_OUTPUT_EXP_2(buff, leng)                          (EN_DRV_RET_OK)

#define _I2C_EXT_MEMORY_WRITE(line, deviceAdr, addr, buff, leng)    (EN_DRV_RET_OK)
#define _I2C_EXT_MEMORY_READ(line, deviceAdr, addr, buff, leng)     (EN_DRV_RET_OK)

#define _I2C_EXT_MEMORY_1_IS_READY()                                _I2C_IS_DEVICE_READY(I2C_LINE_3, EXT_MEMORY_1_I2C_ADDR, 10, 500)
#define _I2C_EXT_MEMORY_1_WRITE(memAddr, buff, leng)                _I2C_EXT_MEMORY_WRITE(I2C_LINE_3, EXT_MEMORY_1_I2C_ADDR, memAddr, buff, leng)
#define _I2C_EXT_MEMORY_1_READ( memAddr, buff, leng)                _I2C_EXT_MEMORY_READ( I2C_LINE_3, EXT_MEMORY_1_I2C_ADDR, memAddr, buff, leng)

#define _I2C_EXT_MEMORY_2_IS_READY()                                _I2C_IS_DEVICE_READY(I2C_LINE_3, EXT_MEMORY_2_I2C_ADDR, 10, 500)
#define _I2C_EXT_MEMORY_2_WRITE(memAddr, buff, leng)                _I2C_EXT_MEMORY_WRITE(I2C_LINE_3, EXT_MEMORY_2_I2C_ADDR, memAddr, buff, leng)
#define _I2C_EXT_MEMORY_2_READ( memAddr, buff, leng)                _I2C_EXT_MEMORY_READ( I2C_LINE_3, EXT_MEMORY_2_I2C_ADDR, memAddr, buff, leng)

/********************* BOARD SPI CONTROL ******************/
#define _SPI_INIT()

/********************* BOARD WDT CONTROL ******************/
#define _WDT_INIT(x)    (EN_DRV_RET_OK)
#define _WDT_FEED()
#define _WDT_START()

/********************* BOARD UART CONTROL ******************/
#define _UART_DEBUG_INIT()
#define _UART_LIN_INIT()
#define _UART_K_LINE_INIT()
#define _UART_REVERSE()

#define _UART_DEBUG_LINE                            ((void*)0)
#define _UART_COMM_LINE                             ((void*)0)

#define _LINE_DBG_RX_IT_ID                          (EN_USART1_IRQ)
#define _LINE_COMM_RX_IT_ID                         (EN_USART2_IRQ)

#define _IS_DBG_UART_IT()                           (1)
#define _IS_COMM_UART_IT()                          (1)

#define _UART_RCV_IT_FUNCTION                       void uartTI(void)

#define _UART_RX_IT_ENABLE(line)
#define _UART_SEND(line, buff, leng, timeout)       (EN_DRV_RET_OK)
#define _UART_RCV_IT(line, pBuff, leng)             (EN_DRV_RET_OK)
#define _UART_CLR_IT_FLAG(line, flag)

#define _UART_DBG_RX_IT_ENABLE()                    _UART_RX_IT_ENABLE(0)
#define _UART_DBG_RCV_IT(pBuff, leng)               _UART_RCV_IT(0, pBuff, leng)
#define _UART_DBG_SEND(buff, leng, timeout)         (EN_DRV_RET_OK)
#define _UART_DBG_CLR_RCV_IT()

#define _UART_LIN_RX_IT_ENABLE()                    _UART_RX_IT_ENABLE(1)
#define _UART_LIN_RCV_IT(pBuff, leng)               _UART_RCV_IT(1, pBuff, leng)
#define _UART_LIN_SEND(buff, leng, timeout)         (EN_DRV_RET_OK)
#define _UART_LIN_CLR_RCV_IT()

#define _UART_K_LINE_RX_IT_ENABLE()                 _UART_RX_IT_ENABLE(0)
#define _UART_K_LINE_RCV_IT(pBuff, leng)            _UART_RCV_IT(0, pBuff, leng)
#define _UART_K_LINE_SEND(buff, leng, timeout)      (EN_DRV_RET_OK)
#define _UART_K_LINE_CLR_RCV_IT()

//#define _UART_RESERVE_RX_IT_ENABLE()                _UART_RX_IT_ENABLE(1)
//#define _UART_RESERVE_RCV_IT(pBuff, leng)           _UART_RCV_IT(1, pBuff, leng)
//#define _UART_RESERVE_SEND(buff, leng, timeout)     (EN_DRV_RET_OK)
//#define _UART_RESERVE_CLR_RCV_IT()

/***************** BOARD INTERNAL RTC CONTROL **************/
typedef struct _L_RTC_TimeTypeDef
{
    unsigned char Seconds;
    unsigned char Minutes;
    unsigned char Hours;
    unsigned int DayLightSaving;
    unsigned int StoreOperation;
#define RTC_DAYLIGHTSAVING_NONE  (0)
#define RTC_STOREOPERATION_RESET (0)

}L_RTC_TimeTypeDef;

typedef struct _L_RTC_DateTypeDef
{
    unsigned char WeekDay;
    unsigned char Month;
    unsigned char Date;
    unsigned char Year;
}L_RTC_DateTypeDef;

typedef  L_RTC_TimeTypeDef   _INT_RTC_TIME_STR;
typedef  L_RTC_DateTypeDef   _INT_RTC_DATE_STR;
#define _RTC_ALARM_IT_ID                 (EN_RTC_Alarm_IRQ)
#define _INIT_INTERNAL_RTC()
#define _RTC_ALARM_IT_FUNCTION           void rtcFoo(void)

#define _INT_RTC_WRITE_TIME(timeStr)    (EN_DRV_RET_OK)
#define _INT_RTC_WRITE_DATE(dateStr)    (EN_DRV_RET_OK)

#define _INT_RTC_READ_TIME(timefStr)    (EN_DRV_RET_OK)
#define _INT_RTC_READ_DATE(dateStr)     (EN_DRV_RET_OK)

/********************* BOARD ADC CONTROL ******************/
#define _ADC_BOARD_MEASURE_BUS_INIT()           (EN_DRV_RET_OK)
#define _ADC_BOARD_VOLTAGE_MEASURE_BUS_INIT()   (EN_DRV_RET_OK)

#define _ADC_CHNL_BOARD_CURR_INIT()             (EN_DRV_RET_OK)
#define _ADC_CHNL_EXT_CURR_IN1_INIT()           (EN_DRV_RET_OK)
#define _ADC_CHNL_VINOP()                       (EN_DRV_RET_OK)
#define _ADC_CHNL_V14V()                        (EN_DRV_RET_OK)
#define _ADC_CHNL_V3V3()                        (EN_DRV_RET_OK)

#define _ACD_READ(bus, chnl)                    (0xAA) //no matter

#define _ADC_READ_BORD_CURR()                   _ACD_READ(1, 12)
#define _ADC_READ_EXT_CURR_IN1()                _ACD_READ(1, 13)
#define _ADC_READ_VINOP()                       _ACD_READ(3, 5)
#define _ADC_READ_V14V()                        _ACD_READ(3, 6)
#define _ADC_READ_V3V3()                        _ACD_READ(3, 7)

/********************* BOARD TIMER CONTROL ******************/
#define _TIMER_ALERT_IT_ID              (EN_TIM6_DAC_IRQ)
#define _TIMER_EVENT_IT_ID              (EN_TIM7_IRQ)

#define _TIMER_ALERT_INIT()
#define _TIMER_EVENT_INIT()

#define _CORE_TIMER_IT_FUNCTION         void foo(void)

#define _TIMER_ALERT_START()            (EN_DRV_RET_OK)
#define _TIMER_EVENT_START()            (EN_DRV_RET_OK)

#define _IS_ALERT_TIMER_IT()            (1)
#define _IS_EVENT_TIMER_IT()            (1)

/********************* BOARD CAN CONTROL ******************/
//typedef struct __CAN_HandleTypeDef
//{
//
//}CAN_HandleTypeDef;
//typedef struct
//{
//
//} CAN_TxHeaderTypeDef;
//typedef struct
//{
//} CAN_RxHeaderTypeDef;
//typedef struct
//{
//} CAN_FilterTypeDef;
#define CAN_RX_FIFO0                (0x00000000U)  /*!< CAN receive FIFO 0 */
#define CAN_RX_FIFO1                (0x00000001U)  /*!< CAN receive FIFO 1 */

#define _CAN1_INIT()
#define _CAN2_INIT()

typedef struct
{
    int StdId;
    int ExtId;
    int IDE;
    int RTR;
    int DLC;
    int TransmitGlobalTime;

}Fake_Can_Hader;

typedef Fake_Can_Hader              _HAL_CAN_TX_HEADER;
#define _CAN_LINE1                  ((void*)0)
#define _CAN_LINE2                  ((void*)0)

#define _CORE_CAN_2_IT_FUNC         void canIT(void)

#define _HAL_CAN_START(v1)                       (EN_DRV_RET_OK)
#define _HAL_CAN_1_START()                       _HAL_CAN_START(&_CAN_LINE1)
#define _HAL_CAN_2_START()                       _HAL_CAN_START(&_CAN_LINE2)


#define _HAL_CAN_ADD_TX_MESSAGE(v1, v2, v3, v4)  (EN_DRV_RET_OK)
#define _HAL_CAN_GET_TXMAILBOXES_FREE_LEVEL(v1)  (EN_DRV_RET_OK)
#define _HAL_CAN_GET_RX_MESSAGE(v1, v2, v3, v4)  (EN_DRV_RET_OK)

/********************* BOARD FMC CONTROL ******************/
#define _READ_PCA(devNum) hwReadPCA(devNum)

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

#endif /* __BOARDCONFIG_LINUXPC_H__ */

/********************************* End Of File ********************************/
