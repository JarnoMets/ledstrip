#include "ledDriver.h"

void driver::init(void) {
    //bt.send("");
    pinMode(cout, OUTPUT);
    pinMode(dout, OUTPUT);
    setColor(0,100,100);
    update();
}

driver::colors driver::getColor(void) {
    return color;
}

void driver::setColor(uint8_t red, uint8_t green, uint8_t blue) {
    color = {(float)red, (float)green, (float)blue};
}

void driver::update(void) {
    colors tmpColor = color;
    color.red *= (float)intensity/255;
    color.green *= (float)intensity/255;
    color.blue *= (float)intensity/255;

    digitalWrite(dout, LOW);

    for (int i = 0; i < 32; i++) {
        digitalWrite(cout, HIGH);
        digitalWrite(cout, LOW);
    }

    for (int i = 0; i < 2; i++) {
        digitalWrite(dout, HIGH);
    
        for (int i = 0; i < 2; i++) {
          digitalWrite(cout, HIGH);
          digitalWrite(cout, LOW);
        }

        if ((int)color.blue & 0x80 > 0)
          digitalWrite(dout, LOW);
        else
          digitalWrite(dout, HIGH);
          
        digitalWrite(cout, HIGH);
        digitalWrite(cout, LOW);

        if ((int)color.blue & 0x40 > 0)
          digitalWrite(dout, LOW);
        else
          digitalWrite(dout, HIGH);

        digitalWrite(cout, HIGH);
        digitalWrite(cout, LOW);

        if ((int)color.green & 0x80 > 0)
          digitalWrite(dout, LOW);
        else
          digitalWrite(dout, HIGH);
          
        digitalWrite(cout, HIGH);
        digitalWrite(cout, LOW);

        if ((int)color.green & 0x40 > 0)
          digitalWrite(dout, LOW);
        else
          digitalWrite(dout, HIGH);

        digitalWrite(cout, HIGH);
        digitalWrite(cout, LOW);

        if ((int)color.red & 0x80 > 0)
          digitalWrite(dout, LOW);
        else
          digitalWrite(dout, HIGH);

        digitalWrite(cout, HIGH);
        digitalWrite(cout, LOW);

        if ((int)color.red & 0x40 > 0)
          digitalWrite(dout, LOW);
        else
          digitalWrite(dout, HIGH);
          
        digitalWrite(cout, HIGH);
        digitalWrite(cout, LOW);

        for (int i = 0; i < 8; i++) {
          if (((int)color.blue << i)&0x80)
            digitalWrite(dout, HIGH);
          else
            digitalWrite(dout, LOW);
            
          digitalWrite(cout, HIGH);
          digitalWrite(cout, LOW);
        }

        for (int i = 0; i < 8; i++) {
          if (((int)color.green << i)&0x80)
              digitalWrite(dout, HIGH);
          else
            digitalWrite(dout, LOW);

          digitalWrite(cout, HIGH);
          digitalWrite(cout, LOW);
        }

        for (int i = 0; i < 8; i++) {
          if (((int)color.red << i)&0x80)
              digitalWrite(dout, HIGH);
          else
            digitalWrite(dout, LOW);

          digitalWrite(cout, HIGH);
          digitalWrite(cout, LOW);
        }
    }
    color = tmpColor;
}


void driver::transition(uint8_t redEnd, uint8_t greenEnd, uint8_t blueEnd, uint32_t dTime) {
    int redStart = color.red;
    int greenStart = color.green;
    int blueStart = color.blue;

    for (int i = 0; i < dTime; i+=50) {
        if (Serial.available() > 0)
            break;

        if (redStart > redEnd)
            color.red     -= ((float)(redStart - redEnd) / (dTime / 50));

        if (greenStart > greenEnd)
            color.green   -= ((float)(greenStart - greenEnd) / (dTime / 50));
        
        if (blueStart > blueEnd)
            color.blue    -= ((float)(blueStart - blueEnd) / (dTime / 50));

        if (redStart < redEnd)
            color.red     += ((float)(redEnd - redStart) / (dTime / 50));
        
        if (greenStart < greenEnd)
            color.green   += ((float)(greenEnd - greenStart) / (dTime / 50));

        if (blueStart < blueEnd)
            color.blue    += ((float)(blueEnd - blueStart) / (dTime / 50));


        if (redStart > redEnd) {
            if (color.red < redEnd) {
                color.red = redEnd;
            }
        }

        if (greenStart > greenEnd) {
            if (color.green < greenEnd) {
                color.green = greenEnd;
            }
        }

        if (blueStart > blueEnd) {
            if (color.blue < blueEnd) {
                color.blue = blueEnd;
            }
        }

        if (redStart < redEnd) {
            if (color.red > redEnd) {
                color.red = redEnd;
            }
        }

        if (greenStart < greenEnd) {
            if (color.green > greenEnd) {
                color.green = greenEnd;
            }
        }

        if (blueStart < blueEnd) {
            if (color.blue > blueEnd) {
                color.blue = blueEnd;
            }
        }
        update();
        delay(50);
    }
}


uint8_t driver::getPattern(void) {
    return cPattern;
}

void driver::setPattern(uint8_t pat) {
    cPattern = pat;
}


void driver::transitionPattern(uint32_t dt) {
    transition(pattern[cPattern][patternStep][0],pattern[cPattern][patternStep][1],pattern[cPattern][patternStep][2],dt);
    patternStep++;

    if (patternStep > pattern[cPattern][patternStep][3])
        patternStep = 0;

}

void driver::displayPattern(void) {
    static int patternStep = 0;
    patternStep++;
    if (patternStep > pattern[cPattern][patternStep][3])
        patternStep = 0;
    setColor(pattern[cPattern][patternStep][0],pattern[cPattern][patternStep][1],pattern[cPattern][patternStep][2]);
    update();
}

void driver::updateOnAudio(void) {
    static int peak = defaultPeak;
    static int counter = 0;
    int shortPeak = 0;

    for (int i = 0; i < 1000; i++) {
        int val = aux.read();
        if (val > shortPeak)
            shortPeak = val;
    }
    
    if (shortPeak > peak)
      peak = shortPeak;

    if (peak > defaultPeak) {
        if ((float)shortPeak/peak > 0.9)
            strip.setColor(0,0,255);
        if ((float)shortPeak/peak > 0.75 && (float)shortPeak/peak < 0.9)
            strip.setColor(0,255,0);
        if ((float)shortPeak/peak > 0.5 && (float)shortPeak/peak < 0.75)
            strip.setColor(255,0,0);
    }

    else
        strip.setColor(255,0,0);

    strip.update();

    counter++;

    if (counter > 50) {
      peak = defaultPeak;
      counter = 0;
    }
}
