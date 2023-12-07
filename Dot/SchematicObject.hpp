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
        SchematicObject();
        ~SchematicObject();
};

#endif
