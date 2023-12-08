#ifndef _SIGNALS_H
#define _SIGNALS_H

#include "RSJparser.tcc"
#include <fstream>
#include <iostream>
#include "Stimulus.hpp"

using namespace std;

class Signals {

private:

  int clock_counts;
  stimulus signal[];

public:

  Signals(int clock_counts, stimulus signal[]);

  ~Signals();

  int get_clock_counts();
  stimulus* get_signals();

  void set_clock_counts(int);
  void set_signal(stimulus*);

};

#endif
