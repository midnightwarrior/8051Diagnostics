// Project 1 - Embedded Systems Design
// Developed by midnightlabs
// Matthew Bridle, Reece Browne, Sam Stichbury
// Project started 5 March 2014
// This version v15.03b05a

#include <compiler_defs.h>
#include <c8051f020_defs.h>
#include <stdio.h>
#include <lcd.h>

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------
sbit LED_16 = P1 ^ 6;	//-- green LED on P1.6


// Function prototypes
void initPorts(void);
void main(void);
void vanityText(void);

//------------------------------------------------------------------------------------
// init
//------------------------------------------------------------------------------------
// general initialization for the development board
//
//
void initPorts(void)
{
	WDTCN = 0x07;		// Watchdog Timer Control Register
	WDTCN = 0xDE;		// Disable watch dog timer
	WDTCN = 0xAD;

	OSCXCN = 0x67;	  				// EXTERNAL Oscillator Control Register   
	while ((OSCXCN & 0x80) == 0);	// wait for xtal to stabilize

	OSCICN = 0x0C;					// Internal Oscillator Control Register

	//---- Configure the Crossbar Registers
	XBR0 = 0x00;
	XBR1 = 0x00;
	XBR2 = 0x40;		  	// Enable the crossbar, weak pullups enabled
	// XBR2 = 0xC0;			// To disable weak pull-ups 

	//---- Port configuration (1 = Push Pull Output, 0 = Open Drain)
	P0MDOUT = 0x00;			// Output configuration for P0 
	P1MDOUT = 0x40;			// Output configuration for P1 (Push-Pull for P1.6) 
	P2MDOUT = 0x00;			// Output configuration for P2 
	P3MDOUT = 0x00;			// Output configuration for P3 

	//---- Set up Ports 7-4 I/O Lines
	P74OUT = 0x48;	// Output configuration for P4-7
					// (P7[0:3] Push Pull) - Control Lines for LCD
					// (P6 Open-Drain)- Data Lines for LCD
					// (P5[7:4] Push Pull) - 4 LEDs
					// (P5[3:0] Open Drain) - 4 Push-Button Switches (input)
					// (P4 Open Drain) - 8 DIP Toggle Switches (input)

	//---- Write a logic 1 to those pins which are to be used for input operations
	P5 |= 0x0F;
	P4 = 0xFF;
}

// The stuff that this thing does with other things

void main(void) {
	EA = 0;			//-- disable global interrupts
	initPorts();	//-- iniatialise development board
	lcd_init();
	P5 = 0x0F;		//-- turn off the four green LEDs on Port 5[7:4]
	//lcd_init();	//-- call this function to initialise LCD
	EA = 1;			//-- enable global interrupts

	while (1)
	{
		//-- add your code here
		lcd_goto(0x80);
		printf("SiLabs C8051F020");
		lcd_goto(0x40);
		printf("Diagnostic Tool ");
		huge_delay(100);
		lcd_goto(0x80);
		printf("**midnightlabs**");
		lcd_goto(0x40);
		printf("v15.04b05a      ");
		huge_delay(100); 
		lcd_goto(0x80);
		printf("All your base   ");
		lcd_goto(0x40);
		printf("are belong to us");
		huge_delay(100);
	}
}

