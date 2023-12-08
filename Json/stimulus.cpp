#include "Stimulus.hpp"


// ===== Constructeur de stimulus =====

Stimulus::Stimulus(string name, string value, int data[], int size_data):
name(name), value(value)){// data(data), size_data(size_data){
  cout << "Constructeur de stimulus" << endl;
}


// ===== Destructeur de stimulus =====

Stimulus::~Stimulus(){
  cout << "Destructeur de stimulus" << endl;
}


// ===== Getters =====

Stimulus::get_name(){
  return this->name;
}

Stimulus::get_value(){
  return this->value;
}

/*Stimulus::get_data(){
  return this->data;
}*/

/*Stimulus::get_size_data(){
  return this->size_data;
}*/


// ===== Setters =====

Stimulus::set_name(string name){
  this->name=name;
}

Stimulus::set_value(string value){
  this->value=value;
}

/*Stimulus::set_data(int data[]){
  this->data=data;
}

Stimulus::get_size_data(int size_data){
  this->size_data=size_data;
}*/
