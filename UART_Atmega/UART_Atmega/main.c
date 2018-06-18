#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void uart_emit (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));            // wait while register is free
	UDR = data;                             // load data in the register
}
unsigned char uart_recieve (void)
{
	while(!(UCSRA) & (1<<RXC));           // wait while data is being received
	return UDR;                             // return 8-bit data
}
void main (void)
{
	unsigned char a;
	DDRA=0xff;
	UBRRL=51;
	UCSRB|=(1<<TXEN)|(1<<RXEN)|(1<<RXCIE)|(1<<TXCIE);  //setting the proper values
	UCSRC|=(1<<UCSZ0)|(1<<UCSZ1);                     //data length is 8 bit.
	
	while(1)
	{
		a=uart_recieve();		//method to recieve the character
		if(a>48){
			uart_emit(a);
		a=0;}                   // save the received data in a variable
	}
}