// simple UART library
// atmega328p
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "UART.h"

enum {locked, unlocked};
volatile uint8_t interrupt_init_semaphore0 = unlocked;

// data
volatile uint8_t UART_RxHead; // first bit
volatile uint8_t UART_RxTail; // last bit

volatile char UART_RxBuf[UART_RX_BUF_SIZE];
volatile char UART_TxBuf[UART_TX_BUF_SIZE];

volatile uint8_t UART_TxHead;
volatile uint8_t UART_TxTail;

void UART_init(void){
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8); // set baud rate
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0); // enable reciver and transmiter
	UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01)); // 8bit data, 1bit stop
}

void UART_sendc(unsigned char data) {
	UART_TxBuf[UART_TxTail] = data;
	UART_TxTail = (UART_TxTail + 1) & UART_TX_BUF_MASK;
	while(UART_TxHead == UART_TxTail); // do something

	if(interrupt_init_semaphore0 == unlocked){
		interrupt_init_semaphore0 = locked;
		UDR0 = UART_TxBuf[UART_TxHead]; // interrupt
	}
}

unsigned char UART_getc() {
	register char temp = 0; // register - fast access to variable

    temp = (UART_RxHead == UART_RxTail) ? 0 : UART_RxBuf[UART_RxHead];
    if(UART_RxHead != UART_RxTail)
    	UART_RxHead = (UART_RxHead+1) & UART_RX_BUF_MASK;
    return temp;
}


// for vt100 purposes
void UART_sendUTF(uint32_t data){
	for(int8_t i = 16; i >= 0; i-=8){
		UART_sendc(data>>i);
	}
}

void UART_sendstr(char *str){ // z RAM na UART
  register char c;
  while ((c = *str++)) UART_sendc(c);
}

void UART_sendint(int value){
	char string[17];
	UART_sendstr(itoa(value, string, 10)); // base 10
}

void UART_sendlint(long int data){
	char buf[33];
		UART_sendstr( ltoa(data, buf, 10) );
}

//void UART_sendstr_P(const char *str){ // RAM to UART
//	register char c;
//	while ( c = pgm_read_byte(str++)) UART_sendstr(c);
//}

ISR(USART_TX_vect) {
	UART_TxHead = (UART_TxHead + 1) & UART_TX_BUF_MASK; // new index for head
	if(UART_TxHead != UART_TxTail) // check
		UDR0 = UART_TxBuf[UART_TxHead];
	else
		interrupt_init_semaphore0 = unlocked;

}

ISR(USART_RX_vect)  {
    register char rx_temp;
    rx_temp = UDR0;

    if(UART_RxHead != (UART_RxTail+1)){ // check if full
    	if((rx_temp != '\r') && (rx_temp != '\n')){
    		UART_RxBuf[UART_RxTail] = rx_temp;//txt
    		UART_RxTail = (UART_RxTail+1) & UART_RX_BUF_MASK;
        }
        if(rx_temp == '\r'){
        	UART_RxBuf[UART_RxTail] = 0; // null
			UART_RxTail = (UART_RxTail+1) & UART_RX_BUF_MASK;
        }
    }
}
