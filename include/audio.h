#ifndef audio_h
#define audio_h

#define pMic A1

#include "Arduino.h"
#include "bluetooth.h"

class audioManager {
    private:
        int neutral = 615;
    
    protected:
        int defaultPeak = 50;
        float treshold = 0.8;

    public:
        void init(void);

        void setNeutral(int);
        int getNeutral();

        void setDefaultPeak(int);

        int getVal(void);
        int read(void);

        void sample(uint8_t*,uint8_t);
};

static audioManager aux;

#endif
