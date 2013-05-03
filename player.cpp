/**********************************************************************************
	Copyright (C) 2013  TechInfo Cegep de Saint-Hyacinthe

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************************/

#include "player.h"


Player::Player()
{
	// Valeurs en decalage
	// d = 2 000 000 / H
	//		    d    note  valeur en hertz
	m_notes[0] =	955; // C  2093
	m_notes[1] =	851; // D  2349 
	m_notes[2] =	758; // E  2637 
	m_notes[3] =	716; // F  2793 
	m_notes[4] =	637; // G  3135
	m_notes[5] =	568; // A  3520 
	m_notes[6] =	506; // B  3951
	m_notes[7] =	902; // C# 2217
	m_notes[8] =	803; // D# 2489
	m_notes[9] =	675; // F# 2959
	m_notes[10] = 602; // G# 3322
	m_notes[11] = 536; // A# 3729

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
			PlayNoteConstFreq(ApplyOctave(m_notes[7], octave)); //C#: 
		else
			PlayNoteConstFreq(ApplyOctave(m_notes[0], octave)); //C: 
	}
	
	//RE
	else if(note == 'D')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(m_notes[8], octave)); //D#
		else
			PlayNoteConstFreq(ApplyOctave(m_notes[1], octave)); //D
	}
	
	//MI
	else if(note == 'E')
	{
		PlayNoteConstFreq(ApplyOctave(m_notes[2], octave));//E
	}
	//FA
	else if(note == 'F')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(m_notes[9], octave));//F#
		else
			PlayNoteConstFreq(ApplyOctave(m_notes[3], octave));//F
	}
	
	//SOL
	else if(note == 'G')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(m_notes[10], octave));//G#
		else
			PlayNoteConstFreq(ApplyOctave(m_notes[4], octave));//G
	}
	
	//LA
	else if(note == 'A')
	{
		if(isDies)
			PlayNoteConstFreq(ApplyOctave(m_notes[11], octave));//A#
		else
			PlayNoteConstFreq(ApplyOctave(m_notes[5], octave));//A
	}
	//SI
	else if(note == 'B')
	{
		PlayNoteConstFreq(ApplyOctave(m_notes[6], octave));//B
	}
	
	// Strum notes
	//DO
	else if(note == 'c')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(m_notes[7], octave)); //C#: 
		else
			PlayNoteStrumFreq(ApplyOctave(m_notes[0], octave)); //C: 
	}
	
	//RE
	else if(note == 'd')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(m_notes[8], octave)); //D#
		else 
			PlayNoteStrumFreq(ApplyOctave(m_notes[1], octave)); //D
	}

	//MI
	else if(note == 'e')
	{
		PlayNoteStrumFreq(ApplyOctave(m_notes[2], octave));//E
	}
	//FA
	else if(note == 'f')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(m_notes[9], octave));//F#
		else
			PlayNoteStrumFreq(ApplyOctave(m_notes[3], octave));//F
	}
	
	//SOL
	else if(note == 'g')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(m_notes[10], octave));//G#
		else
			PlayNoteStrumFreq(ApplyOctave(m_notes[4], octave));//G
	}
	
	//LA
	else if(note == 'a')
	{
		if(isDies)
			PlayNoteStrumFreq(ApplyOctave(m_notes[11], octave));//A#
		else
			PlayNoteStrumFreq(ApplyOctave(m_notes[5], octave));//A
	}
	//SI
	else if(note == 'b')
	{
		PlayNoteStrumFreq(ApplyOctave(m_notes[6], octave));//B
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

