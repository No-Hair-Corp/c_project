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


map<string, Stimulus*> Signals::getStimuli(void) const {
  return this->signals;
}
Stimulus* Signals::getStimulus(const string& name) const {
  // TODO: check if it exists
  return this->signals.at(name);
}

int Signals::addSignal(const string& signal_name, Stimulus *stimulus) {
  this->signals.insert({signal_name, stimulus});
  return 0;
}

