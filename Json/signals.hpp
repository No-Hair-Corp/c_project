#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <fstream>
#include <iostream>
#include <vector>
#include "Stimulus.hpp"

using namespace std;

class Signals {

    private:
        int clock_counts;
        bool has_clock_duplication;
        vector<Stimulus*> signals;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Signals(int clock_counts, bool has_clock = false);
        // Signals(int clock_counts, Stimulus signal[]);
        ~Signals();

        // =======  GETTERS / SETTERS =======
        unsigned getClockCounts() const;
        void setClockCounts(unsigned int clk_count);

        bool getHasClockDuplication() const;
        void setHasClockDuplication(bool has_clock_duplication);
        
        vector<Stimulus*> getStimuli(void) const;
        int addSignal(Stimulus *signal);
        // Stimulus* getSignals();
};

#endif
