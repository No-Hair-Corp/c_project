#ifndef _JSON_H
#define _JSON_H

#include "RSJparser.tcc"
#include <fstream>
#include <iostream>
#include "signals.hpp"

using namespace std;

class json {

private:
  
  string json_pathOrNoun;
  RSJresource jsonArray;
  signals signal;

public:

  json(string json_pathOrNoun, RSJresource jsonArray, signals signal);

  ~json();

  string get_json_pathOrNoun();
  RSJresource get_jsonArray();
  signals get_signal();

  void set_json_pathOrNoun(string);
  void set_jsonArray(RSJresource);
  void set_signal(signals);

  int loadJson(string);
  void removeUseless();
  void removeSpace();
  void manageName();
  void manageClkP();
  void manageClkN();
  void manageData();
  void managePeriod();
  int convertToSignals();

};

#endif
