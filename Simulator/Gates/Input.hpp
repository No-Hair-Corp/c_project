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
        static unsigned int min_nb_inputs;
        static unsigned int default_nb_inputs;
        static unsigned int max_nb_inputs;
        
    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Input();
        Input(string gate_id, Stimulus *values);
        ~Input();



        // =======  GETTERS / SETTERS =======
        int setValues(Stimulus* signal);


        // =======  OTHER FUNCTIONS =======
        int calculateValue(void);// -> return errorCode not value ;)

};


#endif