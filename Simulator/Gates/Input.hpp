#ifndef _INPUT_GATE_H_
#define _INPUT_GATE_H_

#include "../../Json/Stimulus.hpp"
#include "../Gate.hpp"
#include <string>
#include <list>
#include <cstdlib>

using namespace std;

class Input : public Gate {
    private:      

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Input(Stimulus *values);
        ~Input();


        // =======  GETTERS / SETTERS =======



        // =======  OTHER FUNCTION =======
        int calculateValue(void);// -> return errorCode not value ;)

};


#endif