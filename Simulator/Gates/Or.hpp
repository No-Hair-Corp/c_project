#ifndef _OR_GATE_H_
#define _OR_GATE_H_

#include "../Gate.hpp"
#include <string>
#include <list>

using namespace std;

class Or : public Gate {
    private:        

    public:
        // =======  STATICS =======
        static list<string> inputs_names;
        static unsigned int min_nb_inputs;
        static unsigned int default_nb_inputs;
        static unsigned int max_nb_inputs;


        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Or();
        Or(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs);
        ~Or();


        // =======  GETTERS / SETTERS =======



        // =======  OTHER FUNCTION =======
        int calculateValue(void);  //-> return errorCode not value ;)
};


#endif