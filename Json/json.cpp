#include "Json.hpp"


// ===== Constructeur de json =====

Json::Json(string json_pathOrNoun, RSJresource jsonArray, signals signal):
json_path(json_pathOrNoun), jsonArray(jsonArray), Signal(signal){
  cout << "Constructeur de json" << endl;
}


// ===== Destructeur de json =====

Json::~Json(){
  cout << "Destructeur de json" << endl;
}


// ===== Getters =====

Json::get_json_pathOrNoun(){
  return this->json_pathOrNoun;
}

Json::get_jsonArray(){
  return this->jsonArray;
}

Json::get_signal(){
  return this->signal;
}


// ===== Setters =====

Json::set_json_pathOrNoun(string json_pathOrNoun){
  this->json_pathOrNoun=json_pathOrNoun;
}

Json::set_signal(signals signal){
  this->signal=signal;
}


// ===== Load json file =====

Json::loadJson(string json_pathOrNoun){
  ifstream my_fstream (json_pathOrNoun);
  this->jsonArray(my_fstream);
}


// ===== Get value =====

Json::getValue(RSJresource jsonArray, int i){
  jsonArray["signal"][i]["wave"].as<string>("error");
}
