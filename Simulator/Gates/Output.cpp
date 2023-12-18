#include "Output.hpp"

list<string> Output::inputs_names = {"in"};


Output::Output(map<string, Gate*>* input_nodes):
Gate("Output", 1, false) {
    this->setInputNodes(input_nodes);
}

Output::~Output() {

}

int Output::calculateValue(void) {
    
    Gate *previous_gate;
    this->getInputNode("in", &previous_gate);
    
    this->incrementClockCount();

    int previous_gate_value;
    previous_gate->getValue(this->getLastCalculationClock(), &previous_gate_value);

    // For an Output, you just get the previous element output
    this->addValue(previous_gate_value);

    return 0;
}
