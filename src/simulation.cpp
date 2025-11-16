#include <TFT_eSPI.h>
#include "simulation.h"

int GLOBAL_PARTICLE_COUNT = 1;

int VECTOR_X[NUM_WALK_DIRECTIONS] = {1, 1, 0, -1, -1, -1, 0, 1};
int VECTOR_Y[NUM_WALK_DIRECTIONS] = {0, 1, 1, 1, 0, -1, -1, -1};

void seed(int grid[][COLS]) {
  const int select_seed = 1;
  switch (select_seed) {
    case 2: // Circle
      for (int o = 0; o < 360; o += 2) {
        float angle = o * M_PI / 180.0;
        int x = round(80 * cos(angle) + CENTRE_X);
        int y = round(80 * sin(angle) + CENTRE_Y);
        grid[y][x] = SEED;
      }
      break;
    case 1: // Bottom line
      for (int x = 0; x < COLS; x++) grid[ROWS-1][x] = SEED;
      break;
    case 0: // Centre
    default: //
      grid[CENTRE_Y][CENTRE_X] = SEED;
  }
}

bool outOfBounds(int x, int y) {
  return (x < 0 || x >= COLS || y < 0 || y >= ROWS);
}

void spawn(int grid[][COLS], Walker *ptr, int radius) {
  if (ptr == NULL) return;
  int x = 0, y = 0;
  if (radius < MAX_SPAWN_RADIUS) {
    float angle = (float)random(0, 360) * M_PI / 180.0;
    x = radius * cos(angle) + CENTRE_X;
    y = radius * sin(angle) + CENTRE_Y;
  } else {
    x = random(0,320+1);
    y = random(0,170+1);
  }
  ptr->x = x;
  ptr->y = y;
  // ptr->s = NEW;
  // Serial.printf("r=%d,(%d,%d)\n",radius,x,y);
  if (outOfBounds(x, y) || grid[y][x] != EMPTY || abs(x-CENTRE_X)+abs(y-CENTRE_Y) < radius) {
    // Serial.printf("failed! trying to respawn\n",ptr->x,ptr->y);
    spawn(grid, ptr, radius);
  } else {
    grid[ptr->y][ptr->x] = NEW;
  }
}

// returns 0 if particle moved successfully within bounds
// returns 1 if particle moved out of bounds
int walk(int grid[][COLS], Walker *ptr) {
  int direction = random(0, NUM_WALK_DIRECTIONS);
  ptr->x += VECTOR_X[direction];
  ptr->y += VECTOR_Y[direction];
  if (outOfBounds(ptr->x, ptr->y)) {
    return 1;
  } else {
    return 0;
  }
}

// returns 1 if non-empty cell detected within Moore neighbourhood
// returns 0 if no non-empty cells are in the neighbourhood
int stick(int grid[][COLS], Walker *ptr) {
  int nx, ny;
  for (int i = 0; i < NUM_WALK_DIRECTIONS; i++) {
    nx = ptr->x + VECTOR_X[i];
    ny = ptr->y + VECTOR_Y[i];
    if (outOfBounds(nx, ny)) {
      continue;
    }
    if (grid[ny][nx] != EMPTY && grid[ny][nx] != NEW && grid[ny][nx] != OUT_OF_BOUNDS) {
      grid[ptr->y][ptr->x] = FULL;
      return 1;
    }
  }
  return 0;
}