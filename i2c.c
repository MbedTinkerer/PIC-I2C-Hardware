/*
 * File Name: i2c.c
 * Author	: Siddharth Chandrasekaran
 * Website	: http://embedjournnal.com/
 * Created on July 20, 2012, 6:12 PM
*/

#include <p18f4520.h>

void i2c_start(void)						// Initiate a Start sequence
{
	TRISCbits.TRISC3=1;						// Define the pin as input
	TRISCbits.TRISC4=1;						// Define the pin as input
	PIR1bits.SSPIF=0;
	SSPCON2bits.SEN=1;	
	while(PIR1bits.SSPIF==0);				// Wait till SSP Interrupt flag is set
	return;
}


void i2c_restart(void)						// Initiate a Restart sequence
{
	PIR1bits.SSPIF=0;
	SSPCON2bits.RSEN=1;						// Initiate Restart
	while(PIR1bits.SSPIF==0);				// Wait till SSP Interrupt flag is set
	return;
}

void i2c_device(unsigned char slave)		// device specification
{
	PIR1bits.SSPIF=0;
	SSPBUF=slave;							// Slave address
	while(PIR1bits.SSPIF==0);				// Wait till SSP Interrupt flag is set
	while(SSPCON2bits.ACKSTAT==1);			// Wait for ACK from slave
	return;
}


void i2c_write(unsigned int data)			// Write data to slave.
{
	PIR1bits.SSPIF=0;
	SSPBUF=data;							// Load dat into SSPBUF
	while(PIR1bits.SSPIF==0);				// Wait till SSP Interrupt flag is set
	return;
}

void i2c_stop(void)							//Initiate a Stop sequence.
{
	PIR1bits.SSPIF=0;
	SSPCON2bits.PEN=1;						// Initiate a Stop Sequence
	while(PIR1bits.SSPIF==0);				// Wait till SSP Interrupt flag is set
	TRISCbits.TRISC3=0;						// Redefine the pin as output.
	TRISCbits.TRISC4=0;						// Redefine the pin as output.
	return;
}

unsigned int i2c_read(void)					//Read data from I2C bus.
{
	unsigned int r;
	PIR1bits.SSPIF=0;
	SSPCON2bits.RCEN=1;						

	while(PIR1bits.SSPIF==0);				// Wait till SSP Interrupt flag is set
	r=SSPBUF;								// Read data from SSPBUF
	PIR1bits.SSPIF=0;
	SSPCON2bits.ACKEN=1;					// Initiate ACK sequence
	while(PIR1bits.SSPIF==0);				// Wait till SSP Interrupt flag is set
	return r;
}

