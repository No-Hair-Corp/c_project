#include "Json.hpp"

// =======  CONSTRUCTOR / DESTRUCTOR =======
Json::Json(string file_path):
file_path(file_path) {
    ifstream json_file(file_path);

    if(json_file.fail()) {
        cout << "Error: An error happened while opening " << file_path << " please check file's path." <<  endl;
        exit(1);
    }

    this->json_dict = new RSJresource(json_file);
    this->json_dict->parse();

    this->assertJsonIntegrity();
    this->simplifyJson((*json_dict)["signal"]);

    // Display content
    // for (RSJresource i: json_clean_array)
    //     std::cout << i.as<string>() << endl;

    // TODO: remove useless stuff from json ()
    // TODO: convert shit to easier stuff like "p..." to "pppp" ...
}


Json::~Json(){

}



// =======  GETTERS / SETTERS =======



// ======= OTHER FUNCTIONS =======
void Json::assertJsonIntegrity(void) {
    // Checks that file as "signal" main structure
    if(!(*json_dict)["signal"].exists()) {
        cout << "Error: WaveDrom file should include `signal` key." <<  endl;
        exit(1);
    }

    if((*json_dict)["signal"].size() < 0) {
        cout << "Error: WaveDrom should contains at least 1 signal." <<  endl;
        exit(1);
    }
}

void Json::simplifyJson(RSJresource &array) {
    for(unsigned int i = 0; i < array.size(); i++) {
        if(array[i].type() == RSJ_LEAF) continue; // skip if it's a value

        if(array[i].type() == RSJ_OBJECT) { // object -> add directly
            this->json_clean_array.push_back(array[i]);
        } else if(array[i].type() == RSJ_ARRAY) { // array -> go deeper
            this->simplifyJson(array[i]);
        }
    }
}


