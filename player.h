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

#ifndef PLAYER_H__
#define PLAYER_H__

#include <msp430.h>

#define STRUM_SILENCE 1

/**
 * @brief Classe permettant de faire jouer des notes sur un MSP430
 * Usage : Utiliser une des méthodes pour jouer une chanson
 * Format d'une chanson :	
 *		Note :	<Note>[#]<Octave>
 *				<Note> : note parmis les lettres de "a" à "c"
 *						 en majuscule ou minuscule
 *						 [#] : optionnel, joue la note en version dies
 *						 <Octave> : octave de la note (0 à 9)
 *												
 *		Silence : < > (1 espace)
 * 
 * Exemple : "A#3a2f4 b#3 b2b2 B1B1B1"
 */
class Player
{
public:
	/**
	 * Constructeur
	 * Initialise les fréquence des notes
	 */
	Player();

	/**
	 * Dtor
	 */
	~Player();

	/**
	 * Joue une chanson une fois
	 * @param song chanson
	 */
	void PlayOnce(const char* song);

	/**
	 * Joue une chanson en boucle
	 * @param song chanson
	 */
	void PlayLoop(const char* song);
	
	void SetNoteLenght(unsigned int l);

private:
	/**
	* Delay de un cycle machine
	* 16000 cycle par milliseconde
	* @param  cycles  Nombre de cycles
	*/
	void DelayCycles(unsigned int cycles);

	/**
	* Silence
	* @param time temps en millisecondes du silence
	*/
	void Silence(unsigned int time);

	/**
	* Joue une note pendant un certain temps
	* @param freq fréquence à jouer
	* @param time durée de la note
	*/
	void PlayNoteFreq(unsigned int freq, unsigned int time);

	/**
	* Joue une note continue
	* @param freq fréquence de la note
	*/
	void PlayNoteConstFreq(unsigned int freq);

	/**
	* Joue une note définie (petit silence à la fin)
	* @param freq fréquence de la note
	*/
	void PlayNoteStrumFreq(unsigned int freq);

	/**
	* Modifie une fréquence avec un octave
	* octave positif monte d'un octave (note plus aigue)
	* octave négatif descend d'un octave (note plus grave)
	* @param freq fréquence à modifier
	* @param octave nombre d'octave
	*/
	unsigned int ApplyOctave(unsigned int freq, int octave);

	/**
	 * Joue une note
	 * majuscule = continue
	 * minuscule = strum
	 * notes : C, D, E, F, G, A, B
	 * @param note Note à jouer parmis les notes
	 * @param isDies Si la note est dies
	 * @param octave Octave de la note (0 à 9)
	 */
	void PlayNote(char note, bool isDies, int octave);
	
	/**
	 * Joue une chanson
	 * @param song chanson
	 */
	void PlaySong(const char* song);

private:
	/// Tableau contenant les fréquences des notes
	int m_notes[12];
	unsigned int m_noteLenght;
};

#endif
