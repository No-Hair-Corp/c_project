#include "Nxor.hpp"

unsigned int Nxor::min_nb_inputs = 2;
unsigned int Nxor::default_nb_inputs = 2;
unsigned int Nxor::max_nb_inputs = 9;


// =======  CONSTRUCTOR / DESTRUCTOR =======
Nxor::Nxor():
Gate("Nxor", "", '^', Nxor::default_nb_inputs, Nxor::min_nb_inputs, Nxor::default_nb_inputs, Nxor::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
}

Nxor::Nxor(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("Nxor", gate_id, '^', nb_inputs, Nxor::min_nb_inputs, Nxor::default_nb_inputs, Nxor::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
    this->setInputNodes(input_nodes);    
}

Nxor::~Nxor() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int Nxor::calculateValue(void) {
    unsigned int nb_1 = 0;
    bool hasX = false;

    // if has at least one x -> return x
    // if nb of 1 odd -> return 0
    // if nb of 1 even -> return 1
    for(unsigned int i = 0; i < this->getNbInputs(); i++) {
        Gate *previous_gate;
        this->getInputNode("i"+to_string(i), &previous_gate);
        
        int previous_gate_value;
        previous_gate->getValue(this->getLastCalculationClock(), &previous_gate_value);

        if(previous_gate_value == 1) {
            nb_1++;
        } else if (previous_gate_value == -1) {
            hasX = true;
        }
    }

    if (hasX) {
        return -1;
    } else if(nb_1 > 0 && nb_1 % 2) {
        return 0; // invert of xor
    } else {
        return 1; // invert of xor
    }

    return 0;
}