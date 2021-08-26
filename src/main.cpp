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
    FastLED.setBrightness(192);
}

uint8_t ls_numberOfFlashes;
uint8_t ls_delayBetweenFlashes;
uint8_t ls_flashLED;
uint8_t ls_flashBrightness;
uint8_t ls_paletteIndex;

// #A LIGHTNING SPARK 1
// TODO: Last flash should fade
void lightningSpark() {
    ls_numberOfFlashes = random8(1, 4); // Determine number of flashes
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

      ls_paletteIndex += x * 10;
    }
}

uint8_t ll_numberOfFlashes;
uint8_t ll_delayBetweenFlashes;
uint8_t ll_flashLED;
uint8_t ll_flashLED_length;
uint8_t ll_flashBrightness;
uint8_t ll_paletteIndex;

// #2 LIGHTNING LINE

// Save the white line
// Flash the white line, brighter
// Last flash should fade
void lightningLine() {
  // fill_gradient_RGB(leds, NUM_LEDS, ll_paletteIndex, 255 / NUM_LEDS, currentPalette, 255, LINEARBLEND);
  ll_numberOfFlashes = random8(1, 6); // Determine number of flashes

  // Run a dim white line
  for (int y = 0; y <= NUM_LEDS; y++) {
    FastLED.setBrightness(32 * y);
    leds[y] = ColorFromPalette(currentPalette, ll_paletteIndex);
    FastLED.show();
    delay(NUM_LEDS / y + 12);
  }

  for (int z = 0; z <= ll_numberOfFlashes; z++) {
    ll_delayBetweenFlashes = random8(z * 24);
    ll_flashBrightness = random8(z * 32, 192);

    fill_palette(leds, NUM_LEDS, ll_paletteIndex, z, currentPalette, ll_flashBrightness, LINEARBLEND);
    FastLED.show();
    delay(ll_delayBetweenFlashes);

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(ll_delayBetweenFlashes);
  }  

  // Randomly select an LED
  // ll_flashLED = random8(NUM_LEDS - 1); // Lock the LED of choice
  // ll_flashLED_length = random8(NUM_LEDS / 2);

  // if (ll_flashLED < NUM_LEDS / 2) {
    // If it's in the first half...      
  // } else {
    // If it's in the last half...
  // }
  
}

uint8_t ls_flashOccurence;

void loop() {
  // TODO: Select between lightning line || lightning flash
  
  // Lightning Flashes
  ls_flashOccurence = random8(8);

  EVERY_N_SECONDS(random16(24)) {
    for (int x = 0; x <= ls_flashOccurence; x++) {
      lightningSpark();
    }
  }
  
  // Lightning Crawl
  EVERY_N_SECONDS(random16(24)) {
    lightningLine();
  }

  EVERY_N_MILLISECONDS(1) {
    ll_paletteIndex++;
  }

  fadeToBlackBy(leds, NUM_LEDS, 1);
}