#include "include.h"
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <vector>

#define NUM_DISKS 64
#define RADIUS 1
#define DELTA 1
#define BOX_WIDTH 10
#define BOX_HEIGHT 10
#define NUM_MOVES 100000

bool ValidAddition(const Disk &newbie, const std::vector<Disk> &actors) {
  for(std::vector<Disk>::const_iterator it = actors.begin(); it != actors.end(); it++) {
    if(newbie.Overlaps(*it)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::srand(std::time(nullptr));
  std::vector<Disk> actors;
  uint8_t n = 0;
  while(n < NUMDISKS) {
    double x = (BOX_WIDTH - 2 * RADIUS) * (std::rand()/(double)RAND_MAX - 0.5);
    double y = (BOX_WIDTH - 2 * RADIUS) * (std::rand()/(double)RAND_MAX - 0.5);
    Disk newbie(RADIUS, Vector2D(x, y));
    if(ValidAddition(newbie, actors)) {
        actors.push_back(Disk(RADIUS, Vector2D(x, y)));
        n++;
    }
  }
  uint64_t moves = 0;
  while(moves < NUM_MOVES) {
    //get random Disk to walk
    n = std::rand() % NUM_DISKS;
    //save reference to Disk, and remove from system
    Disk mover = actors[n];
    actors.erase(actors.begin()+n);
    //create copy of Disk, and move it by delta vector
    Disk mover_clone = Disk(mover);
    double dx = DELTA * (2 * std::rand()/(double)RAND_MAX - 1);
    double dy = DELTA * (2 * std::rand()/(double)RAND_MAX - 1);
    mover_clone.position += Vector2D(dx, dy);
    //if result is valid state, keep it, else restore old Disk
    if(ValidAddition(mover_clone, actors)) {
      actors.push_back(mover_clone);
      moves++;
    } else {
      actors.push_back(mover);
    }
  }
}