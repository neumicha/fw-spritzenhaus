/*
 * fw-spritzenhaus.c
 *
 * Created: 24.07.2016 17:13:54
 * Author : Michael
 */ 

#define F_CPU 8000000UL //8 MHz

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define an(port,b) (port) |= (1<<(b))
#define aus(port,b) (port) &= ~(1<<(b))


volatile uint8_t windows; //8 Bit, je 1 = Fenster steht noch
volatile uint8_t ausgeloest; //Auf 1 wenn ausgeloest und noch nicht resettet


int main(void) {

	//Eing�nge und Ausg�nge definieren
	
		//Eing�nge Spritzenhaus
			DDRD = 0; //DDRD als Eingang
			PORTD = 0xFF; //PORTD Pullups an
		//Ausg�nge LEDs
			DDRB = 0xFF; //DDRB als Ausgang
		//Bereit-/Resetknopf (setzt ausgeloest zur�ck)
			DDRC &= ~(1<<PC0); //PC0 als Eingang f�r Resetknopf
			PORTC |= (1<<PC0); //PC Pullup an
		//Ausg�nge Peripherie
			DDRC |= (1<<PC1); //Relaisausgang f�r Horn
			DDRC |= (1<<PC2); //Relaisausgang f�r Blaulicht
			DDRC |= (1<<PC3); //LED-ausgang f�r Status/Bereit-LED
	
	//Boot-LED-Test
		//Reset
			PORTC |= (1<<PC3);
			_delay_ms(500);
			PORTC &= ~(1<<PC3);
		//Feuer-Anzeige-LEDs
			uint8_t i=0;
			PORTB = 1;
			do {
				_delay_ms(500);
				PORTB = PORTB << 1;
				i++;
			} while (i<8);
	
	//Vorbelegung Variablen
		windows = 255; //Anfangs alle Fenster stehend - erster ISR-Aufruf aktualisiert das
		ausgeloest = 1; //Zu Beginn muss Reset gedr�ckt werden
	
	//Timer f�r Abfrage der Feuer
	
		//Timer 0 konfigurieren
			TCCR0 |= (1<<CS00)|(1<<CS02);   // Timer 0 mit Prescaler 1024
		//Overflow Interrupt erlauben
			TIMSK |= (1<<TOIE0);
			//(3686400/1024)/256 Hz = 14,0625Hz
			//bzw.  1/14,0625 s = 71,1 ms
	
		//Interrupts einschalten
			sei();

	while (1) {
		PORTB = windows; //Umgefallene Feuer auf LEDs ausgeben
		if ((ausgeloest == 0) && (windows==0)) { //Alle Feuer umgefallen
			ausgeloest = 1;
			PORTB = windows; //LEDs erneut setzen, da sonst evtl. letzte LED noch leuchtet 

			//Peripherie schalten
				//Song abspielen
				PORTC |= (1<<PC1);
				_delay_ms(250);
				PORTC &= ~(1<<PC1);
				//Blauchlicht an
				_delay_ms(500);
					PORTC |= (1<<PC2);
				//Blaulicht aus
					_delay_ms(9750);
					PORTC &= ~(1<<PC2);

			//Sirene und Blaulicht wieder aus
		}
	}
}

ISR (TIMER0_OVF_vect) {
	
	if (ausgeloest == 0) { //Wenn Schaltung scharf (noch nicht ausgel�st), verUNDe Eing�nge, damit gefallene Feuer gefallen bleiben
		windows = windows & PIND;
	}
	else { //Schaltung inaktiv => Gebe tats�chlich gerade ausgelesene Werte aus
		windows = PIND;
		//Wenn aber alle Feuer aufgestellt, setze Schaltung aktiv
		if (PIND == 255) {
			ausgeloest = 0;
		}
	}
	
	//Wenn Resetknopf gedr�ckt, setze windows und ausgeloest zur�ck
	if ( !(PINC & (1<<PC0)) ) {
		windows = 255;
		ausgeloest = 0;
	}
	if (ausgeloest == 0) { //Wenn noch nicht ausgel�st, Status-LED an
		PORTC |= (1<<PC3);
	}
	else { //Wenn schon ausgel�st, Status-LED aus
		PORTC &= ~(1<<PC3);
	}
}

