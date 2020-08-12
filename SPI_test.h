/*
 * SPI_test.h
 *
 * Created: 09-08-2020 8.25.46 AM
 *  Author: molla
 */ 


#ifndef SPI_TEST_H_
#define SPI_TEST_H_

static enum _PORTS {A = 1, B, C};
typedef enum _PORTS _PORT;

void SPI_MasterInit(_PORT p, unsigned int mosi_pin, unsigned int sck_pin,unsigned int clock_rate)
{
	/* Set MOSI and SCK output, all others input */
	switch(p)
	{
		case A:
		DDRA = (1<<mosi_pin)|(1<<sck_pin);
		break;
		case B:
		DDRB = (1<<mosi_pin)|(1<<sck_pin);
		break;
		case C:
		DDRC = (1<<mosi_pin)|(1<<sck_pin);
		break;
	}
	//DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_SlaveInit(_PORT p, unsigned int miso_pin, unsigned int sck_pin)
{
	/* Set MOSI and SCK output, all others input */
	switch(p)
	{
		case A:
		DDRA = (1<<miso_pin);
		break;
		case B:
		DDRB = (1<<miso_pin);
		break;
		case C:
		DDRC = (1<<miso_pin);
		break;
	}
	/* Enable SPI */
	SPCR = (1<<SPE);
}
char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
}

void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}


#endif /* SPI_TEST_H_ */