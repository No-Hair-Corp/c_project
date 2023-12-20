#include "Mux.hpp"

unsigned int Mux::min_nb_inputs = 2;
unsigned int Mux::default_nb_inputs = 2;
unsigned int Mux::max_nb_inputs = 8;


// =======  CONSTRUCTOR / DESTRUCTOR =======
Mux::Mux():
Gate("Mux", "", '%', Mux::default_nb_inputs, Mux::min_nb_inputs, Mux::default_nb_inputs, Mux::max_nb_inputs, false) {
    this->setInputsNames({"i@", "sel"});
}

Mux::Mux(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("Mux", gate_id, '%', nb_inputs, Mux::min_nb_inputs, Mux::default_nb_inputs, Mux::max_nb_inputs, false) {
    this->setInputsNames({"i@", "sel"});
    this->setInputNodes(input_nodes);    
}

Mux::~Mux() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int Mux::calculateValue(void) {
    this->incrementClockCount();

    // TODO: calculate output

    return 0;
}