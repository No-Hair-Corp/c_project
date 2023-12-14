#include "SchematicObject.hpp"


// Constructor: initializes an empty SchematicObject in order to fill it after
SchematicObject::SchematicObject(): gate_type(""), gate_id(""), inputList(), outputList() {}

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
const vector<string>& SchematicObject::getInputs() const{
        return this->inputList;
    }

void SchematicObject::setInputs(const string& input) {
        this->inputList.push_back(input);
    }


// Getters et setters pour outputs
const vector<string>& SchematicObject::getOutputs() const{
        return this->outputList;
    }

void SchematicObject::setOutputs(const std::string& input) {
        this->outputList.push_back(input);
    }


    
