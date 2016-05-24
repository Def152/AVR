/*
 * main.c
 *
 *  Created on: 8 lut 2015
 *      Author: Karol
 */

/*
 * Simple arcade game
 * The task is to press the button after led flashes
 * You have 100ms to press the button :P
 * */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include "game.h"


volatile u08 pressed;
u16 tmo;
u08 rnd;
u08 attempts=3;
u08 max_err;
u08 score;


void Led_off(){
	PORTD |= LED1|LED2|LED3|LED4|LED5;
}

ISR(PCINT1_vect){
	if(!(PINC & KEY1)) {
		pressed = 1;
		LED1_OFF;
	}
	if(!(PINC & KEY2)){
		pressed = 2;
		LED2_OFF;
	}
	if(!(PINC & KEY3)){
		pressed = 3;
		LED3_OFF;
	}
	if(!(PINC & KEY4)){
		pressed = 4;
		LED4_OFF;
	}
	if(!(PINC & KEY5)){
		pressed = 5;
		LED5_OFF;
	}
}

void Buz_win(){
	for(int i = 0; i < 5; i++){
		BUZZ_TOG;
		_delay_ms(50);
	}
}
void Start(){
	while(1){
		//Led_off();
		LED1_TOG; LED2_TOG; LED3_TOG; LED4_TOG; LED5_TOG;
		_delay_ms(1000);
		if(pressed){
			break;
		}
	}
	Led_off();
}

int main() {

	// output leds
	DDRD |= LED1|LED2|LED3|LED4|LED5;
	Led_off();
	DDRC |= BUZZ;
	PORTC |= BUZZ_TOG;
	// vcc pull up
	PORTC |= KEY1|KEY2|KEY3|KEY4|KEY5;


	PCICR |= (1<<PCIE1);
	PCMSK1 |= KEY1|KEY2|KEY3|KEY4|KEY5; // PCINT9-PCINT13 pins
	sei();
	//u08 a = 0;
	attempts = 0;
	pressed = 0;
	max_err = 0;

	while(1){
		Start();
		Led_off();
		_delay_ms(5000);

		attempts = 0;
		while(attempts < 3){
			_delay_ms(1000);
			pressed = 0;
			rnd =  (rand() % 5);
					switch(rnd){
						case 0: LED1_ON; break;
						case 1: LED2_ON; break;
						case 2: LED3_ON; break;
						case 3: LED4_ON; break;
						case 4: LED5_ON; break;
					}
					tmo = 0;
					while(!pressed){
						_delay_ms(10);
						tmo++;
						if(tmo > 100){
							break;
						}
					}

			if(pressed == rnd+1){
				score++;
			}
			else attempts++;


			Led_off();
		}
	}



	return 0;
}



