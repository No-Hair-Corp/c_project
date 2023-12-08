#include "signals.hpp"


// ===== Constructeur de signals =====

signals::signals(int clok_counts, stimulus signal[]):
clock_counts(clock_counts), signal(signal){
  cout << "Constructeur de signals" << endl;
}


// ===== Destructeur de signals =====

signals::~signals(){
  cout << "Destructeur de signals" << endl;
}


// ===== Getters =====

signals::get_clock_counts(){
  return this->clock_counts;
}

signals::get_signal(){
  return this->signal;
}
