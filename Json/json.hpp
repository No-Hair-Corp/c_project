#ifndef _JSON_H
#define _JSON_H

#include "RSJparser.tcc"
#include <fstream>
#include <iostream>
#include "Signals.hpp"

using namespace std;

class Json {

private:
  
  string json_pathOrNoun;
  RSJresource jsonArray;
  signals signal;

public:

  Json(string json_pathOrNoun, RSJresource jsonArray, signals signal);

  ~Json();

  string get_json_pathOrNoun();
  RSJresource get_jsonArray();
  signals get_signal();

  void set_json_pathOrNoun(string);
  void set_signal(signals);

  int loadJson(string);

  void removeUseless();

  void verifyLength();

  void getName(RSJresource);

  string getValue(RSJresource);
  void manageValue(string);

  void manageClkP();
  void manageClkN();

  
  void managePeriod();

  int convertToSignals();

};

#endif
