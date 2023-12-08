#include "stimulus.hpp"


// ===== Constructeur de stimulus =====

stimulus::stimulus(string name, string value, int data[], int size_data):
name(name), value(value), data(data), size_data(size_data){
  cout << "Constructeur de stimulus" << endl;
}


// ===== Destructeur de stimulus =====

stimulus::~stimulus(){
  cout << "Destructeur de stimulus" << endl;
}


// ===== Getters =====

stimulus::get_name(){
  return this->name;
}

stimulus::get_value(){
  return this->value;
}

stimulus::get_data(){
  return this->data;
}

stimulus::get_size_data(){
  return this->size_data;
}