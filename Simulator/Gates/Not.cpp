#include "Not.hpp"

list<string> Not::inputs_names = {"in"};


Not::Not(map<string, Gate*>* input_nodes):
Gate("Not", 0, false) {
    this->setInputNodes(input_nodes);    
}

Not::~Not() { }


int Not::calculateValue(void) {
    
    Gate *previous_gate;
    this->getInputNode("in", &previous_gate);
    
    this->incrementClockCount();

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