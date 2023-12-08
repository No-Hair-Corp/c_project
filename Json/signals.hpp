#ifndef _SIGNALS_H
#define _SIGNALS_H

#include "RSJparser.tcc"
#include <fstream>
#include <iostream>
#include "stimulus.hpp"

using namespace std;

class signals {

private:

  int clock_counts;
  stimulus signal[];

public:

  signals(int clok_counts, stimulus signal[]);

  ~signals();

  int get_clock_counts();
  stimulus* get_signals();

  void set_clock_counts(int);
  void set_signal(stimulus*);

};

#endif
