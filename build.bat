del leds.elf
msp430-g++ -mmcu=msp430g2553 -O2 -Wall -g -c -o main.o main.cpp
msp430-g++ -mmcu=msp430g2553 -o leds.elf main.o
del *.o
mspdebug rf2500 "prog leds.elf"
pause