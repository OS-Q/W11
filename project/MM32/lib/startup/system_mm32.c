////////////////////////////////////////////////////////////////////////////////
/// @file    SYSTEM_MM32.C
/// @author  AE TEAM
/// @version 2.0.0
/// @date    2018-08-01
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
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
#define _SYSTEM_MM32_C_

// Files includes  -------------------------------------------------------------
#include <string.h>
#include "types.h"
#include "mm32.h"

#include "system_mm32.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_RESOURCE
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Exported_Constants
/// @{

#if defined(__MM3N1)
//  #define VECT_TAB_SRAM
    #define VECT_TAB_OFFSET  0x0000
#endif
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  This function handles SysTick Handler.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SysTick_Handler(void)
{
    AppTickPtr();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  This function get the MCU ID.
/// @param  None.
/// @retval  MCU ID.
////////////////////////////////////////////////////////////////////////////////
EM_MCUID DBGMCU_GetDEVID()
{
    // Automatic Identification
    if ((SCB->CPUID & COREID_MASK) == 0) {
        switch (((DBGMCU_TypeDef*)0x40013400)->IDCODE ) {
            case MCUID_MM0N1:
                return emMCUID_MM32L073;        // emMCUID_MM0N1;
            case MCUID_MM0P1:
            case MCUID_MM0P2:
                return emMCUID_MM32SPIN27;      // emMCUID_MM0P1;
            case MCUID_MM0Q1:
                return emMCUID_MM32F031;        // emMCUID_MM0Q1;
            case MCUID_MM0M1:
                return emMCUID_MM32F031_OLD;    // emMCUID_MM0M1;
            default: break;
        }
    }
    else if ((SCB->CPUID & COREID_MASK) == 0x0030) {
        RCC->APB1ENR = 0;
        RCC->APB1ENR |= RCC_APB1ENR_PWR;
        if (((DBGMCU_TypeDef*)0x40007080)->IDCODE == MCUID_MM3O1)
            return emMCUID_MM32L395;            // emMCUID_MM3O1;
        else {
            RCC->APB1ENR |= RCC_APB1ENR_PWR;
            if (((DBGMCU_TypeDef*)0x40007080)->IDCODE == MCUID_MM3N1)
                return emMCUID_MM32L373;        // emMCUID_MM3N1;
            else if (((DBGMCU_TypeDef*)0xE0042000)->IDCODE == MCUID_MM3M1)
                return emMCUID_MM32F103_OLD;    // emMCUID_MM3M1;
        }
    }
    return Unknown;
}

static u32 greatest_common_divisor(u32 a, u32 b)
{
    while (a != b) {
    
        if (a > b) a = a - b;
        if (b > a) b = b - a;
    }
    
    return a;
}

static void pll_calculate(u32 src, u32 target, u8 *mul, u8 *div)
{
    u32 common_factor = greatest_common_divisor(src, target);
    
    *mul = target / common_factor - 1;
    *div = src / common_factor - 1;
}

////////////////////////////////////////////////////////////////////////////////
//  @brief  System clock configuration
//  @param  enable: Enable or disable the systick.
//  @param  callbackPtr: The pointer point to the systick callback function.
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
EM_MCUID SetSystemClock(SystemClock_TypeDef *sys_clk)
{
    u8 mul = 0, div = 0;
    
#if defined(__EX_AES)
    sys_clk->clk_src    = 0;
    sys_clk->clk_target = 72000000;
#endif
    
    // DeInit RCC
    SET_BIT(RCC->CR, RCC_CR_HSION);
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_SW);
#if defined(__MM3N1) || defined(__MM0N1) || defined(__MM3O1) || defined(MM0P1)
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON | RCC_CR_PLLDIV | RCC_CR_PLLMUL);
#endif
#if defined(__MM0Q1)
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
#endif
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
    CLEAR_REG(RCC->CFGR);
    CLEAR_REG(RCC->CIR);
        
    if (!sys_clk->clk_src) {  // HSI 
        
        if (sys_clk->clk_target > MCU_MAX_FREQ) {
            sys_clk->clk_target = MCU_MAX_FREQ;
        }
        
        SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
        MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (sys_clk->clk_target - 1) / 24000000);
        
        CLEAR_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
        
        if (sys_clk->clk_target != 8000000) {
            SET_BIT(RCC->CR,  RCC_CR_PLLON);
            while(!READ_BIT(RCC->CR, RCC_CR_PLLRDY));
            
            pll_calculate(12, sys_clk->clk_target / 1000000, &mul, &div);
            
            MODIFY_REG(RCC->CR, RCC_CR_PLLMUL, mul << RCC_CR_PLLMUL_Pos);
            MODIFY_REG(RCC->CR, RCC_CR_PLLDIV, div << RCC_CR_PLLDIV_Pos);
            
            MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
            while(!READ_BIT(RCC->CFGR, RCC_CFGR_SWS_PLL));
        } else {
            MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_HSI_DIV6);
            while(!READ_BIT(RCC->CFGR, RCC_CFGR_SWS_HSI_DIV6));
        }
        
    } else {
        
        SET_BIT(RCC->CR, RCC_CR_HSEON);
        while(!READ_BIT(RCC->CR, RCC_CR_HSERDY));
        
    }
    
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE,  (sys_clk->ahb1_div + 7 - 1) << RCC_CFGR_HPRE_Pos);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, (sys_clk->apb1_div + 3 - 1) << RCC_CFGR_PPRE1_Pos);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, (sys_clk->apb2_div + 3 - 1) << RCC_CFGR_PPRE2_Pos);
    
    if (sys_clk->sys_tick_enable) {
        SysTick_Config(sys_clk->clk_target / 1000);
    } else {
        CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
    }
    
#if defined(__MM3N1) || defined(__MM3O1) 
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif
#endif
    
    AppTickPtr = sys_clk->app_tick_ptr;
    
    return DBGMCU_GetDEVID();
}

/// @}


/// @}

/// @}


