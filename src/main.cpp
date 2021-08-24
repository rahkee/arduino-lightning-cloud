#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 37
#define DATA_PIN 5

CRGB leds[NUM_LEDS];

// Gradient palette "bhw1_06_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_06.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_06_gp ) {
    0, 184,  1,128,
  160,   1,193,182,
  219, 153,227,190,
  255, 255,255,255
};

CRGBPalette16 currentPalette = bhw1_06_gp;

void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255);
}

uint8_t ls_numberOfFlashes;
uint8_t ls_delayBetweenFlashes;
uint8_t ls_flashLED;
uint8_t ls_flashBrightness;
uint8_t ls_paletteIndex = 0;

// #A LIGHTNING SPARK 1
// TODO: Last flash should fade
void lightningSpark_one() {
    ls_numberOfFlashes = random8(1, 8); // Determine number of flashes
    // Randomly select an LED || Group of LEDs in the strip
    ls_flashLED = random8(0, NUM_LEDS - 1); // Lock the LED of choice

    for(int x = 0; x <= ls_numberOfFlashes; x++) {
      // Flash a random number of times, each brighter
      ls_delayBetweenFlashes = random(x * 4, 64);
      ls_flashBrightness = random(x * 25, 255);

      leds[ls_flashLED] = ColorFromPalette(currentPalette, ls_paletteIndex, ls_flashBrightness, LINEARBLEND);
      FastLED.show();
      delay(ls_delayBetweenFlashes);
      leds[ls_flashLED] = CRGB::Black;
      FastLED.show();
      delay(ls_delayBetweenFlashes);

      ls_paletteIndex += 16;
    }
}

uint8_t ll_numberOfFlashes;
uint8_t ll_delayBetweenFlashes;
uint8_t ll_flashLED;
uint8_t ll_flashBrightness;
uint8_t ll_paletteIndex = 0;

// #2 LIGHTNING LINE
void lightningLine() {

  ll_numberOfFlashes = random8(2, 10); // Determine number of flashes

  EVERY_N_MILLISECONDS(random16(2048, 4096)) {
    // Randomly select an LED || Group of LEDs in the strip
    ll_flashLED = random8(0, NUM_LEDS - 1); // Lock the LED of choice

    for(int x = 0; x <= ll_numberOfFlashes; x++) {
      // Flash a random number of times, each brighter
      ll_delayBetweenFlashes = random(x * 4, 64);
      ll_flashBrightness = random(x * 25, 255);

      leds[ll_flashLED] = ColorFromPalette(currentPalette, ll_paletteIndex, ll_flashBrightness, LINEARBLEND);
      FastLED.show();
      delay(ll_delayBetweenFlashes);
      leds[ll_flashLED] = CRGB::Black;
      FastLED.show();
      delay(ll_delayBetweenFlashes);

      ll_paletteIndex += 16;
    }

    // TODO: Last flash should fade
  }
}
// Run a dim white line
// Save the white line
// Flash the white line, brighter
// Last flash should fade

uint8_t flashOccurence = random8(1, 6);

void loop() {

    EVERY_N_MILLISECONDS(random16(2048, 4096)) {
      for (int x = 0; x <= flashOccurence; x++) {
        lightningSpark_one();
      }
    }

    // lightningLine();

    // TODO: Select between lightning line || lightning flash

    // #SAVE MOVING PALETTE FOR #2

    // fill_palette(leds, NUM_LEDS, ls_paletteIndex, 255 / NUM_LEDS, myPal, 255, LINEARBLEND);
    //   FastLED.show();

    // EVERY_N_MILLISECONDS(32) {
    // }

  

    // leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(myPal, random8(), 255, LINEARBLEND);

    // fadeToBlackBy(leds, NUM_LEDS, 50);

  
}