// atmega328p
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h"



int main(){
	sei();

	while(1){
		UART_sendc('f');
	}
}

