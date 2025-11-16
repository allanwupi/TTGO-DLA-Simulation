#ifndef SIMULATION_H
#define SIMULATION_H
#include <TFT_eSPI.h>

#define NUM_WALK_DIRECTIONS 8 // Moore
#define PARTICLE_NUM 5 // (not used)
#define MAX_SPAWN_RADIUS 85
#define COLS 320
#define ROWS 170
#define CENTRE_X 160
#define CENTRE_Y 85
#define NUM_COLOURS 10
#define COLOUR_SWITCH 200

typedef enum {
  SEED = -3,
  NEW = -2,
  OUT_OF_BOUNDS = -1,
  EMPTY = 0,
  FULL = 1,
  // values above 1 map to HUE colours
} State;

typedef struct {
  int x;
  int y;
  // State s;
} Walker;

/*int VECTOR_X[NUM_WALK_DIRECTIONS] = {1, 0, -1, 0};
int VECTOR_Y[NUM_WALK_DIRECTIONS] = {0, 1, 0, -1};*/

// DEFINE COLOURS
extern uint32_t TEXT_COLOUR;
extern uint32_t BG_COLOUR;
extern uint32_t SEED_COLOUR;
extern uint32_t NEW_COLOUR;
extern uint32_t HUE[NUM_COLOURS];

extern int GLOBAL_PARTICLE_COUNT;
extern int VECTOR_X[NUM_WALK_DIRECTIONS];
extern int VECTOR_Y[NUM_WALK_DIRECTIONS];

extern TFT_eSPI tft;

// LOGIC FUNCTIONS
void seed(int grid[][COLS]);
void spawn(int grid[][COLS], Walker *ptr, int radius);
bool outOfBounds(int x, int y);
int walk(int grid[][COLS], Walker *ptr);
int stick(int grid[][COLS], Walker *ptr);

// VISUALISER FUNCTIONS
uint32_t colourMap(int state);
void drawGrid(int grid[][COLS]);

#endif