#include "Output.hpp"

unsigned int Output::min_nb_inputs = 1;
unsigned int Output::default_nb_inputs = 1;
unsigned int Output::max_nb_inputs = 1;

Output::Output():
Gate("Output", "", ' ', Output::default_nb_inputs, Output::min_nb_inputs, Output::default_nb_inputs, Output::max_nb_inputs, false) {
    this->setInputsNames({"i0"});
}

Output::Output(string gate_id, map<string, Gate*>* input_nodes):
Gate("Output", gate_id, ' ', Output::default_nb_inputs, Output::min_nb_inputs, Output::default_nb_inputs, Output::max_nb_inputs, false) {
    this->setInputsNames({"i0"});
    this->setInputNodes(input_nodes);
}

Output::~Output() {

}

int Output::calculateValue(void) {

    Gate *previous_gate;
    this->getInputNode("i0", &previous_gate);
    
    int previous_gate_value;
    previous_gate->getValue(this->getLastCalculationClock(), &previous_gate_value);

    // For an Output, you just get the previous element output
    return previous_gate_value;
}
