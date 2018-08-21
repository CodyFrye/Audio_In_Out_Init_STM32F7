/*
 * File :	stm32f7.h
 * Brief:	Register defines for the stm32f767zi
 * 			microcontroller
 * Note:	This File Only defines the registers
 * 			that were used for initialization.
 * 			Modifying or adding on to the template
 * 			involving other peripherals will require
 * 			further defining of the peripheral address
 */

#ifndef STM32F7_H
#define STM32F7_H

/*--------- RCC Clock Registers -------------*/
typedef struct
{
	/*----Registers----*/			/* Mem. Addr. offset */
	unsigned long CR;				//0x00
	unsigned long PLLCFGR;			//0x04
	unsigned long CFGR;				//0x08
	unsigned long CIR;				//0x0c
	unsigned long AHB1RSTR;			//0x10
	unsigned long AHB2RSTR;			//0x14
	unsigned long AHB3RSTR;			//0x18
	const unsigned long Reserved_1;	//0x1c
	unsigned long APB1RSTR;			//0x20
	unsigned long APB2RSTR;			//0x24
	const unsigned long Reserved_2;	//0x28
	const unsigned long Reserved_3;	//0x2c
	unsigned long AHB1ENR;			//0x30
	unsigned long AHB2ENR;			//0x34
	unsigned long AHB3ENR;			//0x38
	const unsigned long Reserved_4;	//0x3c
	unsigned long APB1ENR;			//0x40
	unsigned long APB2ENR;			//0x44
	const unsigned long Reserved_5;	//0x48
	const unsigned long Reserved_6;	//0x4c
	unsigned long AHB1LPENR;		//0x50
	unsigned long AHB2LPENR;		//0x54
	unsigned long AHB3LPENR;		//0x58
	const unsigned long Reserved_7;	//0x5c
	unsigned long APB1LPENR;		//0x60
	unsigned long APB2LPENR;		//0x64
	const unsigned long Reserved_8;	//0x68
	const unsigned long Reserved_9;	//0x6c
	unsigned long BDCR;				//0x70
	unsigned long CSR;				//0x74
	const unsigned long Reserved_10;//0x78
	const unsigned long Reserved_11;//0x7c
	unsigned long SSCGR;			//0x80
	unsigned long PLLI2SCFGR;		//0x84
	unsigned long PLLSAICFGR;		//0x88
	unsigned long DCKCFGR1;			//0x8c
	unsigned long DCKCFGR2;			//0x90
}clock_Typedef;
#define RCC ((clock_Typedef *)(0x40023800))
/*-------------------------------------------*/

/*-------------- GPIO Registers ------------------*/
typedef struct
{
	/*----Registers----*/		/* Mem. Addr. offset */
	unsigned long MODER;		//0x00
	unsigned long OTYPER;		//0x04
	unsigned long OSPEEDR;		//0x08
	unsigned long PUPDR;		//0x0c
	unsigned long IDR;			//0x10
	unsigned long ODR;			//0x14
	unsigned long BSRR;			//0x18
	unsigned long LCKR;			//0x1c
	unsigned long AFRL;			//0x20
	unsigned long AFRH;			//0x24

}GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)(0x40020000))
#define GPIOB ((GPIO_TypeDef *)(0x40020400))
#define GPIOC ((GPIO_TypeDef *)(0x40020800))
#define GPIOD ((GPIO_TypeDef *)(0x40020c00))
#define GPIOE ((GPIO_TypeDef *)(0x40021000))
#define GPIOF ((GPIO_TypeDef *)(0x40021400))
#define GPIOG ((GPIO_TypeDef *)(0x40021800))
#define GPIOH ((GPIO_TypeDef *)(0x40021c00))
#define GPIOI ((GPIO_TypeDef *)(0x40022000))
#define GPIOJ ((GPIO_TypeDef *)(0x40022400))
#define GPIOK ((GPIO_TypeDef *)(0x40022800))
/*------------------------------------------------*/

/*-------------- UART Registers ------------------*/
typedef struct
{
	unsigned long CR1;
	unsigned long CR2;
	unsigned long CR3;
	unsigned long BRR;
	unsigned long GTPR;
	unsigned long RTOR;
	unsigned long RQR;
	unsigned long ISR;
	unsigned long ICR;
	unsigned long RDR;
	unsigned long TDR;
} USART_typeDef;
#define USART3 ((USART_typeDef *)(0x40004800))
/*-----------------------------------------------*/

/*-------------- SAI1 Registers --------------*/
typedef struct
{
	unsigned long GCR;
	unsigned long ACR1;
	unsigned long ACR2;
	unsigned long AFRCR;
	unsigned long ASLOTR;
	unsigned long AIM;
	unsigned long ASR;
	unsigned long ACLRFR;
	unsigned long ADR;
	unsigned long BCR1;
	unsigned long BCR2;
	unsigned long BFRCR;
	unsigned long BSLOTR;
	unsigned long BIM;
	unsigned long BSR;
	unsigned long BCLRFR;
	unsigned long BDR;
} SAI_typeDef;
#define SAI1 ((SAI_typeDef *)(0x40015800))
/*-------------------------------------------*/

/*-------------------DMA Registers------------------*/
typedef struct
{
	/*--- Registers ---*/	/* Mem. Addr. offset */
	unsigned long LISR;		//0x00
	unsigned long HISR;		//0x04
	unsigned long LIFCR;	//0x08
	unsigned long HIFCR;	//0x0c
	/* Stream 0 */
	unsigned long S0CR;		//0x10
	unsigned long S0NDTR;	//0x14
	unsigned long S0PAR;	//0x18
	unsigned long S0M0AR;	//0x1c
	unsigned long S0M1AR;	//0x20
	unsigned long S0FCR;	//0x24
	/* Stream 1 */
	unsigned long S1CR;		//0x28
	unsigned long S1NDTR;	//0x2c
	unsigned long S1PAR;	//0x30
	unsigned long S1M0AR;	//0x34
	unsigned long S1M1AR;	//0x38
	unsigned long S1FCR;	//0x3c
	/* Stream 2 */
	unsigned long S2CR;		//0x40
	unsigned long S2NDTR;	//0x44
	unsigned long S2PAR;	//0x48
	unsigned long S2M0AR;	//0x4c
	unsigned long S2M1AR;	//0x50
	unsigned long S2FCR;	//0x54
	/* Stream 3 */
	unsigned long S3CR;		//0x58
	unsigned long S3NDTR;	//0x5c
	unsigned long S3PAR;	//0x60
	unsigned long S3M0AR;	//0x64
	unsigned long S3M1AR;	//0x68
	unsigned long S3FCR;	//0x6c
	/* Stream 4 */
	unsigned long S4CR;		//0x70
	unsigned long S4NDTR;	//0x74
	unsigned long S4PAR;	//0x78
	unsigned long S4M0AR;	//0x7c
	unsigned long S4M1AR;	//0x80
	unsigned long S4FCR;	//0x84
	/* Stream 5 */
	unsigned long S5CR;		//0x88
	unsigned long S5NDTR;	//0x8c
	unsigned long S5PAR;	//0x90
	unsigned long S5M0AR;	//0x94
	unsigned long S5M1AR;	//0x98
	unsigned long S5FCR;	//0x9c
	/* Stream 6 */
	unsigned long S6CR;		//0xa0
	unsigned long S6NDTR;	//0xa4
	unsigned long S6PAR;	//0xa8
	unsigned long S6M0AR;	//0xac
	unsigned long S6M1AR;	//0xb0
	unsigned long S6FCR;	//0xb4
	/* Stream 7 */
	unsigned long S7CR;		//0xb8
	unsigned long S7NDTR;	//0xbc
	unsigned long S7PAR;	//0xc0
	unsigned long S7M0AR;	//0xc4
	unsigned long S7M1AR;	//0xc8
	unsigned long S7FCR;	//0xcc
}DMA_typeDef;
#define DMA1 ((DMA_typeDef *)(0x40026000))
#define DMA2 ((DMA_typeDef *)(0x40026400))
/*--------------------------------------------------*/

#endif
