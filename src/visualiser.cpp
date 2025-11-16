#include <TFT_eSPI.h>
#include "simulation.h"

uint32_t TEXT_COLOUR = TFT_GREEN;
uint32_t BG_COLOUR = TFT_BLACK;
uint32_t SEED_COLOUR = TFT_WHITE;
uint32_t NEW_COLOUR = TFT_GREEN;

extern TFT_eSPI tft;

uint32_t colourMap(int state) {
  switch (state) {
    case NEW:
      return NEW_COLOUR;
    case SEED:
      return SEED_COLOUR;
    case EMPTY:
      return BG_COLOUR;
    default:
      int i = state / COLOUR_SWITCH;
      if (i >= NUM_COLOURS) i = NUM_COLOURS-1;
      return HUE[i];
  }
}

void drawGrid(int grid[][COLS]) {
  if (grid == NULL) return;
  int cell_colour;
  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      if (grid[y][x] == OUT_OF_BOUNDS) continue;
      if (grid[y][x] == FULL)
        grid[y][x] = GLOBAL_PARTICLE_COUNT;
      cell_colour = colourMap(grid[y][x]);
      tft.drawPixel(x, y, cell_colour);
      if (grid[y][x] == NEW) grid[y][x] = EMPTY;
    }
  }
}