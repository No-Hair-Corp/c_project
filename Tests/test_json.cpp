#include "Test.hpp"
#include "../Json/Json.hpp"

using namespace std;

int main() {

    /*// Setup for all test cases
    Json jsonParse("Tests/database/json/test1.json");*/

    // === assertJsonIntegrity ===
    Test TC_Verify_Min_Json("Verify if there is all minimum elements on Json");
        // Setup
        Json file1("Tests/database/json/test1.json");
        Json file2("Tests/database/json/test2.json");
        //Json file3("Tests/database/json/test3.json");
        
        // Test
        TC_Verify_Min_Json.check(file1.assertJsonIntegrity()==0);
        TC_Verify_Min_Json.check(file2.assertJsonIntegrity()==0);
        //TC_Verify_Min_Json.check(file3.assertJsonIntegrity()==1);

    /*// === simplifyJson ===
    Test TC_Simplify_Json("Simplify Json");
        // Setup
        file2.simplifyJson();
        
        // Test
        cout << json_clean_array << endl;

    // === consistencyAndPrepare ===
    Test TC_Consistency_And_Prepare("Consistency and prepare");
        // Setup
        file1.simplifyJson();
        file1.consistencyAndPrepare();
        
        // Test
        cout << json_clean_array << endl;

    // === simplifyWaves ===
    Test TC_Simplify_Waves("Simplify_Waves");
        // Setup
        file1.simplifyJson();
        file1.consistencyAndPrepare();
        file1.simplifyWaves();
        
        // Test
        cout << json_clean_array << endl;
    */
    return 0;
}