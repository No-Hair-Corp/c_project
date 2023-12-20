#include "Simulator.hpp"

map<string, function<Gate*()>> Simulator::existing_gates = {
    {"input", []() -> Gate* { return new Input; } },
    {"output", []() -> Gate* { return new Output; } },
    {"not", []() -> Gate* { return new Not; } },
    {"and", []() -> Gate* { return new And; } },
    {"mux", []() -> Gate* { return new Mux; } },
};

// map<string, Gate*(*)()> Simulator::existing_gates["input"] = & Simulator::createGateInstance<Input>;

Simulator::Simulator(const string& dot_file_path, const string& json_file_path):
dot_file_path(dot_file_path), json_file_path(json_file_path), has_sequential(false), current_clock_count(0) {

    // parsing json and preparing DOT
    this->dot = new Dot(dot_file_path);
    this->json = new Json(json_file_path);

    // running dot lexing and parsing 
    this->dot->lexer();
    
    if(this->dot->parse()) {
        return;
    }

    // check consistancy of inputs between json and dot
    if(this->checkInputs()) {
        return;
    }

    
    // check that gates exist and are correctly given (nb of inputs, name, ...)
    if(this->checkAllGates()) {
        return;
    }

    // generate link between Gates
    if(this->setLinks()) {
        return;
    }


    // TODO: Simulate :)
    if(this->runSimulation()) {
        return;
    }
    //      2) split into combinatorial blocks
    //      3) manage loops (watchdog)


    // TODO: Output json file


    // cout << "   A: 000x1101xx" << endl;
    // cout << " & B: 0x11100xx0" << endl;
    // cout << " = ";
    // for(Gate* const& gate : this->output_gates) {
    //     cout << gate->getGateId() << ": " <<  *gate << endl;
    // }
    // cout << endl << endl;

}

int Simulator::checkInputs(void) {
    map<string, SchematicObject*> SOList = this->dot->getSchematicObjectsList();

    unordered_set<string> input_names; // json's inputs

    for(auto const& el : this->json->getSignals()->getStimuli()) {
        input_names.emplace(el.first);
    }

    if(input_names.size() < 1) {
        cout << "Error: Waveform doesn't have any input." << endl; 
        return 1;
    }

    unsigned int nb_dot_inputs = 0;
    for(auto const& el: SOList) {
        string lower_name =  el.second->getGateType();
        transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

        if(lower_name == "input") {
            if(!input_names.count(el.second->getGateId())) {
                cout << "Error: Input " << el.second->getGateId() << " doesn't exist in waveform file." << endl; 
                return 2;
            }
            nb_dot_inputs++;
        }
    }


    if(nb_dot_inputs != input_names.size()) {
        cout << "Error: The Dot and the Wavedrom don't have the same number of inputs. Found " << nb_dot_inputs 
            << " in Dot, but " << input_names.size()  << " in Json." << endl; 

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
        // TODO: trim spaces ?

        // regex to check gate type format : <type>[nb_inputs][nb_outputs]
        std::regex gate_type_regex("^([a-zA-Z]+)([1-9]?)([1-9]?)$"); 
        std::smatch gate_type_match;
        std::regex_search(lower_name, gate_type_match, gate_type_regex);

        // .size must be 4 -> group 0 general, 1: gate name, 2: nb inputs, 3: nb outputs
        if(gate_type_match.size() != 4) {
            cout << "Error: Gate type `" << el.second->getGateType() << "` is not properly formed. Authorized form : "
                << "<type>[nb_inputs][nb_outputs]." << endl; 
            return 1;
        }

        Gate* gate;
        // check if gate exists
        if(!Simulator::existing_gates.count(gate_type_match[1])) {
            cout << "Error: Unknow gate type `" << gate_type_match[1] << "`. Available gates: ["; 
            for(auto const& el : Simulator::existing_gates) {
                cout << " " << el.first;
            }
            cout << " ]." << endl;
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

        // TODO : Manage number of outputs > 1 (ex: MUX42)


        // Check if all inputs are filled by specified inputs 
        if(this->checkInputsNames(gate, el.second->getInputs())) {
            cout << " (Gate id: `" << el.second->getGateId() << "`)" << endl;
            return 4;
        }

        // check if at least one gate is sequential
        if(gate->getIsSequential()) {
            this->has_sequential = true;
        }

        gate->setGateId(el.second->getGateId()); // saving gate id to Gate
        // add gate to map for the link edition (simulator next step)
        this->gates_graph.insert({el.second->getGateId(), gate});

        if(lower_name == "output") {
            hasOutput = true; // we ensure that we have at list one input
        
            this->output_gates.insert(gate);
        }

        if(gate->getName() == "Input") {
            ((Input*) gate)->setValues(this->json->getSignals()->getStimulus(el.second->getGateId()));
        }
    } 

    if(!hasOutput) {
        cout << "Error: Dot file doesn't specify any output." << endl; 
    }

    return 0;
}


int Simulator::checkInputsNames(Gate *gate, const map<string, string> &inputs) {
    // used for the sequential elements mostly, ex mux, because we have an importance
    // with the order like i0, i1 and the sel. Might be used with typical gates
    // wildcards: i@ -> AND2 : i0, i1; AND3: i0, i1, i2; ...;

    unsigned int total_nb_inputs = 0;

    for(string const& gate_el : *gate->getInputsNames()) {

        if(gate_el.find_first_of('@') != string::npos) { // check if we have a wildcard
            string input_name = gate_el; // editable copy
            for(char i = 0; i < gate->getNbInputs(); i++) { // replace @ by corresponding integer
                input_name = gate_el;
                replace(input_name.begin(), input_name.end(), '@', (char)('0'+i));

                if(!inputs.count(input_name)) { // wildcarded input isn't specified
                    cout << "Error: Input `" << input_name << "` is missing for gate of type " << gate->getName() << gate->getNbInputs()
                        << ".";
                    return 2;
                }
                total_nb_inputs++;
            }
        } else if(!inputs.count(gate_el)) { // not wilcarded input isn't specified
            cout << "Error: Input `" << gate_el << "` is missing for gate of type " << gate->getName() << gate->getNbInputs()
                << ".";
            return 2;
        } else {
            total_nb_inputs++;
        }
    }

    if(inputs.size() != total_nb_inputs) { // check that the total number of output is correct (@ + additional inputs)
        cout << "Error: Gate " << gate->getName() << gate->getNbInputs() << " should have " << gate->getNbInputs() << " inputs, "
                << inputs.size() << " given.";
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
    // TODO: add option to save intermediaries node
    for(; this->current_clock_count < this->json->getSignals()->getClockCounts(); this->current_clock_count++) {
        for(Gate* const& gate : this->output_gates) {
            int tmp; // not used
            gate->getValue(this->current_clock_count, &tmp);
        }
    }

    return 0;
}


void printRecursive(Gate* gate) {
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
    for(Gate* const& gate : this->output_gates) {
        cout << endl;
        cout << "Calculation for output `" << gate->getGateId() << "`:" << endl;
        printRecursive(gate);
    }    
}
