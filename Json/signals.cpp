#include "Signals.hpp"


// =======  CONSTRUCTOR / DESTRUCTOR =======
Signals::Signals(int clock_counts):
clock_counts(clock_counts) {

}

Signals::~Signals(){

}


// =======  GETTERS / SETTERS =======
unsigned int Signals::getClockCounts() const {
  return this->clock_counts;
}
void Signals::setClockCounts(unsigned  clock_counts){
  this->clock_counts = clock_counts;
}


int Signals::addSignal(Stimulus& stimulus) {
  // return this->signal;
  return 0;
}

