#include "Or.hpp"

unsigned int Or::min_nb_inputs = 2;
unsigned int Or::default_nb_inputs = 2;
unsigned int Or::max_nb_inputs = 9;


// =======  CONSTRUCTOR / DESTRUCTOR =======
Or::Or():
Gate("Or", "", '|', Or::default_nb_inputs, Or::min_nb_inputs, Or::default_nb_inputs, Or::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
}

Or::Or(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("Or", gate_id, '|', nb_inputs, Or::min_nb_inputs, Or::default_nb_inputs, Or::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
    this->setInputNodes(input_nodes);    
}

Or::~Or() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int Or::calculateValue(void) {
    
    bool hasOne = false;
    bool hasX = false;

    // For an Or, 1+1=1; 1+0=1; 1+x=1; 0+x=x; 0+0=0
    // if there is at least one 1 -> 1
    // else if there is at least one x -> x
    // else -> 0
    for(unsigned int i = 0; i < this->getNbInputs(); i++) {
        Gate *previous_gate;
        this->getInputNode("i"+to_string(i), &previous_gate);
        
        int previous_gate_value;
        previous_gate->getValue(this->getLastCalculationClock(), &previous_gate_value);

        if(previous_gate_value == 1) {
            hasOne = true;
        } else if(previous_gate_value == -1) {
            hasX = true;
        }
    }

    if(hasOne) {
        return 1;
    } else if(hasX) {
        return -1;
    } else {
        return 0;
    }

    return 0;
}