#include "json.hpp"


// ===== Constructeur de json =====

json::json(string json_pathOrNoun, RSJresource jsonArray, signals signal):
json_path(json_pathOrNoun), jsonArray(jsonArray), Signal(signal){
  cout << "Constructeur de json" << endl;
}


// ===== Destructeur de json =====

json::~json(){
  cout << "Destructeur de json" << endl;
}


// ===== Getters =====

json::get_json_pathOrNoun(){
  return this->json_pathOrNoun;
}

json::get_jsonArray(){
  return this->jsonArray;
}

json::get_signal(){
  return this->signal;
}


// ===== Load json file =====

json::loadJson(string json_pathOrNoun){
  ifstream my_fstream (json_pathOrNoun);
  RSJresource my_resource (my_fstream);
}
