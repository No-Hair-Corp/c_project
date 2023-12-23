#include "And.hpp"

unsigned int And::min_nb_inputs = 2;
unsigned int And::default_nb_inputs = 2;
unsigned int And::max_nb_inputs = 9;


// =======  CONSTRUCTOR / DESTRUCTOR =======
And::And():
Gate("And", "", '&', And::default_nb_inputs, And::min_nb_inputs, And::default_nb_inputs, And::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
}

And::And(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("And", gate_id, '&', nb_inputs, And::min_nb_inputs, And::default_nb_inputs, And::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
    this->setInputNodes(input_nodes);    
}

And::~And() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int And::calculateValue(void) {
    
    bool hasZero = false;
    bool hasX = false;

    // For an And, 1+1=1; 1+0=0; 1+x=x; 0+x=0;
    // if there is at least one 0 -> 0
    // else if there is at least one x -> x
    // else -> 1
    for(unsigned int i = 0; i < this->getNbInputs(); i++) {
        Gate *previous_gate;
        this->getInputNode("i"+to_string(i), &previous_gate);
        
        int previous_gate_value;
        previous_gate->getValue(this->getLastCalculationClock(), &previous_gate_value);

        if(previous_gate_value == 0) {
            hasZero = true;
        } else if(previous_gate_value == -1) {
            hasX = true;
        }
    }

    if(hasZero) {
        return 0;
    } else if(hasX) {
        return -1;
    } else {
        return 1;
    }

    return 0;
}