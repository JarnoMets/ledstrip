#ifndef driver_h
#define driver_h

#include "Arduino.h"
#include "audio.h"
#include "bluetooth.h"
#include "patterns.h"

#define cout 7
#define dout 6

class driver: public audioManager {
    private:
        struct colors {
            float red;
            float green;
            float blue;
        } color;
    uint8_t cPattern = 1;
    int patternStep = 0;

    public:
        uint8_t intensity = 255;

        void init(void);

        colors getColor(void);
        void setColor(uint8_t, uint8_t, uint8_t);

        void update();
        void transition(uint8_t, uint8_t, uint8_t, uint32_t);

        uint8_t getPattern(void);
        void setPattern(uint8_t);

        void displayPattern(void);
        void transitionPattern(uint32_t);

        void updateOnAudio(void);

};

static driver strip;

#endif
