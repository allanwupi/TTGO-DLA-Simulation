#include <Arduino.h>
#include <TFT_eSPI.h>
#include <math.h>
#include <limits.h>

// #define PARTICLE_NUM 5
#define COLS 320
#define ROWS 170
#define CENTRE_X 160
#define CENTRE_Y 85
// Moore neighbourhood
#define NUM_WALK_DIRECTIONS 8
#define SLEEP_MILLIS 100
#define ERROR_FLAG -1

typedef enum {
  SEED = 2,
  FULL = 1,
  EMPTY = 0,
} State;

typedef struct {
  int x;
  int y;
  State s;
} Walker;

/*int VECTOR_X[NUM_WALK_DIRECTIONS] = {1, 0, -1, 0};
int VECTOR_Y[NUM_WALK_DIRECTIONS] = {0, 1, 0, -1};*/

int VECTOR_X[NUM_WALK_DIRECTIONS] = {1, 1, 0, -1, -1, -1, 0, 1};
int VECTOR_Y[NUM_WALK_DIRECTIONS] = {0, 1, 1, 1, 0, -1, -1, -1};

TFT_eSPI tft = TFT_eSPI();
int grid[ROWS][COLS] = {0};

void spawn(Walker *ptr, int radius);
bool invalid(int x, int y);
int walk(int grid[][COLS], Walker *ptr);
int stick(int grid[][COLS], Walker *ptr);
uint32_t colourMap(int state);
void drawGrid(int grid[][COLS]);

void setup() {
  int DEFAULT_ROTATION = 3;
  int RANDOM_SEED_PIN = 1;
  // Serial.begin(115200);

  tft.init();
  tft.setRotation(DEFAULT_ROTATION);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  randomSeed(analogRead(RANDOM_SEED_PIN));
}

void loop() {
  static Walker p = {.x = CENTRE_X, .y = CENTRE_Y};
  static unsigned long prevUpdate = millis();
  static int num_particles = 0;
  static int radius = 3;
  static int increment = 1;
  static bool respawn = false;
  static bool force_refresh = false;
  // MAIN PROGRAM LOOP
  grid[CENTRE_Y][CENTRE_X] = SEED;
  if (walk(grid, &p) == 1) {
    respawn = true;
  }
  if (stick(grid, &p) == 1) {
    num_particles++;
    if (num_particles % 10 == 0) {
      radius += 1;
    }
    respawn = true;
    force_refresh = true;
  }
  if (respawn) {
    spawn(&p, radius);
    respawn = false;
  }
  // Serial.printf("r=%d, x=%d, y=%d\n", radius, p.x, p.y);
  // REFRESH SCREEN
  if (force_refresh) {
    drawGrid(grid);
    force_refresh = false;
    prevUpdate = millis();
    delay(SLEEP_MILLIS);
  }
}

bool invalid(int x, int y) {
  return (x < 0 || x >= COLS || y < 0 || y >= ROWS);
}

void spawn(Walker *ptr, int radius) {
  if (ptr == NULL) return;
  float angle = (float)random(0, 360) * M_PI / 180.0;
  int x = radius * cos(angle);
  int y = radius * sin(angle);
  ptr->x = x + CENTRE_X;
  ptr->y = y + CENTRE_Y;
  // Serial.printf("spawned @ x=%d, y=%d\n",ptr->x,ptr->y);
  ptr->s = FULL;
  if (!invalid(ptr->x, ptr->y)) {
    grid[ptr->y][ptr->x] = FULL;
  } else {
    // Serial.printf("failed! trying to respawn\n",ptr->x,ptr->y);
    spawn(ptr, radius);
  }
}

// returns 0 if particle moved successfully within bounds
// returns 1 if particle moved out of bounds
int walk(int grid[][COLS], Walker *ptr) {
  if (ptr == NULL) return ERROR_FLAG;
  int direction = random(0, NUM_WALK_DIRECTIONS);
  grid[ptr->y][ptr->x] = EMPTY;
  ptr->x += VECTOR_X[direction];
  ptr->y += VECTOR_Y[direction];
  if (invalid(ptr->x, ptr->y)) {
    return 1;
  } else {
    grid[ptr->y][ptr->x] = FULL;
    return 0;
  }
}

// returns 1 if non-empty cell detected within Moore neighbourhood
// returns 0 if no non-empty cells are in the neighbourhood
int stick(int grid[][COLS], Walker *ptr) {
  if (ptr == NULL) return ERROR_FLAG;
  int nx, ny;
  for (int i = 0; i < NUM_WALK_DIRECTIONS; i++) {
    nx = ptr->x + VECTOR_X[i];
    ny = ptr->y + VECTOR_Y[i];
    if (invalid(nx, ny)) {
      continue;
    }
    if (grid[ny][nx] != EMPTY) {
      return 1;
    }
  }
  return 0;
}

uint32_t colourMap(int state) {
  switch (state) {
    case FULL: return TFT_WHITE;
    case SEED: return TFT_GREEN;
    case EMPTY: return TFT_BLACK;
    default:
      int val = (state > 31) ? 31 : state;
      return ((val << 11) | (1+2*val << 5) | val);
  }
}

void drawGrid(int grid[][COLS]) {
  if (grid == NULL) return;
  int cell_colour;
  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      cell_colour = colourMap(grid[y][x]);
      tft.drawPixel(x, y, cell_colour);
    }
  }
}
