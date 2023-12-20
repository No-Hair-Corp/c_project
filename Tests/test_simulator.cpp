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
    string dot_path = "Tests/database/dot/test_and2_true.dot";
    string json_path = "Tests/database/json/xtest_and2.json";
    Simulator(dot_path, json_path);

    return 0;
}