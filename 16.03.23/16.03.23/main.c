#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

char lvLetter1[] = "Kocham pana nierodke ";

char lvLetter2[] = "Nie k";

char tablica[50];

void send(char *txt);

int main(void)
{
	//USART
    UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);		//Character-size = 8bit 
	UCSRB |= (1<<RXEN);								//Receiver enabled
	UCSRB |= (1<<TXEN);								//Transmitter enabled
	UBRRL = 12;										//9600 bps
	UCSRA |= (1<<U2X);
	
	DDRD &=~ (1<<PD0);								//ustawienie PD0 na wejœcie
	PORTD |= (1<<PD0);								//ustawienie pullup on
	
	DDRC |= (1<<PC5);								//led wyjscie
	
	
	//ADC
	ADMUX |= (1<<REFS0);							//AVCC voltage reference
													//kana³ pomiarowy ADC0
	ADCSRA |= (1<<ADEN);							//ADC enable
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1);				//preskaler 8													

	while (1) 
    {
		
		if(!(PIND & (1<<PD0)))
		{
			PORTC |= (1<<PC5);
			sprintf(tablica, "sjkdfhskdjf s%d dfjhskjf", 123);
			send(tablica);
		} 
		else	PORTC &=~ (1<<PC5);	
	
		ADCSRA |=(1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		
		
		sprintf(tablica, "wynik: %d\r\n", ADC);
		send(tablica);
		
	}
}						

void send(char *txt)
{
	while(*txt != 0)
	{
		UDR	=	*txt++;
		_delay_ms(2);
	}
}