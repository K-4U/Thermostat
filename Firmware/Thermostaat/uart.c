#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "headers/uart.h"

unsigned char recvByte[UART_BUFFER_SIZE];
int						recvTotal;

void uart_init(void) {

#if F_CPU < 2000000UL && defined(U2X)
  //UCSRA = _BV(U2X);             // improve baud rate error by using 2x clk 
  //UBRR0L = (F_CPU / (8UL * UART_BAUD)) - 1;
#else
  //UBRR0L = (F_CPU / (16UL * UART_BAUD)) - 1;
#endif

	UBRR0L = 51;
	//UBRRL = 129;
	UCSR0B = _BV(TXEN0); /* tx/rx/RX Interrupt enable */
}

/*
 * Send character c down the UART Tx, wait until tx holding register
 * is empty.
 */
int uart_putchar(char c, FILE *stream) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}

void uart_putB(char c){
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

int uart_getchar(FILE *stream){
	return 0;
}

char bufferContainsData(void){
	return recvTotal;
}

char readBuffer(int pntr){
	if(pntr == recvTotal){
		recvTotal = 0;
	}
	
	return recvByte[pntr];
}


ISR(USART_RX_vect){
	recvTotal++;
	recvByte[recvTotal] = UDR0;
}

