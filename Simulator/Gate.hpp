#ifndef _GATE_H_
#define _GATE_H_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace std;

class Gate {
    private:
        string name;

        bool is_sequential;

        unsigned int nb_inputs;
        static list<string> inputs_names; // used for the sequential elements mostly, ex mux, because we have an importance
                                    // with the order like i0, i1 and the sel. Might be used with typical gates
                                    // wildcards: i+ -> i0, i1, i2... 
                                    //            i@ -> AND2 : i0, i1; AND3: i0, i1, i2; ...
        // unsigned int nb_outputs; // TODO: gates can only have 1 output, otherwise we create a second gate
        //                              -> 1 output = formula; 1 formula = 1 gate

        map<string, Gate*>* input_nodes;
        // Gate* output_nodes;

        int last_calculation_clock;
        vector<int> values; // 1 int per clock count -> 1: high; 0 low; -1: x/unknow

        

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Gate(string name, unsigned int nb_inputs, bool is_sequential);
        virtual ~Gate() = 0; // virtual class



        // =======  GETTERS / SETTERS =======
        unsigned int getNbInputs(void) const;

        void setInputNodes(map<string, Gate*>* new_input_nodes);
        int getInputNode(string input_name, Gate** node) const;

        void incrementClockCount(void);
        void setLastCalculationClock(int new_clock_count);
        int getLastCalculationClock(void) const;

        const string& getName(void) const;


        void addValue(int value);
        int getValue(int clock_count, int* value); //-> if unset, run calculate value
        // unsigned char getPreviousValue(unsigned int delta);
        // unsigned char getValue(unsigned int clock_count); // maybe keep only this one or the previous


        // =======  OTHER FUNCTION =======
        virtual int calculateValue(void) = 0; // -> return errorCode not value ;)
        //      -> recursive, to calculate previous gates
        //      -> take care of sequential, and split of combinatoire blocks
        //      -> by the way if there is sequential better to get from start or end ?
};


#endif