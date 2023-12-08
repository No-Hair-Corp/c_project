#include "Signals.hpp"


// ===== Constructeur de signals =====

Signals::Signals(int clock_counts, stimulus signal[]):
clock_counts(clock_counts), signal(signal){
  cout << "Constructeur de signals" << endl;
}


// ===== Destructeur de signals =====

Signals::~Signals(){
  cout << "Destructeur de signals" << endl;
}


// ===== Getters =====

Signals::get_clock_counts(){
  return this->clock_counts;
}

Signals::get_signal(){
  return this->signal;
}


// ===== Setters =====

Signals::set_clock_counts(int clock_counts){
  this->clock_counts=clock_counts;
}

Signals::set_signal(stimulus signal[]){
  this->signal=signal;
}
