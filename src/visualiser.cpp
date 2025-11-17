#include <TFT_eSPI.h>
#include "simulation.h"

uint32_t TEXT_COLOUR = TFT_GREEN;
uint32_t BG_COLOUR = TFT_BLACK;
uint32_t LIVE_COLOUR = TFT_DARKGREY;

bool ENABLE_COLOUR = true;
bool SHOW_PARTICLES = true;

uint32_t HUE[NUM_COLOURS] = {
  TFT_WHITE,
  TFT_PINK,
  TFT_MAGENTA,
  TFT_RED,
  TFT_ORANGE,
  TFT_YELLOW,
  TFT_GREEN,
  TFT_CYAN,
  TFT_BLUE,
  TFT_PURPLE,
};

uint32_t SHADE[] = {
  0xFFFF, // 31
  0xEF7D, // 29
  0xDEFB, // 27
  0xC638, // 24
  0xAD75, // 21
  0x94B2, // 18
  0x8430, // 16
  0x73AE, // 14
  0x632C, // 12
  0x528A, // 10
};

int STAGE[NUM_COLOURS] = {
  100,
  200,
  300,
  500,
  800,
  1200,
  1600,
  2000,
  2500,
  4000,
};

uint32_t *COLOURSCHEME = HUE;

void toggleColours(void) {
  ENABLE_COLOUR = !ENABLE_COLOUR;
  if (ENABLE_COLOUR) COLOURSCHEME = HUE;
  else COLOURSCHEME = SHADE;
}

void toggleParticles(void) {
  static uint32_t ORIGINAL_COLOUR = LIVE_COLOUR;
  SHOW_PARTICLES = !SHOW_PARTICLES;
  if (SHOW_PARTICLES) LIVE_COLOUR = ORIGINAL_COLOUR;
  else LIVE_COLOUR = BG_COLOUR;
}

uint32_t colourMap(int state) {
  switch (state) {
    case LIVE:
      return LIVE_COLOUR;
    case GARBAGE:
    case EMPTY:
      return BG_COLOUR;
    default: // particle age
      for (int i = 0; i < NUM_COLOURS; i++)
        if (state < STAGE[i]) return COLOURSCHEME[i];
      return COLOURSCHEME[NUM_COLOURS-1];
  }
}

void drawGrid(int grid[][COLS], TFT_eSPI *tft) {
  if (grid == NULL) return;
  int cell_colour;
  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      if (grid[y][x] == OUT_OF_BOUNDS || grid[y][x] == EMPTY) continue;
      if (grid[y][x] == DEAD)
        grid[y][x] = GLOBAL_PARTICLE_COUNT;
      cell_colour = colourMap(grid[y][x]);
      tft->drawPixel(x, y, cell_colour);
      if (grid[y][x] == LIVE) {
        grid[y][x] = GARBAGE;
        continue;
      } 
      if (grid[y][x] == GARBAGE) {
        grid[y][x] = EMPTY;
      }
    }
  }
}