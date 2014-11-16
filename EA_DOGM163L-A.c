#include"EA_DOGM163L-A.h"

//waits until SPIF flag in SPSR register is set
#define WAIT_FOR_SPIF_FLAG 	while (!(SPSR&(1<<SPIF)))

/**Initialization of the SPI for display*/
void spiInit(){
	DDRB |= (1<<PB3) | (1<<PB5);	// MOSI + SCK as Outputs
	SPCR  = (1<<SPE) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR1);
	SPSR |= (1<<SPI2X);
	DISPLAY_RS_DDR 	|= 1<<DISPLAY_RS_PIN;
	DISPLAY_CSB_DDR |= 1<<DISPLAY_CSB_PIN;
}

/**write data over spi*/
static void spi_transmit(char data){
	_delay_us(27);
	unsigned char sreg;
	sreg = SREG;
	/* Disable interrupts */
	cli();
	SPDR = data;
	WAIT_FOR_SPIF_FLAG;
	/* Restore global interrupt flag */
	SREG = sreg;
	_delay_us(27);
}

void spi_write_instruction (char instruction){
	DISPLAY_CSB_low;
	DISPLAY_RS_low;
	spi_transmit(instruction);
	DISPLAY_CSB_high;
}

void spi_write_char(char data){
	DISPLAY_RS_high;
	DISPLAY_CSB_low;
	spi_transmit(data);
	DISPLAY_CSB_high;
}

//not testet
void spi_write_string(char *string){
	while(*string){
		spi_write_char(*string);
		string++;
	}
}

//not ready
void display_set_row(uint8_t row){
	if(row==0){
		spi_write_instruction(0x80);
	}else if(row==1){
		spi_write_instruction(0x80+0x10);
	}else if(row==2){
		spi_write_instruction(0x80+0x20);
	}
}

void display_clear(){
	spi_write_instruction(0x01);
	_delay_us(1080);
}

void display_return_home(){
	spi_write_instruction(0x02);
	_delay_us(1080);
}


void display_contrast(uint8_t contrast){
	contrast = contrast & 0x0F;		//use only the 4 least significant bits
	contrast = contrast | 0b01110000;
	spi_write_instruction(contrast);
}

/**initialize DOGM163; 3 lines*/
void DOGM163_init(){
	_delay_ms(200);
	DISPLAY_CSB_low;
	DISPLAY_RS_low;
	spi_write_instruction(0x39);		//Funktion Set
	_delay_ms(1);
	spi_write_instruction(0x15);		//Bias Set
	_delay_ms(1);
	spi_write_instruction(0x5F);		//50
	_delay_ms(1);
	spi_write_instruction(0x69);		//6C
	_delay_ms(1);
	spi_write_instruction(0x7F);		//7C
	_delay_ms(1);
	spi_write_instruction(0x38);


	_delay_ms(200);		//>200ms
	spi_write_instruction(0x0C);		//display on; cursor off; cursor position off
	_delay_ms(1);
	display_clear();
	spi_write_instruction(0x06);
	_delay_ms(1);
	DISPLAY_CSB_high;
}

