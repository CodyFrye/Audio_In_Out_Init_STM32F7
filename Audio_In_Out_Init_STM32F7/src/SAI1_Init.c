/*
 * file :	SAI1_Init.c
 * Brief:	Initialization of the SAI Peripheral to
 * 			allow the retrieval and transmission of
 * 			audio data
 */

#include "stm32f7.h"

void SAI1_Init()
{
	/* Enable SAI1 A clocks */
	RCC->AHB1ENR |= (1<<4);						//enable GPIOE Clock
	GPIOE->MODER |= (2<<8)|(2<<10)|(2<<12);		//set GPIOE pins to alt. function mode
	GPIOE->OSPEEDR |= (2<<8)|(2<<10)|(2<<12);	//set speeds to high
	GPIOE->AFRL |= (6<<16)|(6<<20)|(6<<24);  	//set to alt. function 6 for pins 4, 5, and 6

	/* Enable SAI1 B clocks */
	RCC->AHB1ENR |= (1<<5);						//enable GPIOF Clock
	GPIOE->MODER |= (2<<6);						//set GPIOE pin to alt. function mode
	GPIOF->MODER |= (2<<18) | (2<<16);			//set GPIOF pins to alt. function mode
	GPIOE->OSPEEDR |= (2<<6);					//set speeds to high
	GPIOF->OSPEEDR |= (2<<18) | (2<<16);
	GPIOE->AFRL |= (6<<12);					  	//set to alt. function 6 for pins 4, 5, and 6
	GPIOF->AFRH |= (6<<4) | (6<<0);
	RCC->APB2ENR |= (1<<22);					//enable SAI peripheral clock

	/* Set SAI1 Block A to Transmit mode */
	// Protocol mode and Master Transmit set on Reset
	SAI1->ACR1 |= (4<<5) | (1<<9) | (2<<20);		//set to 16 bit mode
													//set MCKDIV to 2 for bit clock
													//set strobe to falling edge
	SAI1->ACR1 &= ~(1<<6);
	SAI1->ACR2 |= (4<<0);							//set FIFO thresh. to full
	SAI1->AFRCR |= (1<<16) | (15<<8) | 31;			//set frame size to 32 bits (16 left and 16 right) and
													//enable frame sync for I2S Protocol
	SAI1->ASLOTR |= (65535<<16) | (1<<8) | (1<<6);	//set number of slots to 2 and
													//set slot size to 16 bits

	/* Set SAI1 block B to Receive mode */
	// Protocol mode set on Reset
	SAI1->BCR1 |= (1<<0);							//set to master receive mode
	SAI1->BCR1 |= (4<<5) | (1<<9) | (2<<20);		//set to 16 bit mode
													//set MCKDIV to 2 for bit clock
													//set strobe to falling edge
	SAI1->BCR1 &= ~(1<<6);
	SAI1->BCR2 |= (4<<0);							//set FIFO thresh. to full
	SAI1->BFRCR |= (1<<16) | (15<<8) | 31;			//set frame size to 32 bits (16 left and 16 right) and
													//enable frame sync for I2S Protocol
	SAI1->BSLOTR |= (65535<<16) | (1<<8) | (1<<6);	//set number of slots to 2 and
													//set slot size to 16 bits

	/* Enable SAI1 and DMA For SAI1  */
	DMA2->S1CR |= (1<<0);	//Enable DMA Stream 1
	DMA2->S0CR |= (1<<0);	//Enable DMA Stream 0
	SAI1->ACR1 |= (1<<17);	//enable DMA on SAI1_A
	SAI1->BCR1 |= (1<<17);	//enable DMA on SAI1_B
	SAI1->ACR1 |= (1<<16);	//enable SAI1_A
	SAI1->BCR1 |= (1<<16);	//enable SAI1_B
}
