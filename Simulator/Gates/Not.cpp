#include "Not.hpp"

list<string> Not::inputs_names = {"i0"};

unsigned int Not::min_nb_inputs = 1;
unsigned int Not::default_nb_inputs = 1;
unsigned int Not::max_nb_inputs = 1;


Not::Not():
Gate("Not", "", '!', Not::default_nb_inputs, Not::min_nb_inputs, Not::default_nb_inputs, Not::max_nb_inputs, false) {
    this->setInputsNames({"i0"});
}

Not::Not(string gate_id, map<string, Gate*>* input_nodes):
Gate("Not", gate_id, '!', Not::default_nb_inputs, Not::min_nb_inputs, Not::default_nb_inputs, Not::max_nb_inputs, false) {
    this->setInputsNames({"i0"});
    this->setInputNodes(input_nodes);
}

Not::~Not() { }


int Not::calculateValue(void) {
    this->incrementClockCount();
    
    Gate *previous_gate;
    this->getInputNode("i0", &previous_gate);
    
    int previous_gate_value;
    previous_gate->getValue(this->getLastCalculationClock(), &previous_gate_value);

    // For a Not, we invert 1 and 0, keep x 
    switch (previous_gate_value) {
        case 0:
            previous_gate_value = 1;
            break;
        
        case 1:
            previous_gate_value = 0;
            break;
        
        default:
            previous_gate_value = -1;
            break;
    }

    this->addValue(previous_gate_value);

    return 0;
}