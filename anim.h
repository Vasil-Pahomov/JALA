#ifndef anim_h
#define anim_h
#include "palette.h"

#define ANIMS 8 //number of animations (not including start one) to cycle randomly
#define PALS 8 //number of palettes
#define INTERVAL 30000 //change interval, msec

#define MAXLEDS 1024 // maximum number of LEDs in the strip TODO: switch to dynamic arrays to save RAM

#define TRANSITION_MS 1000 // transition time between animations, ms

// brigthness animation amplitude shift. true BrA amplitude is calculated as (0..127) value shifted right by this amount
#define BRA_AMP_SHIFT 1
// brigthness animation amplitude offset
#define BRA_OFFSET (222-64)

//probability of spark when in idle plase
#define SPARK_PROB 3

extern int paletteInd;
extern int animInd;

class Anim {
    
private:
    bool initialized;

    int ledsNum;//actual number of LEDs
    
    //Color arrays - two for making transition
    static Color leds1[MAXLEDS];
    static Color leds2[MAXLEDS];
    //auxiliary colors array
    static Color ledstmp[MAXLEDS];

    void animStart();
    
    // length of animation timeslot (period)
    byte period;
    // array of Color to work with
    Color *leds;
    Palette *palette;

    // millis for next timeslot 
    unsigned long nextms;
    // millis to transition end
    unsigned long transms;

    //animation-specific variables
    int phase;
    int pos;
    int inc;

    //whether to call SetUp on palette change
    //(some animations require full transition with fade, otherwise the colors would change in a step, some not)
    bool setUpOnPalChange;

    Color curColor = Color(0);
    Color prevColor = Color(0);

    Color sparkleColor = Color(0xFFFFFF);

    static byte seq[MAXLEDS];

    //brigthness animation (BrA) current initial phase
    byte braPhase;
    //braPhase change speed 
    byte braPhaseSpd=5;
    //BrA frequency (spatial)
    byte braFreq=150;

    //glow animation setup
    void glowSetUp();

    //glow animation - must be called for each LED after it's BASIC color is set
    //note this overwrites the LED color, so the glow assumes that color will be stored elsewhere (not in leds[])
    //or computed each time regardless previous leds[] value
    void glowForEachLed(int i);
    
    //glow animation - must be called at the end of each animaton run
    void glowRun();

    void setUp();

    //run and setup handlers
    void (Anim::*runImpl)();
    void (Anim::*setUpImpl)();


    //animation implementations
    void animOff_SetUp();
    void animOff_Run();

    
    void animStart_SetUp();
    void animStart_Run();

    void animRun_SetUp();
    void animRun_Run();
    
    void animPixieDust_SetUp();
    void animPixieDust_Run();
    
    void animSparkr_SetUp();
    void animSparkr_Run();

    void animRandCyc_SetUp();
    void animRandCyc_Run();

    void animStars_SetUp();
    void animStars_Run();

    void animSpread_SetUp();
    void animSpread_Run();

    void animFly_SetUp();
    void animFly_Run();

    void animPulse_SetUp();
    void animPulse_Run();

    void animMagic_SetUp();
    void animMagic_Run();
public:


    Anim();
    void setPeriod(byte period);
    void setPalette(int palind);
    void setAnim(byte animInd);
    void run();
    void doSetUp();
    void setMagicParams(byte ind, byte position, byte color, boolean isBoom);

};

extern Anim anim;

void setAnimPal();

unsigned int rng();

byte rngb();

#endif
