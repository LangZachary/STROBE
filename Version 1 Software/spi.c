




// This function sends the data in the spi_command structure out the data
// line to the OLED. The first bit send is RS, then RW, then the command byte
// starting with the MSB.  The SPI unit is turned off while the command is sent
// and turned back on after the command is sent. The chip select line is made active
// low before the command is sent and returned high after the command is sent.
void spi_send_command(void)
{
	while (!oled_ready);
	SSP1CON1bits.SSPEN = 0;	// Turn off the SPI Module
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	scs1 = 0;				// Set Chip Select low to start transmission.
	Nop();
	Nop();
	sck1 = 0;				// Set clock low to get ready to clock data in.
	sdo1 = rs;				// Send RS out the data line.
	Nop();
	Nop();
	sck1 = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = rw;				// Send RW out the data line.
	Nop();
	Nop();
	sck1 = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = spi_data.b7;
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = spi_data.b6;
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = spi_data.b5;
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = spi_data.b4;
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = spi_data.b3;
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = spi_data.b2;
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = spi_data.b1;
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	Nop();
	Nop();
	sck1 = 0;
	sdo1 = spi_data.b0;
	Nop();
	Nop();
	sck1 = 1;
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	scs1 = 1;
	SSP1CON1bits.SSPEN = 1;	// Turn on the SPI Module
	oled_ready = 0;
	
}

