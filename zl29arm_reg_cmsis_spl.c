#include <stdint.h>

/*
		LED1 - PE14
		LED2 - PE15
 */

#define PERIPH_BASE             ((uint32_t)0x40000000)

#define AHBPERIPH_BASE          (PERIPH_BASE + 0x20000)
#define APB2PERIPH_BASE         (PERIPH_BASE + 0x10000)

#define RCC_BASE 		(AHBPERIPH_BASE + 0x1000)
#define RCC_APB2ENR 		*((uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB2ENR_IOPEEN	((uint32_t)0x00000040)

#define GPIOE_BASE              (APB2PERIPH_BASE + 0x1800)
#define GPIOE               	((GPIO_TypeDef *) GPIOE_BASE)

#define GPIOE_CRH            	*((uint32_t *) (GPIOE_BASE + 0x04))
#define GPIOE_ODR            	*((uint32_t *) (GPIOE_BASE + 0x0C))

#define GPIO_CRH_MODE14         ((uint32_t)0x03000000)
#define GPIO_CRH_MODE14_0       ((uint32_t)0x01000000)
#define GPIO_CRH_MODE14_1       ((uint32_t)0x02000000)

#define GPIO_ODR_ODR14          ((uint16_t)0x4000)


int main(void)
{


}

