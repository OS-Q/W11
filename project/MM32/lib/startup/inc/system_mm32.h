////////////////////////////////////////////////////////////////////////////////
/// @file    SYSTEM_MM32.H
/// @author  AE TEAM
/// @version V2.0.0
/// @date    2018-08-01
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT 2018 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////


// Define to prevent recursive inclusion  --------------------------------------
#ifndef __SYSTEM_MM32_H
#define __SYSTEM_MM32_H

// Files includes  -------------------------------------------------------------
#include "types.h"

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Example_Layer
/// @brief MM32 Example Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_RESOURCE
/// @brief MM32 Examples resource modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Constants
/// @{


#define IDCODE_DEVID_MASK       (0x00000FFFU)
#define COREID_MASK             (0x00000070U)
#define MCUID_MM0N1             (0xCC568091U)
#define MCUID_MM0P1             (0xCC56A091U)   // Rev.C
#define MCUID_MM0P2             (0xCC56A097U)   // Rev.E
#define MCUID_MM0Q1             (0xCC4460B1U)
#define MCUID_MM0M1             (0xCC567071U)
#define MCUID_MM3O1             (0xCC9AA0A1U)
#define MCUID_MM3M1             (0xCC888045U)
#define MCUID_MM3N1             (0xCC888047U)

#if defined(__MM3N1)
    #define MCU_MAX_FREQ            96000000L
#elif defined(__MM0N1)
    #define MCU_MAX_FREQ            72000000L
#elif defined(__MM3O1)
    #define MCU_MAX_FREQ            168000000L
#elif defined(__MM0P1)
    #define MCU_MAX_FREQ            48000000L
#elif defined(__MM0Q1)
    #define MCU_MAX_FREQ            72000000L
#endif

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Enumeration
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief MCU ID enumerate definition.
/// @anchor EM_MCUID
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    Unknown,
    emMCUID_MM32L073,
    emMCUID_MM32SPIN27,
    emMCUID_MM32F031,
    emMCUID_MM32F031_OLD,
    emMCUID_MM32L395,
    emMCUID_MM32F103_OLD,
    emMCUID_MM32L373
}EM_MCUID;

////////////////////////////////////////////////////////////////////////////////
/// @brief  System clock configuration
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    u32 clk_src;
    u32 clk_target;
    u8  ahb1_div;
    u8  ahb2_div;
    u8  apb1_div;
    u8  apb2_div;
    bool sys_tick_enable;
    void (*app_tick_ptr)(void);
} SystemClock_TypeDef;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Variables
/// @{
#ifdef _SYSTEM_MM32_C_
#define GLOBAL

GLOBAL int nTimeOutCnt = 0;

GLOBAL bool sysTickFlag1mS = false;
GLOBAL u32 sysTickCnt1mS = 0;

GLOBAL bool sysTickFlag = false;
GLOBAL u32 sysTickCnt = 0;

GLOBAL bool tickFlag = false;
GLOBAL u32 tickCnt = 0;

#else
#define GLOBAL extern
#endif

GLOBAL bool sysTickFlag1mS;
GLOBAL u32 sysTickCnt1mS;
GLOBAL int nTimeOutCnt;
GLOBAL bool sysTickFlag;
GLOBAL u32 sysTickCnt;
GLOBAL bool tickFlag;
GLOBAL u32 tickCnt;


GLOBAL u16 g_KEY_buffer[8];


GLOBAL bool sysTickFlag;
GLOBAL u32 sysTickCnt;
GLOBAL EM_MCUID MCUID;

GLOBAL void (*AppTickPtr)(void);

#undef GLOBAL

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{

//void PutKeyBuffer(u8 key);

void SysTickLED(void);

EM_MCUID DBGMCU_GetDEVID(void);
//EM_MCUID SystemInit(EM_SystemClock ClockSoucre, EM_SYSTICK enable , u32* address);
EM_MCUID SetSystemClock(SystemClock_TypeDef *sys_clk);

/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
