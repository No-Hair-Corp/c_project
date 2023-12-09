#include "Stimulus.hpp"


// =======  CONSTRUCTOR / DESTRUCTOR =======
Stimulus::Stimulus(string name, string value):
name(name), value(value) {
  
}

Stimulus::~Stimulus(){
  // TODO : Free memory ?
}


// =======  GETTERS / SETTERS =======
string Stimulus::getName(void) const {
  return this->name;
}
void Stimulus::setName(string &name) {
  this->name = name;
}

string Stimulus::getValue() const {
  return this->value;
}
void Stimulus::setValue(string &value) {
  this->value = value;
}
