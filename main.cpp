#include <unistd.h>
#include <getopt.h>

#include "Dot/Dot.hpp"
#include "Json/Json.hpp"
#include "Simulator/Simulator.hpp"


static struct option long_options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"json", required_argument, nullptr, 'j'},
    {"dot", required_argument, nullptr, 'd'},
    {"output", required_argument, nullptr, 'o'},
    {nullptr, 0, nullptr, 0} // Indicates the end of options
};


int main(int argc, char* argv[]) {
    int option;
    int option_index = 0;

    // Variables pour suivre les options requises
    bool jsonSpecified = false;
    bool dotSpecified = false;
    bool outputSpecified = false;

    while ((option = getopt_long(argc, argv, "hj:d:o:", long_options, &option_index)) != -1) {
        switch (option) {
            case 'h':
                std::cout << "usage: ./main [options] args" << std::endl << "--json   specify json file path" << std::endl << "--dot   specify dot file path" << std::endl << "--output   output file path" << std::endl;
                break;
            case 'j':
                if (optarg) {
                    std::cout << "JSON option with argument: " << optarg << std::endl;
                    jsonSpecified = true;
                } else {
                    // std::cerr << "--json option requires an argument" << std::endl;
                    return 1;  // Indiquer une erreur
                }
                break;
            case 'd':
                if (optarg) {
                    std::cout << "Dot option with argument: " << optarg << std::endl;
                    dotSpecified = true;
                } else {
                    // std::cerr << "--dot option requires an argument" << std::endl;
                    return 1;  // Indiquer une erreur
                }
                break;
            case 'o':
                if (optarg) {
                    std::cout << "Output option with argument: " << optarg << std::endl;
                    outputSpecified = true;
                } else {
                    // std::cerr << "--output option requires an argument" << std::endl;
                    return 1;  // Indiquer une erreur
                }
                break;
            case '?':
                if (optopt == 'j' || optopt == 'd' || optopt == 'o') {
                    std::cerr << "Option -" << static_cast<char>(optopt) << " requires an argument." << std::endl;
                } else if (isprint(optopt)) {
                    std::cerr << "Unknown option '-" << static_cast<char>(optopt) << "'." << std::endl;
                } else {
                    std::cerr << "Unknown option character '\\x" << std::hex << optopt << "'." << std::endl;
                }
                return 1;  // Indiquer une erreur
            default:
                break;
        }
    }

    // Vérifier que toutes les options requises sont spécifiées
    if (!jsonSpecified || !dotSpecified || !outputSpecified) {
        std::cerr << "Missing required options." << std::endl;
        return 1;  // Indiquer une erreur
    }

    // Process remaining non-option arguments (if any)
    for (int i = optind; i < argc; ++i) {
        std::cout << "Non-option argument: " << argv[i] << std::endl;
    }

    return 0;
}