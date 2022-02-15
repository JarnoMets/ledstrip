#include "Arduino.h"

#include "audio.h"
#include "bluetooth.h"
#include "ledDriver.h"
#include "patterns.h"
#include "timer.h"

#define __MY_VERSION__ "1.0.5"

//Timing diagram:
//  Frame 1: 32 0's -> start frame
//  Frame 2: 1 1 Bi7 Bi6 Gi7 G6 R7 R6 B7->B0 G7->G0 R7 -> R0
//  Frame 3: 1 1 Bi7 Bi6 Gi7 G6 R7 R6 B7->B0 G7->G0 R7 -> R0

char string[32];

bool state = true;

void parser(void);


void setup() {
    bt.init();
    strip.init();
    strip.setPattern(0);
    aux.init();
    mode = 'p';
    patternTime = 1000;

    Serial.println("Device booted succesfully!");
}

void loop() {
    parser();
    if (state) {
        if (mode == 'p')
            if (patternTime > 100)
            strip.transitionPattern(patternTime);

        if (mode == 'm')
            strip.updateOnAudio();
    }
}


void parser(void) {
	strcpy(string,bt.read());
	if (strcmp(string,"")==0)
	    return;
    if (isDigit(string[0])) {
        if (mode == 'n') {
            char* tmpr;
            char* tmpg;
            char* tmpb;
            tmpr = strtok(string, ",");
            tmpg = strtok(NULL, ",");
            tmpb = strtok(NULL, ",");
            strip.setColor((float)atoi(tmpr), (float)atoi(tmpg), (float)atoi(tmpb));
        }
    } else {
        if (strstr(string, "CONNECTED") != NULL) {
            Serial.println("Led strip controls");
            Serial.print("Version ");
            Serial.println(__MY_VERSION__);
            Serial.println("By Jarno Mets");
            Serial.print("app cPattern ");
            Serial.println(strip.getPattern());
            Serial.print("app patternTime ");
            Serial.println(patternTime);
            Serial.print("app patternAmount ");
            Serial.println(N_PATTERN);
            Serial.print("app mode ");
            Serial.println(mode);
            Serial.print("app on ");
            Serial.println(state);
            Serial.print("app intensity ");
            Serial.println(strip.intensity);
            Serial.println("Unused chars ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        } else if (strcmp(string, "on") == 0) {
            strip.setColor(10, 10, 10);
            state = true;
        }   
        if (strcmp(string, "audioy") == 0) {
            mode = 'm';
        } else if (strcmp(string, "audion") == 0) {
            mode = 'n';
        } else if (strcmp(string, "audioget") == 0) {
            Serial.println(aux.read());
        } else if (strcmp(string, "audiocalibrate") == 0) {
            aux.setNeutral(aux.getVal());
         } else if (strstr(string, "intensity") != NULL) {   
            strtok(string, " ");
            strip.intensity = atoi(strtok(NULL, " "));
        } else if (strcmp(string, "pattern") == 0) {
            mode = 'p';
        } else if (strstr(string, "patternTime") != NULL) {   
            strtok(string, " ");
            patternTime = atoi(strtok(NULL, " "));
        } else if (strstr(string, "patternSet") != NULL) {
            strtok(string, " ");
            strip.setPattern(atoi(strtok(NULL, " ")));
        } else if (strstr(string, "peak") != NULL) {
            strtok(string, " ");
            aux.setDefaultPeak(atoi(strtok(NULL, " ")));
        } else if (strcmp(string, "red") == 0) {
            mode = 'n';
            strip.setColor(255, 0, 0);
        } else if (strcmp(string, "green") == 0) {
            mode = 'n';
            strip.setColor(0, 255, 0);
        } else if (strcmp(string, "blue") == 0) {
            mode = 'n';
            strip.setColor(0, 0, 255);
        } else if (strcmp(string, "white") == 0) {
            mode = 'n';
            strip.setColor(255, 255, 255);
        } else if (strcmp(string, "off") == 0) {
            state = false;
            strip.setColor(0, 0, 0);
        }
    }
    for (int i = 0; i < 32; i++) {
        string[i] = B0;
    }
    strip.update();
}

ISR(TIMER2_OVF_vect) {
    /*if (bt.dataAvailable())
      return;
    
    static volatile int c = 0;
    c++;
    if (c >= (int)4096*tim.getFrequencyt0()) {
        c = 0;
        tim.runt0();
    }*/
}

