#include "SchematicObject.hpp"


// Constructor: initializes an empty SchematicObject in order to fill it after
SchematicObject::SchematicObject(): gate_type(""), gate_id(""), inputList(), outputList() {}
// Constructor: initializes a SchematicObject with attributs gateId and gateType
SchematicObject::SchematicObject(string gateID, string gateType) : gate_type(gateType), gate_id(gateID), inputList(), outputList() {}
// Constructor: initializes a SchematicObject with attributs gateID, gateType and additionnalOptions
SchematicObject::SchematicObject(string gateID, string gateType, map<string, string> additionnalOptions): gate_type(gateType), gate_id(gateID), inputList(), outputList(), additionnalOptions(additionnalOptions) {}
// Destructor: delete SchematicObject instances
SchematicObject::~SchematicObject(){
}

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

void SchematicObject::print(){
    cout << "GateId: " << getGateId() << " , gateType: " << getGateType() << endl;
    for (const auto& input : getInputs()) {
        cout << "InputLabel: " << input.first << " , Source: " << input.second << endl;
    }
    for (const auto& output : getOutputs()) {
        cout << "Output: " << output << endl;
    }
}




    
