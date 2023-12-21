#include "Test.hpp"
#include "../Json/Json.hpp"

using namespace std;

int main() {

    // === assertJsonIntegrity ===
    Test TC_Verify_Min_Json("Verify if there is all minimum elements on Json");
        // Setup
        Json fileVerifyMinJson1("Tests/database/json/test1_verifyMinJson.json");
        Json fileVerifyMinJson2("Tests/database/json/test2_verifyMinJson.json");
        
        // Test
        TC_Verify_Min_Json.check(fileVerifyMinJson1.assertJsonIntegrity()==0);
        TC_Verify_Min_Json.check(fileVerifyMinJson2.assertJsonIntegrity()==1);

    // === simplifyJson ===
    Test TC_Simplify_Json("Simplify Json");
        // Setup
        Json fileSimplifyJson1("Tests/database/json/test1_simplifyJson.json");
        Json fileSimplifyJson2("Tests/database/json/test1_simplifyJson.json");
        fileSimplifyJson1.eraseJsonCleanArray();
        RSJresource* array = fileSimplifyJson1.getJsonDict();
        fileSimplifyJson1.simplifyJson((*array)["signal"]);
        vector<RSJresource> clean_array = fileSimplifyJson1.getJsonCleanArray();

        // Test
        cout << array->as_str() << endl;
        for(RSJresource el : clean_array){
            cout<<el.as_str()<<endl;
        }
        TC_Simplify_Json.check(true);

    // === consistencyAndPrepare ===
    Test TC_Consistency_And_Prepare("Consistency and prepare");
        // Setup
        Json fileConsistencyAndPrepare1("Tests/database/json/test1_consistencyAndPrepare.json");
        Json fileConsistencyAndPrepare2("Tests/database/json/test2_consistencyAndPrepare.json");
        Json fileConsistencyAndPrepare3("Tests/database/json/test3_consistencyAndPrepare.json");
        Json fileConsistencyAndPrepare4("Tests/database/json/test4_consistencyAndPrepare.json");
        Json fileConsistencyAndPrepare5("Tests/database/json/test5_consistencyAndPrepare.json");
        Json fileConsistencyAndPrepare6("Tests/database/json/test6_consistencyAndPrepare.json");
        Json fileConsistencyAndPrepare7("Tests/database/json/test7_consistencyAndPrepare.json");

        // Test
        TC_Consistency_And_Prepare.check(fileConsistencyAndPrepare1.consistencyAndPrepare()==0);
        TC_Consistency_And_Prepare.check(fileConsistencyAndPrepare2.consistencyAndPrepare()==1);
        TC_Consistency_And_Prepare.check(fileConsistencyAndPrepare3.consistencyAndPrepare()==2);
        TC_Consistency_And_Prepare.check(fileConsistencyAndPrepare4.consistencyAndPrepare()==3);
        TC_Consistency_And_Prepare.check(fileConsistencyAndPrepare5.consistencyAndPrepare()==4);
        TC_Consistency_And_Prepare.check(fileConsistencyAndPrepare6.consistencyAndPrepare()==5);
        TC_Consistency_And_Prepare.check(fileConsistencyAndPrepare7.consistencyAndPrepare()==6);

    // === simplifyWaves ===
    Test TC_Simplify_Waves("Simplify_Waves");
        // Setup
        Json fileSimplifyWaves1("Tests/database/json/test1_simplifyWaves.json");
        Json fileSimplifyWaves2("Tests/database/json/test2_simplifyWaves.json");
        
        // Test
        TC_Simplify_Waves.check(fileSimplifyWaves1.simplifyWaves()==0);
        TC_Simplify_Waves.check(fileSimplifyWaves2.simplifyWaves()==1);

    // === Final Tests Json ===
    Test TC_Final_Tests_Json("Final Tests Json");
        //Setup
        Json fileFinalTestJson1("Tests/database/Examen/stimuli/full_adder.json");
        Json fileFinalTestJson2("Tests/database/Examen/stimuli/half_adder.json");
        Json fileFinalTestJson3("Tests/database/Examen/stimuli/lfsr.json");
        Json fileFinalTestJson4("Tests/database/Examen/stimuli/one_input.json");
        Json fileFinalTestJson5("Tests/database/Examen/stimuli/two_inputs.json");
        Json fileFinalTestJson6("Tests/database/Examen/stimuli/three_inputs.json");

        //Test
        TC_Final_Tests_Json.check(fileFinalTestJson1.getErrorCode()==0); //no error
        TC_Final_Tests_Json.check(fileFinalTestJson2.getErrorCode()==0); //no error
        TC_Final_Tests_Json.check(fileFinalTestJson3.getErrorCode()==0); //no error
        TC_Final_Tests_Json.check(fileFinalTestJson4.getErrorCode()==0); //no error
        TC_Final_Tests_Json.check(fileFinalTestJson5.getErrorCode()==0); //no error
        TC_Final_Tests_Json.check(fileFinalTestJson6.getErrorCode()==0); //no error
        
    return 0;
}