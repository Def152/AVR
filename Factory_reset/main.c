/*
 * main.c
 *
 *  Created on: 25 kwi 2015
 *      Author: Karol
 */
/* Can be used to provide (stored in internal avr memory) default data/settings
 * In case of factory reset (push button PD5) reset to default settings
 * */
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include "UART/UART.h"


#define LED_PIN (1<<PD6)
#define LED_TOG PORTD ^= LED_PIN

#define KEY1_PIN (1<<PD5)
#define LED_TOG PORTD ^= LED_PIN

// stored struct
typedef const struct{
	uint8_t led;
	uint8_t time_hh;
	uint8_t time_mm;
	uint8_t time_ss;
}CONFIG;
// reset to default
const CONFIG pgm_cfg PROGMEM = {20, 8, 20, 0}; // flash
CONFIG eem_cfg EEMEM; // eeprom
CONFIG ram_cfg; // ram



volatile uint8_t Timer1, Timer2;
uint8_t key_lock;

void load_defaults(){
	// copy ram to flash
	memcpy_P(&ram_cfg, &pgm_cfg, sizeof(pgm_cfg));
	// copy ram to eeprom
	eeprom_write_block(&ram_cfg, &eem_cfg, sizeof(ram_cfg));
}


void check_and_load_defaults(){
	uint8_t i = 0;
	uint8_t len = sizeof(ram_cfg);
	uint8_t *ptr = (uint8_t*)&ram_cfg; // set pointer at the start of structure
	// copy eeprom to ram
	eeprom_read_block(&ram_cfg, &eem_cfg, sizeof(ram_cfg));
	while(i < len){ // check if eeprom is zeroed
		if(0xff == *ptr++) // zeroed eeprom contains 0xff only
			continue;
		else
			return; // error, eeprom is storing data
		i++;
	}
	// finally get defaults values
	load_defaults();
}


int main(){

	// copy eeprom to ram
	eeprom_read_block(&ram_cfg, &eem_cfg, sizeof(ram_cfg));
	// copy ram to eeprom
	eeprom_write_block(&ram_cfg, &eem_cfg, sizeof(ram_cfg));
	// copy flash to ram
	memcpy_P(&ram_cfg, &pgm_cfg, sizeof(pgm_cfg));

	/* debug
	DDRD |= LED_PIN;
	DDRD &= ~KEY1_PIN;
	PORTD |= KEY1_PIN; // pull up
	*/

	TCCR0A |= (1<<WGM01); // CTC mode
	TCCR0B |= (1<<CS02)|(1<<CS00); // 1024 prescaller
	OCR0A = F_CPU/1024UL/100UL; //38;
	TIMSK0 |= (1<<OCIE0A); // enable Compare Match

	sei();
	UART_init();
	UART_sendstr("starting...");
	while(1){
		if(!Timer1){
			Timer1 = ram_cfg.led;
			LED_TOG;
		}
		if(!Timer2){
			Timer2 = 50;
			UART_sendstr("multi\r\n");
		}
		 if( !key_lock && !(PIND & KEY1_PIN ) ) {
		   key_lock=1;

		   // PRESS
		   UART_sendstr("Pressed");

		  }
		 else if( key_lock && (PIND & KEY1_PIN ) ) key_lock=0;
	}
// resetting watchdog
//	cli(); // disable interrupt
//	wdt_enable(0); // reset
//	while(1);


}

ISR(TIMER0_COMPA_vect){
	uint8_t n = Timer1;
	if(n) Timer1 = --n;
	n = Timer2;
	if(n) Timer2 = --n;
}

