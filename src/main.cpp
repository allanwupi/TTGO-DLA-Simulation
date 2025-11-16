#include <Arduino.h>
#include <TFT_eSPI.h>
#include <math.h>

#define PARTICLE_NUM 5 (not used)
#define MAX_SPAWN_RADIUS 85
#define COLS 320
#define ROWS 170
#define CENTRE_X 160
#define CENTRE_Y 85
#define NUM_WALK_DIRECTIONS 8 // Moore
#define SLEEP_MILLIS 75 // (not used)
#define NUM_COLOURS 10
#define COLOUR_SWITCH 200

// Colours
uint32_t TEXT_COLOUR = TFT_GREEN;
uint32_t BG_COLOUR = TFT_BLACK;
uint32_t SEED_COLOUR = TFT_WHITE;
uint32_t NEW_COLOUR = TFT_GREEN;

uint32_t HUE[NUM_COLOURS] = {
  TFT_WHITE,
  TFT_MAGENTA,
  TFT_RED,
  TFT_ORANGE,
  TFT_YELLOW,
  TFT_GREEN,
  TFT_CYAN,
  TFT_BLUE,
  TFT_PURPLE,
  TFT_DARKGREY,
};

typedef enum {
  SEED = -3,
  NEW = -2,
  OUT_OF_BOUNDS = -1,
  EMPTY = 0,
  FULL = 1,
} State;

typedef struct {
  int x;
  int y;
  State s;
} Walker;

/*int VECTOR_X[NUM_WALK_DIRECTIONS] = {1, 0, -1, 0};
int VECTOR_Y[NUM_WALK_DIRECTIONS] = {0, 1, 0, -1};*/

int GLOBAL_PARTICLE_COUNT = 1;

int VECTOR_X[NUM_WALK_DIRECTIONS] = {1, 1, 0, -1, -1, -1, 0, 1};
int VECTOR_Y[NUM_WALK_DIRECTIONS] = {0, 1, 1, 1, 0, -1, -1, -1};

TFT_eSPI tft = TFT_eSPI();
int grid[ROWS][COLS] = {0};

void spawn(Walker *ptr, int radius);
bool outOfBounds(int x, int y);
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
  tft.fillScreen(BG_COLOUR);
  tft.setTextColor(TEXT_COLOUR, BG_COLOUR);
  tft.setTextFont(0);
  tft.setTextSize(1);
  randomSeed(analogRead(RANDOM_SEED_PIN));

  for (int x = 0; x < 30; x++) {
    for (int y = 0; y < 9; y++) {
      grid[y][x] = OUT_OF_BOUNDS;
      // tft.drawPixel(x, y, TFT_GREEN);
    }
  }

  //for (int i = 0; i < NUM_COLOURS; i += 2) HUE[i] = ((31-i << 11) | (2*(31-i)+1 << 5) | 31-i);
}

void loop() {
  static Walker p = {.x = CENTRE_X, .y = CENTRE_Y};
  static unsigned long prevUpdate = millis();
  static int radius = 3;
  static int growth_bar = 10;
  static bool respawn = false;
  static bool draw_screen = false;
  grid[CENTRE_Y][CENTRE_X] = SEED;
  if (walk(grid, &p) == 1) {
    respawn = true;
  }
  if (stick(grid, &p) == 1) {
    GLOBAL_PARTICLE_COUNT++;
    if (radius < MAX_SPAWN_RADIUS && GLOBAL_PARTICLE_COUNT % growth_bar == 0) {
      if (GLOBAL_PARTICLE_COUNT < 200) radius++;
      if (GLOBAL_PARTICLE_COUNT == 200) growth_bar = 20;
      radius++;
    }
    respawn = true;
    draw_screen = true;
  }
  if (respawn) {
    spawn(&p, radius);
    respawn = false;
  }
  // Serial.printf("r=%d, x=%d, y=%d\n", radius, p.x, p.y);
  if (draw_screen) {
    drawGrid(grid);
    draw_screen = false;
    prevUpdate = millis();
    tft.setCursor(0,0);
    tft.printf("%-5d", GLOBAL_PARTICLE_COUNT);
  }
}

bool outOfBounds(int x, int y) {
  return (x < 0 || x >= COLS || y < 0 || y >= ROWS);
}

void spawn(Walker *ptr, int radius) {
  if (ptr == NULL) return;
  int x = 0, y = 0;
  if (radius < MAX_SPAWN_RADIUS) {
    float angle = (float)random(0, 360) * M_PI / 180.0;
    x = radius * cos(angle) + CENTRE_X;
    y = radius * sin(angle) + CENTRE_Y;
  } else {
    while (x*x + y*y < MAX_SPAWN_RADIUS * MAX_SPAWN_RADIUS) {
      x = random(0,320+1);
      y = random(0,170+1);
    }
  }
  ptr->x = x;
  ptr->y = y;
  ptr->s = NEW;
  // Serial.printf("r=%d,(%d,%d)\n",radius,x,y);
  if (outOfBounds(x, y) || grid[y][x] != EMPTY) {
    // Serial.printf("failed! trying to respawn\n",ptr->x,ptr->y);
    spawn(ptr, radius);
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

uint32_t colourMap(int state) {
  switch (state) {
    case NEW:
      return NEW_COLOUR;
    case SEED:
      return SEED_COLOUR;
    case EMPTY:
      return BG_COLOUR;
    default:
      state -= 2;
      if (state >= NUM_COLOURS) state = NUM_COLOURS-2;
      return HUE[state];
  }
}

void drawGrid(int grid[][COLS]) {
  if (grid == NULL) return;
  int cell_colour;
  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      if (grid[y][x] == OUT_OF_BOUNDS) continue;
      if (grid[y][x] == FULL) grid[y][x] = 2+GLOBAL_PARTICLE_COUNT / COLOUR_SWITCH;
      cell_colour = colourMap(grid[y][x]);
      tft.drawPixel(x, y, cell_colour);
      if (grid[y][x] == NEW) grid[y][x] = EMPTY;
    }
  }
}
