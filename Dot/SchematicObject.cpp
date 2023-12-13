#include "SchematicObject.hpp"


// Constructor: initializes an empty SchematicObject in order to fill it after
SchematicObject::SchematicObject(): gate_type(""), gate_id(""), inputs(), outputs() {}

// Getters et setters pour gate_type
string SchematicObject::getGateType() const {
    return this->gate_type;
}

void SchematicObject::setGateType(const string& type) {
    this->gate_type = type;
}

// Getters et setters pour gate_id
string SchematicObject::getGateId() const {
    return this->gate_id;
}

void SchematicObject::setGateId(const string& id) {
    this->gate_id = id;
}

// Getters et setters pour inputs
list<SchematicObject*>& SchematicObject::getInputs() {
    return this->inputs;
}

void SchematicObject::setInputs(const list<SchematicObject*>& in) {
        this->inputs = in;
    }


// Getters et setters pour outputs
list<SchematicObject*>& SchematicObject::getOutputs() {
    return this->outputs;
}

void SchematicObject::setOutputs(const list<SchematicObject*>& out) {
    outputs = out;
}


    
