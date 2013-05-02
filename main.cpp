#include <msp430.h>

#define NOTE_LENGHT 30
#define STRUM_SILENCE 1

int notes[12];

/**
 * Delay de un cycle machine
 * 16000 cycle par milliseconde
 */
void DelayCycles(unsigned int ms)
{
	while(ms--)
		__delay_cycles(1);
		
}

/**
 * Silence
 * @param time temps en millisecondes du silence
 */
void Silence(unsigned int time)
{
	P1OUT &= ~BIT0;
	P1OUT &= ~BIT3;
	while(time--) {
		DelayCycles(16000);
	}
	P1OUT |= BIT3;
}

/**
 * Joue une note pendant un certain temps
 * @param freq fréquence à jouer
 * @param time durée de la note
 */
void PlayNoteFreq(unsigned int freq, unsigned int time)
{
	unsigned int ticks = 0;
	while(time) {
		P1OUT ^= BIT0;
		P1OUT ^= BIT3;
		DelayCycles(freq);
		ticks += freq;
		if(ticks >= 16000)
		{
			unsigned int div = ticks / 16000;
			ticks = ticks % 16000;
			time -= div;
		}
	}
}

/**
 * Joue une note continue
 * @param freq fréquence de la note
 */
void PlayNoteConstFreq(unsigned int freq)
{
	PlayNoteFreq(freq, NOTE_LENGHT);
}

/**
 * Joue une note définie (petit silence à la fin)
 * @param freq fréquence de la note
 */
void PlayNoteStrumFreq(unsigned int freq)
{
	PlayNoteFreq(freq, NOTE_LENGHT - STRUM_SILENCE);
	Silence(STRUM_SILENCE);
}

/**
 * Modifie une fréquence avec un octave
 * octave positif monte d'un octave (note plus aigue)
 * octave négatif descend d'un octave (note plus grave)
 * @param freq fréquence à modifier
 * @param octave nombre d'octave
 */
unsigned int ApplyOctave(unsigned int freq, int octave)
{
	if(octave >= 0) 
	{
		unsigned int facteur = 1;
		facteur <<= octave;
		return freq / facteur;
	}
	else
	{
		octave *= -1;
		unsigned int facteur = 1;
		facteur <<= octave;
		return freq * facteur;
	}
}

void PlayNote(char note, bool isDies, int octave)
{
	octave -= 5;
	//Notes continues
	//DO
	if(note == 'C')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(notes[7], octave)); //C#: 
		else
			PlayNoteConstFreq(ApplyOctave(notes[0], octave)); //C: 
	}
	
	//RE
	else if(note == 'D')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(notes[8], octave)); //D#
		else
			PlayNoteConstFreq(ApplyOctave(notes[1], octave)); //D
	}
	
	//MI
	else if(note == 'E')
	{
		PlayNoteConstFreq(ApplyOctave(notes[2], octave));//E
	}
	//FA
	else if(note == 'F')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(notes[9], octave));//F#
		else
			PlayNoteConstFreq(ApplyOctave(notes[3], octave));//F
	}
	
	//SOL
	else if(note == 'G')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(notes[10], octave));//G#
		else
			PlayNoteConstFreq(ApplyOctave(notes[4], octave));//G
	}
	
	//LA
	else if(note == 'A')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(notes[11], octave));//A#
		else
			PlayNoteConstFreq(ApplyOctave(notes[5], octave));//A
	}
	//SI
	else if(note == 'B')
	{
		PlayNoteConstFreq(ApplyOctave(notes[6], octave));//B
	}
	
	// Strum notes
	//DO
	else if(note == 'c')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(notes[7], octave)); //C#: 
		else
			PlayNoteStrumFreq(ApplyOctave(notes[0], octave)); //C: 
	}
	
	//RE
	else if(note == 'd')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(notes[8], octave)); //D#
		else 
			PlayNoteStrumFreq(ApplyOctave(notes[1], octave)); //D
	}
	
	//MI
	else if(note == 'e')
	{
		PlayNoteStrumFreq(ApplyOctave(notes[2], octave));//E
	}
	//FA
	else if(note == 'f')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(notes[9], octave));//F#
		else
			PlayNoteStrumFreq(ApplyOctave(notes[3], octave));//F
	}
	
	//SOL
	else if(note == 'g')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(notes[10], octave));//G#
		else
			PlayNoteStrumFreq(ApplyOctave(notes[4], octave));//G
	}
	
	//LA
	else if(note == 'a')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(notes[11], octave));//A#
		else
			PlayNoteStrumFreq(ApplyOctave(notes[5], octave));//A
	}
	//SI
	else if(note == 'b')
	{
		PlayNoteStrumFreq(ApplyOctave(notes[6], octave));//B
	}	
}

void PlaySong(char* song)
{
	while(*song)
	{
		if(*song == ' ') {
			Silence(NOTE_LENGHT);
			song++;
		}
		else if(*(song + 1) == '#') {
			PlayNote(*song, true, (int)(*(song + 2) - '0'));
			song += 3;
		}
		else
		{
			PlayNote(*song, false, (int)(*(song + 1) - '0'));
			song += 2;
		}
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
	unsigned int removeOctave = 0;
	
	// calcul octaves
	unsigned int addFacteur = 1 << addOctave;
	unsigned int removeFacteur = 1 << removeOctave;
	// valeurs en delay
	notes[0] = removeFacteur * 955 / addFacteur; // C 2093
	notes[1] = removeFacteur * 851 / addFacteur; // D 2349 
	notes[2] = removeFacteur * 758 / addFacteur; // E 2637 
	notes[3] = removeFacteur * 716 / addFacteur; // F 2793 
	notes[4] = removeFacteur * 637 / addFacteur; // G 3135
	notes[5] = removeFacteur * 568 / addFacteur; // A 3520 
	notes[6] = removeFacteur * 506 / addFacteur; // B 3951
	notes[7] = removeFacteur * 902 / addFacteur; //C# 2217
	notes[8] = removeFacteur * 803 / addFacteur; //D# 2489
	notes[9] = removeFacteur * 675 / addFacteur; //F# 2959
	notes[10] = removeFacteur * 602 / addFacteur; //G# 3322
	notes[11] = removeFacteur * 536 / addFacteur; //A# 3729
	
	// P1.0 est une sortie
	P1DIR |= BIT0;
	P1DIR |= BIT3;
	
	P1OUT |= BIT3;
	P1OUT &= ~BIT0;
	
	while(true) {
		PlaySong("e3e3 E3 c3e3 G3   G2   c3  g2  e2  a2 b2 A#2a2 G2e3 g3a3 f3g3 e3 c3d3b2        "); //  e3g3a3f3g3e3c3d3b3 
	}
}