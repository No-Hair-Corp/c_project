#include "Test.hpp"
#include "../Dot/SchematicObject.hpp"
#include "../Simulator/Simulator.hpp"
#include "../Simulator/Gates/Input.hpp"
#include "../Simulator/Gates/Output.hpp"
#include "../Simulator/Gates/Not.hpp"
#include "../Simulator/Gates/And.hpp"

using namespace std;

int main() {


    // A ---+----\.
    //      | AND |--- O
    // B ---+----/.
    string dot_path = "Tests/database/dot/xtest_full_adder.dot";
    string json_path = "Tests/database/json/xtest_full_adder.json";
    Simulator sim_and2(dot_path, json_path);

    if(!sim_and2.getErrorCode()) {
        sim_and2.printSimulation();
    }

    return 0;
}