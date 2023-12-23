#include "Gate.hpp"

#define MAX_LOOP_ITERATION 20


bool Gate::loop_error = false;
unsigned int Gate::values_history_iterator = 0;

// =======  CONSTRUCTOR / DESTRUCTOR =======
Gate::Gate(string name, string gate_id, char gate_sign, unsigned int nb_inputs,unsigned int min_nb_inputs,
    unsigned int default_nb_inputs, unsigned int max_nb_inputs, bool is_sequential):
name(name), gate_id(gate_id), gate_sign(gate_sign), is_sequential(is_sequential), nb_inputs(nb_inputs),
    min_nb_inputs(min_nb_inputs), default_nb_inputs(default_nb_inputs), max_nb_inputs(max_nb_inputs),
    last_calculation_clock(-1) {

    this->input_nodes = new map<string, Gate*>;
}

Gate::~Gate() {}



// =======  GETTERS / SETTERS =======
const string& Gate::getName(void) const {
    return this->name;
}

const string& Gate::getGateId(void) const {
    return this->gate_id;
}
void Gate::setGateId(const string& new_gate_id) {
    this->gate_id = new_gate_id;
}

char Gate::getGateSign(void) const {
    return this->gate_sign;
}



bool Gate::getIsSequential(void) const {
    return this->is_sequential;
}

unsigned int Gate::getNbInputs(void) const {
    return this->nb_inputs;
}
int Gate::setNbInputs(unsigned int new_nb_inputs) {
    if(new_nb_inputs > this->max_nb_inputs) {
        Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, this->name + " can't have more than " + to_string(this->max_nb_inputs) + " inputs.");
        return 1;
    }

    if(new_nb_inputs < this->min_nb_inputs) {
        Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, this->name + " can't have less than " + to_string(this->min_nb_inputs) + " inputs.");
        return 2;
    }

    this->nb_inputs = new_nb_inputs;
    return 0;
}


unsigned int Gate::getMinNbInputs() const {
    return this->min_nb_inputs;
}
unsigned int Gate::getDefaultNbInputs() const {
    return this->default_nb_inputs;
}
unsigned int Gate::getMaxNbInputs() const {
    return this->max_nb_inputs;
}

void Gate::setInputsNames(const list<string>& new_value) {
    this->inputs_names = new_value;
}
list<string>* Gate::getInputsNames() {
    return &this->inputs_names;
}

void Gate::setInputNodes(map<string, Gate*>* new_input_nodes) {
    this->input_nodes = new_input_nodes;
} 
void Gate::addInputNode(const string& input_name, Gate* linked_gate) {
    this->input_nodes->insert({input_name, linked_gate});
}
int Gate::getInputNode(string input_name, Gate** node) const {
    if(this->input_nodes->count(input_name) > 0) {
        *node = this->input_nodes->at(input_name);
    } else {
        Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Trying to access a non existing input.");
        return 1;
    }
    return 0;
}
const map<string, Gate*>* Gate::getInputNodes(void) {
    return this->input_nodes;
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

void Gate::addValue(int value) {
    this->values.push_back(value);
}
int Gate::setValue(int clock_count, int value) {
        if(clock_count <= this->getLastCalculationClock()) {
        if(this->values.size() == clock_count) {
            this->values.push_back(value);
        } else {
            this->values[clock_count] = value;
        }
    } else {
        Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Can't set a value in the future.");
        return 1;
    }
    return 0;
}
int Gate::getValue(int clock_count, int *value) {
    if(loop_error) return 2;

    if(Gate::values_history_iterator > MAX_LOOP_ITERATION) {
        Gate::loop_error = true;
        return 2;
    }

    if(!this->getHadCalculatedValue()) {
        if(this->getName() != "Input") {
            this->incrementClockCount(); 
            this->setHadCalculatedValue(true);
        }

        if(clock_count < this->values.size()) { // the value is in the past 
            *value = this->values.at(clock_count); // -> we just give it

            return 0; // no further thing to check
        } else if (clock_count > this->values.size() + 1) {
            Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Trying to get a value that is in the future.");
            return 1;
        } else { // we never calculated the value, we calculate it
            int calculated_value = this->calculateValue(); // we calculate the value, save it, and return it
            this->addValue(calculated_value);
            *value = calculated_value;
        }
    } else { // we already were is this gate
        // 
        if(Gate::values_history_iterator == 0) {// we never started the cycle iterator,
            if(clock_count == 0) { // first clock, we can't get previous value
                *value = -1; // -> return x
            } else {
                *value = this->values[clock_count - 1];  // get the value at previous clock
            }
    
            Gate::values_history_iterator++; // increment the values iterator
        } else { // we need to take the value calculated before but at that clock count
            // if inputs has change -> recalulate

            Gate::values_history_iterator++; // increment the values iterator

            bool gate_has_changed = false;
            for(auto const& el : *this->getInputNodes()) {
                Gate* prev_gate = el.second;
                if(prev_gate->last_calculated_values.size() > 1) {
                    int prev_value = prev_gate->last_calculated_values[prev_gate->last_calculated_values.size() - 2];
                    if(prev_value != prev_gate->last_calculated_values.back()) {
                        *value = this->calculateValue();
                        gate_has_changed = true;
                    }
                }
            }

            if(!gate_has_changed) {
                *value = this->last_calculated_values.back();
            }
        }
    }

    this->last_calculated_values.push_back(*value);
    if(this->last_calculated_values.size() > 1) {
        int previous_value = this->last_calculated_values.at(this->last_calculated_values.size() - 2);
        if(previous_value != *value) {
            *value = this->calculateValue();
        }
    }

    if(loop_error) return 2;

    return 0;
}

bool Gate::getHadCalculatedValue(void) const {
    return this->had_calculate_value;
}
void Gate::setHadCalculatedValue(bool new_value) {
    this->had_calculate_value = new_value;
}


void Gate::resetValuesHistory(void) {
    Gate::values_history_iterator = 0;
}

void Gate::resetLastValues(void) {
    this->last_calculated_values.clear();
}





// =======  OTHER FUNCTIONS =======
string Gate::to_str(void) const {
    string tmp_value;

    for(const int& value : this->values) {
        if(value == -1) {
            tmp_value.push_back('x');
        }  else {
            tmp_value.push_back((char)('0'+value));
        }
    }

    return tmp_value;
}

ostream& operator<<(ostream& out, const Gate &gate) {
    out << gate.to_str();
    return out;
}