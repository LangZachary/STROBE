/*************************************************************************************
 *                                  Memory											 *
 *************************************************************************************/

/*  Root function for processing Program Memory saves and loads.
 */
void strobe_mem(unsigned char mem_process, static unsigned char *trigger)
{
	static unsigned char	ms_adc_enable = 0;

	

	// Variable passed into the function decides which process is completed.
	// 1 - Manual Save Initialization.
	// 2 - Manual Initialization.
	// 3 - MS General Operation.
	// 4 - Manual General Operation.
	// 5 - MS Deinitialization.
	// 6 - Manual Deinitialization.
	switch (mem_process) {

		case mem_manual_save_init:	{

										} break;

		case mem_manual_save_run:	{

										} break;	
	}
}															

/*	Memory Read Command.
 *	This function will read a bit from the EEPROM and return it.  Before the read begins the
 *	function waits util the EEPROM is ready for a read command.
 *	eeprom_addh -		High byte for the EEPROM address. Only the 2 LSB are read.
 *  eeprom_addl -		Low byte for the EEPROM address.
 */
unsigned char mem_read(unsigned char mem_addh, unsigned char mem_addl)
{

	EEADRH = mem_addh;		// Point to the read address in mem.
	EEADR = mem_addl;

	EECON1bits.EEPGD = 0;		// Point to mem.
	EECON1bits.CFGS = 0;

	EECON1bits.RD = 1;			// Initiate Read.

	Nop();

	return EEDATA;
}

/*	EEPROM Write Command.
 *	This function will write a byte to EEPROM. Before the write begins the function waits
 *	until the EEPROM is ready for a write command. During the write sequence interrupts are
 *  disabled to prevent undesired operation.
 *  eeprom_data -		Byte to be saved to the EEPROM.
 *  eeprom_addh -		High byte for the EEPROM address. Only the 2 LSB are read.
 *	eeprom_addl	-		Low byte for the EEPROM address.
 */
void mem_write(unsigned char mem_data, unsigned char mem_addh, unsigned char mem_addl)
{
	// Test for Ready Step.
	while (EECON1bits.WR);
	while (EECON1bits.RD);

	// Write Step.
	EEADRH = mem_addh;		// Point to the save address in EEPROM.
	EEADR = mem_addl;

	EEDATA = mem_data;		// Store the data to be written.

	EECON1bits.EEPGD = 0;		// Point to EEPROM.
	EECON1bits.CFGS = 0;

	EECON1bits.WREN = 1;		// Enable write options.
	
	INTCONbits.GIE = 0;			// Disable interrupts for the write sequence.

	EECON2 = 0x55;				// Special write sequence.
	EECON2 = 0xAA;

	EECON1bits.WR = 1;			// Initiate the write.

	INTCONbits.GIE = 1;			// Enable interrupts after write sequence.

}

