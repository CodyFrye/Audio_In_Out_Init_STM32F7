/*
 * File : 	Main.c
 * Brief: 	main body file used in the process of initializing
 * 		  	the stm32f767zi microcontroller For audio Applications
 * 		  	@ a sampling rate of approximately 48KHz.
 */

#include "stm32f7.h"
#include "main.h"

void main()
{
	/*
	 * Audio Buffers:
	 * 		Set of Audio Buffers to take advantage of the DMA
	 * 		Double Buffer (Ping Pong) Feature.
	 */
	unsigned long BufferPingTx[128];
	unsigned long BufferPongTx[128];
	unsigned long BufferPingRx[128];
	unsigned long BufferPongRx[128];

	/*
	 * Initialize Clock:
	 * 		Enable HSE in Bypass mode			(+)
	 * 		Enable PLL @ 48MHz					(+)
	 * 		Enable SAI PLL (SAIPLLQ) @ 48Mhz	(+)
	 *
	 */
		RCC_Init();

	/*
	 *	Initialize DMA:
	 *		Param: 	PingTx -> addr. of Ping Transmit Buffer
	 *				PongTx -> addr. of Pong Transmit Buffer
	 *				PingRx -> addr. of Ping Receive Buffer
	 *				PongRx -> addr. of Pong Receive Buffer
	 *
	 *		Enable Double Buffer mode			(+)
	 *		Enable Circular buffer mode			(+)
	 *		Set Peripheral and Memory addresses	(+)
	 *		Set increment memory				(+)
	 *		Set Size to 128						(+)
	 *
	 */
		unsigned long *PingTx = BufferPingTx;
		unsigned long *PongTx = BufferPongTx;
		unsigned long *PingRx = BufferPingRx;
		unsigned long *PongRx = BufferPongRx;
		DMA_SAI_Init(PingTx, PongTx, PingRx, PongRx);

	/*
	 *
	 * Initialize SAI1:
	 * 		Block A -> Master Transmit	(+)
	 * 		Block B -> Master Receive	(+)
	 * 		16 Bit data size 			(+)
	 * 		2 slots 					(+)
	 * 		48 KHz sampling Rate		(+)
	 * 			error -> ~2%
	 *
	 *
	 */
		SAI1_Init();

	/*
	 *  LED to To Show Initialization was successful
	 *  Note: Does not show if initialization was set up properly
	 */
		RCC->AHB1ENR |= (1<<1);
		GPIOB->MODER |= (1<<14);
		GPIOB->ODR |= (1<<7);

		/* infinite loop */
		while(1)
		{
			/* Audio Bypass code */
			if(((DMA2->S1CR)&(1<<19)) == (1<<19))
			{
			  for (char i = 0; i<128; i++)
			  {
				  *PongTx++ = *PongRx++;
			  }

			  PongRx = BufferPongRx;
			  PongTx = BufferPongTx;
			}

			else
			{
			  for (char i = 0; i<128; i++)
			  {
				  *PingTx++ = *PingRx++;
			  }

			  PingRx = BufferPingRx;
			  PingTx = BufferPingTx;
			}
		}


}
