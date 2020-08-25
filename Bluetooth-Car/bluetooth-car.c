//works with HC-05 Bluetooth Module by interfacing with 8051 uC.
#include<reg51.h>
sbit m1p = P2^0;		
sbit m1n = P2^1;
sbit m2p = P2^2;		//interfacing ports with L293D motor driver
sbit m2n = P2^3;
//motor input connections//
void main()
{
	unsigned char x;
	SCON = 0x50;	//initializing serial communication modes of operation.
	TMOD = 0x20; //timer 1 mode 2 
	TH1 = -3;	//setting baud rate to 9600
	TR1 = 1;	//start timer  //initialize serial communication
	while(1)
	{
		while(RI == 0);
		x = SBUF;						//receiving data from serial buffer 
		RI = 0;
		SBUF = x;
		while(TI == 0);	
		TI = 0;							// we're not transferring any data to serial buffer...
		if(x == 'f')
		{
			m1p = 1; m1n = 0;
			m2p = 1; m2n = 0;	//robot moves forward
		}
		if(x == 'b')
		{
			m1p = 0; m1n = 1;
			m2p = 0; m2n = 1;	//robot moves backwards
		}
		if(x == 'l')
		{
			m1p = 1; m1n = 0;
			m2p = 0; m2n = 1;	// turns left
		}
		if(x == 'r')
		{
			m1p = 0; m1n = 1;
			m2p = 1; m2n = 0;  //turns right
		}
		if(x == 's')
		{
			m1p = 0; m1n = 0;
			m2p = 0; m2n = 0;  //stop
		}
	}
}