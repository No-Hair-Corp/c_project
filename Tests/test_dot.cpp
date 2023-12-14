#include "Test.hpp"
#include "../Dot/Dot.hpp"
#include "../Dot/Token.hpp"

using namespace std;

int main() {

    // === Token Functions ===
    Test TC_Token("Token Functions"); // create test case for Token Functions 
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
    Test TC_Check("Check Functions"); //TODO: fonctions a passer en static et en bool
        // == checkType checkKeywords CheckArrow ==
        // Setup
        Dot file("/database/Dot/test_and2_true");

        char c1 = '[';
        char c2 = '\"';
        char c3 = '`';

        string keyword1 = "label";
        string keyword2 = "bonjour";

        string one = "A->B";
        string two = "A--B";
        string three = "A-B";

        // Test
        TC_Check.check(file.checkType(c1, Dot::specialCharacter));
        TC_Check.check(file.checkType(c2, Dot::stringStarter));
        TC_Check.check(file.checkType(c3, Dot::forbiddenCharacter));
        TC_Check.check(!file.checkType(c1, Dot::forbiddenCharacter));
        TC_Check.check(file.checkKeywords(keyword1,5));
        TC_Check.check(!file.checkKeywords(keyword2,5));
        TC_Check.check(file.CheckArrow(one,1));
        TC_Check.check(file.CheckArrow(two,1));
        TC_Check.check(!file.CheckArrow(three,1));
    
    // === Register Functions ===
    Test TC_Register("Register Functions"); //TODO: passer fonctions en static et en bool
        // == registerString ==
        // Setup
        ifstream fileString1("/database/Dot/test1_registerString");
        ifstream fileString2("/database/Dot/test2_registerString");
        ifstream fileString3("/database/Dot/test3_registerString");

        string line;
        string buffer="";
        unsigned int line_number = 0;
        unsigned int column_number = 0;

        // Test
        TC_Register.check(file.registerString(fileString1,line,column_number,line_number,buffer));
        TC_Register.check(file.registerString(fileString2,line,column_number,line_number,buffer));
        TC_Register.check(!file.registerString(fileString3,line,column_number,line_number,buffer));

        // == registerKeywords ==
        // Setup
        ifstream fileKeyword1("/database/Dot/test1_registerKeywords");
        ifstream fileKeyword2("/database/Dot/test1_registerKeywords");

        buffer="";
        line_number = 0;
        column_number = 0;

        // Test
        TC_Register.check(file.registerString(fileKeyword1,line,column_number,line_number,buffer));
        TC_Register.check(!file.registerString(fileKeyword2,line,column_number,line_number,buffer));
    
    // === jumpComments Function ===
    Test TC_Jump_Comments("Jump Comments Function"); //passer fonction en static et en bool
        // == jumpComments ==
        // Setup
        ifstream fileComment1("/database/Dot/test1_jumpComments");
        ifstream fileComment2("/database/Dot/test2_jumpComments");
        ifstream fileComment3("/database/Dot/test3_jumpComments");
        ifstream fileComment4("/database/Dot/test4_jumpComments");
        ifstream fileComment5("/database/Dot/test5_jumpComments");
        ifstream fileComment6("/database/Dot/test6_jumpComments");

        // Test
        TC_Jump_Comments.check(file.registerString(fileComment1,line,column_number,line_number,buffer));
        TC_Jump_Comments.check(file.registerString(fileComment2,line,column_number,line_number,buffer));
        TC_Jump_Comments.check(file.registerString(fileComment3,line,column_number,line_number,buffer));
        TC_Jump_Comments.check(!file.registerString(fileComment4,line,column_number,line_number,buffer));
        TC_Jump_Comments.check(!file.registerString(fileComment5,line,column_number,line_number,buffer));
        TC_Jump_Comments.check(!file.registerString(fileComment6,line,column_number,line_number,buffer));


    // === Lexer Function ===
    Test TC_Lexer("Lexer Function"); //passer fonction en static et en bool
        // == lexer ==
        // Setup
        Dot file1("/database/Dot/test_and2_true");
        Dot file2("/database/Dot/test_and2_correct");
        Dot file3("/database/Dot/test_and2_false");

        // Test
        TC_Lexer.check(file1.lexer());
        TC_Lexer.check(file2.lexer());
        TC_Lexer.check(file3.lexer());

        //TODO afficher token et comparer avec fichier entrée pour voir si ça lexe bien

    return 0;
}


/*// Setup
        Dot dotParser("database/dot/test1.dot");
        dotParser.lexer();
        Token* firstDotToken = dotParser.getFirstToken();

    // // run the lexer for the test dot (0 means error while lexing)
    // dotLexer.check(!dotParser.launchLexer());
    
    
    
    // dotLexer.assert(1 == 1);*/