#ifndef _STIMULUS_H
#define _STIMULUS_H

#include "RSJparser.tcc"
#include <fstream>
#include <iostream>

using namespace std;

class Stimulus {

private:

  string name;
  string value;
  //int data[];
  //int size_data;

public:

  Stimulus(string name, string value)// int data[], int size_data);

  ~Stimulus();

  string get_name();
  char get_value();
  //int* get_data();
  //int get_size_data();

  void set_name(string);
  void set_value(string);
  //void set_data(int*);
  //void set_size_data(int);

};

#endif
