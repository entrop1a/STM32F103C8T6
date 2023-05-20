/*
 *	UART functions
 *
 *	File: uart.c
 *
 *	Author: Eduardo Gomes
 *
 */

//_________________ Library _________________________________________
//___________________________________________________________________

#include "uart.h"


//_________________ Development of functions ________________________
//___________________________________________________________________


void init_uart2(void){

	// Pin configuration

	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;				//Enable clock to USART2
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;				//Enable clock to GPIOA

	GPIOA -> CRL |=   GPIO_CRL_MODE2_1 | GPIO_CRL_MODE2_0; 		// Set PA2(TX) as OUTPUT
	GPIOA -> CRL |=   GPIO_CRL_CNF2_1; 				// Set PA2(TX) as alternate Push-pull
	GPIOA -> CRL &= ~(GPIO_CRL_CNF2_0);

	GPIOA -> CRL &= ~(GPIO_CRL_MODE3_1 |  GPIO_CRL_MODE3_0); 	// Set PA2(TX) as INPUT
	GPIOA -> CRL &= ~(GPIO_CRL_CNF3_1); 				// Set PA2(TX) as floating input
	GPIOA -> CRL |=   GPIO_CRL_CNF3_0;


	// Definitions of UART2

	USART2 -> CR1 = 0x00;			//Reset state CR1

	USART2 -> CR1 |= USART_CR1_UE		// Enable USART
		      |  USART_CR1_TE		// Enable TX
		      |  USART_CR1_RE;		// Enable RX

	USART2 -> CR1 &= ~(USART_CR1_M);	// Determine => [1 start bit, 8 data bits, n stop bit]


	// Boud rate Configuration

	/*
	 * BAUD = f_ck/(16*USARTDIV)
	 * 9600 = 8 MHz/(16*USARTDIV)
	 * USARTDIV = 52,083
	 *
	 * DIV_MANTISSA = 0d52 ; DIV_FRACTION = 16*0,083 = 1,33 ~= 0d1
	 * BRR = (DIV_MANTISSA << 4) | (DIV_FRACTION) = 0d833
	 * BRR = 0x341
	 *
	 * */

	USART2 -> BRR = 0x341; // Define baud rate = 9600

} //End init_uart2()


void TX_uart2(uint8_t byte){

	while(!(USART2 -> SR & USART_SR_TXE)); // Check transmission occurrence
	USART2 -> DR = byte;

} //End TX_uart2()


uint16_t RX_uart2(){

	while(!(USART2 -> SR & USART_SR_RXNE));
	return USART2 -> DR;

} // RX_uart()
