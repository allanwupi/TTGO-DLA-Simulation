#include <Arduino.h>
#include <TFT_eSPI.h>
#include <math.h>
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
      //tft.drawPixel(x, y, HUE[NUM_COLOURS-1]);
    }
  }

  seed(world);
  //for (int i = 0; i < NUM_COLOURS; i += 2) HUE[i] = ((31-i << 11) | (2*(31-i)+1 << 5) | 31-i);
}

void loop() {
  static Walker p = {.x = CENTRE_X, .y = CENTRE_Y};
  static unsigned long prevUpdate = millis();
  static int radius = 3;
  static int growth_bar = 10;
  static bool respawn = false;
  static bool draw_screen = false;
  if (walk(world, &p) == 1) {
    respawn = true;
  }
  if (stick(world, &p) == 1) {
    GLOBAL_PARTICLE_COUNT++;
    if (radius < MAX_SPAWN_RADIUS && GLOBAL_PARTICLE_COUNT % growth_bar == 0) {
      if (GLOBAL_PARTICLE_COUNT < 150) radius++;
      if (GLOBAL_PARTICLE_COUNT == 250) growth_bar = 25;
      if (GLOBAL_PARTICLE_COUNT == 500) growth_bar = 40;
      radius++;
    }
    respawn = true;
    draw_screen = true;
  }
  if (respawn) {
    spawn(world, &p, radius);
    respawn = false;
  }
  // Serial.printf("r=%d, x=%d, y=%d\n", radius, p.x, p.y);
  if (draw_screen) {
    drawGrid(world);
    draw_screen = false;
    prevUpdate = millis();
    tft.setCursor(0,0);
    tft.printf("%-5d", GLOBAL_PARTICLE_COUNT);
  }
}