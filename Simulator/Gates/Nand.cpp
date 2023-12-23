#include "Nand.hpp"

unsigned int Nand::min_nb_inputs = 2;
unsigned int Nand::default_nb_inputs = 2;
unsigned int Nand::max_nb_inputs = 9;


// =======  CONSTRUCTOR / DESTRUCTOR =======
Nand::Nand():
Gate("Nand", "", '&', Nand::default_nb_inputs, Nand::min_nb_inputs, Nand::default_nb_inputs, Nand::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
}

Nand::Nand(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("Nand", gate_id, '&', nb_inputs, Nand::min_nb_inputs, Nand::default_nb_inputs, Nand::max_nb_inputs, false) {
    this->setInputsNames({"i@"});
    this->setInputNodes(input_nodes);    
}

Nand::~Nand() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int Nand::calculateValue(void) {
    
    bool hasZero = false;
    bool hasOne = false;
    bool hasX = false;

    // For an Nand, 1+1=0; 1+0=1; 1+x=x; 0+x=1;
    // if there is at least one 0 -> 1
    // else if there is at least one x -> x
    // else -> 1
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

    if(hasZero) {
        return 1;
    } else if(hasX) {
        return -1;
    } else {
        return 0;
    }

    return 0;
}