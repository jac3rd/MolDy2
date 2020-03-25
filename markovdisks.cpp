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

//returns number of disks that are at least partially contained in bin of width bin_width centered on bin_center
unsigned int NumIntersections(const double &bin_center, const double &bin_width, const std::forward_list<Disk> &actors) {
  unsigned int total = 0;
  for(std::forward_list<Disk>::const_iterator it = actors.begin(); it != actors.end(); it++) {
    if((*it).position.x - (*it).radius <= x + bin_width/2 && x - bin_width/2 <= (*it).position.x + (*it).radius) {
      total++;
    }
  }
  return total;
}

int main(int argc, char** argv) {
  std::srand(std::time(nullptr));
  std::list<Disk> actors;
  const double radius = BOX_LENGTH/(double)NUM_DISKS;
  unsigned int n = 0;
  while(n < NUMDISKS) {
    const double x = (BOX_LENGTH - 2 * radius) * (std::rand()/(double)RAND_MAX) + radius;
    const double y = (BOX_LENGTH - 2 * radius) * (std::rand()/(double)RAND_MAX) + radius;
    Disk newbie(radius, Vector2D(x, y));
    if(ValidAddition(newbie, actors)) {
        actors.push_back(Disk(radius, Vector2D(x, y)));
        n++;
    }
  }

  const double bin_width = BOX_LENGTH/(double)NUM_BINS;
  //TBD: record initial state with ROOT
  for(double bin_center = bin_width/2; bin_center < BOX_LENGTH; bin_center += bin_width) {
    unsigned int hits = NumIntersections(bin_center, bin_width, actors);
  }

  unsigned int moves = 0;
  while(moves < NUM_MOVES) {
    //get random Disk to walk
    n = std::rand() % actors.size();
    //save reference to Disk, and remove from system
    Disk mover = *(actors.begin()+n);
    actors.erase(actors.begin()+n);
    //create copy of Disk, and move it by delta forward_list
    Disk mover_clone = Disk(mover);
    const double dx = DELTA * (2 * std::rand()/(double)RAND_MAX - 1);
    const double dy = DELTA * (2 * std::rand()/(double)RAND_MAX - 1);
    mover_clone.position += Vector2D(dx, dy);
    //if result is valid state, keep it, else restore old Disk
    if(ValidAddition(mover_clone, actors)) {
      actors.push_back(mover_clone);
      moves++;
      //TBD: record state after each move
      for(double bin_center = bin_width/2; bin_center < BOX_LENGTH; bin_center += bin_width) {
        unsigned int hits = NumIntersections(bin_center, bin_width, actors);
      }
    } else {
      actors.push_back(mover);
    }
  }

  //TBD: normalize results
}