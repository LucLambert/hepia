/* Description: algorithm finding the shortest path beetween 2 points in a grid.
   The diagonal moves are allowed and the "trip durations" are in
   range of 0 to 5. 0 means that no path exists beetween 2 adjacent cells.
   Author: VP
   Date  : 20.9.2021
*/
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FIELD_SIDE 10
#define START_X 1
#define START_Y 1
#define DEST_X (FIELD_SIDE - 2)
#define DEST_Y (FIELD_SIDE - 2)

// field of cells containing the 8 paths duration for the 8 directions, starting
// from left to right, top to bottom
static int field[FIELD_SIDE][FIELD_SIDE][8]; // contains the 8 values of the
                                             // distance of the 8 cells around

typedef struct {
  int x;
  int y;
} coord_t;

typedef struct {
  coord_t trip[FIELD_SIDE *
               FIELD_SIDE]; // point on the current trip (max path: 100)
  int cells_nb;             // current number of cells explored on the same path
  int dist;                 // real distance from the starting point
} trip_t;

static int shortest_trip_length = FIELD_SIDE * FIELD_SIDE; // in [nb of cells]
static int shortest_dist = 100000;                         // real distance
static coord_t shortest_trip[FIELD_SIDE * FIELD_SIDE]; // store the final trip
                                                       // (size is maximised)

static const coord_t dir[8] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                               {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

static trip_t *to_free[10000];
static int cpt_trip = 0;

static void print_hline() {
  for (int i = 0; i < FIELD_SIDE; i++)
    printf("------");
  printf("\n");
}

/* Description: prints all cells with the best path found. Each cell visited
                contains an increasing number to know where the vehicule passed.
*/
static void print_path() {
  bool path_found;
  printf("Path length [cells]: %d, trip length: %d\n", shortest_trip_length,
         shortest_dist);
  print_hline();

  for (int j = 0; j < FIELD_SIDE; j++) // line (y)
  {
    for (int i = 0; i < FIELD_SIDE; i++) // column (x)
    {
      path_found = false;
      for (int k = 0; k < shortest_trip_length; k++)
        if (shortest_trip[k].x == i && shortest_trip[k].y == j) {
          printf(" %3d |", k);
          path_found = true;
          break;
        }
      if (!path_found)
        printf(" %3c |", ' ');
    }
    printf("\n");
    print_hline();
  }
}

/* Description: tests if a cell has already been visited or not
   Parameters: ctx : pointer on the curent trip
               cell: cell coordinates to test
   Return: true if the cell has been visted, false otherwise
*/
static bool is_visited(trip_t *ctx, coord_t cell) {
  for (int i = 0; i < ctx->cells_nb; i++)
    if (ctx->trip[i].x == cell.x && ctx->trip[i].y == cell.y)
      return true;
  return false;
}

/* Description: recursive function that finds the best (=shortest) path. All
                paths are explored, unless the current path duration is
                longer than the best found until there. In this case, it is
                directly discarded.
                As soon as the destination is reached, the total distance
                and the path are saved.
   Parameters: trip_ctx : pointer on the current trip parameters
*/

void cp_trip(trip_t *from, trip_t *to) {

  for (int j = 0; j < from->cells_nb; j++) {
    to->trip[j] = from->trip[j];
  }
  to->cells_nb = from->cells_nb;
  to->dist = from->dist;
}

static void *explore(void *v_trip_ctx) // last element of ctx->trip contains current cell coord.
{
  int d;
  coord_t new_cell;
  trip_t *trip_ctx = (trip_t *)v_trip_ctx;
  int cpt_th = 0;
  pthread_t th[8];

  int x = trip_ctx->trip[trip_ctx->cells_nb - 1].x; // get coord. of current cell
  int y = trip_ctx->trip[trip_ctx->cells_nb - 1].y;

  if (x == DEST_X && y == DEST_Y) // end of path reached
  {
    if (trip_ctx->dist < shortest_dist) {
      shortest_dist = trip_ctx->dist;
      shortest_trip_length = trip_ctx->cells_nb;
      for (int k = 0; k < shortest_trip_length; k++) // copy trip
        shortest_trip[k] = trip_ctx->trip[k];
    }
  } else {
    if (trip_ctx->dist <= shortest_dist) // if wrong, discard this path (too long)
    {
      for (int i = 0; i < 8; i++) // explore cells around
      {
        new_cell.x = x + dir[i].x;
        new_cell.y = y + dir[i].y;
        d = field[x][y][i];
        if (d == 0) // no way
          continue;
        if (is_visited(trip_ctx, new_cell)) // cell already visited
          continue;
        trip_ctx->trip[trip_ctx->cells_nb++] = new_cell; // add last cell
        trip_ctx->dist += d;
        usleep(d); // simulate the trip duration

        trip_t *trip = (trip_t *)malloc(sizeof(trip_t));

        cp_trip(trip_ctx, trip);
        to_free[cpt_trip++] = trip;

        trip_ctx->cells_nb--; // return to last cell with previous distance
        trip_ctx->dist -= d;

        if (pthread_create(&th[cpt_th++], NULL, explore, trip) != 0)
          fprintf(stderr, "can't create thread\n");
      }
      for (int i = 0; i < cpt_th; i++) {
        if (pthread_join(th[i], NULL) != 0)
          fprintf(stderr, "can't join thread\n");
      }
    }
  }
  return NULL;
}

/* Description: initialises the field of cells with the paths duration.
                PLEASE do NOT MODIFY this function!
*/
static void init_field() {
  int distance, d;

  srand(3);
  for (int i = 0; i < FIELD_SIDE; i++)
    for (int j = 0; j < FIELD_SIDE; j++) {
      do {
        distance = 0;
        for (int k = 0; k < 8; k++) {
          if (i + dir[k].x < 0 ||
              i + dir[k].x >= FIELD_SIDE || // if border in direction
              j + dir[k].y < 0 || j + dir[k].y >= FIELD_SIDE) {
            field[i][j][k] = 0; // no path
            continue;
          }
          if (k < 4) // copy the distance of the connected cell previously
            d = field[i + dir[k].x][j + dir[k].y]
                     [7 -
                      k]; // filled (directions 0 to 3 points on those cells)
          else {
            if (rand() % 7 < 4)
              d = 0;
            else
              d = rand() % 6;
          }
          field[i][j][k] = d; // distance is 1,3 or 5. 0 means no path.
          distance += d;
        }
      } while (distance == 0); // at least one path must be valid
    }
}

int main() {
  struct timespec start, finish;
  trip_t trip_ctx = {{{1, 1}}, 1, 0};

  setbuf(stdout, 0);

  // initialize the common field array:
  init_field();
  lock_gettime(CLOCK_MONOTONIC, &start);
  explore(&trip_ctx);
  clock_gettime(CLOCK_MONOTONIC, &finish);

  print_path();
  double elapsed = 1000 * (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000.0;
  printf("Path found after: %g ms\n", elapsed);

  for (int i = 0; i < cpt_trip; i++) {
    free(to_free[i]);
  }

  return EXIT_SUCCESS;
}
