#include "player.h"


Player::Player()
{
	// Valeurs en decalage
	// d = 2 000 000 / H
	//		    d    note  valeur en hertz
	notes[0] =	955; // C  2093
	notes[1] =	851; // D  2349 
	notes[2] =	758; // E  2637 
	notes[3] =	716; // F  2793 
	notes[4] =	637; // G  3135
	notes[5] =	568; // A  3520 
	notes[6] =	506; // B  3951
	notes[7] =	902; // C# 2217
	notes[8] =	803; // D# 2489
	notes[9] =	675; // F# 2959
	notes[10] = 602; // G# 3322
	notes[11] = 536; // A# 3729

	// P1.0 est une sortie
	P1DIR |= BIT0;
	P1DIR |= BIT3;

	P1OUT |= BIT3;
	P1OUT &= ~BIT0;
}

Player::~Player()
{

}

void Player::PlayOnce(const char* song)
{
	PlaySong(song);
}

void Player::PlayLoop(const char* song)
{
	while(true) {
		PlaySong(song);
	}
}

void Player::DelayCycles(unsigned int ms)
{
	while(ms--)
		__delay_cycles(1);
		
}

void Player::Silence(unsigned int time)
{
	P1OUT &= ~BIT0;
	P1OUT &= ~BIT3;
	while(time--) {
		DelayCycles(16000);
	}
	P1OUT |= BIT3;
}

void Player::PlayNoteFreq(unsigned int freq, unsigned int time)
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

void Player::PlayNoteConstFreq(unsigned int freq)
{
	PlayNoteFreq(freq, NOTE_LENGHT);
}

void Player::PlayNoteStrumFreq(unsigned int freq)
{
	PlayNoteFreq(freq, NOTE_LENGHT - STRUM_SILENCE);
	Silence(STRUM_SILENCE);
}

unsigned int Player::ApplyOctave(unsigned int freq, int octave)
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

void Player::PlayNote(char note, bool isDies, int octave)
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

void Player::PlaySong(const char* song)
{
	char* songPtr = (char*)song;
	while(*songPtr)
	{
		if(*songPtr == ' ') {
			Silence(NOTE_LENGHT);
			songPtr++;
		}
		else if(*(songPtr + 1) == '#') {
			PlayNote(*songPtr, true, (int)(*(songPtr + 2) - '0'));
			songPtr += 3;
		}
		else
		{
			PlayNote(*songPtr, false, (int)(*(songPtr + 1) - '0'));
			songPtr += 2;
		}
	}
}

