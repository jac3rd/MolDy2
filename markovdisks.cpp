#include "include.h"
#include <cstdlib>
#include <ctime>
#include <list>
#include "TH1.h"
#include "TCanvas.h"
#include "TImage.h"

#define NUM_DISKS 64
#define DELTA 0.1
#define BOX_LENGTH 1
#define NUM_MOVES 100000
#define NUM_BINS 10

bool ValidAddition(const Disk &newbie, const std::list<Disk> &actors) {
  for(std::list<Disk>::const_iterator it = actors.begin(); it != actors.end(); it++) {
    if(newbie.Overlaps(*it)) {
      return false;
    }
  }
  if(newbie.position.x - newbie.radius < 0 || newbie.position.x + newbie.radius > BOX_LENGTH)
    return false;
  if(newbie.position.y - newbie.radius < 0 || newbie.position.y + newbie.radius > BOX_LENGTH)
    return false;
  return true;
}

//returns number of disks that are at least partially contained in bin of width bin_width centered on bin_center
unsigned int NumIntersections(const double &bin_center, const double &bin_width, const std::list<Disk> &actors) {
  unsigned int total = 0;
  for(std::list<Disk>::const_iterator it = actors.begin(); it != actors.end(); it++) {
    if((*it).position.x - (*it).radius <= bin_center + bin_width/2 && bin_center - bin_width/2 <= (*it).position.x + (*it).radius) {
      total++;
    }
  }
  return total;
}

int main(int argc, char** argv) {
  std::srand(std::time(nullptr));
  std::list<Disk> actors;
  const double radius = BOX_LENGTH/(double)NUM_DISKS/4;
  unsigned int n = 0;
  while(n < NUM_DISKS) {
    const double x = (BOX_LENGTH - 2 * radius) * (1.0*std::rand()/((double)RAND_MAX)) + radius;
    const double y = (BOX_LENGTH - 2 * radius) * (1.0*std::rand()/((double)RAND_MAX)) + radius;
    Disk newbie(radius, Vector2D(x, y));
    if(ValidAddition(newbie, actors)) {
        actors.push_back(Disk(radius, Vector2D(x, y)));
        n++;
    }
  }

  const std::string box_length_string = std::to_string(BOX_LENGTH);
  const std::string num_disks_string = std::to_string(NUM_DISKS);
  const std::string radius_string = std::to_string(radius);
  const std::string num_moves_string = std::to_string(NUM_MOVES);
  const std::string delta_string = std::to_string(DELTA);
  TH1D* h = new TH1D((const char*)"h", (const char*)("X-Positions of "+num_disks_string+" r="+radius_string+" Disks in "+box_length_string+"-by-"+box_length_string+" Box over "+num_moves_string+" Markov Steps with delta_max="+delta_string+";X-Position;Disks").c_str(), (Int_t)NUM_BINS, (Double_t)0, (Double_t)BOX_LENGTH); 
  const double bin_width = h->GetBinWidth(1);
  //TBD: record initial state with ROOT
  for(double bin_center = bin_width/2; bin_center < BOX_LENGTH; bin_center += bin_width) {
    unsigned int hits = NumIntersections(bin_center, bin_width, actors);
    while(hits > 0) {
      h->Fill(bin_center);
      hits--;
    }
  }

  unsigned int moves = 0;
  while(moves < NUM_MOVES) {
    //get random Disk to walk
    n = std::rand() % actors.size();
    //save reference to Disk, and remove from system
    std::list<Disk>::iterator it = actors.begin();
    std::advance(it, n);
    Disk mover = *(it);
    actors.erase(it);
    //create copy of Disk, and move it by delta forward_list
    Disk mover_clone = Disk(mover);
    const double dx = DELTA * (2 * std::rand()/((double)RAND_MAX) - 1);
    const double dy = DELTA * (2 * std::rand()/((double)RAND_MAX) - 1);
    mover_clone.position += Vector2D(dx, dy);
    //if result is valid state, keep it, else restore old Disk
    if(ValidAddition(mover_clone, actors)) {
      actors.push_back(mover_clone);
      moves++;
      //TBD: record state after each move
      for(double bin_center = bin_width/2; bin_center < BOX_LENGTH; bin_center += bin_width) {
        unsigned int hits = NumIntersections(bin_center, bin_width, actors);
	while(hits > 0) {
	  h->Fill(bin_center);
	  hits--;
	}
      }
    } else {
      actors.push_back(mover);
    }
  }

  TCanvas* c = new TCanvas();
  h->Draw();
  c->Update();
  TImage* img = TImage::Create();
  img->FromPad(c);
  img->WriteImage("markovdisks.png");
  
}
