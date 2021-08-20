#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 37
#define DATA_PIN 5

#define PALETTE_ARRAY

CRGB leds[NUM_LEDS];

CRGBPalette16 paletteWhitePurple = CRGBPalette16 (
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,

    CRGB::Pink,
    CRGB::Pink,
    CRGB::Linen,
    CRGB::Linen,

    CRGB::Pink,
    CRGB::Pink,
    CRGB::DarkViolet,
    CRGB::DarkViolet,

    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::Linen,
    CRGB::Linen
    );

CRGBPalette16 paletteYellowPurple = CRGBPalette16 (
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,

    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Linen,
    CRGB::Linen,

    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Orange,
    CRGB::Orange,

    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::Linen,
    CRGB::Linen
    );

CRGBPalette16 paletteWhiteBlue = CRGBPalette16 (
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue,

    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Linen,
    CRGB::Linen,

    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Pink,
    CRGB::Pink,

    CRGB::Blue,
    CRGB::Blue,
    CRGB::Linen,
    CRGB::Linen
    );

CRGBPalette16 myPalWP = paletteWhitePurple;
CRGBPalette16 myPalYP = paletteYellowPurple;
CRGBPalette16 myPalWB = paletteWhiteBlue;

uint8_t paletteIndex = 0;

void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255);
}

// Select between lightning line || lightning flash
uint8_t numberOfFlashes;
uint8_t delayBetweenFlashes;
uint8_t flashLED;
uint8_t flashBrightness;

// #1 LIGHTNING SPARK
void lightningSpark() {
  numberOfFlashes = random8(1, 12); // Determine number of flashes

  EVERY_N_MILLISECONDS(random16(2048, 4096)) {
    // Randomly select an LED || Group of LEDs in the strip
    flashLED = random8(0, NUM_LEDS - 1); // Lock the LED of choice

    for(int x = 0; x < numberOfFlashes; x++) {
      // Flash a random number of times, each brighter
      delayBetweenFlashes = random(2 * numberOfFlashes, 32);
      flashBrightness = random8(128, numberOfFlashes * 21);

      leds[flashLED] = ColorFromPalette(myPalYP, random(), flashBrightness, LINEARBLEND);
      FastLED.show();
      delay(delayBetweenFlashes);
      leds[flashLED] = CRGB::Black;
      FastLED.show();
      delay(delayBetweenFlashes);
    }

    // TODO: Last flash should fade
    fadeToBlackBy(leds, NUM_LEDS, 1);
  }

  
}



// #2 LIGHTNING LINE
// Run a dim white line
// Save the white line
// Flash the white line, brighter
// Last flash should fade

void loop() {

  lightningSpark();

  // #SAVE MOVING PALETTE FOR #2

  // fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, myPal, 255, LINEARBLEND);
  //   FastLED.show();


  // EVERY_N_MILLISECONDS(32) {
  //     paletteIndex++;
  //   }


    // leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(myPal, random8(), 255, LINEARBLEND);

    // fadeToBlackBy(leds, NUM_LEDS, 50);

  
}