#include "Gate.hpp"

Gate::Gate(string name, unsigned int nb_inputs, bool is_sequential):
name(name), nb_inputs(nb_inputs), is_sequential(is_sequential), last_calculation_clock(-1) {

}

Gate::~Gate() {}



// =======  GETTERS / SETTERS =======
unsigned int Gate::getNbInputs(void) const {
    return this->nb_inputs;
}


void Gate::setInputNodes(map<string, Gate*>* new_input_nodes) {
    this->input_nodes = new_input_nodes;
} 

int Gate::getInputNode(string input_name, Gate** node) const {

    if(this->input_nodes->count(input_name) > 0) {
        *node = this->input_nodes->at(input_name);
    } else {
        cout << "Error: Trying to access a non existing input." << endl;
        return 1;
    }
    return 0;
}


void Gate::incrementClockCount(void) {
    this->last_calculation_clock++;
}
int Gate::getLastCalculationClock(void) const {
    return this->last_calculation_clock;
}
void Gate::setLastCalculationClock(int new_clock_count) {
    this->last_calculation_clock = new_clock_count;
}


const string& Gate::getName(void) const {
    return this->name;
}



void Gate::addValue(int value) {
    this->values.push_back(value);
}

int Gate::getValue(int clock_count, int *value) {
    if(clock_count <= this->last_calculation_clock) {
        *value = this->values.at(clock_count);
    } else if(clock_count == this->last_calculation_clock + 1) {
        if(clock_count >= this->values.size()) {
            this->calculateValue();
        }
        *value = this->values.at(clock_count);
    } else {
        cout << "Error: Trying to get a value that is to far in the future." << endl;
        return 1;
    }

    return 0;
}