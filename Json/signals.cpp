#include "Signals.hpp"


// =======  CONSTRUCTOR / DESTRUCTOR =======
Signals::Signals(int clock_counts, bool has_clock_duplication):
clock_counts(clock_counts), has_clock_duplication(has_clock_duplication) {

}

Signals::~Signals(){
  // TODO : Free memory ?
}


// =======  GETTERS / SETTERS =======
unsigned int Signals::getClockCounts() const {
  return this->clock_counts;
}
void Signals::setClockCounts(unsigned int clock_counts){
  this->clock_counts = clock_counts;
}

bool Signals::getHasClockDuplication() const {
  return this->has_clock_duplication;
}
void Signals::setHasClockDuplication(bool has_clock_duplication){
  this->has_clock_duplication = has_clock_duplication;
}


vector<Stimulus*> Signals::getStimuli(void) const {
  return this->signals;
}
int Signals::addSignal(Stimulus *stimulus) {
  this->signals.push_back(stimulus);
  return 0;
}

