/*
 * EA_DOGM163L-A.c
 * This is a library for the EA DOGM163L Display connectet via spi
 *
 *  Created on: 01.02.2014
 *      Author: Toni Bartsch
 */


#include<util/delay.h>
#include<stdlib.h>
#include<avr/interrupt.h>


#define DISPLAY_RS_low  (PORTB &= ~ (1<<PB0))
#define DISPLAY_RS_high (PORTB |= (1<<PB0))
#define DISPLAY_CSB_low  (PORTB &= ~ (1<<PB2))
#define DISPLAY_CSB_high (PORTB |= (1<<PB2))

void spiInit();
void spi_write_instruction (char instruction);
void spi_write_char(char data);
void spi_write_string(char *string);
void display_set_row(uint8_t row);
void display_clear();
void display_return_home();
void display_contrast(uint8_t contrast);
void DOGM163_init();

/*Note: MOSI and SCK and SS are automatically set as output by init funktion */


//first call spiInit();
//then DOGM163_init();
