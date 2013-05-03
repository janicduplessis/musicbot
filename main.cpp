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


#include <msp430.h>

#include "player.h"

int main()
{
	// Desactiver le watchdod
	WDTCTL = WDTPW + WDTHOLD;
	
	// frequence de 16 mhz
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;

	//Chansons!
	const char* mario = "e3e3 E3 c3e3 G3   G2   c3  g2  e2  a2 b2 A#2a2 G2e3 g3a3 f3g3 e3 c3d3b2        ";
	const char* pirate = "d2 d2d2 d2d2 d2d2d2d2d2 d2d2 d2d2 d2d2d2d2d2 d2d2 d2d2 d2 a2c3 d3 d3 d3e3f3 f3 f3g3 "
						 "e3 e3 d3c3c3e3 a2c3 d3 d3 d3e3f3 f3 f3g3 e3 e3 d3c3D3d3 a2c3 d3 d3 d3f3g3 g3 g3a3a#3 "
						 "a#3 a3g3a3d3 d3e3f3 f3 f3g3a3d3 d3f3e3 e3 f3d3e3  a3c4d4 d4 d4e4f4 f4 f4g4e4 e4 d4c4c4d4 "
						 "a3c4d4 d4 d4e4f4 f4 f4g4e4 e4 d4c4D4d4 a2c4d4 d4 d4f4g4 g4 g4a4 a#4 a#4 a4g4a4d4 d3e3f3 f3 "
						 "f3g3a3d3 d3f3e3 e3 d3c3d3 d3d3e3 f3 f3f3g3 A3a3 f3d3A2a2 A#3a#3 f3d3A#2a#2 d3a2 d3 e3  "
						 "f3g3a3 a3 a3 a#3a3 g3 g3 g3 g3a3  a3 a3 a3 a#3a3  g3 f3 e3 d3  d3e3F3f3 g3a3g3 f3 e3 f3 g3  "
						 "a3 g3  f3g3A3a3 g3f3e3 f3 e3 D3d3 e3c3 d4  d4e4f4 g4 a4 a#4 d4 g4 f4 g4e4 d4 e4c#4 A4a4 A#4a#4 "
						 "a4 a4 a4 a4g4  G4g4 F4f4 e4 f4 e4 d4 d3e3f3a3 d3e3f3a#3 d3e3f3a3 a3 a3c4a3g3  G3g3 F3f3 e3 f3 "
						 "d3e3 f3 d3e3 f3 e3 d3c#3d3f#3e3f#3g3f#3g3g#3g3g#3f3f3f3e3e3e3d3d3d3e3e3e3d4 a3A3a3 g3 f3g3 C4C4C4c4 "
						 "c4 E3E3E3e3 d3e3F3f3 d3c3d3f3e3c3d4 A3A3a3g3 f3g3 C4C4c4 a#3 a3a3 A#3A#3A#3a#3 f3g3A3a3 A3a3 a#3 D4D4d4c4"
						 "a#3c4 F3F3F3f3 a3 A4A4a4e4 d4e4 A3A3A3a3 a#3 D5D5d5c5 d5a4 D4d4 f4e4 d4d4 E4e4 c4d4 e4Dd4 D3D3D3D3D3d3  " 
						 "c3 d3 f3 e3 d3 c3 c3 D3D3d3      c3 d3 f3 e3 d3 c3 c3 D3D3D3D3d3      c3 d3 f3 e3 d3 c3 d3 E3E3E3E3e3  "
						 "c3 d3 f3 e3 d3 c3 D3d3 A2a2 F3f3F3f3E3e3 E3e3 D3d3 C3c3 D3d3 A2a2 C3c3 A3a3 G3g3 C4c4 E3e3E3e3C3c3 F3f3F3f3E3e3 "
						 "E3e3 D3d3 F3F3F3f3F3f3E3e3 E3E3E3e3E3e3E3e3D3d3 D3D3D3d3 a2d3a2d3a2d3a2d3a2d3a2d3a2d3a2d3a2d3a2d3a2d3a2d3D3D3D3d3";
	const char* tetris = "D4 b3c4d4 c4b3a3 a3c4e4 d4C4b3 c4d4 e4 c4 a3 a3a3b3c4 d4 f4a4 g4f4e4 c4e4 d4c4b3 b3c4d4 e4 c4 a3 a3  D4 b3c4d4"
						 " c4b3a3 a3c4e4 d4C4b3 c4d4 e4 c4 a3 a3a3b3c4 d4 f4a4 g4f4e4 c4e4 d4c4b3 b3c4d4 e4 c4 a3 a3   E4e4 C4c4 D4d4 B3b3 c4 e4 A4a4 G#4g#4    ";
	
	Player p;
	p.SetNoteLenght(32);
	p.PlayLoop(pirate);

	while(1);
}
