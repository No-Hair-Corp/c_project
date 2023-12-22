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
    Test TC_Check_Inputs("Check Inputs Function");
        //Setup
        string dot_path_checkInputs1 = "Tests/database/simulator/test_and2_true.dot";
        string json_path_checkInputs1 = "Tests/database/simulator/test_2inputs_A_B.json";
        string dot_path_checkInputs2 = "Tests/database/simulator/test2_and2_true.dot";
        string json_path_checkInputs2 = "Tests/database/simulator/test_3inputs_A_B_C.json";

        Simulator simCheckInputs1(dot_path_checkInputs1, json_path_checkInputs1);
        Simulator simCheckInputs2(dot_path_checkInputs2, json_path_checkInputs1);
        Simulator simCheckInputs3(dot_path_checkInputs1, json_path_checkInputs2);
        
        //Test
        TC_Check_Inputs.check(simCheckInputs1.checkInputs()==0);
        TC_Check_Inputs.check(simCheckInputs2.checkInputs()==2);
        TC_Check_Inputs.check(simCheckInputs3.checkInputs()==3);

    // === checkAllGates ===
    Test TC_Check_All_Gates("Check All Gates Function");
        // Setup
        string dot_path_checkAllGates1 = "Tests/database/simulator/test1_checkAllGates.dot";
        string json_path_checkAllGates1 = "Tests/database/simulator/test_2inputs_A_B.json";
        string dot_path_checkAllGates2 = "Tests/database/simulator/test2_checkAllGates.dot";
        string json_path_checkAllGates2 = "Tests/database/simulator/test2_checkAllGates.json";
        string dot_path_checkAllGates3 = "Tests/database/simulator/test3_checkAllGates.dot";
        string dot_path_checkAllGates4 = "Tests/database/simulator/test_and2_true.dot";

        Simulator simCheckAllGates1(dot_path_checkAllGates1, json_path_checkAllGates1);
        Simulator simCheckAllGates2(dot_path_checkAllGates2, json_path_checkAllGates2);
        Simulator simCheckAllGates3(dot_path_checkAllGates3, json_path_checkAllGates1);
        Simulator simCheckAllGates4(dot_path_checkAllGates4, json_path_checkAllGates1);

        //Test
        TC_Check_All_Gates.check(simCheckAllGates1.checkAllGates()==2);
        TC_Check_All_Gates.check(simCheckAllGates2.checkAllGates()==3);
        TC_Check_All_Gates.check(simCheckAllGates3.checkAllGates()==1);
        TC_Check_All_Gates.check(simCheckAllGates4.checkAllGates()==0);

    return 0;
}