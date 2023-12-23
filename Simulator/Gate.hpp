#ifndef _GATE_H_
#define _GATE_H_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <unordered_set>
#include <map>

using namespace std;


class Gate {
    private:
        string name;
        string gate_id;
        char gate_sign;

        bool is_sequential;

        unsigned int nb_inputs;

        unsigned int min_nb_inputs;
        unsigned int default_nb_inputs;
        unsigned int max_nb_inputs;
        list<string> inputs_names; // used for the sequential elements mostly, ex mux, because we have an importance
                                    // with the order like i0, i1 and the sel. Might be used with typical gates
                                    // wildcards: i+ -> i0, i1, i2... 
                                    //            i@ -> AND2 : i0, i1; AND3: i0, i1, i2; ...
        // unsigned int nb_outputs; // TODO: gates can only have 1 output, otherwise we create a second gate
        //                              -> 1 output = formula, and 1 formula = 1 gate

        map<string, Gate*>* input_nodes;
        // Gate* output_nodes;

        int last_calculation_clock;
        vector<int> values; // 1 int per clock count -> 1: high; 0 low; -1: x/unknown

        static bool loop_error;
        bool had_calculate_value;
        vector<unsigned int> last_calculated_values;
        static unsigned int values_history_iterator;
        // static map<string, int> values_history;
        // static vector<string> tmp_test;
        

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Gate(string name, string gate_id, char gate_sign, unsigned int nb_inputs,unsigned int min_nb_inputs,
                unsigned int default_nb_inputs, unsigned int max_nb_inputs, bool is_sequential);

        virtual ~Gate() = 0; // virtual class



        // =======  GETTERS / SETTERS =======
        const string& getName(void) const;

        const string& getGateId(void) const;
        void setGateId(const string& new_gate_id);

        char getGateSign(void) const;

        bool getIsSequential(void) const;

        unsigned int getNbInputs(void) const;
        int setNbInputs(unsigned int);

        unsigned int getMinNbInputs() const;
        unsigned int getDefaultNbInputs() const;
        unsigned int getMaxNbInputs() const;

        void setInputsNames(const list<string>& new_value);
        list<string>* getInputsNames();

        void setInputNodes(map<string, Gate*>* new_input_nodes);
        void addInputNode(const string& input_name, Gate* linked_gate);
        int getInputNode(string input_name, Gate** node) const;
        const map<string, Gate*>* getInputNodes(void);

        void incrementClockCount(void);
        void setLastCalculationClock(int new_clock_count);
        int getLastCalculationClock(void) const;

        void addValue(int value);
        int setValue(int clock_count, int value);
        int getValue(int clock_count, int* value); //-> if unset, run calculate value
        // unsigned char getPreviousValue(unsigned int delta);
        // unsigned char getValue(unsigned int clock_count); // maybe keep only this one or the previous

        bool getHadCalculatedValue(void) const;
        void setHadCalculatedValue(bool new_value);

        static int getValueHistory(string gate_id);
        static void setValueHistory(string gate_id, int new_value);
        static void resetValuesHistory(void);

        void resetLastValues(void);




        // =======  OTHER FUNCTIONS =======
        virtual int calculateValue(void) = 0; // -> return errorCode not value ;)
        //      -> recursive, to calculate previous gates
        //      -> take care of sequential, and split of combinatoire blocks
        //      -> by the way if there is sequential better to get from start or end ?

        string to_str(void) const;
        friend ostream& operator<<(ostream& out, const Gate &gate);
};


#endif