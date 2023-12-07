#include "Test.hpp"
#include "../Dot/Dot.hpp"
#include "../Dot/Token.hpp"

using namespace std;

int main() {

    Dot dotParser("database/dot/test1.dot");


    // === Token Function ===
    Test TC_Token("Token Functions");
        //  == `checkFirstToken` ==
        // Setup
        Token firstToken("label", "keyword", NULL, NULL, 2, 10);
        Token secondToken("label", "keyword", &firstToken, NULL, 2, 10);
        firstToken.setNextToken(&secondToken);
        
        // Test
        TC_Token.check(firstToken.isFirst());
        TC_Token.check(!secondToken.isFirst());




    Test dotLexer("Dot Lexer"); // create test case for Lexer
    // // run the lexer for the test dot (0 means error while lexing)
    // dotLexer.check(!dotParser.launchLexer());
    
    
    
    // dotLexer.assert(1 == 1);


}



