#include <Arduino.h>
#include <TFT_eSPI.h>
#include "simulation.h"

#define SLEEP_MILLIS 75 // (not used)
#define DEFAULT_ROTATION 1
#define RANDOM_SEED_PIN 1

TFT_eSPI tft = TFT_eSPI();
int world[ROWS][COLS] = {0};

void setup() {
  // Serial.begin(115200);
  tft.init();
  tft.setRotation(DEFAULT_ROTATION);
  tft.fillScreen(BG_COLOUR);
  tft.setTextColor(TEXT_COLOUR, BG_COLOUR);
  tft.setTextFont(0);
  tft.setTextSize(1);
  randomSeed(analogRead(RANDOM_SEED_PIN));

  for (int x = 0; x < 30; x++) {
    for (int y = 0; y < 9; y++) {
      world[y][x] = OUT_OF_BOUNDS;
    }
  }
  seed(world, 0);
}

void loop() {
  simulate(world, &tft);
}