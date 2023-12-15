#include "Test.hpp"
#include "../Dot/Dot.hpp"
#include "../Dot/Token.hpp"

using namespace std;

int main() {

    // === Token Functions ===
    Test TC_Token("Token Functions"); // create test case for Token Functions 
        //  == checkFirstToken ==
        // Setup
        Token firstToken("label", StatementKeyWords, NULL, NULL, 2, 10);
        Token secondToken("label", StatementKeyWords, &firstToken, NULL, 2, 10);
        firstToken.setNextToken(&secondToken);
        
        // Test
        TC_Token.check(firstToken.isFirst());
        TC_Token.check(!secondToken.isFirst());

    // === Dot Lexer ===
    // === Check Functions ===
    Test TC_Check("Check Functions"); //TODO: fonctions a passer en static et en bool
        // == checkType checkKeywords CheckArrow ==
        // Setup
        Dot file("Tests/database/Dot/test_and2_true");

        ifstream fileCheckArrow1("Tests/database/Dot/test1_checkArrow.dot");
        ifstream fileCheckArrow2("Tests/database/Dot/test2_checkArrow.dot");
        ifstream fileCheckArrow3("Tests/database/Dot/test3_checkArrow.dot");

        char c1 = '[';
        char c2 = '\"';
        char c3 = '`';

        string keyword1 = "label"; 
        string keyword2 = "bonjour";
        string keyword3 = "digraph";

        string lineCA1;
        string lineCA2;
        string lineCA3;

        getline(fileCheckArrow1,lineCA1);
        getline(fileCheckArrow2,lineCA2);
        getline(fileCheckArrow3,lineCA3);

        // Test
        TC_Check.check(file.checkType(c1, Dot::specialCharacter));
        TC_Check.check(file.checkType(c2, Dot::stringStarter));
        TC_Check.check(file.checkType(c3, Dot::forbiddenCharacter));
        TC_Check.check(!file.checkType(c1, Dot::forbiddenCharacter));
        TC_Check.check(file.checkKeywords(keyword1,2,Dot::statementKeywords));
        TC_Check.check(!file.checkKeywords(keyword2,2,Dot::statementKeywords));
        TC_Check.check(file.checkKeywords(keyword3,3,Dot::starterKeywords));
        TC_Check.check(file.CheckArrow(lineCA1,1));
        TC_Check.check(file.CheckArrow(lineCA2,1));
        TC_Check.check(!file.CheckArrow(lineCA3,1));
    
    // === Register Functions ===
    Test TC_Register("Register Functions"); //TODO: passer fonctions en static et en bool
        // == registerString ==
        // Setup
        ifstream fileString1("Tests/database/Dot/test1_registerString.string");
        ifstream fileString2("Tests/database/Dot/test2_registerString.string");
        ifstream fileString3("Tests/database/Dot/test3_registerString.string");

        string buffer="";
        unsigned int ln = 0, cn = 1;

        string lineRS1;
        string lineRS2;
        string lineRS3;

        getline(fileString1,lineRS1);
        getline(fileString2,lineRS2);
        getline(fileString3,lineRS3);
        
        // Test
        TC_Register.check(file.registerString(fileString1,lineRS1,cn,ln,buffer)==0); ln = 0, cn = 1;
        TC_Register.check(file.registerString(fileString2,lineRS2,cn,ln,buffer)==0); ln = 0, cn = 1;
        TC_Register.check(file.registerString(fileString3,lineRS3,cn,ln,buffer)==1); ln = 0, cn = 1;

        // == registerKeywords ==
        // Setup
        ifstream fileKeyword1("Tests/database/Dot/test1_registerKeywords.dot");
        ifstream fileKeyword2("Tests/database/Dot/test2_registerKeywords.dot");
        ifstream fileKeyword3("Tests/database/Dot/test3_registerKeywords.dot");

        buffer="";

        ln = 0, cn = 0;

        string lineRK1;
        string lineRK2;
        string lineRK3;

        getline(fileKeyword1,lineRK1);
        getline(fileKeyword2,lineRK2);
        getline(fileKeyword3,lineRK3);

        // Test
        TC_Register.check(file.registerKeywords(fileKeyword1,lineRK1,cn,ln,buffer)==0); ln = 0, cn = 0;
        TC_Register.check(file.registerKeywords(fileKeyword2,lineRK1,cn,ln,buffer)==0); ln = 0, cn = 0;
        TC_Register.check(file.registerKeywords(fileKeyword3,lineRK3,cn,ln,buffer)==0); ln = 0, cn = 0;
    
    // === jumpComments Function ===
    Test TC_Jump_Comments("Jump Comments Function"); //passer fonction en static et en bool
        // == jumpComments ==
        // Setup
        ifstream fileComment1("Tests/database/Dot/test1_jumpComments.string");
        ifstream fileComment2("Tests/database/Dot/test2_jumpComments.string");
        ifstream fileComment3("Tests/database/Dot/test3_jumpComments.string");
        ifstream fileComment4("Tests/database/Dot/test4_jumpComments.string");
        ifstream fileComment5("Tests/database/Dot/test5_jumpComments.string");
        ifstream fileComment6("Tests/database/Dot/test6_jumpComments.string");

        buffer="";
        ln = 0, cn = 0;
        
        string lineJC1;
        string lineJC2;
        string lineJC3;
        string lineJC4;
        string lineJC5;
        string lineJC6;

        getline(fileComment1,lineJC1);
        getline(fileComment2,lineJC2);
        getline(fileComment3,lineJC3);
        getline(fileComment4,lineJC4);
        getline(fileComment5,lineJC5);
        getline(fileComment6,lineJC6);

        // Test
        TC_Jump_Comments.check(file.jumpComments(fileComment1,lineJC1,cn,ln)==0); ln = 0; cn = 0;
        TC_Jump_Comments.check(file.jumpComments(fileComment2,lineJC2,cn,ln)==0); ln = 0; cn = 0;
        TC_Jump_Comments.check(file.jumpComments(fileComment3,lineJC3,cn,ln)==0); ln = 0; cn = 0;
        TC_Jump_Comments.check(file.jumpComments(fileComment4,lineJC4,cn,ln)==0); ln = 0; cn = 0;
        TC_Jump_Comments.check(file.jumpComments(fileComment5,lineJC5,cn,ln)==0); ln = 0; cn = 0;
        TC_Jump_Comments.check(file.jumpComments(fileComment6,lineJC6,cn,ln)==1); ln = 0, cn = 0;

    // === Lexer Function ===
    Test TC_Lexer("Lexer Function"); //passer fonction en static et en bool
        // == lexer ==
        // Setup
        Dot file1("Tests/database/Dot/test_and2_true.dot");
        Dot file2("Tests/database/Dot/test_and2_correct.dot");
        Dot file3("Tests/database/Dot/test_and2_false.dot");

        // Test
        TC_Lexer.check(file1.lexer()==0);
        TC_Lexer.check(file2.lexer()==0);
        TC_Lexer.check(file3.lexer()==2);

        //Visualisation lexing
        file1.lexer();
        Token* current = file1.getFirstToken();
        while (current->Token::getNextToken() != NULL) {
            cout << "Token: "<< current->Token::getType() << ", Value: "<< current->Token::getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;
            current = current->getNextToken();
        }
        cout << "Token: "<< current->Token::getType() << ", Value: "<< current->Token::getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;

    return 0;
}
