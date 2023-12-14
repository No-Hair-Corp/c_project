#ifndef _SCHEMATIC_OBJECT_H_
#define _SCHEMATIC_OBJECT_H_

#include <string>
#include <vector>


using namespace std;

class SchematicObject {
    private:
        string gate_type;
        string gate_id;
        vector<string> inputList;
        vector<string> outputList;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        SchematicObject();
        ~SchematicObject();


        // =======  GETTER / SETTER =======
        string getGateType() const;
        void setGateType(const string& type);
        string getGateId() const;
        void setGateId(const string& id);
        const vector<string>& getInputs() const;
        void setInputs(const string& input);
        const vector<string>& getOutputs() const;
        void setOutputs(const string& input);


};

#endif
