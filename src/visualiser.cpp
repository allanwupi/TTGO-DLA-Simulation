#include <TFT_eSPI.h>
#include "simulation.h"

uint32_t TEXT_COLOUR = TFT_GREEN;
uint32_t BG_COLOUR = TFT_BLACK;
uint32_t SEED_COLOUR = TFT_WHITE;
uint32_t NEW_COLOUR = TFT_GREEN;

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

int AGE[NUM_COLOURS] = {
  100,
  200,
  300,
  500,
  800,
  1300,
  2100,
  3400,
  5500,
  8900,
};

uint32_t colourMap(int state) {
  switch (state) {
    case NEW:
      return NEW_COLOUR;
    case SEED:
      return SEED_COLOUR;
    case EMPTY:
      return BG_COLOUR;
    default: // particle age
      for (int i = 0; i < NUM_COLOURS; i++)
        if (state < AGE[i]) return HUE[i];
      return HUE[NUM_COLOURS-1];
  }
}

void drawGrid(int grid[][COLS], TFT_eSPI *tft) {
  if (grid == NULL) return;
  int cell_colour;
  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      if (grid[y][x] == OUT_OF_BOUNDS) continue;
      if (grid[y][x] == FULL)
        grid[y][x] = GLOBAL_PARTICLE_COUNT;
      cell_colour = colourMap(grid[y][x]);
      tft->drawPixel(x, y, cell_colour);
      if (grid[y][x] == NEW) grid[y][x] = EMPTY;
    }
  }
}