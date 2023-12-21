#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include <string>
#include <unordered_set>
#include <iostream>
#include <regex>
#include <map>

#include "../Dot/Dot.hpp"
#include "../Json/Json.hpp"
#include "Gate.hpp"

#include "Gates/And.hpp"
#include "Gates/Or.hpp"
#include "Gates/Xor.hpp"
#include "Gates/Input.hpp"
#include "Gates/Output.hpp"
#include "Gates/Not.hpp"
#include "Gates/Mux.hpp"

using namespace std;

enum SimulatorErrorCodes { SUCCESS, JSON_ERROR, LEXER_ERROR, PARSE_ERROR, INPUTS_INCONSISTENCY_ERROR,
    BAD_GATE_ERROR, LINK_ERROR, SIMULATION_ERROR };

class Simulator {
    private:
        
        SimulatorErrorCodes error_code;

        unsigned int current_clock_count; // TODO: useless ?

        string dot_file_path, json_file_path;
        Dot* dot;
        Json* json;

        bool has_sequential;

        static map<string, function<Gate*()>> existing_gates;

        map<string, Gate*> gates_graph;
        unordered_set<Gate*> output_gates;
        

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Simulator(const string& dot_file_path, const string& json_file_path);
        // ~Simulator();



        // =======  GETTERS / SETTERS =======
        SimulatorErrorCodes getErrorCode(void) const;

        // =======  OTHER FUNCTIONS =======
        int checkInputs(void);

        int checkAllGates(void); // -> register if there is sequential stuff, check input/output number consistency, 
                            // ambiguity on naming

        int checkInputsNames(Gate *gate, const map<string, string> &inputs);

        int setLinks(void);
        
        int runSimulation(void);

        void printRecursive(Gate* gate);
        void printSimulation(void);

        void saveToJson(const string& file_path);


};


#endif