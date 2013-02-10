/*
 * uart.c
 *
 * Created: 7-2-2013 16:49:47
 *  Author: Koen Beckers
 */ 
#include <avr/interrupt.h>

#include "Headers/config.h"
#include "Headers/uart.h"

FILE  uart_str= FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

unsigned char recvByte[UART_BUFFER_SIZE];
int	recvTotal;

void init_uart(void) {
#if F_CPU < 2000000UL && defined(U2X0)
  UCSR0A = _BV(U2X0);             // improve baud rate error by using 2x clk 
  UBRR0L = (F_CPU / (8UL * UART_BAUD)) - 1;
#else
  UBRR0L = (F_CPU / (16UL * UART_BAUD)) - 1;
#endif

	//UBRR0L = 51;
	//UBRRL = 129;
	//UBRR0L = 64;
	UCSR0B = _BV(TXEN0); /* tx/rx/RX Interrupt enable */
	
	stdout = stderr = &uart_str; //So that we can use printf() to print to our UART
}

int uart_putchar(const char c, FILE *stream) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}
void uart_putB(const char c){
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

int uart_getchar(FILE *stream){
	return 0;
}

char bufferContainsData(void){
	return recvTotal;
}

char readBuffer(const uint8_t pntr){
	if(pntr == recvTotal){
		recvTotal = 0;
	}
	
	return recvByte[pntr];
}


ISR(USART0_RX_vect ){
	recvTotal++;
	recvByte[recvTotal] = UDR0;
}

