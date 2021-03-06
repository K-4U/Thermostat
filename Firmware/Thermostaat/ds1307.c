/*
 * ds1307.c
 *
 * Created: 24-10-2011 14:56:01
 *  Author: Koen Beckers
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <compat/twi.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "headers/structs.h"
#include "headers/uart.h"
#include "headers/main.h"


#define MAX_TRIES	50

#define DS1307_ID    0xD0        // I2C DS1307 Device Identifier
#define DS1307_ADDR  0x00        // I2C DS1307 Device Address

#define I2C_START 0
#define I2C_DATA 1
#define I2C_DATA_ACK 2
#define I2C_STOP 3
#define ACK 1
#define NACK 0

// DS1307 Register Address
// Second: ds1307_addr[0]
// Minute: ds1307_addr[1]
// Hour  : ds1307_addr[2]
// Day   : ds1307_addr[3]
// Date  : ds1307_addr[4]
// Month : ds1307_addr[5]
// Year  : ds1307_addr[6]

#define HOUR_24 0
#define HOUR_12 1

char ds1307_addr[7];
char sdigit[3]={'0','0','\0'};
char hour_mode, ampm_mode;


/* START I2C Routine */
unsigned char i2c_transmit(unsigned char type) {
	switch(type) {
		case I2C_START:    // Send Start Condition
			TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
			break;
		case I2C_DATA:     // Send Data with No-Acknowledge
			TWCR = (1 << TWINT) | (1 << TWEN);
			break;
		case I2C_DATA_ACK: // Send Data with Acknowledge
			TWCR = (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
			break;
		case I2C_STOP:     // Send Stop Condition
			TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
			return 0;
	}

	// Wait for TWINT flag set on Register TWCR
	while (!(TWCR & (1 << TWINT)));

	// Return TWI Status Register, mask the prescaller bits (TWPS1,TWPS0)
	return (TWSR & 0xF8);
	}

char i2c_start(unsigned int dev_id, unsigned int dev_addr, unsigned char rw_type){
	unsigned char n = 0;
	unsigned char twi_status;
	char r_val = -1;

	i2c_retry:
	if (n++ >= MAX_TRIES) return r_val;

	// Transmit Start Condition
	twi_status=i2c_transmit(I2C_START);

	// Check the TWI Status
	if (twi_status == TW_MT_ARB_LOST) goto i2c_retry;
	if ((twi_status != TW_START) && (twi_status != TW_REP_START)) goto i2c_quit;

	// Send slave address (SLA_W)
	TWDR = (dev_id & 0xF0) | (dev_addr & 0x07) | rw_type;

	// Transmit I2C Data
	twi_status=i2c_transmit(I2C_DATA);

	// Check the TWSR status
	if ((twi_status == TW_MT_SLA_NACK) || (twi_status == TW_MT_ARB_LOST)) goto i2c_retry;
	if (twi_status != TW_MT_SLA_ACK) goto i2c_quit;

	r_val=0;

	i2c_quit:
	return r_val;
}

void i2c_stop(void){
	unsigned char twi_status;

	// Transmit I2C Data
	twi_status=i2c_transmit(I2C_STOP);
}

char i2c_write(char data){
	unsigned char twi_status;
	char r_val = -1;

	// Send the Data to I2C Bus
	TWDR = data;

	// Transmit I2C Data
	twi_status=i2c_transmit(I2C_DATA);

	// Check the TWSR status
	if (twi_status != TW_MT_DATA_ACK) goto i2c_quit;

	r_val=0;

	i2c_quit:
	return r_val;
}

char i2c_read(char *data,char ack_type){
	unsigned char twi_status;
	char r_val = -1;               

	printf("i2c_read\r\n");
	if (ack_type) {
	// Read I2C Data and Send Acknowledge
		printf("acking\r\n");
		twi_status=i2c_transmit(I2C_DATA_ACK);
		
		printf("I2c status: %i\r\n",twi_status);
		if (twi_status != TW_MR_DATA_ACK) goto i2c_quit;
	} else {
	// Read I2C Data and Send No Acknowledge
		twi_status=i2c_transmit(I2C_DATA);

		if (twi_status != TW_MR_DATA_NACK) goto i2c_quit;
	}

	// Get the Data
	*data=TWDR;
	r_val=0;

	i2c_quit:
	return r_val;
}

// Convert Decimal to Binary Coded Decimal (BCD)
char dec2bcd(char num){
	return ((num/10 * 16) + (num % 10));
}

// Convert Binary Coded Decimal (BCD) to Decimal
char bcd2dec(char num){
	return ((num/16 * 10) + (num % 16));
}

void Read_DS1307(void){
	char data;
	// First we initial the pointer register to address 0x00
	// Start the I2C Write Transmission
	//printf("Starting i�C\r\n");
	i2c_start(DS1307_ID,DS1307_ADDR,TW_WRITE);

	// Start from Address 0x00
	//printf("Writing 0 as address\r\n");
	i2c_write(0x00);

	//printf("Stopping the write\r\n");
	// Stop I2C Transmission
	i2c_stop();

	// Start the I2C Read Transmission
	//printf("Starting the read\r\n");
	i2c_start(DS1307_ID,DS1307_ADDR,TW_READ);

	// Read the Second Register, Send Master Acknowledge
	//printf("Reading seconds\r\n");
	i2c_read(&data,ACK);
	ds1307_addr[0] = bcd2dec(data & 0x7F);
	currentDateTime.seconds=ds1307_addr[0];

	// Read the Minute Register, Send Master Acknowledge
	//printf("Reading minutes\r\n");
	i2c_read(&data,ACK);
	ds1307_addr[1] = bcd2dec(data);
	currentDateTime.minute= ds1307_addr[1];

	// Read the Hour Register, Send Master Acknowledge
	//printf("Reading hours\r\n");
	i2c_read(&data,ACK);
	if ((data & 0x40) == 0x40) {
		hour_mode = HOUR_12;
		ampm_mode=(data & 0x20) >> 5;   // ampm_mode: 0-AM, 1-PM
		ds1307_addr[2] = bcd2dec(data & 0x1F);
		currentDateTime.hours= ds1307_addr[2];
	} else {
		hour_mode = HOUR_24;
		ampm_mode=0;
		ds1307_addr[2] = bcd2dec(data & 0x3F);
		currentDateTime.hours=ds1307_addr[2];
	}

	// Read the Day of Week Register, Send Master Acknowledge
	//printf("Reading Day of week\r\n");
	i2c_read(&data,ACK);
	ds1307_addr[3] = bcd2dec(data);
	currentDateTime.day=ds1307_addr[3];

	// Read the Day of Month Register, Send Master Acknowledge
	i2c_read(&data,ACK);
	ds1307_addr[4] = bcd2dec(data);
	currentDateTime.date = ds1307_addr[4];

	// Read the Month Register, Send Master Acknowledge
	i2c_read(&data,ACK);
	ds1307_addr[5] = bcd2dec(data);
	currentDateTime.month=ds1307_addr[5];

	// Read the Year Register, Send Master No Acknowledge
	i2c_read(&data,NACK);
	ds1307_addr[6] = bcd2dec(data);
	currentDateTime.year=ds1307_addr[6];
	// Stop I2C Transmission
	i2c_stop();
}

void Write_DS1307(dateTime *toWrite){
	unsigned char i, hour_format;
	ds1307_addr[0] = toWrite->seconds;
	ds1307_addr[1] = toWrite->minute;
	ds1307_addr[2] = toWrite->hours;
	ds1307_addr[3] = toWrite->day;
	ds1307_addr[4] = toWrite->date;
	ds1307_addr[5] = toWrite->month;
	ds1307_addr[6] = toWrite->year;
	
	currentDateTime = *toWrite;

	// Make sure we enable the Oscillator control bit CH=0 on Register 0x00
	ds1307_addr[0]=ds1307_addr[0] & 0x7F;

	// Start the I2C Write Transmission
	i2c_start(DS1307_ID,DS1307_ADDR,TW_WRITE);

	// Start from Address 0x00
	i2c_write(0x00);

	// Write the data to the DS1307 address start at 0x00
	// DS1307 automatically will increase the Address.
	for (i=0; i<7; i++) {
		if (i == 2) {
			hour_format=dec2bcd(ds1307_addr[i]);

			if (hour_mode) {
				hour_format |= (1 << 6);
				if (ampm_mode)
					hour_format |= (1 << 5);
				else
					hour_format &= ~(1 << 5);
			} else {
				hour_format &= ~(1 << 6);
			}

			i2c_write(hour_format);
		} else {
			i2c_write(dec2bcd(ds1307_addr[i]));
		}
	}

	// Stop I2C Transmission
	i2c_stop();
}

// Implementing integer value from 00 to 99
char *num2str(char number){
	unsigned char digit;     

	digit = '0';                       // Start with ASCII '0'
	while(number >= 10)                // Keep Looping for larger than 10
	{
		digit++;                         // Increase ASCII character
		number -= 10;                    // Subtract number with 10
	}

	sdigit[0]='0';                     // Default first Digit to '0'
	if (digit != '0')
		sdigit[0]=digit;                 // Put the Second digit

	sdigit[1]='0' + number;
	return sdigit;
}
