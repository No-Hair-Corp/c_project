#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include "Gate.hpp"
#include <string>
#include <iostream>

using namespace std;

class Simulator {
    private:
        unsigned int current_clock_count;

        bool has_sequential;

        

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Simulator();
        // ~Simulator();



        // =======  GETTERS / SETTERS =======



        // =======  OTHER FUNCTION =======
       // int checkAllGates(); -> register if there is sequential stuff, check input/output number consistency,
       //                     ambiguity on naming, that is exists...
};


#endif