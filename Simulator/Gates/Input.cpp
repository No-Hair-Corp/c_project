#include "Input.hpp"

Input::Input(Stimulus *values):
Gate("Input", 0, false) {

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


int Input::calculateValue(void) {
    return 0;
}