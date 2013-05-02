#include <msp430.h>

int notes[7];

void DelayCycles(unsigned int ms)
{
	while(ms--)
		__delay_cycles(1);
		
}

void Silence()
{
	P1OUT &= ~BIT0;
	P1OUT &= ~BIT3;
	int time = 250;
	while(time--) {
		DelayCycles(3000);
	}
	P1OUT |= BIT3;
}

void PlayNoteFreq(unsigned int freq)
{
	int time = 250;
	while(time--) {
		P1OUT ^= BIT0;
		P1OUT ^= BIT3;
		DelayCycles(freq);
	}
}

void PlayNote(char note)
{
	if(note == 'A')
	{
		PlayNoteFreq(notes[3]);
	}
	else if(note == 'B')
	{
		PlayNoteFreq(notes[4]);
	}
	else if(note == 'C')
	{
		PlayNoteFreq(notes[5]);
	}
	else if(note == 'D')
	{
		PlayNoteFreq(notes[6]);
	}
	else if(note == 'E')
	{
		PlayNoteFreq(notes[0]);
	}
	else if(note == 'F')
	{
		PlayNoteFreq(notes[1]);
	}
	else if(note == 'G')
	{
		PlayNoteFreq(notes[2]);
	}
	else if(note == ' ')
	{
		Silence();
	}	
}

void PlaySong(char* song)
{
	while(*song)
	{
		PlayNote(*song);
		song++;
	}
}

int main()
{
	// Desactiver le watchdod
	WDTCTL = WDTPW + WDTHOLD;
	
	// frequence de 16 mhz
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;
	
	// PARAMS CHANGE MOI!
	unsigned int addOctave = 0;
	unsigned int removeOctave = 2;
	
	// calcul octaves
	unsigned int addFacteur = 1 << addOctave;
	unsigned int removeFacteur = 1 << removeOctave;
	// valeurs en delay
	notes[0] = removeFacteur * 3033 / 4 / addFacteur; // E 2637
	notes[1] = removeFacteur * 2864 / 4 / addFacteur; // F 2793
	notes[2] = removeFacteur * 2551 / 4 / addFacteur; // G 3135
	notes[3] = removeFacteur * 2272 / 4 / addFacteur; // A 3520
	notes[4] = removeFacteur * 2024 / 4 / addFacteur; // B 3951
	notes[5] = removeFacteur * 1911 / 4 / addFacteur; // C 4186
	notes[6] = removeFacteur * 1702 / 4 / addFacteur; // D 4698
	
	// P1.0 est une sortie
	P1DIR |= BIT0;
	P1DIR |= BIT3;
	
	P1OUT |= BIT3;
	P1OUT &= ~BIT0;
	
	while(true) {
		PlaySong("EEECEGGCGEABAGEGAFGE CDBCGEABA GEGAFGECDB GFFDEGACACDGFFECC G");
	}
}