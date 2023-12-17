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
const map<string, string>& SchematicObject::getInputs() const{
        return this->inputList;
    }

void SchematicObject::addInputs(const string& key, const string& inputs) {
        this->inputList[key] = inputs;
    }


// Getters et setters pour outputs
const vector<string>& SchematicObject::getOutputs() const{
        return this->outputList;
    }

void SchematicObject::addOutputs(const string& outputs) {
        this->outputList.push_back(outputs);
    }

const map<string, string> SchematicObject::getAdditionnalOptions() const{
    return this->additionnalOptions;
}
void SchematicObject::addAdditionnalOptions(const string& key, const string& options){
    this->additionnalOptions[key] = options;
}




    
