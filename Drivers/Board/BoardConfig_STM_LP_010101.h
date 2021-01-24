/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : BoardConfig_STM_LP_010101.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __BOARD_CONFIG_STM_010101_H__
#define __BOARD_CONFIG_STM_010101_H__
/*********************************INCLUDES*************************************/
#include "main.h"
#include "stm32l4xx_hal_def.h"
#include "stm32l4xx_hal.h"
#include "DriverCoreIWDT.h"
#include "DriverSTM32_ADC.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#define BOARD_NAME            "EBP_STM_LP_010101"
#define BOARD_VERSION         "V1.0"
#define BOARD_FILE_NAME       "BoardConfig_STM_LP_010101.h"
#define WORKING_PLATFORM_STM  (111020)
#define _WORKING_PLATFORM     WORKING_PLATFORM_STM
#define _PLATFORM_NAME        "STM"
#define _MCU_BIT_SIZE         (32)
#define MCU_CORE              "CORTEX-M4"
#define MCU_PART_NUM          "STM32L476RGTX-64-LQFP"
/******************************MACRO DEFINITIONS*******************************/
typedef HAL_StatusTypeDef   _DRV_RET_TYPE;
#define _DRV_RET_OK         (HAL_OK)
#define _DRV_RET_ERROR      (HAL_ERROR)
#define _DRV_RET_BUSY       (HAL_BUSY)
#define _DRV_RET_TIMEOUT    (HAL_TIMEOUT)

/* -------- MCU_CORE_STM32F Interrupt List --------*/
/*
 * You can comment unused interrupt.
 */
typedef enum _EN_INTERRUPT_LIST
{
//  EN_WWDG_IRQ,
//  EN_PVD_PVM_IRQ,
//  EN_TAMP_STAMP_IRQ,
//  EN_RTC_WKUP_IRQ,
//  EN_FLASH_IRQ,
//  EN_RCC_IRQ,
	EN_EXTI0_IRQ,
	EN_EXTI1_IRQ,
	EN_EXTI2_IRQ,
//  EN_EXTI3_IRQ,
//  EN_EXTI4_IRQ,
//  EN_DMA1_Channel1_IRQ,
//  EN_DMA1_Channel2_IRQ,
//  EN_DMA1_Channel3_IRQ,
//  EN_DMA1_Channel4_IRQ,
//  EN_DMA1_Channel5_IRQ,
//  EN_DMA1_Channel6_IRQ,
//  EN_DMA1_Channel7_IRQ,
//  EN_ADC1_2_IRQ,
//  EN_CAN1_TX_IRQ,
	EN_CAN1_RX0_IRQ,
	EN_CAN1_RX1_IRQ,
//  EN_CAN1_SCE_IRQ,
//  EN_EXTI9_5_IRQ,
//  EN_TIM1_BRK_TIM15_IRQ,
//  EN_TIM1_UP_TIM16_IRQ,
//  EN_TIM1_TRG_COM_TIM17_IRQ,
//  EN_TIM1_CC_IRQ,
//  EN_TIM2_IRQ,
//  EN_TIM3_IRQ,
//  EN_TIM4_IRQ,
//  EN_I2C1_EV_IRQ,
//  EN_I2C1_ER_IRQ,
//  EN_I2C2_EV_IRQ,
//  EN_I2C2_ER_IRQ,
//  EN_SPI1_IRQ,
//  EN_SPI2_IRQ,
	EN_USART1_IRQ,
	EN_USART2_IRQ,
	EN_USART3_IRQ,
	EN_EXTI15_10_IRQ,
//  EN_RTC_Alarm_IRQ,
//  EN_DFSDM1_FLT3_IRQ,
//  EN_TIM8_BRK_IRQ,
//  EN_TIM8_UP_IRQ,
//  EN_TIM8_TRG_COM_IRQ,
//  EN_TIM8_CC_IRQ,
//  EN_ADC3_IRQ,
//  EN_FMC_IRQ,
//  EN_SDMMC1_IRQ,
//  EN_TIM5_IRQ,
//  EN_SPI3_IRQ,
//  EN_UART4_IRQ,
//  EN_UART5_IRQ,
	EN_TIM6_DAC_IRQ,
	EN_TIM7_IRQ,
//  EN_DMA2_Channel1_IRQ,
//  EN_DMA2_Channel2_IRQ,
//  EN_DMA2_Channel3_IRQ,
//  EN_DMA2_Channel4_IRQ,
//  EN_DMA2_Channel5_IRQ,
//  EN_DFSDM1_FLT0_IRQ,
//  EN_DFSDM1_FLT1_IRQ,
//  EN_DFSDM1_FLT2_IRQ,
//  EN_COMP_IRQ,
//  EN_LPTIM1_IRQ,
//  EN_LPTIM2_IRQ,
//  EN_OTG_FS_IRQ,
//  EN_DMA2_Channel6_IRQ,
//  EN_DMA2_Channel7_IRQ,
//  EN_LPUART1_IRQ,
//  EN_QUADSPI_IRQ,
//  EN_I2C3_EV_IRQ,
//  EN_I2C3_ER_IRQ,
//  EN_SAI1_IRQ,
//  EN_SAI2_IRQ,
//  EN_SWPMI1_IRQ,
//  EN_TSC_IRQ,
//  EN_LCD_IRQ,
//  EN_RNG_IRQ,
//  EN_FPU_IRQ,

  EN_INTERRUPT_LIST_MAX_NUM // dont move this line
} _EN_INTERRUPT_LIST;

#if (MAX_USING_INT > 2)
#error "You maight have unused interrupt ID. Please check MAX_USING_INT in BoardConfig_LinuxPC.h." \
       "Comment unused interrupt ID and set MAX_USING_INT"
#endif
typedef void (*InterruptCallback)(_EN_INTERRUPT_LIST intList);

/********************* BOARD MCU CLOCK CONTROL **************/
#define _MCU_CORE_INIT()                HAL_Init()
#define _CONF_MCU_CLOCK()               SystemClock_Config()

#define _DELAY_MS(x)                    HAL_Delay(x)

/********************* BOARD GPIO CONTROL ******************/
#define _GPIO_INIT()                    MX_GPIO_Init()

#define _WRITE_GPIO(port, pin, status)  HAL_GPIO_WritePin(port, pin, status)
#define _GPIO_TOGGLE(port, pin)         HAL_GPIO_TogglePin(port, pin)
#define _GPIO_READ(port, pin)           HAL_GPIO_ReadPin(port, pin)

#define _LED_1(x)                       _WRITE_GPIO(OUT_LED_PROC_GPIO_Port, OUT_LED_PROC_Pin, x)
#define _LED_2(x)                       _WRITE_GPIO(OUT_LED_PWR_GPIO_Port, OUT_LED_PWR_Pin, x)

#define _TOGGLE_LED_1()                  _GPIO_TOGGLE(OUT_LED_PROC_GPIO_Port, OUT_LED_PROC_Pin)
#define _TOGGLE_LED_2()                  _GPIO_TOGGLE(OUT_LED_PWR_GPIO_Port, OUT_LED_PWR_Pin)

#define _BUZZER(x)                      _WRITE_GPIO(OUT_BUZZER_GPIO_Port, OUT_BUZZER_Pin, x)
#define _BUZZER_TOGGLE()                _GPIO_TOGGLE(OUT_BUZZER_GPIO_Port, OUT_BUZZER_Pin)

#define _GPIO_EXT_INT_ID                EN_EXTI1_IRQ
#define _GPIO_KEYPAD_CHNL               EXTI15_10_IRQn
#define _GPIO5_9_EXT_INT_ID             EN_EXTI2_IRQ

#define _CORE_EXT_IT_FUNCTION     		void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) // pin4 external interrupt

/********************* BOARD I2C CONTROL ******************/
#define _I2C_LINE_1                                                 (hi2c1)
#define _I2C_LINE_3                                                 (hi2c2)

#define _I2C1_INIT()                                                MX_I2C1_Init()
#define _I2C2_INIT()                                                MX_I2C2_Init()

#define _I2C_IS_DEVICE_READY(line, deviceAdr, try, timeout)         HAL_I2C_IsDeviceReady(&line, (uint16_t)deviceAdr, try, timeout)

#define _I2C_SEND(line, deviceAdr, buff, leng)                      HAL_I2C_Master_Transmit(&line, (uint16_t)deviceAdr, \

#define _I2C_RECIVE(line, deviceAdr, buff, leng)                    HAL_I2C_Master_Receive(&line, (uint16_t)deviceAdr,\
                                                                                           (uint8_t *)buff, leng, 300)
#define _I2C_WRITE(line, deviceAdr, addr, buff, leng)               HAL_I2C_Mem_Write(&line, (uint16_t)deviceAdr, addr, \
                                                                                        I2C_MEMADD_SIZE_8BIT, (uint8_t *)buff, leng, 100)

#define _I2C_READ(line, deviceAdr, addr, buff, leng)                HAL_I2C_Mem_Read(&line, (uint16_t)deviceAdr, addr,\
                                                                                       I2C_MEMADD_SIZE_8BIT, (uint8_t *)buff, leng, 100)

/********************* BOARD SPI CONTROL ******************/
#define _SPI_INIT()

/********************* BOARD WDT CONTROL ******************/
#define _WDT_INIT(x)    drvIwdtInit(x)
#define _WDT_FEED()     drvIwdtFeed()
#define _WDT_START()    drvIwdtStart()

/********************* BOARD UART CONTROL ******************/
#define _UART_DEBUG_INIT()                          MX_USART1_UART_Init()
#define _UART_COMM_INIT()                           MX_USART2_UART_Init();

#define _UART_LINE_OBJ_TYPE                         UART_HandleTypeDef
#define _UART_DEBUG_LINE                            (huart1)
#define _UART_COMM_LINE_1                           (huart1)
#define _UART_COMM_LINE_2                           (huart3)

#define _LINE_DBG_RX_IT_ID                          (EN_USART1_IRQ)
#define _LINE_COMM_1_RX_IT_ID                       (EN_USART2_IRQ)
#define _LINE_COMM_2_RX_IT_ID                       (EN_USART3_IRQ)

#define _IS_DBG_UART_IT()                           (USART1 == huart->Instance)
#define _IS_COMM_1_UART_IT()                        (USART2 == huart->Instance)
#define _IS_COMM_2_UART_IT()                        (USART3 == huart->Instance)

#define _UART_RCV_IT_FUNCTION                       void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)

#define _UART_RX_IT_DISABLE(line)                   __HAL_UART_DISABLE_IT(line, UART_IT_RXNE)
#define _UART_RX_IT_ENABLE(line)                    __HAL_UART_ENABLE_IT(line, UART_IT_RXNE)
#define _UART_RCV_IT(line, pBuff, leng)             HAL_UART_Receive_IT(line, pBuff, leng)
#define _UART_CLR_IT_FLAG(line, flag)               __HAL_UART_CLEAR_FLAG(line, flag)
#define _UART_SEND(line, buff, leng, timeout)       HAL_UART_Transmit(line, buff, leng, timeout)

/********************* BOARD ADC CONTROL ******************/
#define _ADC_BOARD_MEASURE_BUS_INIT()               drvADCInitBus(EN_ADC_BUS_1, NULL)
#define _ADC_CHNL_MEASURE_INIT()                    drvADCInitChannel(EN_ADC_BUS_1, EN_ADC_CHANNEL_4)
#define _ACD_READ(bus, chnl)                        drvADCRead(bus, chnl)
#define _ADC_READ_X_SENSOR()                        _ACD_READ(EN_ADC_BUS_1, EN_ADC_CHANNEL_4)

/********************* BOARD TIMER CONTROL ******************/
#define _TIMER_ALERT_IT_ID              (EN_TIM6_DAC_IRQ)
#define _TIMER_EVENT_IT_ID              (EN_TIM7_IRQ)

#define _TIMER_ALERT_INIT()             MX_TIM6_Init()
#define _TIMER_EVENT_INIT()             MX_TIM7_Init()

#define _CORE_TIMER_IT_FUNCTION         void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)

#define _TIMER_ALERT_START()            HAL_TIM_Base_Start_IT(&htim6)
#define _TIMER_EVENT_START()            HAL_TIM_Base_Start_IT(&htim7)

#define _IS_ALERT_TIMER_IT()            (htim->Instance == TIM6)
#define _IS_EVENT_TIMER_IT()            (htim->Instance == TIM7)

/********************* BOARD CAN CONTROL ******************/
typedef CAN_TxHeaderTypeDef                         _HAL_CAN_TX_HEADER;
typedef CAN_RxHeaderTypeDef						    _HAL_CAN_RX_HEADER;
#define CAN_RX_FIFO0                                (0x00000000U)  /*!< CAN receive FIFO 0 */
#define CAN_RX_FIFO1                                (0x00000001U)  /*!< CAN receive FIFO 1 */

#define _CAN_INIT()	                                MX_CAN1_Init()

#define _CAN_LINE1                                  (hcan1)
#define _CAN_LINE2                                  (hcan1)

#define _CORE_CAN_2_IT_FUNC                         void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)

#define CAN_RCV_IT_ID                               (EN_CAN2_RX0_IRQ)
#define CAN_RCV_IT_FUNCTION                         void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
#define HAL_CAN_REGISTERCALLBACK(v1, v2, v3)        HAL_CAN_RegisterCallback(v1,v2,v3)
#define HAL_CAN_UNREGISTERCALLBACK(v1, v2)          HAL_CAN_UnRegisterCallback(v1, v2)
#define HAL_CAN_ACTIVATENOTIFICATION(v1, v2)        HAL_CAN_ActivateNotification(v1, v2)
#define HAL_CAN_DEACTIVATENOTIFICATION(v1, v2)      HAL_CAN_DeactivateNotification(v1, v2)
#define HAL_CAN_CONFIGFILTER(v1, v2)                HAL_CAN_ConfigFilter(v1, v2)
#define HAL_CLEAR_TX_MAILBOX(canLine)               HAL_CAN_AbortTxRequest(canLine, CAN_TX_MAILBOX0 | CAN_TX_MAILBOX1 | CAN_TX_MAILBOX2);

#define _HAL_CAN_START(v1)                          HAL_CAN_Start(v1)
#define _HAL_CAN_1_START()                          _HAL_CAN_START(&_CAN_LINE1)
#define _HAL_CAN_2_START()                          _HAL_CAN_START(&_CAN_LINE2)

#define _HAL_CAN_STOP(v1)                           HAL_CAN_Stop(v1)
#define _HAL_CAN_ADD_TX_MESSAGE(v1, v2, v3, v4)     HAL_CAN_AddTxMessage(v1, v2, v3, v4)
#define _HAL_CAN_GET_TXMAILBOXES_FREE_LEVEL(v1)     HAL_CAN_GetTxMailboxesFreeLevel(v1)
#define _HAL_CAN_GET_RX_MESSAGE(v1, v2, v3, v4)     HAL_CAN_GetRxMessage(v1, v2, v3, v4)


/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

#endif /* DRIVERS_BOARD_BOARDCONFIG_STM_010101_H_ */
/********************************* End Of File ********************************/
