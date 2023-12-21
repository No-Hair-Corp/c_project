#include "Xor.hpp"

unsigned int Xor::min_nb_inputs = 2;
unsigned int Xor::default_nb_inputs = 2;
unsigned int Xor::max_nb_inputs = 9;


// =======  CONSTRUCTOR / DESTRUCTOR =======
Xor::Xor():
Gate("Xor", "", '&', Xor::default_nb_inputs, Xor::min_nb_inputs, Xor::default_nb_inputs, Xor::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
}

Xor::Xor(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("Xor", gate_id, '&', nb_inputs, Xor::min_nb_inputs, Xor::default_nb_inputs, Xor::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
    this->setInputNodes(input_nodes);    
}

Xor::~Xor() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int Xor::calculateValue(void) {
    this->incrementClockCount();
    
    unsigned int nb_1;
    bool hasX = false;

    // if has at least one x -> return x
    // if nb of 1 odd -> return 1
    // if nb of 1 even -> return 0
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
        this->addValue(-1);
    } else if(nb_1 % 2) {
        this->addValue(0);
    } else {
        this->addValue(1);
    }

    return 0;
}