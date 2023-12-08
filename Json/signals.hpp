#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <fstream>
#include <iostream>
#include <list>
#include "Stimulus.hpp"

using namespace std;

class Signals {

    private:
        int clock_counts;
        list<Stimulus*> signals;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Signals(int clock_counts);
        // Signals(int clock_counts, Stimulus signal[]);
        ~Signals();

        // =======  GETTERS / SETTERS =======
        unsigned getClockCounts() const;
        void setClockCounts(unsigned int clk_count);
        
        int addSignal(Stimulus &signal);
        // Stimulus* getSignals();
};

#endif
