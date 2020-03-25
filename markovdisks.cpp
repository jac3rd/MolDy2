#include "include.h"
#include <cstdlib>
#include <ctime>
#include <forward_list>

#define NUM_DISKS 64
#define DELTA 1
#define BOX_LENGTH 1
#define NUM_MOVES 100000
#define NUM_BINS 10

bool ValidAddition(const Disk &newbie, const std::forward_list<Disk> &actors) {
  for(std::forward_list<Disk>::const_iterator it = actors.begin(); it != actors.end(); it++) {
    if(newbie.Overlaps(*it)) {
      return false;
    }
  }
  return true;
}

unsigned int NumIntersections(const double &x, const std::forward_list<Disk> &actors) {
  unsigned int total = 0;
  for(std::forward_list<Disk>::const_iterator it = actors.begin(); it != actors.end(); it++) {
    if((*it).position.x - (*it).radius <= x && x <= (*it).position.x + (*it).radius) {
      total++;
    }
  }
  return total;
}

int main(int argc, char** argv) {
  std::srand(std::time(nullptr));
  std::list<Disk> actors;
  double radius = BOX_LENGTH/(double)NUM_DISKS;
  unsigned int n = 0;
  while(n < NUMDISKS) {
    double x = (BOX_LENGTH - 2 * radius) * (std::rand()/(double)RAND_MAX) + radius;
    double y = (BOX_LENGTH - 2 * radius) * (std::rand()/(double)RAND_MAX) + radius;
    Disk newbie(radius, Vector2D(x, y));
    if(ValidAddition(newbie, actors)) {
        actors.push_back(Disk(radius, Vector2D(x, y)));
        n++;
    }
  }

  //TBD: record initial state

  unsigned int moves = 0;
  while(moves < NUM_MOVES) {
    //get random Disk to walk
    n = std::rand() % actors.size();
    //save reference to Disk, and remove from system
    Disk mover = *(actors.begin()+n);
    actors.erase(actors.begin()+n);
    //create copy of Disk, and move it by delta forward_list
    Disk mover_clone = Disk(mover);
    double dx = DELTA * (2 * std::rand()/(double)RAND_MAX - 1);
    double dy = DELTA * (2 * std::rand()/(double)RAND_MAX - 1);
    mover_clone.position += Vector2D(dx, dy);
    //if result is valid state, keep it, else restore old Disk
    if(ValidAddition(mover_clone, actors)) {
      actors.push_back(mover_clone);
      moves++;
      //TBD: record state after each move
      //
    } else {
      actors.push_back(mover);
    }
  }
}