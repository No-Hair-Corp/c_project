#include "Input.hpp"

unsigned int Input::min_nb_inputs = 0;
unsigned int Input::default_nb_inputs = 0;
unsigned int Input::max_nb_inputs = 0;



// =======  CONSTRUCTOR / DESTRUCTOR =======
Input::Input():
Gate("Input", "", Input::default_nb_inputs, Input::min_nb_inputs, Input::default_nb_inputs, Input::max_nb_inputs, false) {
}

Input::Input(string gate_id, Stimulus *values):
Gate("Input", gate_id, Input::default_nb_inputs, Input::min_nb_inputs, Input::default_nb_inputs, Input::max_nb_inputs, false) {

    this->setValues(values);
}

Input::~Input() {

}



// =======  GETTERS / SETTERS =======
int Input::setValues(Stimulus* signal) {
    // '0' -> 0; '1' -> 1; 'x' -> -1
    for(unsigned int i = 0; i < signal->getValue().length(); i++) {
        if(signal->getValue()[i] == 'x') {
            this->addValue(-1);
        } else {
            this->addValue(signal->getValue()[i] - '0');
        }
    } 
    
    this->setLastCalculationClock(signal->getValue().length() - 1);

    return 0;
}



// =======  OTHER FUNCTIONS =======
int Input::calculateValue(void) {
    return 0;
}

