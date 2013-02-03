//#define F_CPU				8000000
#define UART_BAUD  			192000
#define UART_BUFFER_SIZE	40

void	uart_init(void);
int	uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);
char bufferContainsData(void);
char readBuffer(int pntr);
void uart_putB(char c);
