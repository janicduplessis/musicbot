del leds.elf
msp430-gcc -mmcu=msp430g2553 -O2 -Wall -g -c -o main.o main.cpp
msp430-gcc -mmcu=msp430g2553 -O2 -Wall -g -c -o player.o player.cpp
msp430-gcc -mmcu=msp430g2553 player.o main.o -o leds.elf
del *.o
mspdebug rf2500 "prog leds.elf"
pause