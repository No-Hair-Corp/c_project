#include "Input.hpp"

unsigned int Input::min_nb_inputs = 0;
unsigned int Input::default_nb_inputs = 0;
unsigned int Input::max_nb_inputs = 0;



// =======  CONSTRUCTOR / DESTRUCTOR =======
Input::Input():
Gate("Input", Input::default_nb_inputs, Input::min_nb_inputs, Input::default_nb_inputs, Input::max_nb_inputs, false) {
}

Input::Input(Stimulus *values):
Gate("Input", Input::default_nb_inputs, Input::min_nb_inputs, Input::default_nb_inputs, Input::max_nb_inputs, false) {

    // TODO: move signals assignation to a function that can be called later (setSignals() for example)

    // '0' -> 0; '1' -> 1; 'x' -> -1
    for(unsigned int i = 0; i < values->getValue().length(); i++) {
        if(values->getValue()[i] == 'x') {
            this->addValue(-1);
        } else {
            this->addValue(values->getValue()[i] - '0');
        }
    } 
    
    this->setLastCalculationClock(values->getValue().length() - 1);
}

Input::~Input() {

}



// =======  GETTERS / SETTERS =======


// =======  OTHER FUNCTIONS =======
int Input::calculateValue(void) {
    return 0;
}

