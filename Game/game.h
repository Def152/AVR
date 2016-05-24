/*
 * game.h
 *
 *  Created on: 8 lut 2015
 *      Author: Karol
 */


#ifndef GAME_H_
#define GAME_H_

typedef uint8_t u08;
typedef uint16_t u16;

// leds
#define LED1 (1<<PD0)
#define LED2 (1<<PD1)
#define LED3 (1<<PD2)
#define LED4 (1<<PD3)
#define LED5 (1<<PD4)

#define LED1_TOG PORTD ^= (1<<PD0)
#define LED2_TOG PORTD ^= (1<<PD1)
#define LED3_TOG PORTD ^= (1<<PD2)
#define LED4_TOG PORTD ^= (1<<PD3)
#define LED5_TOG PORTD ^= (1<<PD4)

#define LED1_ON PORTD &= ~(1<<PD0)
#define LED2_ON PORTD &= ~(1<<PD1)
#define LED3_ON PORTD &= ~(1<<PD2)
#define LED4_ON PORTD &= ~(1<<PD3)
#define LED5_ON PORTD &= ~(1<<PD4)

#define LED1_OFF PORTD |= (1<<PD0)
#define LED2_OFF PORTD |= (1<<PD1)
#define LED3_OFF PORTD |= (1<<PD2)
#define LED4_OFF PORTD |= (1<<PD3)
#define LED5_OFF PORTD |= (1<<PD4)

// keys
#define KEY1 (1<<PC1)
#define KEY2 (1<<PC2)
#define KEY3 (1<<PC3)
#define KEY4 (1<<PC4)
#define KEY5 (1<<PC5)
// buzzer
#define BUZZ (1<<PC0)
#define BUZZ_TOG PORTC ^= (1<<PC0) // buzzer on


#endif /* GAME_H_ */
