#ifndef _OUTPUT_GATE_H_
#define _OUTPUT_GATE_H_

#include "../Gate.hpp"
#include <string>
#include <list>

using namespace std;

class Output : public Gate {
    private:        

    public:
        // =======  STATICS =======
        static list<string> inputs_names;

        static unsigned int min_nb_inputs;
        static unsigned int default_nb_inputs;
        static unsigned int max_nb_inputs;

        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Output();
        Output(map<string, Gate*>* input_nodes);
        ~Output();


        // =======  GETTERS / SETTERS =======



        // =======  OTHER FUNCTION =======
        int calculateValue(void); //-> return errorCode not value ;)
};


#endif