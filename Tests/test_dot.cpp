#include "Test.hpp"
#include "../Dot/Dot.hpp"
#include "../Dot/Token.hpp"
#include "../Dot/SchematicObject.hpp"

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
    Test TC_Check("Check Functions");
        // == checkType checkKeywords CheckArrow ==
        // Setup
        Dot file("Tests/database/dot/test_and2_true");

        ifstream fileCheckArrow1("Tests/database/dot/test1_checkArrow.dot");
        ifstream fileCheckArrow2("Tests/database/dot/test2_checkArrow.dot");
        ifstream fileCheckArrow3("Tests/database/dot/test3_checkArrow.dot");

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
        TC_Check.check(file.checkKeywords(keyword1,176,Dot::statementKeywords));
        TC_Check.check(!file.checkKeywords(keyword2,176,Dot::statementKeywords));
        TC_Check.check(file.checkKeywords(keyword3,3,Dot::starterKeywords));
        TC_Check.check(file.CheckArrow(lineCA1,1));
        TC_Check.check(file.CheckArrow(lineCA2,1));
        TC_Check.check(!file.CheckArrow(lineCA3,1));
    
    // === Register Functions ===
    Test TC_Register("Register Functions");
        // == registerString ==
        // Setup
        ifstream fileString1("Tests/database/dot/test1_registerString.string");
        ifstream fileString2("Tests/database/dot/test2_registerString.string");
        ifstream fileString3("Tests/database/dot/test3_registerString.string");

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
        ifstream fileKeyword1("Tests/database/dot/test1_registerKeywords.dot");
        ifstream fileKeyword2("Tests/database/dot/test2_registerKeywords.dot");
        ifstream fileKeyword3("Tests/database/dot/test3_registerKeywords.dot");

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
    Test TC_Jump_Comments("Jump Comments Function");
        // == jumpComments ==
        // Setup
        ifstream fileComment1("Tests/database/dot/test1_jumpComments.string");
        ifstream fileComment2("Tests/database/dot/test2_jumpComments.string");
        ifstream fileComment3("Tests/database/dot/test3_jumpComments.string");
        ifstream fileComment4("Tests/database/dot/test4_jumpComments.string");
        ifstream fileComment5("Tests/database/dot/test5_jumpComments.string");
        ifstream fileComment6("Tests/database/dot/test6_jumpComments.string");

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

    // === lexer Function ===
    Test TC_Lexer("Lexer Function");
        // == lexer ==
        // Setup
        Dot file1("Tests/database/dot/test_and2_true.dot");
        Dot file2("Tests/database/dot/test_and2_correct.dot");
        Dot file3("Tests/database/dot/test_and2_false.dot");

        // Test
        TC_Lexer.check(file1.lexer()==0);
        TC_Lexer.check(file2.lexer()==0);
        /*TC_Lexer.check(file3.lexer()==2); //only with a return instead of exit(1)

        // Visualisation lexing
        file1.lexer();
        Token* current = file1.getFirstToken();
        while (current->Token::getNextToken() != NULL) {
            cout << "Token: "<< current->Token::getType() << ", Value: "<< current->Token::getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;
            current = current->getNextToken();
        }
        cout << "Token: "<< current->Token::getType() << ", Value: "<< current->Token::getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;
        */

    // === Dot Parser ===
    // === throwParseError Functions ===
    /*Test TC_Throw_Parse_Error("Throw Parse Error Functions"); //only with function type int and return 1 instead of exit(1)
        // == throwParseError(const string& error_message) ==
        // Setup
        string error_message1 = "Test error 1";

        // Test
        TC_Throw_Parse_Error.check(file.throwParseError(error_message1)==1);

        // == throwParseError(const string& error_message, unsigned int line, unsigned int column) ==
        // Setup
        string error_message2 = "Test error 2";
        unsigned int lineError = 0, columnError = 0;

        // Test
        TC_Throw_Parse_Error.check(file.throwParseError(error_message2, lineError, columnError)==1);
    */

    // === checkExistence Functions ===
    Test TC_Check_Existence("Check Existence Functions"); //only with function type int and return 1 instead of exit(1)
        // == checkExistence(map<string, SchematicObject*>& schematicObjectsList, map<string, vector<string>>& tempLink) ==
        // Setup
        SchematicObject SO1("A");
        SchematicObject SO2("B");

        SchematicObject* p = &SO1;
        SchematicObject* q = &SO2;

        map<string, SchematicObject*> schematicObjectsList1;

        schematicObjectsList1["A"] = p;
        schematicObjectsList1["B"] = q;

        vector<string> v1={"B"};
        vector<string> v2={"B","C"};

        map<string, vector<string>> tempLink1;
        map<string, vector<string>> tempLink2;
        map<string, vector<string>> tempLink3;

        tempLink1[SO1.getGateId()]=v1; //SO1 ou A prend B en entrée, les 2 existent donc ça doit marcher
        //tempLink2[SO1.getGateId()]=v2; //SO1 ou A prend B et C en entrée, C n'existe pas donc ça ne doit pas marcher
        //tempLink3["D"]=v1; //D prend B en entrée, D n'existe pas donc ça ne doit pas marcher

        // Test
        TC_Check_Existence.check(file.checkExistence(schematicObjectsList1, tempLink1));
        //TC_Check_Existence.check(!file.checkExistence(schematicObjectsList1, tempLink2));
        //TC_Check_Existence.check(!file.checkExistence(schematicObjectsList1, tempLink3)); //for both of them with function type bool and return false instead of exit(1)

        // == checkExistence(map<string, SchematicObject*>& schematicObjectsList) ==
        // Setup
        map<string, string> addOptions1;
        map<string, string> addOptions2;

        addOptions1["sel"] = "A";
        addOptions2["sel"] = "B";
        
        SchematicObject SO3("A", addOptions1);
        SchematicObject SO4("A", addOptions2);

        SchematicObject* r = &SO3;
        SchematicObject* s = &SO4;

        map<string, SchematicObject*> schematicObjectsList2;
        map<string, SchematicObject*> schematicObjectsList3;

        schematicObjectsList2["A"] = r;
        schematicObjectsList3["A"] = s;

        // Test
        TC_Check_Existence.check(file.checkExistence(schematicObjectsList2));
        //TC_Check_Existence.check(!file.checkExistence(schematicObjectsList3)); //with function type bool and return false instead of exit(1)

    // === checkLabel Function ===
    Test TC_Check_Label("Check Label Function");
        //  == checkLabel ==
        // Setup
        SchematicObject SO5("A", "input");
        
        // Test
        TC_Fill_Io_List.check(file.fillIoList(tempLinkToFill));


    // === fillIoList Function ===
    Test TC_Fill_Io_List("Fill Io List Function");
        //  == fillIoList ==
        // Setup
        map<string, vector<string>> tempLinkToFill;

        vector<string> v3={"B","C"};

        tempLinkToFill["GATE1"]=v3;
        
        // Test
        TC_Fill_Io_List.check(file.fillIoList(tempLinkToFill));

    return 0;
}
