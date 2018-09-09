/*
 * file : 	RCC_Init.c
 * Brief:	initialization of of the clocks using
 * 		using the HSE pin in Bypass mode and
 * 		the on board PLL
 */

#include "stm32f7.h"

void RCC_Init()
{
	/* set the output clock */
	RCC->CFGR |= (1<<22)|(1<<21);		//Configure clock for PLL Mode
	RCC->AHB1ENR |= (1<<0);			//enable GPIOA Clock
	GPIOA->MODER |= (2<<16);		//GPIOA Pin 16 Alternate Function
	GPIOA->OSPEEDR |= (3<<16);		//Speed High

	/* enable HSE in bypass mode */
	RCC->CR |= (1<<18);			//enable bypass mode
	RCC->CR |= (1<<16);			//Enable HSE
	while(RCC->CR != (RCC->CR | (1<<17)))	//loop until Ready
	{
		//do nothing
	}
	RCC->CFGR |= (1<<0);			//HSE Becomes Main Clock Temporarily

	/* disable HSI */
	if(RCC->CR == (RCC->CR | (1<<0)))	//Check if HSI is Still on
	{
		RCC->CR &= ~(1<<0);		//Turn HSI off
	}

	/*
	 * PLL Clock:	CLK_VCO = 8MHz * (PLLN/PLLM)
	 * 				CLK_VCO = 8MHZ * (96/8)
	 * 				CLK_VCO = 96MHZ
	 * 				PLLCLK  = CLK_VCO / PLLP
	 * 				PLLCLK  = 96MHz / 2
	 * 				PLLCLK  = 48MHz
	 */
	/* set m to 8 */
	RCC->PLLCFGR &= ~(63<<0);
	RCC->PLLCFGR |= (8<<0);

	/* set n to 96 */
	RCC->PLLCFGR &= ~(511<<6);
	RCC->PLLCFGR |= (96<<6);

	/* set p to 2 */
	RCC->PLLCFGR &= ~(3<<16);

	/* set MCO2 to PLL (check if correct frequency)*/
	RCC->AHB1ENR |= (1<<2);
	GPIOC->MODER |= (2<<18);
	GPIOC->OSPEEDR |= (2<<18);
	GPIOC->AFRH &= ~(15<<4);
	RCC->CFGR |= (3<<30);

	/* enable main PLL */
	RCC->PLLCFGR |= (1<<22);		//PLL clock source is HSE
	RCC->CR |= (1<<24);			//Enable PLL (Not main Clock Source yet)
	while(RCC->CR != (RCC->CR | (1<<25)))	//loop until ready
		{
			//do nothing
		}


	/*
	 * SAI CLock: Clk_VCO = 8Mhz * (PLLSAIN/PLLM)
	 * 			  Clk_VCO = 8MHz * (192/8)
	 * 			  Clk_VCO = 192MHz < 432MHz (+)
	 *
	 * 			  Clk_SAIQ = CLK_VCO / PLLSAIQ
	 * 			  Clk_SAIQ = 192MHz / 4
	 * 			  Clk_SAIQ = 48MHz
	 *
	 */

	/* set Q to 2 */
	//RCC->PLLSAICFGR &= ~(15<<24);
	//RCC->PLLSAICFGR |= (4<<24);

	/* enable SAIPLL */
	RCC->CR |= (1<<28);
	while(RCC->CR != (RCC->CR | (1<<29)))
			{
				//do nothing
			}

	RCC->CFGR ^= (3<<0);			//PLL Becomes Main Clock

	/* catch if PLL not main clock */
	while(RCC->CFGR != (RCC->CFGR | (2<<2)))
	{
		//do nothing
	}
}
