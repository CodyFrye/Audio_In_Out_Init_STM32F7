/*
 * file :	DMA_Init.c
 * Brief:	Initialization of the DMA Peripheral for
 * 		access to the SAI Tx and Rx Data Registers
 */

#include "stm32f7.h"

#define SAI1_A_PERIPH_ADDR (0x40015800 + 0x20)
#define SAI1_B_PERIPH_ADDR (0x40015800 + 0x40)
#define BUFFER_SIZE 128

void DMA_SAI_Init(unsigned long* PingTx, unsigned long* PongTx, unsigned long* PingRx, unsigned long* PongRx)
{
	/*-----------------------------Enable DMA For SAI TX------------------------------*/
	RCC->AHB1ENR |= (1<<22);				//enable DMA2 Clock
	DMA2->S1CR &= ~(15<<25);				//set stream 1 to channel 0
	DMA2->S1CR |= (1<<10) | (1<<6) | (1<<13) | (1<<11);	//set direction mem. -> periph.,
								//enable memory increment mode,
								//set data size to 16 bit, and
								//set peripheral size to 32 bit
	DMA2->S1CR |= (1<<18) | (1<<8);				//enable double buffer and
								//enable circular buffer
	DMA2->S1NDTR = BUFFER_SIZE;				//set DMA size
	DMA2->S1PAR = SAI1_A_PERIPH_ADDR;			//Set Periph. Addr. to SAI1_A Data Register
	DMA2->S1M0AR = (unsigned long)PingTx;			//Set Address of Mem. Buffer 0
	DMA2->S1M1AR = (unsigned long)PongTx;			//Set Address of Mem. Buffer 1
	DMA2->S1FCR &= ~(1<<2);					//set FIFO to Full
	DMA2->S1FCR |= (2<<0);
	/*--------------------------------------------------------------------------------*/

	/*-----------------------------Enable DMA For SAI RX------------------------------*/
	DMA2->S0CR &=  ~(1<<6);					//set direction periph. -> mem.
	DMA2->S0CR |= (10<<25) |(1<<10) | (1<<13) | (1<<11);	//set stream 0 to channel 10,
								//enable memory increment mode,
								//set data size to 16 bit, and
								//set peripheral size to 16 bit
	DMA2->S0CR |= (1<<18) | (1<<8);				//enable double buffer
								//enable circular buffer
	DMA2->S0NDTR = BUFFER_SIZE;				//set DMA size
	DMA2->S0PAR = SAI1_B_PERIPH_ADDR;			//Set Periph. Addr. to SAI1_A Data Register
	DMA2->S0M0AR = (unsigned long)PingRx;			//Set Address of Mem. Buffer 0
	DMA2->S0M1AR = (unsigned long)PongRx;			//Set Address of Mem. Buffer 1
	DMA2->S0FCR &= ~(1<<2);					//Set FIFO to Full
	DMA2->S0FCR |= (2<<0);
	/*--------------------------------------------------------------------------------*/

	/*
	 * DMA Enables are in SAI_Init
	 */
}
