#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 37
#define DATA_PIN_A 5
#define DATA_PIN_B 6
#define BRIGHTNESS 192

CRGB leds_A[NUM_LEDS];
CRGB leds_B[NUM_LEDS];

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

uint8_t ls_flashOccurence; // Number of flashes
uint8_t chainLightning; // Chance of chain
uint8_t lightningStrand; // Conduit selector

void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN_A, GRB>(leds_A, NUM_LEDS);
    FastLED.addLeds<WS2812B, DATA_PIN_B, GRB>(leds_B, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

uint8_t ls_numberOfFlashes;
uint8_t ls_delayBetweenFlashes;
uint8_t ls_flashLED;
uint8_t ls_flashBrightness;
uint8_t ls_paletteIndex;

// #A LIGHTNING SPARK
void lightningSpark() {
  lightningStrand = random8(12); // Which conduit
  ls_numberOfFlashes = random8(1, 4); // Determine number of flashes
  // Randomly select an LED || Group of LEDs in the strip
  ls_flashLED = random8(0, NUM_LEDS - 1); // Lock the LED of choice

  for (int x = 0; x <= ls_numberOfFlashes; x++)
  {
    // Flash a random number of times, each brighter
    ls_delayBetweenFlashes = random(x * 4, 64);
    ls_flashBrightness = random(x * 25, BRIGHTNESS);

    if (lightningStrand <= 6) {
      leds_A[ls_flashLED] = ColorFromPalette(currentPalette, ls_paletteIndex, ls_flashBrightness, LINEARBLEND);
      FastLED.show();

      delay(ls_delayBetweenFlashes);

      leds_A[ls_flashLED] = CRGB::Black;
      FastLED.show();

      delay(ls_delayBetweenFlashes);
    }

    if (lightningStrand > 6) {
      leds_B[ls_flashLED] = ColorFromPalette(currentPalette, ls_paletteIndex, ls_flashBrightness, LINEARBLEND);
      FastLED.show();

      delay(ls_delayBetweenFlashes);

      leds_B[ls_flashLED] = CRGB::Black;
      FastLED.show();

      delay(ls_delayBetweenFlashes);
    }

    ls_paletteIndex += x + 12;
  }
}

uint8_t ll_numberOfFlashes;
uint8_t ll_delayBetweenFlashes;
uint8_t ll_flashLED;
uint8_t ll_flashLED_length;
uint8_t ll_flashBrightness;
uint8_t ll_paletteIndex;

// #2 LIGHTNING LINE
// TODO: Random direction and number of LEDs involved...
// Randomly select an LED
// ll_flashLED = random8(NUM_LEDS - 1); // Lock the LED of choice
// ll_flashLED_length = random8(NUM_LEDS / 2);

// if (ll_flashLED < NUM_LEDS / 2) {
//   // If it's in the first half...      
// } else {
//   // If it's in the last half...
// }
void lightningLine() {
  lightningStrand = random8(12); // Which conduit
  ll_numberOfFlashes = random8(1, 6); // Determine number of flashes

  if (lightningStrand <= 6) {
    for (int y = 0; y < NUM_LEDS; y++) {
      FastLED.setBrightness(32 * y);
      leds_A[y] = ColorFromPalette(currentPalette, ll_paletteIndex);
      FastLED.show();
      delay(NUM_LEDS / y + 1);
    }

    for (int z = 0; z <= ll_numberOfFlashes; z++) {
      ll_delayBetweenFlashes = random8(z * 24);
      ll_flashBrightness = random8(z * 32, BRIGHTNESS); // Flash the white line, brighter

      fill_palette(leds_A, NUM_LEDS, ll_paletteIndex, z, currentPalette, ll_flashBrightness, LINEARBLEND);
      FastLED.show();
      delay(ll_delayBetweenFlashes);

      fill_solid(leds_A, NUM_LEDS, CRGB::Black);
      FastLED.show();
      delay(ll_delayBetweenFlashes);
    }
  }

  if (lightningStrand > 6) {
    for (int y = 0; y < NUM_LEDS; y++) {
      FastLED.setBrightness(32 * y);
      leds_B[y] = ColorFromPalette(currentPalette, ll_paletteIndex);
      FastLED.show();
      delay(NUM_LEDS / y + 1);
    }

    for (int z = 0; z <= ll_numberOfFlashes; z++) {
      ll_delayBetweenFlashes = random8(z * 24);
      ll_flashBrightness = random8(z * 32, BRIGHTNESS); // Flash the white line, brighter

      fill_palette(leds_B, NUM_LEDS, ll_paletteIndex, z, currentPalette, ll_flashBrightness, LINEARBLEND);
      FastLED.show();
      delay(ll_delayBetweenFlashes);

      fill_solid(leds_B, NUM_LEDS, CRGB::Black);
      FastLED.show();
      delay(ll_delayBetweenFlashes);
    }
  }
}

// #3 LIGHTNING CRAWL
void lightningCrawl() {
  lightningStrand = random8(12); // Which conduit
  chainLightning = random16(256);

  if (lightningStrand <= 6) {
    for (int n = 0; n < NUM_LEDS; n++) {
      leds_A[n] = ColorFromPalette(currentPalette, ll_paletteIndex);
      FastLED.show();
      delay(NUM_LEDS / n + 1);
      leds_A[n] = CRGB::Black;
      FastLED.show();
      delay(NUM_LEDS / n + 1);
    }
  }

  if (lightningStrand > 6) {
    for (int n = 0; n < NUM_LEDS; n++) {
      leds_B[n] = ColorFromPalette(currentPalette, ll_paletteIndex);
      FastLED.show();
      delay(NUM_LEDS / n + 1);
      leds_B[n] = CRGB::Black;
      FastLED.show();
      delay(NUM_LEDS / n + 1);
    }
  }

  if (chainLightning >= 200) {
    lightningLine();
  } else if (chainLightning <= 100) {
    lightningSpark();
  }
}

void loop() {  
  // Lightning Flashes
  EVERY_N_SECONDS(random8(32)) { 
    ls_flashOccurence = random8(8);

    for (int x = 0; x <= ls_flashOccurence; x++) {
      lightningSpark();
    }
  }

  // Lightning Crawl
  EVERY_N_SECONDS(random8(32)) {
    lightningCrawl();
  }
  
  // Lightning Line
  EVERY_N_SECONDS(random8(32)) {
    lightningLine();
  }

  EVERY_N_MILLISECONDS(10) {
    ll_paletteIndex++;
  }
  
  fadeToBlackBy(leds_A, NUM_LEDS, 12);
  fadeToBlackBy(leds_B, NUM_LEDS, 12);
}