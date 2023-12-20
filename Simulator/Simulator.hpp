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
#include "Gates/Input.hpp"
#include "Gates/Output.hpp"
#include "Gates/Not.hpp"
#include "Gates/Mux.hpp"

using namespace std;

class Simulator {
    private:
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


        // =======  OTHER FUNCTION =======
        int checkInputs(void);

        int checkAllGates(void); // -> register if there is sequential stuff, check input/output number consistency, 
                            // ambiguity on naming

        int checkInputsNames(Gate *gate, const map<string, string> &inputs);

        int setLinks(void);
        
        int runSimulation(void);

        void printSimulation(void);


};


#endif