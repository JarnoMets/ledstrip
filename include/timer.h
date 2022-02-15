#ifndef timer_h
#define timer_h

#include "Arduino.h"
#include "ledDriver.h"

class timers {
    private:
        float frequency;
    public:
        void initt0(void);

        float getFrequencyt0(void);
        void setFrequencyt0(float);

        void (*runt0)(void);
};

static timers tim;

#endif