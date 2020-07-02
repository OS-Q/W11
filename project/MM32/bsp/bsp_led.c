#include "types.h"
#include "mm32.h"

void bsp_led_init(void)
{
#if defined(__MM3N1)
    RCC->APB2ENR |= RCC_APB2ENR_GPIOA | RCC_APB2ENR_GPIOC | RCC_APB2ENR_GPIOB;
#else
    RCC->AHBENR |= RCC_AHBENR_GPIOA | RCC_AHBENR_GPIOB | RCC_AHBENR_GPIOC | RCC_AHBENR_GPIOD;
#endif

#if defined(__MM32_MINI) || defined(__MM32_EMINI)
    GPIOB->BRR |= 0x0030;
    GPIOB->BSRR |= 0x0030;

    GPIOB->CRL = (GPIOB->CRL & 0xFFF0FFFF) | (u32)(0x00 | 0x02) << 16;	// 0x00000006; 	// GPIOB_Pin4  OUTOD
    GPIOB->CRL = (GPIOB->CRL & 0xFF0FFFFF) | (u32)(0x00 | 0x02) << 20;	// 0x00600000; 	// GPIOB_Pin5  OUTOD

#elif defined(__MB020)
    GPIOD->BSRR |= 0x0030;
    GPIOB->BSRR |= 0x0018;
    GPIOA->BSRR |= 0x8000;

    GPIOD->CRL = (GPIOD->CRL & 0xFFFF0FFF) | (u32)(0x00 | 0x02) << 12;	// 0x00000006; 	// GPIOB_Pin4  OUTOD
    GPIOB->CRL = (GPIOB->CRL & 0xFFFF0FFF) | (u32)(0x00 | 0x02) << 12;	// 0x00600000; 	// GPIOB_Pin5  OUTOD
    GPIOB->CRL = (GPIOB->CRL & 0xFFF0FFFF) | (u32)(0x00 | 0x02) << 16;	// 0x00600000; 	// GPIOB_Pin5  OUTOD
    GPIOA->CRH = (GPIOA->CRH & 0x0FFFFFFF) | (u32)(0x00 | 0x02) << 28;	// 0x00600000; 	// GPIOB_Pin5  OUTOD

#elif defined(__MB023)
    GPIOB->BSRR |= 0x0038;
    GPIOA->BSRR |= 0x8000;

    GPIOB->CRL = (GPIOB->CRL & 0xFFFF0FFF) | (u32)(0x00 | 0x02) << 12;	
    GPIOB->CRL = (GPIOB->CRL & 0xFFF0FFFF) | (u32)(0x00 | 0x02) << 16;	
    GPIOB->CRL = (GPIOB->CRL & 0xFF0FFFFF) | (u32)(0x00 | 0x02) << 20;	
    GPIOA->CRH = (GPIOA->CRH & 0x0FFFFFFF) | (u32)(0x00 | 0x02) << 28;	

#elif defined(__MB024)
    GPIOB->BSRR |= 0x0038;
    GPIOA->BSRR |= 0x8000;

    GPIOB->CRL = (GPIOB->CRL & 0xFFFF0FFF) | (u32)(0x00 | 0x02) << 12;	
    GPIOB->CRL = (GPIOB->CRL & 0xFFF0FFFF) | (u32)(0x00 | 0x02) << 16;	
    GPIOB->CRL = (GPIOB->CRL & 0xFF0FFFFF) | (u32)(0x00 | 0x02) << 20;	
    GPIOA->CRH = (GPIOA->CRH & 0x0FFFFFFF) | (u32)(0x00 | 0x02) << 28;	

#else
    GPIOA->BSRR |= 0x0100;
    GPIOC->BSRR |= 0x2000;

    GPIOA->CRH = (GPIOA->CRH & 0xFFFFFFF0) | (u32)(0x04 | 0x02) << 0;	// 0x00000006; 	// GPIOA_Pin8  OUTOD
    GPIOC->CRH = (GPIOC->CRH & 0xFF0FFFFF) | (u32)(0x04 | 0x02) << 20;	// 0x00600000; 	// GPIOC_Pin13 OUTOD
#endif
}

#if defined(__MM32_MINI) || defined(__MM32_EMINI)
void LD1_on(void)	{	GPIOB->BRR  = 0x0020;	}
void LD1_off(void)	{	GPIOB->BSRR = 0x0020;	}
void LD2_on(void)	{	GPIOB->BRR  = 0x0010;	}
void LD2_off(void)	{	GPIOB->BSRR = 0x0010;	}
void CloseLED(void)	{	GPIOB->BSRR = 0x0030;   }
void OpenLED(void)	{	GPIOB->BRR  = 0x0030;   }

#elif defined(__MB020)
void LD1_on(void)	{	GPIOD->BRR  = 0x0008;	}
void LD1_off(void)	{	GPIOD->BSRR = 0x0008;	}
void LD2_on(void)	{	GPIOB->BRR  = 0x0008;	}
void LD2_off(void)	{	GPIOB->BSRR = 0x0008;	}
void CloseLED(void)	{	LD1_off(); LD2_off();   }
void OpenLED(void)	{	LD1_on(); LD2_on();   }

#elif defined(__MB023)
void LD1_on(void)	{	GPIOA->BRR  = 0x8000;	}
void LD1_off(void)	{	GPIOA->BSRR = 0x8000;	}
void LD2_on(void)	{	GPIOB->BRR  = 0x0020;	}
void LD2_off(void)	{	GPIOB->BSRR = 0x0020;	}
void CloseLED(void)	{	LD1_off(); LD2_off();   }
void OpenLED(void)	{	LD1_on(); LD2_on();   }

#elif defined(__MB024)
void LD1_on(void)	{	GPIOA->BRR  = 0x8000;	}
void LD1_off(void)	{	GPIOA->BSRR = 0x8000;	}
void LD2_on(void)	{	GPIOB->BRR  = 0x0020;	}
void LD2_off(void)	{	GPIOB->BSRR = 0x0020;	}
void CloseLED(void)	{	LD1_off(); LD2_off();   }
void OpenLED(void)	{	LD1_on(); LD2_on();   }

#else
void LD1_on(void)	{	GPIOC->BRR  = 0x2000;	}
void LD1_off(void)	{	GPIOC->BSRR = 0x2000;	}
void LD2_on(void)	{	GPIOA->BRR  = 0x0100;	}
void LD2_off(void)	{	GPIOA->BSRR = 0x0100;	}
void CloseLED(void)	{	GPIOC->BSRR = 0x2000;	GPIOA->BSRR = 0x0100;	}
void OpenLED(void)	{	GPIOC->BRR  = 0x2000;	GPIOA->BRR  = 0x0100;	}
#endif
