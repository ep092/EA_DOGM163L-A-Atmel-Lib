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


#define DISPLAY_RS_low   (DISPLAY_RS_PORT &= ~(1<<DISPLAY_RS_PIN))
#define DISPLAY_RS_high  (DISPLAY_RS_PORT |= (1<<DISPLAY_RS_PIN))

#define DISPLAY_CSB_low  (DISPLAY_CSB_PORT &= ~(1<<DISPLAY_CSB_PIN))
#define DISPLAY_CSB_high (DISPLAY_CSB_PORT |= (1<<DISPLAY_CSB_PIN))

void spiInit(void);
void spi_write_instruction (char instruction);
void spi_write_char(char data);
void spi_write_string(char *string);
void display_set_row(uint8_t row);
void display_clear(void);
void display_return_home(void);
void display_contrast(uint8_t contrast);
void DOGM163_init(void);

/*Note: MOSI, SCK,SS and RS are automatically set as output by init funktion */


//first call spiInit();
//then DOGM163_init();