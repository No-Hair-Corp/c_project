#ifndef _SCHEMATIC_OBJECT_H_
#define _SCHEMATIC_OBJECT_H_

#include <string>
#include <list>
#include <map>
#include <vector>

using namespace std;

class SchematicObject {
    private:
        string gate_type;
        string gate_id;
        map<string, string> inputList;  //TODO: i0:U0
        vector<string> outputList;//TODO:UO
        map<string, string> additionnalOptions;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        SchematicObject();
        ~SchematicObject();


        // =======  GETTER / SETTER =======
        string getGateType() const;
        void setGateType(const string& type);
        string getGateId() const;
        void setGateId(const string& id);
        const map<string, string>& getInputs() const;
        void addInputs(const string& key, const string& inputs);
        const vector<string>& getOutputs() const;
        void addOutputs(const string& outputs);
        const map<string, string> getAdditionnalOptions() const;
        void addAdditionnalOptions(const string& key, const string& options);
};

#endif
