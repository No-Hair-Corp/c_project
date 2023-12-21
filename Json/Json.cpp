#include "Json.hpp"

// TODO: add Debug/verbose option 

// =======  CONSTRUCTOR / DESTRUCTOR =======
Json::Json(string file_path):
file_path(file_path) {
    ifstream json_file(file_path);

    this->error_code = JSON_SUCCESS;

    if(json_file.fail()) {
        cout << "Error: An error happened while opening " << file_path << " please check file's path." <<  endl;
        this->error_code = JSON_FILE_READ_ERROR;
        return;
    }

    this->json_dict = new RSJresource(json_file);
    this->json_dict->parse();

    if(this->assertJsonIntegrity()) { // check json is correct, exit program otherwise
        this->error_code = JSON_INTEGRITY_ERROR;
        return;
    }
    this->simplifyJson((*json_dict)["signal"]); // remove signals group

    // No usable signal found
    if(!this->json_clean_array.size()) {
        cout << "Error: No suitable signal was found in the given JSON. This might be a JSON syntax issue." << endl;
        this->error_code = JSON_NB_SIGNAL_ERROR;
        return;
    }
    cout << "Debug: Found " << this->json_clean_array.size() << " potential signals." << endl; 

    if(this->consistencyAndPrepare()) { // check signals, exit program if errors
        this->error_code = JSON_PREPARE_ERROR;
        return;
    }
    if(this->simplifyWaves()) {  // convert wave to easier value ("1.0." -> "1100"...)
        this->error_code = JSON_SIMPLIFY_ERROR;
        return;
    }
    
    json_file.close();
}

Json::~Json(){
    // TODO : free memory ?
}



// =======  GETTERS / SETTERS =======
JsonErrorCodes Json::getErrorCode(void) const {
    return this->error_code;
}

const string& Json::getFilePath(void) const {
    return this->file_path;
}
int Json::setFilePath(string& new_file_path) {
    // TODO: check if file exists
    this->file_path = new_file_path;

    return 0;
}

RSJresource* Json::getJsonDict(void) const {
    return this->json_dict;
}

vector<RSJresource> Json::getJsonCleanArray(void) const {
    return this->json_clean_array;
}

Signals* Json::getSignals(void) const {
    return this->signals;
}
int Json::setSignals(Signals *new_signals) {
    this->signals = new_signals;

    return 0;
}



// ======= OTHER FUNCTIONS =======
int Json::assertJsonIntegrity(void) {
    // Checks that file as "signal" main structure
    if(!(*json_dict)["signal"].exists()) {
        cout << "Error: WaveDrom file should include `signal` key." <<  endl;
        return 1;
    }

    if((*json_dict)["signal"].size() < 1) {
        cout << "Error: WaveDrom should contains at least 1 signal." <<  endl;
        return 1;
    }

    return 0;
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

void Json::eraseJsonCleanArray(void) {
    this->json_clean_array.erase(json_clean_array.begin(),json_clean_array.end());
}

int Json::consistencyAndPrepare(void) {
    std::regex removeSideQuotes("^(\'|\")(.+)(\'|\")$");
    unsigned int tmp_clock_counts = 0;
    bool has_clock_duplication = false;
    set<string> signal_names;

    unsigned int i = 1; 
    for (RSJresource signal: json_clean_array) {
        // verify presence of field name
        if(!signal["name"].exists()) {
            cout << "Error: Signal n°" << i <<  " should have a field `name`." << endl;
            return 1;
        }
        string signal_name = regex_replace(signal["name"].as_str(), removeSideQuotes, "$2"); // remove surrounding quotes
        json_clean_array.at(i-1).as_object()["name"] = signal_name; // update origin (signal is just a copy)

        if(!signal["wave"].exists()) {
            cout << "Error: Signal \"" << signal_name <<  "\" should have a field `wave`." << endl;
            return 2;
        }
        string signal_wave = regex_replace(signal["wave"].as_str(), removeSideQuotes, "$2"); // remove surrounding quotes

        // check for `|`
        if (signal_wave.find('|') != std::string::npos) {
            cout << "Warning: `|` character is not managed. It will be removed from the signal." << endl;
        }

        // remove `|` from signal
        signal_wave.erase(remove(signal_wave.begin(), signal_wave.end(), '|'), signal_wave.end());

        // update origin (signal is just a copy)
        json_clean_array.at(i-1).as_object()["wave"] = signal_wave; 

        // verify that wave field isn't empty
        if(signal_wave.length() == 0) {
            cout << "Error: Signal's \"" << signal_name <<  "\" can't have an empty `wave` field." << endl;
            return 3;
        }

        // if there is a P,p,n or an n in the signal -> we switch to clock duplication mode
        if(signal_wave.find_first_of("nNpP") != string::npos) {
            has_clock_duplication = true;
            // TODO: uptate `signals`'s clock_counts ? or use `has_clock_duplication`in the needed steps
        }

        // checks that there is no several signals with the same name
        if(signal_names.count(signal_name)) {
            cout << "Error: Several signals named \"" << signal_name << "\", this is not allowed." << endl;
            return 4;
        }
        signal_names.insert(signal_name);

        unsigned int signal_clock_counts = signal_wave.length();
        // counts clock count, multiply by period if needed
        if(signal["period"].exists()) {
            signal_clock_counts *= signal["period"].as<int>();
        }

        // check consistency of clock_counts
        if(!tmp_clock_counts) tmp_clock_counts = signal_clock_counts;
        else if(tmp_clock_counts != signal_clock_counts) {
            cout << "Error: Signal \"" << signal_name << "\" has a different `wave` length than previous signals. All the signals should have the same `wave` length (period ratio taken in account)." << endl;
            return 5;
        }

        // Simulator is not made to manage phase shift of signals, warns the user that option will be skipped 
        if(signal["phase"].exists()) {
            cout << "Warning: Signals' phase option is not managed. Signal \"" << signal_name << "\" will be treated without phase shift." << endl;
        }

        // Simulator is not made to manage data shift of signals, warns the user that option will be skipped 
        if(signal["data"].exists()) {
            cout << "Error: Signals' data option is not *yet* managed. Signal \"" << signal_name << "\" cannot be treated." << endl;
            return 6;
        }
        // TODO: Manage data bus; Like with custom formatting: (maybe in `Json::simplifyWaves()`)
        //     name: 'addr',  data: 'x3, xa' // x-> hexa; d/nothing-> decimal; b->binary
        //        becomes -> name: "addr[0]",  wave: "10"
        //                -> name: "addr[1]",  wave: "11"
        //                -> name: "addr[2]",  wave: "00"
        //                -> name: "addr[3]",  wave: "02"

        i++;
    }

    this->signals = new Signals(tmp_clock_counts, has_clock_duplication);

    return 0;
}


int Json::simplifyWaves(void) {
    // Allowed chars : ".pn10lh"
    // TODO: decide what to do with :
    //      - z: high impedance -> ?
    //      - u: dotted high -> ?;      - s: dotted low -> ?

    for (RSJresource signal: json_clean_array) {
        string wave = signal["wave"].as_str(); // simplify var name
        transform(wave.begin(), wave.end(), wave.begin(), ::tolower); // lowercase string
        string new_wave;

        for(unsigned int i = 0; i < wave.length(); i++) {
            if(i == 0 && wave[i] ==  '.') {
                cout << "Error: Signal \"" << signal["name"].as_str() << "\" start with a `.`. This is forbidden." << endl;
                return 1;
            }

            unsigned int duplicate_factor = (this->signals->getHasClockDuplication())? 2 : 1; // double chars if has clock
            duplicate_factor *= (signal["period"].exists())? signal["period"].as<int>() : 1;  // dupplicate according to period factor

            char char_to_push;
            switch (wave[i]){
                case '.':
                    char_to_push = new_wave[i*duplicate_factor-1]; // take previous char (from new signal format)
                    break;

                case '0':
                case 'l':
                    char_to_push = '0';
                    break;

                case '1':
                case 'h':
                    char_to_push = '1';
                    break;
                
                case 'x':
                    char_to_push = 'x';
                    break;

                case 'p':
                    char_to_push = 'p';
                    break;

                case 'n':
                    char_to_push = 'n';
                    break;
                
                default:
                    cout << "Error: In signal \"" << signal["name"].as_str() << "\", foribdden character `" << wave[i] << "`." << endl;
                    return 1;
                    break;
            }

            for(unsigned int i = 0; i < duplicate_factor; i++) {
                if(char_to_push == 'n') {  // first 0 then 1
                    new_wave.push_back((i < duplicate_factor / 2)? '0' : 'n');//need to keep n, for `.`repetition
                } else if(char_to_push == 'p') { // first 1 then 0
                    new_wave.push_back((i < duplicate_factor / 2)? '1' : 'p');//need to keep p, for `.`repetition
                } else {
                    new_wave.push_back(char_to_push);
                }
            }
        }

        replace(new_wave.begin(), new_wave.end(), 'p', '0'); // replace p (due to `.`repetition) by 0
        replace(new_wave.begin(), new_wave.end(), 'n', '1'); // replace n (due to `.`repetition) by 1

        // create stimulus, and add it to `signals`
        Stimulus *tmp_stimulus = new Stimulus(signal["name"].as_str(), new_wave);
        this->signals->addSignal(signal["name"].as_str(), tmp_stimulus);
    }

    return 0;
}



int Json::printJson(const string& file_path, set<Stimulus*> stimuli) {
    ifstream checked_file(file_path);
    if(checked_file.good()) {
        // TODO: take force option
        cout << "Error: File " << file_path << " already exists." <<  endl;
        return 1;
    }
    checked_file.close();


    ofstream output_file(file_path); // append at end of file to avoid 
    if(output_file.fail()) {
        cout << "Error: Couldn't open " << file_path << "." <<  endl;
        return 2;
    }

    RSJresource json_out("{\"signal\": []}");

    unsigned int i = 0;
    for(Stimulus* const& stimulus : stimuli) {
        // TODO: wave -> replace repetition by `.`
        RSJresource signal("{\"name\": \"" + stimulus->getName() + "\", \"wave\": \"" + stimulus->getValue() + "\"}");
        json_out["signal"][i] = signal;
        i++;
    }

    cout << "Debug: Saving output JSON to " << file_path << endl;

    output_file << json_out.as_str() << endl; 

    output_file.close();

    return 0;
}

