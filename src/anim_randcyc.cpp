#include "anim.h"

void Anim::animRandCyc_SetUp() {
    Serial.print(F("(randCyc)"));
    for (int i=0;i<ledsNum;i++) {
        seq[i] = rngb();
    }
}

void Anim::animRandCyc_Run() {
    for (int i=0;i<ledsNum;i++) {
        leds[i] = palette->getPalColor((float)seq[i] / 256);
        seq[i]+=rngb() >> 6;
    }
}
