#include <unistd.h>
#include <getopt.h>
#include "Help/Help.hpp"
#include "Simulator/Simulator.hpp"


static struct option long_options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"json", required_argument, nullptr, 'j'},
    {"dot", required_argument, nullptr, 'd'},
    {"output", required_argument, nullptr, 'o'},
    {"force", no_argument, nullptr, 'f'},
    {"add", required_argument, nullptr, 'a'},
    {"verbose", required_argument, nullptr, 'v'},
    {nullptr, 0, nullptr, 0} // Indicates the end of options
};


int main(int argc, char* argv[]) {
    int option;
    int option_index = 0;

    //Variables des chemins d'accès aux fichiers d'inputs/outputs
    string json_path;
    string dot_path;
    string output_path;
    debug_level verbose_level = SUCCESS_DEBUG;
    vector <string> additionnal_outputs = {};

    // Variables pour suivre les options requises
    bool jsonSpecified = false;
    bool dotSpecified = false;
    bool outputSpecified = false;
    bool forceSpecified = false;
    bool addSpecified = false;
    bool verboseSpecified = false;

    while ((option = getopt_long(argc, argv, "hj:d:o:fa:v:", long_options, &option_index)) != -1) {
        switch (option) {
            case 'h':
                Help::debug(GENERAL_DEBUG, INFO_DEBUG,"usage: ./main [options] args \n --json     specify json file path\n --dot      specify dot file path \n --output   output file path\n --force    overwrites output file \n --add      add output signal to output file\n --verbose  int between 0 and 5 to set debug level\n");
                exit(0);
                break;
            case 'j':
                if (optarg) {
                    json_path = optarg;
                    jsonSpecified = true;
                } else {
                    Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "--json option requires an argument");
                    return 1;  // Indiquer une erreur
                }
                break;
            case 'd':
                if (optarg) {
                    dot_path = optarg;
                    dotSpecified = true;
                } else {
                    Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "--dot option requires an argument");
                    return 1;  // Indiquer une erreur
                }
                break;
            case 'o':
                if (optarg) {
                    output_path = optarg;
                    outputSpecified = true;
                } else {
                    Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "--output option requires an argument");
                    return 1;  // Indiquer une erreur
                }
                break;
            case 'f':
                    forceSpecified = true;
                break; 
            case 'a'://ajouter tous les arguments dans une liste
                if (optarg) {
                    addSpecified = true;
                    additionnal_outputs.push_back(optarg);
                    while (optind < argc && argv[optind][0] != '-') {
                        additionnal_outputs.push_back(argv[optind++]);
                    }
                } else {
                    Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "--add option requires at least one argument");
                    return 1;  // Indiquer une erreur
                }
                break;
            case 'v':
                if (optarg) {
                    verboseSpecified = true;
                    verbose_level = (debug_level)stoi(optarg);

                    if(verbose_level > DEBUG_DEBUG){
                        Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "--verbose requires integer argument between 0 and 4");
                        return 1;
                    }
                } else {
                    Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "--verbose requires integer argument between 0 and 4");
                    return 1;  // Indiquer une erreur
                }
                break;
            case '?':
                Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "Invalid option");
                return 1;
            default:
                break;
        }
    }

    Help::setVerboseLevel(verbose_level);
    // Vérifier que toutes les options requises sont spécifiées
    if (!jsonSpecified) {
        Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "Missing required option --json.");
        return 1; // Indiquer une erreur
    }

    if (!dotSpecified) {
        Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "Missing required option --dot.");
        return 1; // Indiquer une erreur
    }

    if (!outputSpecified) {
        Help::debug(GENERAL_DEBUG, ERROR_DEBUG, "Missing required option --output.");
        return 1; // Indiquer une erreur
    }

    // Process remaining non-option arguments (if any)
    for (int i = optind; i < argc; ++i) {
        std::cout << "Non-option argument: " << argv[i] << std::endl;
    }

    Help::debug(GENERAL_DEBUG, INFO_DEBUG,"Json file: " + json_path);
    Help::debug(GENERAL_DEBUG, INFO_DEBUG,"Dot file: " + dot_path);
    Help::debug(GENERAL_DEBUG, INFO_DEBUG,"Output file: " + output_path);

    Simulator sim(dot_path, json_path);
    if(!sim.getErrorCode()) {
        Help::debug(GENERAL_DEBUG, SUCCESS_DEBUG,"Successful simulation");
        sim.saveToJson(output_path, forceSpecified, additionnal_outputs);
    }

    return 0;
}