#include "types.h"
#include "mm32.h"

#include "bsp_led.h"

void bsp_key_init(void)
{
#if defined(__MM3N1)
    RCC->APB2ENR |= RCC_APB2ENR_GPIOA | RCC_APB2ENR_GPIOC | RCC_APB2ENR_GPIOB;
#endif
#if defined(__MM0N1) || defined(__MM0P1) || defined(__MM0Q1) || defined(__MM0S1)
    RCC->AHBENR |= RCC_AHBENR_GPIOA | RCC_AHBENR_GPIOC | RCC_AHBENR_GPIOB;
#endif
#if defined(__MB020)
    RCC->AHBENR |= RCC_AHBENR_GPIOA | RCC_AHBENR_GPIOC | RCC_AHBENR_GPIOB | RCC_AHBENR_GPIOD;
#endif

#if defined(__MM32_MINI)

    GPIOA->BRR  |= 1 << 0;
    GPIOB->BSRR |= 1 << 10;
    GPIOB->BSRR |= 1 << 11;

    GPIOA->CRL = (GPIOA->CRL & 0xFFFFFFF0) | (u32)0x08 << 0;	// 0x00000008; 	// GPIOA_Pin0-IPD
    GPIOB->CRH = (GPIOB->CRH & 0xFFFFF0FF) | (u32)0x08 << 8;	// 0x00000800; 	// GPIOC_Pin10-IPU
    GPIOB->CRH = (GPIOB->CRH & 0xFFFF0FFF) | (u32)0x08 << 12;	// 0x80000000; 	// GPIOA_Pin15-IPU

#elif defined(__MM32_EMINI)

    GPIOB->BRR |= 1 << 1;
    GPIOB->BSRR |= 1 << 2;
    GPIOB->BSRR |= 1 << 10;
    GPIOB->BSRR |= 1 << 11;

    GPIOB->CRL = (GPIOB->CRL & 0xFFFFFF0F) | (u32)0x08 << 4;	// 0x00000800; 	// GPIOB_Pin10-IPU
    GPIOB->CRL = (GPIOB->CRL & 0xFFFFF0FF) | (u32)0x08 << 8;	// 0x00000800; 	// GPIOB_Pin10-IPU
    GPIOB->CRH = (GPIOB->CRH & 0xFFFFF0FF) | (u32)0x08 << 8;	// 0x00000800; 	// GPIOB_Pin10-IPU
    GPIOB->CRH = (GPIOB->CRH & 0xFFFF0FFF) | (u32)0x08 << 12;	// 0x80000000; 	// GPIOA_Pin11-IPU

#elif defined(__MB020)

    GPIOD->BSRR |= 1 << 2;
    GPIOC->BSRR |= 1 << 13;
    GPIOC->BSRR |= 1 << 14;
    GPIOC->BSRR |= 1 << 15;

    GPIOD->CRL = (GPIOD->CRL & 0xFFFFF0FF) | (u32)0x08 << 8;	// 0x00000800; 	// GPIOB_Pin10-IPU
    GPIOC->CRL = (GPIOC->CRH & 0xFF0FFFFF) | (u32)0x08 << 20;	// 0x00000800; 	// GPIOB_Pin10-IPD
    GPIOC->CRH = (GPIOC->CRH & 0xF0FFFFFF) | (u32)0x08 << 24;	// 0x00000800; 	// GPIOB_Pin10-IPD
    GPIOC->CRH = (GPIOC->CRH & 0x0FFFFFFF) | (u32)0x08 << 28;	// 0x80000000; 	// GPIOA_Pin11-IPD

#else
    GPIOA->BRR  |= 1 << 0;
    GPIOC->BSRR |= 1 << 10;
    GPIOA->BSRR |= 1 << 15;

    GPIOA->CRL = (GPIOA->CRL & 0xFFFFFFF0) | (u32)0x08 << 0;	// 0x00000008; 	// GPIOA_Pin0-IPD
    GPIOC->CRH = (GPIOC->CRH & 0xFFFFF0FF) | (u32)0x08 << 8;	// 0x00000800; 	// GPIOC_Pin10-IPU
    GPIOA->CRH = (GPIOA->CRH & 0x0FFFFFFF) | (u32)0x08 << 28;	// 0x80000000; 	// GPIOA_Pin15-IPU

#endif
}