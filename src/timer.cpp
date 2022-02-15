#include "timer.h"

void timers::initt0(void) {
    frequency = 1;
    cli();
    TIMSK2 = (TIMSK2 & B11111110) | 0x01;
    TCCR2B = (TCCR2B & B11111000) | 0x02;
    sei(); //enable global interrupts
}

float timers::getFrequencyt0(void) {
    return frequency;
}

void timers::setFrequencyt0(float freq) {
    frequency = freq;
}

