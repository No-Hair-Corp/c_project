#include "Test.hpp"
#include "../Dot/Dot.hpp"
#include "../Dot/Token.hpp"

using namespace std;

int main() {

    // === Token Functions ===
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
    // === Check Functions ===
    Test TC_Check("Check Functions"); // create test case for Check functions
        
        // == checkType checkKeywords CheckArrow ==
        // Setup

        Dot file1("/database/Dot/test_and2_true");

        //string specialCharacter = ">/\\[]=";
        //string stringStarter = "\"";
        //string keywords[5] = {"label", "sel", "digraph", "strict", "graph"};
        //string forbiddenCharacter = "\'`";

        char c1 = '[';
        char c2 = '\"';
        char c3 = '`';

        string keyword1 = "label";
        string keyword2 = "bonjour";

        string one = "A->B";
        string two = "A--B";
        string three = "A-B";

        // Test
        TC_Check.check(file1.checkType(c1, Dot::specialCharacter));
        TC_Check.check(file1.checkType(c2, Dot::stringStarter));
        TC_Check.check(file1.checkType(c3, Dot::forbiddenCharacter));
        TC_Check.check(file1.checkKeywords(keyword1,5));
        TC_Check.check(!file1.checkKeywords(keyword2,5));
        TC_Check.check(file1.CheckArrow(one,1));
        TC_Check.check(file1.CheckArrow(two,1));
        TC_Check.check(!file1.CheckArrow(three,1));
    
    Test TC_Register("Register Functions");

        // == registerString ==
        // Setup
        

        // Test
        TC_Register.check(file1.registerString())

        // == registerKeyword ==
        // Setup

        // Test
*/
    return 0;
}


/*// Setup
        Dot dotParser("database/dot/test1.dot");
        dotParser.lexer();
        Token* firstDotToken = dotParser.getFirstToken();

    // // run the lexer for the test dot (0 means error while lexing)
    // dotLexer.check(!dotParser.launchLexer());
    
    
    
    // dotLexer.assert(1 == 1);*/