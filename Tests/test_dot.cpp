#include "Test.hpp"
#include "../Dot/Dot.hpp"

using namespace std;

int main() {

    Dot dotParser("database/dot/test1.dot");

    Test dotLexer("Dot Lexer"); // create test case for Lexer
    // run the lexer for the test dot (0 means error while lexing)
    dotLexer.check(!dotParser.launchLexer());
    
    
    
    // dotLexer.assert(1 == 1);


}



