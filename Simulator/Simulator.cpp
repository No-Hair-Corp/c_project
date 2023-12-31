#include "Simulator.hpp"

// Map to instanciate Gate() from string name
map<string, function<Gate*()>> Simulator::existing_gates = {
    {"input", []() -> Gate* { return new Input; } },
    {"output", []() -> Gate* { return new Output; } },
    {"not", []() -> Gate* { return new Not; } },
    {"and", []() -> Gate* { return new And; } },
    {"nand", []() -> Gate* { return new Nand; } },
    {"or", []() -> Gate* { return new Or; } },
    {"nor", []() -> Gate* { return new Nor; } },
    {"xor", []() -> Gate* { return new Xor; } },
    {"xnor", []() -> Gate* { return new Nxor; } },
    {"mux", []() -> Gate* { return new Mux; } },
    {"ff", []() -> Gate* { return new Flipflop; } },
};



// =======  CONSTRUCTOR / DESTRUCTOR =======
Simulator::Simulator(const string& dot_file_path, const string& json_file_path):
current_clock_count(0), dot_file_path(dot_file_path), json_file_path(json_file_path), has_sequential(false) {

    this->error_code = SIM_SUCCESS;

    // parsing json and preparing DOT
    this->dot = new Dot(dot_file_path);
    this->json = new Json(json_file_path);

    // running dot lexing and parsing 
    this->dot->lexer();
    
    if(this->dot->parse()) {
        this->error_code = SIM_PARSE_ERROR;
        return;
    }

    // check consistancy of inputs between json and dot
    if(this->checkInputs()) {
        this->error_code = SIM_INPUTS_INCONSISTENCY_ERROR;
        return;
    }

    
    // check that gates exist and are correctly given (nb of inputs, name, ...)
    if(this->checkAllGates()) {
        this->error_code = SIM_BAD_GATE_ERROR;
        return;
    }

    // generate link between Gates
    if(this->setLinks()) {
        this->error_code = SIM_LINK_ERROR;
        return;
    }

    if(this->runSimulation()) {
        this->error_code = SIM_SIMULATION_ERROR;
        return;
    }
}

Simulator::~Simulator() {
    delete this->dot;
    delete this->json;
    for(auto const& el : this->gates_graph) {
        delete el.second; // free dynamically created gates
    }
}



// =======  GETTERS / SETTERS =======
SimulatorErrorCodes Simulator::getErrorCode(void) const {
    return this->error_code;
}

map<string, Gate*> Simulator::getGates(void) {
    return this->gates_graph;
}
unordered_set<Gate*> Simulator::getOutputGates(void) {
    return this->output_gates;
}



// =======  OTHER FUNCTIONS =======
int Simulator::checkInputs(void) {
    map<string, SchematicObject*> SOList = this->dot->getSchematicObjectsList();

    unordered_set<string> input_names; // json's inputs

    for(auto const& el : this->json->getSignals()->getStimuli()) {
        input_names.emplace(el.first);
    }

    if(input_names.size() < 1) {
        Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Waveform doesn't have any input.");
        return 1;
    }

    unsigned int nb_dot_inputs = 0;
    for(auto const& el: SOList) {
        string lower_name =  el.second->getGateType();
        transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

        if(lower_name == "input") { // verify dot's input with json
            if(!input_names.count(el.second->getGateId())) {
                Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Input " + el.second->getGateId() +
                    " doesn't exist in waveform file.");
                return 2;
            }
            nb_dot_inputs++;
        }
    }


    if(nb_dot_inputs != input_names.size()) {
        Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "The Dot and the Wavedrom don't have the same number of inputs. Found " + 
            to_string(nb_dot_inputs) + " in Dot, but " + to_string(input_names.size()) + " in Json."); 
        return 3;
    }

    return 0;
}


int Simulator::checkAllGates(void) {
    map<string, SchematicObject*> SOList = this->dot->getSchematicObjectsList();
    bool hasOutput = false;

    for(auto const& el: SOList) { // checking all gates
        string lower_name = el.second->getGateType();
        transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower); // lowering gate type name

        // regex to check gate type format : <type>[nb_inputs][nb_outputs]
        std::regex gate_type_regex("^([a-zA-Z]+)([1-9]?)([1-9]?)$"); 
        std::smatch gate_type_match;
        std::regex_search(lower_name, gate_type_match, gate_type_regex);

        // .size must be 4 -> group 0 general, 1: gate name, 2: nb inputs, 3: nb outputs
        if(gate_type_match.size() != 4) {
            Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Gate type `" + el.second->getGateType() +
                "` is not properly formed. Authorized form : <type>[nb_inputs][nb_outputs].");
            return 1;
        }

        Gate* gate;
        // check if gate exists
        if(!Simulator::existing_gates.count(gate_type_match[1])) {
            string allowed_gates = "";
            for(auto const& el : Simulator::existing_gates) { // small loop just to show availables gates type
                allowed_gates.push_back(' ');
                allowed_gates += el.first;
            }

            Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Unknow gate type `" + gate_type_match[1].str() +
                "`. Available gates: [" + allowed_gates + "].");

            return 2;
        } else {
            gate = Simulator::existing_gates[gate_type_match[1]]();
        }
        
        // Checks number of inputs
        if(gate_type_match[2].str() == "") { // no inputs nb specified -> using default
            gate->setNbInputs(gate->getDefaultNbInputs());
        } else {
            if (gate->setNbInputs( stoi(gate_type_match[2].str()) )) {
                return 3; // if specified nb of inputs is out of bound -> error 
            }
        }

        // TODO: Manage number of outputs > 1 (ex: MUX42)

        gate->setGateId(el.second->getGateId()); // saving gate id to Gate


        // Check if all inputs are filled by specified inputs 
        if(this->checkInputsNames(gate, el.second->getInputs())) {
            return 4;
        }

        // check if at least one gate is sequential
        if(gate->getIsSequential()) {
            this->has_sequential = true;
        }

        // add gate to map for the link edition (simulator next step)
        this->gates_graph.insert({el.second->getGateId(), gate});

        if(lower_name == "output") {
            hasOutput = true; // we ensure that we have at least one input
            this->output_gates.insert(gate);
        }

        if(gate->getName() == "Input") {
            ((Input*) gate)->setValues(this->json->getSignals()->getStimulus(el.second->getGateId()));
        }
    } 

    if(!hasOutput) {
        Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Dot file doesn't specify any output.");
    }

    return 0;
}


int Simulator::checkInputsNames(Gate *gate, const map<string, string> &inputs) {
    // used for the sequential elements mostly, ex mux, because we have an importance
    // with the order like i0, i1 and the sel. Might be used with typical gates
    // wildcards:   i@ -> AND2: i0, i1; AND3: i0, i1, i2; ...;
    //            sel% -> MUX2: sel0; MUX3: sel0 sel1; MUX4: sel0 sel1; ...;

    unsigned int total_nb_inputs = 0;

    for(string const& gate_el : *gate->getInputsNames()) {

        if(gate_el.find_first_of('@') != string::npos) { // check if we have a wildcard
            string input_name = gate_el; // editable copy
            for(char i = 0; i < gate->getNbInputs(); i++) { // replace @ by corresponding integer
                input_name = gate_el;
                replace(input_name.begin(), input_name.end(), '@', (char)('0'+i));

                if(!inputs.count(input_name)) { // wildcarded input isn't specified
                    Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Input `" + input_name + "` is missing for gate " +
                        gate->getGateId() + " (" + gate->getName() + to_string(gate->getNbInputs()) + ").");
                    return 2;
                }
                total_nb_inputs++;
            }
        } else if(gate_el.find_first_of('%') != string::npos) { // check if we have a wildcard for log2 mode
            string input_name = gate_el; // editable copy
            int nbOfLogGate = (int) ceilf(log2f(gate->getNbInputs()));

            for(char i = 0; i < nbOfLogGate; i++) { // replace % by corresponding integer
                input_name = gate_el;
                replace(input_name.begin(), input_name.end(), '%', (char)('0'+i));

                if(!inputs.count(input_name)) { // wildcarded input isn't specified
                    Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Input `" + input_name + "` is missing for gate " +
                        gate->getGateId() + " (" + gate->getName() + to_string(gate->getNbInputs()) + ").");
                    return 2;
                }
                total_nb_inputs++;
            }
        } else if(!inputs.count(gate_el)) { // not wildcarded input isn't specified
            Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Input `" + gate_el + "` is missing for gate " +
                gate->getGateId() + " (" + gate->getName() + to_string(gate->getNbInputs()) + ").");
            return 2;
        } else {
            total_nb_inputs++;
        }
    }

    if(inputs.size() < total_nb_inputs) { // check that the total number of output is correct (@ + additional inputs)
        Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Gate " + gate->getGateId() + " (" + gate->getName()
            + to_string(gate->getNbInputs()) + ") should have " + to_string(gate->getNbInputs()) + " inputs, "
            + to_string(inputs.size()) + " given.");
        return 1;
    }

    return 0;
}

int Simulator::setLinks(void) {
    map<string, SchematicObject*> SOList = this->dot->getSchematicObjectsList();

    // TODO: detect when path don't lead to any output ?
    // TODO: detect other error ? can there be errors at that point ?

    for(auto const& el: SOList) {
        for(auto const& inputs : el.second->getInputs()) {
            Gate *tmp_gate = this->gates_graph[el.first];
            Gate *previous_gate = this->gates_graph[inputs.second]; // inputs.second -> gateId that goes into our gate
            // inputs.first -> input name; 
            tmp_gate->addInputNode(inputs.first, previous_gate);
        }
    }

    return 0;
}


int Simulator::runSimulation(void) {
    for(; this->current_clock_count < this->json->getSignals()->getClockCounts(); this->current_clock_count++) {
        for(Gate* const& gate : this->output_gates) {
            int tmp; // not used
            if(gate->getValue(this->current_clock_count, &tmp) == 2) { // We have a loop error
                Help::debug(SIMULATOR_DEBUG, ERROR_DEBUG, "Found an unresolvable inifinite loop in simulation at clock count "
                    + to_string(this->current_clock_count) + " when calculating output `" + gate->getGateId() + "`. "
                    + "Try to increase th number of iterations with -i option (current max iteration: "
                    + to_string(Gate::getValuesHistoryIterator()) + ").");
                
                this->error_code = SIM_LOOP_ERROR;
                return 1;
            }
        }
        // reset had calculated
        Gate::resetValuesHistory();
        for(auto const& el : this->gates_graph) {
            el.second->setHadCalculatedValue(false);
            el.second->resetLastValues();
        }
    }

    return 0;
}


void Simulator::printRecursive(Gate* gate) {
    if(gate->getNbInputs() < 1) return;

    unsigned int i = 0;
    for(auto const& el : *gate->getInputNodes()) {
        printRecursive(el.second);

        if(i || gate->getNbInputs() == 1) cout << gate->getGateSign();
        else cout << ' ';

        cout << " " << *el.second << "  <- " << el.first << "(" << el.second->getGateId() << ")" << endl;

        i++;
    }
    cout << "-------------------- "  << gate->getGateId() << " [" << gate->getName()  << "]" << endl;
}

void Simulator::printSimulation(void) {
    //TODO: fix with loop
    for(Gate* const& gate : this->output_gates) {
        cout << endl;
        cout << "Calculation for output `" << gate->getGateId() << "`:" << endl;
        this->printRecursive(gate);
    }
    cout << endl;
}


void Simulator::saveToJson(const string& file_path, bool overwrite, vector<string> additional_outputs) {
    set<Stimulus*> stimuli;
    
    // save outputs that were specified with -a option
    for(string node_name : additional_outputs) {
        if(this->gates_graph.count(node_name)) {

            Stimulus* tmp_stimulus = new Stimulus(this->gates_graph[node_name]->getGateId(),
                this->gates_graph[node_name]->to_str()); // create tmp stimulus for the print

            stimuli.insert(tmp_stimulus); // save in set
        } else {
            Help::debug(SIMULATOR_DEBUG, WARNING_DEBUG, "Node " + node_name + " doesn't exist in simulation, and "
                + "won't be added to output JSON.");
        }
    }

    for(Gate* const& gate : this->output_gates) {
        Stimulus* tmp_stimulus = new Stimulus(gate->getGateId(), gate->to_str()); // create tmp stimulus for the print
        stimuli.insert(tmp_stimulus); // save to set
    }
    

    Json::printJson(file_path, stimuli, overwrite); // call json function

    for(Stimulus* stimulus : stimuli) {
        delete stimulus; // clean memory
    }
}