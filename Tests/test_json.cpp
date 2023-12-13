#include "Test.hpp"
#include "../Json/Json.hpp"

using namespace std;

int main() {

    /*// Setup for all test cases
    Json jsonParse("Tests/database/json/test1.json");*/

    // === assertJsonIntegrity ===
    Test TC_Verify_Min_Json("Verify if there is all minimum elements on Json");
        // Setup
        Json json1("Tests/database/json/test1.json");
        Json json2("Tests/database/json/test2.json");
        Json json3("Tests/database/json/test3.json");
        
        // Test
        TC_Verify_Min_Json.check(json1.assertJsonIntegrity());
        TC_Verify_Min_Json.check(!json2.assertJsonIntegrity());
        TC_Verify_Min_Json.check(!json3.assertJsonIntegrity());

    // === simplifyJson ===
    Test TC_Simplify_Json("Simplify Json");
        // Setup
        Json json1("Tests/database/json/test2.json");
        json1.simplifyJson();
        
        // Test
        cout << json_clean_array << endl;

    // === consistencyAndPrepare ===
    Test TC_Consistency_And_Prepare("Consistency and prepare");
        // Setup
        Json json1("Tests/database/json/test1.json");
        json1.simplifyJson();
        json1.consistencyAndPrepare();
        
        // Test
        cout << json_clean_array << endl;

    // === simplifyWaves ===
    Test TC_Simplify_Waves("Simplify_Waves");
        // Setup
        Json json1("Tests/database/json/test1.json");
        json1.simplifyJson();
        json1.consistencyAndPrepare();
        json1.simplifyWaves();
        
        // Test
        cout << json_clean_array << endl;
    
    return 0;
}
