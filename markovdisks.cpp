#include "include.h"
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <forward_list>

#define NUM_DISKS 64
#define RADIUS 1
#define DELTA 1
#define BOX_WIDTH 10
#define BOX_HEIGHT 10
#define NUM_MOVES 100000

int main() {
  std::srand(std::time(nullptr));
  std::forward_list<Disk> actors;
  for(uint8_t n = 0; n < NUM_DISKS; n++) {
    double x = (BOW_WIDTH - 2 * RADIUS) * (std::rand()/(double)RAND_MAX - 0.5);
    double y = (BOX_WIDTH - 2 * RADIUS) * (std::rand()/(double)RAND_MAX - 0.5);
    actors.push_front(Disk(Vector(x, y)));
  }
}
