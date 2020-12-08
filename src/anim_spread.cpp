#include "anim.h"
#include "color.h"
#include "palette.h"

#define SPREAD_MAX_WIDTH 20

void Anim::animSpread_SetUp() {
    Serial.print(F("(spread)"));
    inc = random(2,8);
    memset(seq, 0, ledsNum);
}

void Anim::animSpread_Run() {
    memset(leds, 0, 3*ledsNum);

    for (int i=0;i<ledsNum;i++) {
        if (seq[i] > 0) {
            byte width = SPREAD_MAX_WIDTH - seq[i];
            for (int j=i-width;j<=(i+width);j++) {
                Color c = ledstmp[i];
                if (j>=0 && j<ledsNum) {
                    leds[j].r += c.r;
                    leds[j].g += c.g;
                    leds[j].b += c.b;
                }
            }
            ledstmp[i].fade(255/SPREAD_MAX_WIDTH);
            seq[i]--;
        }
    }

    if (random(inc) == 0) {
        byte pos = random(0,ledsNum); 
        ledstmp[pos] = palette->getPalColor((float)rngb()/256);
        seq[pos] = SPREAD_MAX_WIDTH;
    }        
}
