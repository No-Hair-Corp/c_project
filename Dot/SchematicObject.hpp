#ifndef _SCHEMATIC_OBJECT_H_
#define _SCHEMATIC_OBJECT_H_

#include <string>
#include <list>

using namespace std;

class SchematicObject {
    private:
        string gate_type;
        string gate_id;
        list<SchematicObject*> inputs;
        list<SchematicObject*> outputs;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        SchematicObject(string gate_type);
        ~SchematicObject();


        // =======  GETTER / SETTER =======
        string getGateType() const;
        void setGateType(const string& type);
        string getGateId() const;
        void setGateId(const string& id);
        list<SchematicObject*>& getInputs();
        void setInputs(const list<SchematicObject*>& in);
        list<SchematicObject*>& getOutputs();
        void setOutputs(const list<SchematicObject*>& out);


};

#endif
