#ifndef UART_H_
#define UART_H_


#define BAUDRATE 115200
#define BAUD_PRESCALLER ((F_CPU+BAUDRATE*8UL) / (16UL*BAUDRATE)-1)


#define UART_RX_BUF_SIZE 32 // rx buffer size
#define UART_RX_BUF_MASK ( UART_RX_BUF_SIZE - 1)

#define UART_TX_BUF_SIZE 16
#define UART_TX_BUF_MASK ( UART_TX_BUF_SIZE - 1)
void UART_init(void);
void UART_sendc(unsigned char data);
unsigned char UART_getc();
void UART_sendstr(char *str);
//void UART_sendstr_P(const char *str);
void UART_sendint(int value);
void UART_sendlint(long int value);
void UART_sendUTF(uint32_t data);




#endif /* UART_H_ */
