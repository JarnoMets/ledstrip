#include "audio.h"
#include "Arduino.h"


void audioManager::init(void) {
    pinMode(pMic, INPUT);
    neutral = analogRead(pMic);
}

int audioManager::read(void) {
    int result = analogRead(pMic);
    //Serial.println(neutral);
    return abs(result - neutral);
}

int audioManager::getVal(void) {
    return analogRead(pMic);
}


void audioManager::setNeutral(int n) {
    this->neutral = n;
}

void audioManager::sample(uint8_t * data, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) {
        *(data+i) = read();
    }
}

void audioManager::setDefaultPeak(int n) {
    this->defaultPeak = n;
}