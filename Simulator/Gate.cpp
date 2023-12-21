#include "Gate.hpp"


unsigned int Gate::values_history_iterator = 0;
map<string, int> Gate::values_history;
vector<string> Gate::tmp_test;

// =======  CONSTRUCTOR / DESTRUCTOR =======
Gate::Gate(string name, string gate_id, char gate_sign, unsigned int nb_inputs,unsigned int min_nb_inputs,
    unsigned int default_nb_inputs, unsigned int max_nb_inputs, bool is_sequential):
name(name), gate_id(gate_id), gate_sign(gate_sign), is_sequential(is_sequential), nb_inputs(nb_inputs),
    min_nb_inputs(min_nb_inputs), default_nb_inputs(default_nb_inputs), max_nb_inputs(max_nb_inputs),
    last_calculation_clock(-1) {

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
        cout << this->name << " can't have more than " << this->max_nb_inputs << " inputs." << endl;
        return 1;
    }

    if(new_nb_inputs < this->min_nb_inputs) {
        cout << this->name << " can't have less than " << this->min_nb_inputs << " inputs." << endl;
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
    if(this->input_nodes == NULL) { // create instance if doens't exist yet
        this->input_nodes = new map<string, Gate*>;
    }

    this->input_nodes->insert({input_name, linked_gate});
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
        //TODO: throw error 'cause it's in the future
        cout << "Error: can't" << endl;
        return 1;
    }
    return 0;
}
int Gate::getValue(int clock_count, int *value) {
    if(!this->getHadCalculatedValue()) {
        if(this->getName() != "Input") {
            this->incrementClockCount(); 
            this->setHadCalculatedValue(true);
        }

        if(clock_count < this->values.size()) {
            *value = this->values.at(clock_count);
        } else if(clock_count == this->values.size()) {
            // this->calculateValue();
            this->addValue(this->calculateValue());
            *value = this->values.at(clock_count);
        } else {
            cout << "Error: Trying to get a value that is in the future." << endl;
            return 1;
        }
    } else {
        // we've already been here
        if(Gate::values_history_iterator) {
            bool skip = false;
            for(string name : Gate::tmp_test) {
                for(auto const& el : *this->getInputNodes()) {
                    if(el.second->getGateId() == name) {
                        *value = this->calculateValue();
                        this->values[clock_count] = *value;
                        skip = true;
                    }
                }
            }
            if(!skip) {
                *value = this->values.at(clock_count);
            }
        } else if(clock_count > 0) {
            *value = this->values.at(clock_count - 1);
        } else {
            *value = -1;
            // *value = -1;
        }
        
        Gate::values_history_iterator++;
        Gate::setValueHistory(this->getGateId(), *value);
    }

    if(Gate::values_history.count(this->getGateId())) {
        if(Gate::getValueHistory(this->getGateId()) != *value) {
            Gate::tmp_test.push_back(this->getGateId());
            int tmp = this->calculateValue();
            Gate::tmp_test.pop_back();

            *value = tmp;
            Gate::setValueHistory(this->getGateId(), *value);
        }
    }

    return 0;
}

bool Gate::getHadCalculatedValue(void) const {
    return this->had_calculate_value;
}
void Gate::setHadCalculatedValue(bool new_value) {
    this->had_calculate_value = new_value;
}


int Gate::getValueHistory(string gate_id) {
    return Gate::values_history[gate_id];
}
void Gate::setValueHistory(string gate_id, int new_value) {
    if(Gate::values_history.count(gate_id)) {
        Gate::values_history[gate_id] = new_value;
    } else {
        Gate::values_history.insert({gate_id,  new_value});
    }
}
void Gate::resetValuesHistory(void) {
    Gate::values_history_iterator = 0;
    Gate::values_history.clear();
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