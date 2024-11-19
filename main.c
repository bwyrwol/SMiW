#include <stdint.h>

/*
		LED1 - PE14
		LED2 - PE15
 */
/*
#define PERIPH_BASE             ((uint32_t)0x40000000)

#define AHBPERIPH_BASE          (PERIPH_BASE + 0x20000)
#define APB2PERIPH_BASE         (PERIPH_BASE + 0x10000)

#define RCC_BASE 		        		(AHBPERIPH_BASE + 0x1000)
#define RCC_APB2ENR 		    		*((uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB2ENR_IOPEEN			((uint32_t)0x00000040)

#define GPIOE_BASE              (APB2PERIPH_BASE + 0x1800)
#define GPIOE               		((GPIO_TypeDef *) GPIOE_BASE)

#define GPIOE_CRH            		*((uint32_t *) (GPIOE_BASE + 0x04)) //!!!
#define GPIOE_ODR            		*((uint32_t *) (GPIOE_BASE + 0x0C)) //!!!

#define GPIO_CRH_MODE14         ((uint32_t)0x03000000)
#define GPIO_CRH_MODE14_0       ((uint32_t)0x01000000)
#define GPIO_CRH_MODE14_1       ((uint32_t)0x02000000)

#define GPIO_ODR_ODR14          ((uint16_t)0x4000)


int main(void)
{
	RCC_APB2ENR = RCC_APB2ENR_IOPEEN;
	GPIOE_CRH |= GPIO_CRH_MODE14_1;
	
	for(;;)
	{
    GPIOE_ODR ^= GPIO_ODR_ODR14;

    for(volatile uint32_t delay = 100000; delay; delay--)
		{
		}
	}
}
*/
//=============================================================================
// CMSIS v1 Common Microcontroller Software Interface Standard
//=============================================================================
/*
#include <stm32f10x.h>

int main(void)
{
  RCC->APB2ENR = RCC_APB2ENR_IOPEEN;
  
  GPIOE->CRH |= GPIO_CRH_MODE14_1;
  //GPIOE->CRH &= ~GPIO_CRH_CNF14_0;
	
	

  volatile uint32_t delay;
  
  while(1)
  {
    GPIOE->ODR ^= GPIO_ODR_ODR14;
    for(delay = 1000000; delay; delay--){}

    //GPIOE->ODR &= ~GPIO_ODR_ODR14;
    //for(delay = 1000000; delay; delay--){}
  } // while(1)

} // main
*/
//=============================================================================
// CMSIS przerwania
//=============================================================================
/*
#include <stm32f10x.h>

int main(void)
{
  RCC->APB2ENR  = RCC_APB2ENR_IOPEEN;
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  
  GPIOE->CRH |= GPIO_CRH_MODE14_1;
  GPIOE->CRH &= ~GPIO_CRH_CNF14_0;

  TIM1->PSC = 999;              // prescaler
  TIM1->ARR = 3999;             // przeladowanie licznika
  TIM1->DIER = TIM_DIER_UIE;    // wywolanie przerwania przy przeladowaniu
  TIM1->CR1 = TIM_CR1_CEN;      // odblokowanie licznika
  
  NVIC_EnableIRQ(TIM1_UP_IRQn); // odblokowanie przerwania od licznika
  
  while(1);
} // main

void TIM1_UP_IRQHandler(void);
void TIM1_UP_IRQHandler(void)
{
    if (TIM1->SR & TIM_SR_UIF)
    {
      TIM1->SR = (uint16_t)~TIM_SR_UIF;
      GPIOE->ODR ^= GPIO_ODR_ODR14;
    }
}
*/
//=============================================================================
// CMSIS v2
//=============================================================================
/*
#include <stm32f10x.h>
#include <GPIO_STM32F10x.h>

#define enable  1
#define disable 0

void delay(uint32_t d)
{
    volatile uint32_t _delay = d;
    for(_delay; _delay; _delay--){};
}

int main(void)
{
  //RCC->APB2ENR = RCC_APB2ENR_IOPEEN;
  GPIO_PortClock(GPIOE, enable);
  
  //GPIOE->CRH |= GPIO_CRH_MODE14_1;
  //GPIOE->CRH &= ~GPIO_CRH_CNF14_0;
  GPIO_PinConfigure(GPIOE, 14, GPIO_OUT_OPENDRAIN, GPIO_MODE_OUT2MHZ);
	
  while(1)
  {
    //GPIOE->ODR |= GPIO_ODR_ODR14;
    GPIO_PortWrite(GPIOE, GPIO_ODR_ODR14, GPIO_ODR_ODR14);
    delay(1000000);

    //GPIOE->ODR &= ~GPIO_ODR_ODR14;
    GPIO_PortWrite(GPIOE, GPIO_ODR_ODR14, 0);
    delay(1000000);
    
  } // while(1)

} // main

*/
//=============================================================================
// SPL v1
//=============================================================================
/*
#include <stm32f10x.h>
//#include <GPIO_STM32F10x.h>
#include <stm32f10x_gpio.h>

void delay(uint32_t d)
{
    volatile uint32_t _delay = d;
    for(_delay; _delay; _delay--){};
}

int main(void)
{
  //RCC->APB2ENR = RCC_APB2ENR_IOPEEN;
  //GPIO_PortClock(GPIOE, enable);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  
  //GPIOE->CRH |= GPIO_CRH_MODE14_1;
  //GPIOE->CRH &= ~GPIO_CRH_CNF14_0;
  //GPIO_PinConfigure(GPIOE, 14, GPIO_OUT_OPENDRAIN, GPIO_MODE_OUT2MHZ);
  
  GPIO_InitTypeDef GPIO_InitStuct;
    GPIO_InitStuct.GPIO_Pin   = GPIO_Pin_14;
    GPIO_InitStuct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStuct.GPIO_Mode  = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOE, &GPIO_InitStuct);
  
  while(1)
  {
    //GPIOE->ODR |= GPIO_ODR_ODR14;
    //GPIO_PortWrite(GPIOE, GPIO_ODR_ODR14, GPIO_ODR_ODR14);
    GPIO_ResetBits(GPIOE, GPIO_Pin_14);
    delay(1000000);

    //GPIOE->ODR &= ~GPIO_ODR_ODR14;
    //GPIO_PortWrite(GPIOE, GPIO_ODR_ODR14, 0);
    GPIO_SetBits(GPIOE, GPIO_Pin_14);
    delay(1000000);
    
  } // while(1)

} // main
*/
//=============================================================================
// SPL SysTick
//=============================================================================
/*
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

int main(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStuct;
    GPIO_InitStuct.GPIO_Pin   = GPIO_Pin_14;
    GPIO_InitStuct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStuct.GPIO_Mode  = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOE, &GPIO_InitStuct);
  
  SysTick_Config(16777215);
  
  while(1);

} // main

void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIOx->ODR ^= GPIO_Pin;
}

void SysTick_Handler(void)
{
  GPIO_ToggleBits(GPIOE, GPIO_Pin_14);
}
*/
//=============================================================================
// SPL Timer
//=============================================================================
/*
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

int main(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN, ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStuct;
    GPIO_InitStuct.GPIO_Pin   = GPIO_Pin_14;
    GPIO_InitStuct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStuct.GPIO_Mode  = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOE, &GPIO_InitStuct);
  
  TIM_TimeBaseInitTypeDef TIM_InitStruct;
    TIM_InitStruct.TIM_Prescaler         = 999;
    TIM_InitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_InitStruct.TIM_Period            = 3999;
    TIM_InitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_InitStruct);
  TIM_Cmd(TIM1, ENABLE);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  
  NVIC_InitTypeDef NVIC_InitStruc;
    NVIC_InitStruc.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStruc.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruc.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruc.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruc);
  
  while(1);
} // main

void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{ GPIOx->ODR ^= GPIO_Pin; }

void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        GPIO_ToggleBits(GPIOE, GPIO_ODR_ODR14);
    }
}
*/

//=============================================================================
// Exceptions
//=============================================================================
/*
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIOx->ODR ^= GPIO_Pin;
}

int main(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStuct;
    GPIO_InitStuct.GPIO_Pin   = GPIO_Pin_14;
    GPIO_InitStuct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStuct.GPIO_Mode  = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOE, &GPIO_InitStuct);
  
    GPIO_InitStuct.GPIO_Pin   = GPIO_Pin_15;
    GPIO_InitStuct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStuct.GPIO_Mode  = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOE, &GPIO_InitStuct);

  SysTick_Config(16777215);
	
	uint32_t times = 10;
  
	GPIO_SetBits(GPIOE, GPIO_Pin_15);
  while (1)
  {
    //GPIO_ToggleBits(GPIOE, GPIO_Pin_15);

    for(volatile uint32_t delay = 1000000; delay; delay--)
		{
		}
		
    if (--times == 0)
    {
        //volatile uint16_t licznik = 50, mianownik = 0;
        // *((uint32_t *)0x40023667) = 0x66666666;
        //licznik = licznik / mianownik;
        //__asm("B 0x40023667"); // nie dziala
        //volatile uint32_t zm = 0;
        //__asm("MOV zm, 0x40023667"); // error
    }
  }

} // main

void SysTick_Handler(void)
{
  GPIO_ToggleBits(GPIOE, GPIO_Pin_14);
}

void HardFault_Handler(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_15);
	while(1)
	{
	}
}

void UsageFault_Handler(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_15);
	while(1)
	{
	}
}
*/