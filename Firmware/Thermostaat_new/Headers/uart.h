/*
 * uart.h
 *
 * Created: 7-2-2013 16:48:52
 *  Author: Koen Beckers
 */ 


#ifndef UART_H_
#define UART_H_

#define UART_BUFFER_SIZE	40

extern FILE uart_str;

extern void	init_uart(void);
extern int	uart_putchar(const char c, FILE *stream);
extern int	uart_getchar(FILE *stream);
extern char	bufferContainsData(void);
extern char	readBuffer(const uint8_t pntr);
extern void	uart_putB(const char c);



#endif /* UART_H_ */