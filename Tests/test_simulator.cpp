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
    string dot_path = "Tests/database/dot/xtest_1.dot";
    string json_path = "Tests/database/json/xtest_1.json";
    Simulator sim_and2(dot_path, json_path);

    sim_and2.printSimulation();

    return 0;
}