//*********************************************************************
//* Pragmas for high and low interrupts.							  *
//*																	  *
//* Written by Zachary Lang                                           *
//* January 12, 2015                                               	  *
//*********************************************************************

// High Interrupt //

#pragma code high_vector=0x08		// ORG 08 which is where the high priority
void high_interrupt()				// interrupts are executed.
{									
	high_interrupt_routine();
}

// Low Interupt //

#pragma code low_vector=0x18		// ORG 18 which is where low priority
void low_interrupt()				// interrupts are executed.
{
	low_interrupt_routine();
}

