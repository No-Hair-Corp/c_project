#include "Flipflop.hpp"

unsigned int Flipflop::min_nb_inputs = 0;
unsigned int Flipflop::default_nb_inputs = 0;
unsigned int Flipflop::max_nb_inputs = 0;


// =======  CONSTRUCTOR / DESTRUCTOR =======
Flipflop::Flipflop():
Gate("Flipflop", "", '#', Flipflop::default_nb_inputs, Flipflop::min_nb_inputs, Flipflop::default_nb_inputs, Flipflop::max_nb_inputs, false) {
    this->setInputsNames({"d", "clk"});
}

Flipflop::Flipflop(string gate_id, map<string, Gate*>* input_nodes):
Gate("Flipflop", gate_id, '#', Flipflop::default_nb_inputs, Flipflop::min_nb_inputs, Flipflop::default_nb_inputs, Flipflop::max_nb_inputs, false) {
    this->setInputsNames({"d", "clk"});
    this->setInputNodes(input_nodes);    
}

Flipflop::~Flipflop() {

}



// =======  GETTERS / SETTERS =======




// =======  OTHER FUNCTION =======
int Flipflop::calculateValue(void) {

    Gate *data_gate, *clock_gate;
    this->getInputNode("d", &data_gate);
    this->getInputNode("clk", &clock_gate);

    int data_value, clock_value;
    data_gate->getValue(this->getLastCalculationClock(), &data_value);
    clock_gate->getValue(this->getLastCalculationClock(), &clock_value);
    // we calculate values anyway, to calculate potential before gates

    if(clock_value == 0) {
        if(this->getLastCalculationClock() == 0) {
            return -1; // we have x, because we don't have a previous value
        } else {
            // we get the previous value (we replace data value to avoid creating a useless new value)
            this->getValue(this->getLastCalculationClock() - 1, &data_value);
            return data_value;
        }
    } else if(clock_value == -1) {
        return -1; // clock -1 -> we can't know what we have in output -> x
    } else { // equal to 1 (in theory)
        return data_value; // copy data value
    }

    return 0;
}