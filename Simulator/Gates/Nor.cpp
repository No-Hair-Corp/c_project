#include "Nor.hpp"

unsigned int Nor::min_nb_inputs = 2;
unsigned int Nor::default_nb_inputs = 2;
unsigned int Nor::max_nb_inputs = 9;


// =======  CONSTRUCTOR / DESTRUCTOR =======
Nor::Nor():
Gate("Nor", "", '}', Nor::default_nb_inputs, Nor::min_nb_inputs, Nor::default_nb_inputs, Nor::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
}

Nor::Nor(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("Nor", gate_id, '}', nb_inputs, Nor::min_nb_inputs, Nor::default_nb_inputs, Nor::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
    this->setInputNodes(input_nodes);    
}

Nor::~Nor() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int Nor::calculateValue(void) {
    
    bool hasZero = false;
    bool hasOne = false;
    bool hasX = false;

    // For an Nor, 1+1=0; 1+0=0; 1+x=0; 0+x=x; 0+0=1
    // if there is at least one 1 -> 0
    // else if there is at least one x -> x
    // else -> 0
    for(unsigned int i = 0; i < this->getNbInputs(); i++) {
        Gate *previous_gate;
        this->getInputNode("i"+to_string(i), &previous_gate);

        int previous_gate_value;
        previous_gate->getValue(this->getLastCalculationClock(), &previous_gate_value);

        if(previous_gate_value == 0) {
            hasZero = true;
        } else if(previous_gate_value == 1) {
            hasOne = true;
        } else if(previous_gate_value == -1) {
            hasX = true;
        }
    }

    if(hasOne) {
        return 0;
    } else if(hasX) {
        return -1;
    } else {
        return 1;
    }
}