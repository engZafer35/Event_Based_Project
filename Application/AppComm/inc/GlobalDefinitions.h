/******************************************************************************
* #Author       : Zafer Satılmış
* #Revision     : 1.0
* #Date         : Jan 27, 2021 - 9:05:66 AM
* #File Name    : GlobalDefinitions.h
*******************************************************************************/

/******************************************************************************
* 
******************************************************************************/
/******************************IFNDEF & DEFINE********************************/
#ifndef __GLOBAL_DEFINITIONS_H__
#define __GLOBAL_DEFINITIONS_H__

/*********************************INCLUDES*************************************/

/******************************MACRO DEFINITIONS*******************************/

#define MCU_16BIT   (16)
#define MCU_32BIT   (32)

//Select project mcu bit size
#define MCU_BIT_SIZE_DEF (MCU_32BIT)

#define FAILURE (-1)
#define SUCCESS (0)

#ifndef FALSE
    #define FALSE 0
    #define TRUE  1
#endif

#ifndef DISABLE
    #define DISABLE (0)
#endif
#ifndef ENABLE
    #define ENABLE (1)
#endif

#define WAIT_10_MS      (10)
#define WAIT_20_MS      (20)
#define WAIT_50_MS      (50)
#define WAIT_100_MS     (100)
#define WAIT_200_MS     (200)
#define WAIT_500_MS     (500)
#define WAIT_1_SEC      (1000)
#define WAIT_2_SEC      (2000)
#define WAIT_3_SEC      (3000)
#define WAIT_4_SEC      (4000)
#define WAIT_5_SEC      (5000)
#define WAIT_6_SEC      (6000)
#define WAIT_7_SEC      (7000)
#define WAIT_8_SEC      (8000)
#define WAIT_9_SEC      (9000)
#define WAIT_10_SEC     (10000)
#define WAIT_15_SEC     (15000)
#define WAIT_20_SEC     (20000)
#define WAIT_30_SEC     (30000)
#define WAIT_40_SEC     (40000)
#define WAIT_50_SEC     (50000)
#define WAIT_1_MIN      (60000)
#define WAIT_5_MIN      (300000)
#define WAIT_10_MIN     (600000)
#define WAIT_20_MIN     (1200000)
#define WAIT_30_MIN     (1800000)
#define WAIT_40_MIN     (2400000)
#define WAIT_50_MIN     (3000000)
#define WAIT_1_HOUR     (6600000)

#define TIME_OUT_10MS   (10)
#define TIME_OUT_20MS   (20)
#define TIME_OUT_50MS   (50)
#define TIME_OUT_75MS   (75)
#define TIME_OUT_100MS  (100)
#define TIME_OUT_200MS  (200)
#define TIME_OUT_500MS  (500)
#define TIME_OUT_1_SEC  (1000)
#define TIME_OUT_2_SEC  (2000)
#define TIME_OUT_3_SEC  (3000)
#define TIME_OUT_4_SEC  (4000)
#define TIME_OUT_5_SEC  (5000)

#ifndef NULL
 #define NULL ((void *)0)
#endif

#define IS_NULL_PTR(x)     (NULL == x)
#define IS_SAFELY_PTR(x)   (NULL != x)

#define SAFE_FREE(x)   do{ if(x) { free(x); x = NULL; } }while(0)
#define SAFE_DELETE(x) do{ if(x) { delete(x); x = NULL; } }while(0)

#define CHECK_BIT(var,pos) (!!((var) & (1<<(pos))))

typedef void (*VoidCallback)(void);
typedef void (*VICallback)(int x);
typedef void (*VUICallback)(unsigned int x);

#if (MCU_BIT_SIZE_DEF == MCU_16BIT)
    typedef signed char         S8;
    typedef unsigned char       U8;
    typedef int                 S16;
    typedef S16                 SSS; //signed system size
    typedef unsigned int        U16;
    typedef U16                 USS; //unsigned system size
    typedef long                S32;
    typedef unsigned long       U32;
    typedef long long           S64;
    typedef unsigned long long  U64;
    typedef S16                 RETURN_STATUS;
    typedef float               FLOAT;
    typedef double              DOUBLE;
    typedef USS                 BOOL;
    typedef BOOL                FLAG;

    #define MAX_USS_NUM         (0xFFFF) //max 16bit unsigned value

#elif (MCU_BIT_SIZE_DEF == MCU_32BIT)
    typedef signed char         S8;
    typedef unsigned char       U8;
    typedef short int           S16;
    typedef unsigned short int  U16;
    typedef int                 S32;
    typedef S32                 SSS; //signed system size
    typedef unsigned int        U32;
    typedef U32                 USS; //unsigned system size
    typedef long long           S64;
    typedef unsigned long long  U64;
    typedef S32                 RETURN_STATUS;
    typedef float               FLOAT;
    typedef double              DOUBLE;
    typedef USS                 BOOL;
    typedef BOOL                FLAG;

    #define MAX_USS_VAL         (0xFFFFFFFF) //max 32bit unsigned value

#else
    #error "Firstly define MCU bit size in GlobalTypedef.h"
#endif

/*******************************TYPE DEFINITIONS ******************************/

/************************* GLOBAL VARIBALE REFERENCES *************************/

/************************* GLOBAL FUNCTION DEFINITIONS ************************/

#endif /* __GLOBAL_DEFINITIONS_H__ */

/********************************* End Of File ********************************/
