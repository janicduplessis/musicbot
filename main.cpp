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
	
	Player p;
	p.PlayLoop(mario);

	while(1);
}