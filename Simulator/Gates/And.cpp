#include "And.hpp"

list<string> And::inputs_names = {"i@"};


And::And(map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("AND", nb_inputs, false) {
    this->setInputNodes(input_nodes);    
}

And::~And() {

}


int And::calculateValue(void) {
    
    this->incrementClockCount();

    bool hasZero = false;
    bool hasOne = false;
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
            break; // we have a 0; no need to go further
        } else if(previous_gate_value == 1) {
            hasOne = true;
        } else if(previous_gate_value == -1) {
            hasX = true;
        }
    }

    if(hasZero) {
        this->addValue(0);
    } else if(hasX) {
        this->addValue(-1);
    } else {
        this->addValue(1);
    }

    return 0;
}