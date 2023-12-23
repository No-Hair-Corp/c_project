#include "Mux.hpp"

unsigned int Mux::min_nb_inputs = 2;
unsigned int Mux::default_nb_inputs = 2;
unsigned int Mux::max_nb_inputs = 8;


// =======  CONSTRUCTOR / DESTRUCTOR =======
Mux::Mux():
Gate("Mux", "", '%', Mux::default_nb_inputs, Mux::min_nb_inputs, Mux::default_nb_inputs, Mux::max_nb_inputs, false) {
    this->setInputsNames({"i@", "sel%"});
}

Mux::Mux(string gate_id, map<string, Gate*>* input_nodes, unsigned int nb_inputs):
Gate("Mux", gate_id, '%', nb_inputs, Mux::min_nb_inputs, Mux::default_nb_inputs, Mux::max_nb_inputs, false) {
    this->setInputsNames({"i@", "sel%"});
    this->setInputNodes(input_nodes);    
}

Mux::~Mux() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int Mux::calculateValue(void) {
    Gate *sel_gate, *output_gate;
    int sel_gate_value, output_value;

    bool hasX = false;
    
    int nbOfSel = (int) ceilf(log2f(this->getNbInputs()));
    int output_id = 0;

    for(int i = 0; i < nbOfSel; i++) {
        this->getInputNode("sel"+to_string(i), &sel_gate);
        sel_gate->getValue(this->getLastCalculationClock(), &sel_gate_value);
        
        if(sel_gate_value == -1) {
            hasX = true;
            continue;
        }

        output_id += (1*sel_gate_value << i);
    }

    // TODO: manage multiple outputs ?
    int saveValue = -1; // set to X by default
    for(int i = 0; i < getNbInputs(); i++) {
        this->getInputNode("i"+to_string(i), &output_gate);
        output_gate->getValue(this->getLastCalculationClock(), &output_value);
        if(i == output_id) saveValue = output_value;
    }

    if(hasX) return 1; // one of the sel is X, we can't know the input to select

    if(output_id + 1 > this->getNbInputs()) {
        cout << "[Simulator] Warning: Trying to get a MUX" << this->getNbInputs() << "'s " << output_id
            << " value which doesn't exist. Returning x." << endl;
        return -1;
    }

    
    return saveValue;
}