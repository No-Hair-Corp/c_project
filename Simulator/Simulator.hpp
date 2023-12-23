#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include <string>
#include <unordered_set>
#include <iostream>
#include <regex>
#include <map>

#include "../Help/Help.hpp"
#include "../Dot/Dot.hpp"
#include "../Json/Json.hpp"
#include "Gate.hpp"

#include "Gates/And.hpp"
#include "Gates/Nand.hpp"
#include "Gates/Or.hpp"
#include "Gates/Nor.hpp"
#include "Gates/Xor.hpp"
#include "Gates/Nxor.hpp"
#include "Gates/Input.hpp"
#include "Gates/Output.hpp"
#include "Gates/Not.hpp"
#include "Gates/Mux.hpp"
#include "Gates/Flipflop.hpp"

using namespace std;

enum SimulatorErrorCodes { SIM_SUCCESS, SIM_JSON_ERROR, SIM_LEXER_ERROR, SIM_PARSE_ERROR, SIM_INPUTS_INCONSISTENCY_ERROR,
    SIM_BAD_GATE_ERROR, SIM_LINK_ERROR, SIM_SIMULATION_ERROR, SIM_LOOP_ERROR };

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

        void saveToJson(const string& file_path, bool overwrite = false, vector<string> additional_outputs = {});


};


#endif