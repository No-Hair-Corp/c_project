#include "Test.hpp"
#include "../Dot/SchematicObject.hpp"
#include "../Simulator/Simulator.hpp"
#include "../Simulator/Gates/Input.hpp"
#include "../Simulator/Gates/Output.hpp"
#include "../Simulator/Gates/Not.hpp"
#include "../Simulator/Gates/And.hpp"

using namespace std;

int main() {

    // === checkInputs ===
    Test TC_Check_Inputs("Check Inputs");
        // Setup
        string dot_path1 = "Tests/database/simulator/test_and2_true.dot";
        string json_path1 = "Tests/database/simulator/test_2inputs_A_B.json";
        string dot_path2 = "Tests/database/simulator/test_and3_true.dot";
        string json_path2 = "Tests/database/simulator/test_empty.json";
        string dot_path3 = "Tests/database/simulator/test2_and2_true.dot";
        Simulator simCheckInputs1(dot_path1, json_path1);
        Simulator simCheckInputs2(dot_path1, json_path2);
        Simulator simCheckInputs3(dot_path2, json_path1);
        Simulator simCheckInputs4(dot_path3, json_path1);
        
        // Test
        TC_Check_Inputs.check(simCheckInputs1.checkInputs()==0);
        TC_Check_Inputs.check(simCheckInputs2.checkInputs()==1);
        TC_Check_Inputs.check(simCheckInputs3.checkInputs()==3);
        TC_Check_Inputs.check(simCheckInputs4.checkInputs()==2);

    return 0;
}

/*
// A ---+----\.
    //      | AND |--- O
// B ---+----/.
    string dot_path = "Tests/database/dot/xtest_full_adder.dot";
    string json_path = "Tests/database/json/xtest_full_adder.json";
    Simulator sim_and2(dot_path, json_path);

    if(!sim_and2.getErrorCode()) {
        sim_and2.printSimulation();
        sim_and2.saveToJson("full_adder_output.json");
    }
*/