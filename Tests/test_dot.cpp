#include "Test.hpp"
#include "../Dot/Dot.hpp"
#include "../Dot/Token.hpp"

using namespace std;

int main() {



    // === Token Function ===

    Test TC_Token("Token Functions");
        //  == checkFirstToken ==
        // Setup
        Token firstToken("label", "keyword", NULL, NULL, 2, 10);
        Token secondToken("label", "keyword", &firstToken, NULL, 2, 10);
        firstToken.setNextToken(&secondToken);
        
        // Test
        TC_Token.check(firstToken.isFirst());
        TC_Token.check(!secondToken.isFirst());


    // === Dot Lexer ===

    Test TC_Check_Type("Check Type"); // create test case for Check type
        
        // == checkType ==
        // Setup

        Dot file1("/database/Dot/test_and2_true");

        string specialCharacter = ">/\\[]=";
        string stringStarter = "\"";
        string keywords[3] = {"label", "sel", "digraph"};
        string forbiddenCharacter = "\'`";

        char c1 = '[';
        char c2 = '\"';
        char c3 = '`';
        string keyword1 = "label";
        string keyword2 = "bonjour";

        // Test
        TC_Check_Type.check(file1.checkType(c1, specialCharacter));
        TC_Check_Type.check(file1.checkType(c2, stringStarter));
        TC_Check_Type.check(file1.checkType(c3, forbiddenCharacter));
        TC_Check_Type.check(file1.checkType(keyword1));
        TC_Check_Type.check(!file1.checkType(keyword2));
    
    Test TC_Register("Register Functions");

        // == registerString ==
        // Setup

        // Test
        TC_Register.check(file1.registerString())
        // == registerKeyword ==
        // Setup

        // Test

}


/*// Setup
        Dot dotParser("database/dot/test1.dot");
        dotParser.lexer();
        Token* firstDotToken = dotParser.getFirstToken();

    // // run the lexer for the test dot (0 means error while lexing)
    // dotLexer.check(!dotParser.launchLexer());
    
    
    
    // dotLexer.assert(1 == 1);*/