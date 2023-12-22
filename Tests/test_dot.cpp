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
    // === Check Lexer Functions ===
    Test TC_Check_Lexer("Check Lexer Functions");
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
        TC_Check_Lexer.check(file.checkType(c1, Dot::specialCharacter));
        TC_Check_Lexer.check(file.checkType(c2, Dot::stringStarter));
        TC_Check_Lexer.check(file.checkType(c3, Dot::forbiddenCharacter));
        TC_Check_Lexer.check(!file.checkType(c1, Dot::forbiddenCharacter));
        TC_Check_Lexer.check(file.checkKeywords(keyword1,176,Dot::statementKeywords));
        TC_Check_Lexer.check(!file.checkKeywords(keyword2,176,Dot::statementKeywords));
        TC_Check_Lexer.check(file.checkKeywords(keyword3,3,Dot::starterKeywords));
        TC_Check_Lexer.check(file.CheckArrow(lineCA1,1));
        TC_Check_Lexer.check(file.CheckArrow(lineCA2,1));
        TC_Check_Lexer.check(!file.CheckArrow(lineCA3,1));
    
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
        Dot fileLexer1("Tests/database/dot/test_and2_true.dot");
        Dot fileLexer2("Tests/database/dot/test_and2_correct.dot");
        Dot fileLexer3("Tests/database/dot/test_and2_false.dot");
        Dot fileLexer4("Tests/database/dot/test_lexer.dot");

        // Test
        TC_Lexer.check(fileLexer1.lexer()==0);
        TC_Lexer.check(fileLexer2.lexer()==0);
        TC_Lexer.check(fileLexer3.lexer()==1); //forbiden character detected so error
        TC_Lexer.check(fileLexer4.lexer()==2); //label empty

        // // Visualisation lexing
        // fileLexer1.lexer();
        // Token* current = fileLexer1.getFirstToken();
        // while (current->Token::getNextToken() != NULL) {
        //     cout << "Token: "<< current->Token::getType() << ", Value: "<< current->Token::getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;
        //     current = current->getNextToken();
        // }
        // cout << "Token: "<< current->Token::getType() << ", Value: "<< current->Token::getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;

    // === Dot Parser ===
    // === Check Parser Functions ===
    Test TC_Check_Parser("Check Parser Functions"); //only with function type int and return 1 instead of exit(1)
        // == checkExistence(map<string, SchematicObject*>& schematicObjectsList, map<string, vector<string>>& tempLink) ==
        // Setup
        SchematicObject SO1("A","input");
        SchematicObject SO2("B","input");

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

        tempLink1[SO1.getGateId()]=v1; 
        tempLink2[SO1.getGateId()]=v2; 
        tempLink3["D"]=v1; 

        // Test
        TC_Check_Parser.check(file.checkExistence(schematicObjectsList1, tempLink1)==0); //SO1 ou A prend B en entrée, les 2 existent donc ça doit marcher
        TC_Check_Parser.check(file.checkExistence(schematicObjectsList1, tempLink2)==1); //SO1 ou A prend B et C en entrée, C n'existe pas donc ça ne doit pas marcher
        TC_Check_Parser.check(file.checkExistence(schematicObjectsList1, tempLink3)==2); //D prend B en entrée, D n'existe pas donc ça ne doit pas marcher

        // == checkExistence(map<string, SchematicObject*>& schematicObjectsList) ==
        // Setup
        map<string, string> addOptions1;
        map<string, string> addOptions2;

        addOptions1["sel"] = "A";
        addOptions2["sel"] = "B";
        
        SchematicObject SO3("A","input", addOptions1);
        SchematicObject SO4("A","input", addOptions2);

        SchematicObject* r = &SO3;
        SchematicObject* s = &SO4;

        map<string, SchematicObject*> schematicObjectsList2;
        map<string, SchematicObject*> schematicObjectsList3;

        schematicObjectsList2["A"] = r;
        schematicObjectsList3["A"] = s;

        // Test
        TC_Check_Parser.check(file.checkExistence(schematicObjectsList2)==0);
        TC_Check_Parser.check(file.checkExistence(schematicObjectsList3)==1);

        //  == checkLabel ==
        // Setup
        SchematicObject SO5("A","input");
        SchematicObject SO6("B","");

        SchematicObject* t = &SO5;
        SchematicObject* u = &SO6;

        map<string, SchematicObject*> schematicObjectsList4;
        map<string, SchematicObject*> schematicObjectsList5;

        schematicObjectsList4["A"] = t;
        schematicObjectsList5["B"] = u;
        
        // Test
        TC_Check_Parser.check(file.checkLabel(schematicObjectsList4)==0);
        TC_Check_Parser.check(file.checkLabel(schematicObjectsList5)==1);

    // === fillIoList Function ===
    Test TC_Fill_Io_List("Fill Io List Function");
        //  == fillIoList ==
        // Setup
        map<string, string> addOptions3;
        map<string, string> addOptions4;

        addOptions4["sel"] = "C";

        SchematicObject SO7("A","input",addOptions3);
        SchematicObject SO8("B","input",addOptions3);
        SchematicObject SO9("C","input",addOptions4);
        SchematicObject SO10("GATE1","mux",addOptions3);
        SchematicObject SO11("O","output",addOptions3);

        SchematicObject* v = &SO7;
        SchematicObject* w = &SO8;
        SchematicObject* x = &SO9;
        SchematicObject* y = &SO10;
        SchematicObject* z = &SO11;

        map<string, SchematicObject*> schematicObjectsList6;

        schematicObjectsList6["A"] = v;
        schematicObjectsList6["B"] = w;
        schematicObjectsList6["C"] = x;
        schematicObjectsList6["GATE1"] = y;
        schematicObjectsList6["O"] = z;

        map<string, vector<string>> tempLinkToFill1;

        vector<string> v3={"A","B","C"};
        vector<string> v4={"GATE1"};

        tempLinkToFill1["GATE1"]=v3;
        tempLinkToFill1["O"]=v4;

        // Test
        TC_Fill_Io_List.check(file.fillIoList(schematicObjectsList6,tempLinkToFill1)==0);
        // // Visualisation liste remplie :
        // cout << "Taille de la liste de SO: " << schematicObjectsList6.size() << endl;
        // for(auto const& x : schematicObjectsList6){
        //     x.second->print();
        // }

    // === parse Function ===
    Test TC_Parser("Parser Function");
        // == parse ==
        // Setup
        Dot fileParse00("Tests/database/dot/test_and2_true.dot");
        Dot fileParse01("Tests/database/dot/test_complexcircuit_true.dot");
        Dot fileParse02("Tests/database/dot/test_graphcircuit_true.dot");
        Dot fileParse03("Tests/database/dot/test_strictcircuit_true.dot");

        Dot fileParse1("Tests/database/dot/test1_parse.dot");
        Dot fileParse2("Tests/database/dot/test2_parse.dot");
        Dot fileParse3("Tests/database/dot/test3_parse.dot");
        Dot fileParse4("Tests/database/dot/test4_parse.dot");
        Dot fileParse5("Tests/database/dot/test5_parse.dot");
        Dot fileParse6("Tests/database/dot/test6_parse.dot");
        Dot fileParse7("Tests/database/dot/test7_parse.dot");
        Dot fileParse8("Tests/database/dot/test8_parse.dot");
        Dot fileParse9("Tests/database/dot/test9_parse.dot");
        Dot fileParse10("Tests/database/dot/test10_parse.dot");
        Dot fileParse11("Tests/database/dot/test11_parse.dot");
        Dot fileParse12("Tests/database/dot/test12_parse.dot");
        Dot fileParse13("Tests/database/dot/test13_parse.dot");
        Dot fileParse14("Tests/database/dot/test14_parse.dot");
        Dot fileParse15("Tests/database/dot/test15_parse.dot");
        Dot fileParse16("Tests/database/dot/test16_parse.dot");
        Dot fileParse18("Tests/database/dot/test18_parse.dot");
        Dot fileParse19("Tests/database/dot/test19_parse.dot");
        Dot fileParse20("Tests/database/dot/test20_parse.dot");
        Dot fileParse21("Tests/database/dot/test21_parse.dot");

        fileParse00.lexer();
        fileParse01.lexer();
        fileParse02.lexer();
        fileParse03.lexer();

        fileParse1.lexer();
        fileParse2.lexer();
        fileParse3.lexer();
        fileParse4.lexer();
        fileParse5.lexer();
        fileParse6.lexer();
        fileParse7.lexer();
        fileParse8.lexer();
        fileParse9.lexer();
        fileParse10.lexer();
        fileParse11.lexer();
        fileParse12.lexer();
        fileParse13.lexer();
        fileParse14.lexer();
        fileParse15.lexer();
        fileParse16.lexer();
        fileParse18.lexer();
        fileParse19.lexer();
        fileParse20.lexer();
        fileParse21.lexer();

        // Test
        TC_Parser.check(fileParse00.parse()==0);
        TC_Parser.check(fileParse01.parse()==0);
        TC_Parser.check(fileParse02.parse()==0);
        TC_Parser.check(fileParse03.parse()==0); //all these tests are good, they are for different structures of dot files

        TC_Parser.check(fileParse1.parse()==1);
        TC_Parser.check(fileParse2.parse()==2);
        TC_Parser.check(fileParse3.parse()==3);
        TC_Parser.check(fileParse4.parse()==4);
        TC_Parser.check(fileParse5.parse()==5);
        TC_Parser.check(fileParse6.parse()==6);
        TC_Parser.check(fileParse7.parse()==7);
        TC_Parser.check(fileParse8.parse()==8);
        TC_Parser.check(fileParse9.parse()==9);
        TC_Parser.check(fileParse10.parse()==10);
        TC_Parser.check(fileParse11.parse()==11);
        TC_Parser.check(fileParse12.parse()==12);
        TC_Parser.check(fileParse13.parse()==13);
        TC_Parser.check(fileParse14.parse()==14);
        TC_Parser.check(fileParse15.parse()==15);
        TC_Parser.check(fileParse16.parse()==16);
        TC_Parser.check(fileParse18.parse()==18);
        TC_Parser.check(fileParse19.parse()==19);
        TC_Parser.check(fileParse20.parse()==20);
        TC_Parser.check(fileParse21.parse()==21);

        // // Visualisation parsing
        // cout << "Taille de la liste de SO: " << fileParse00.getSchematicObjectsList().size() << endl;
        // for(auto const& x : fileParse00.getSchematicObjectsList()){
        //     x.second->print();
        // }

    // === Final Tests Dot ===
    Test TC_Final_Tests_Dot("Final Tests Dot");
        //grammar_check
        //Setup
        Dot fileFinalTestDotGC1("Tests/database/Examen/grammar_check/case_insentive.dot");
        Dot fileFinalTestDotGC2("Tests/database/Examen/grammar_check/direct_connection_inversed.dot");
        Dot fileFinalTestDotGC3("Tests/database/Examen/grammar_check/double_declaration_1.dot");
        Dot fileFinalTestDotGC4("Tests/database/Examen/grammar_check/double_declaration_2.dot");
        Dot fileFinalTestDotGC5("Tests/database/Examen/grammar_check/empty_graph.dot");
        Dot fileFinalTestDotGC6("Tests/database/Examen/grammar_check/empty.dot");
        Dot fileFinalTestDotGC7("Tests/database/Examen/grammar_check/input_loop.dot");
        Dot fileFinalTestDotGC8("Tests/database/Examen/grammar_check/label_empty.dot");
        Dot fileFinalTestDotGC9("Tests/database/Examen/grammar_check/label_incomplete.dot");
        Dot fileFinalTestDotGC10("Tests/database/Examen/grammar_check/label_missing_bracket_1.dot");
        Dot fileFinalTestDotGC11("Tests/database/Examen/grammar_check/label_missing_bracket_2.dot");
        Dot fileFinalTestDotGC12("Tests/database/Examen/grammar_check/label_missing.dot");
        Dot fileFinalTestDotGC13("Tests/database/Examen/grammar_check/label_wrong.dot");
        Dot fileFinalTestDotGC14("Tests/database/Examen/grammar_check/long_name_1.dot");
        Dot fileFinalTestDotGC15("Tests/database/Examen/grammar_check/long_name_2.dot");
        Dot fileFinalTestDotGC16("Tests/database/Examen/grammar_check/missing_bracket_1.dot");
        Dot fileFinalTestDotGC17("Tests/database/Examen/grammar_check/missing_bracket_2.dot");
        Dot fileFinalTestDotGC18("Tests/database/Examen/grammar_check/missing_connection.dot");
        Dot fileFinalTestDotGC19("Tests/database/Examen/grammar_check/missing_declaration.dot");
        Dot fileFinalTestDotGC20("Tests/database/Examen/grammar_check/missing_semicolomn_1.dot");
        Dot fileFinalTestDotGC21("Tests/database/Examen/grammar_check/missing_semicolomn_multiple.dot");
        Dot fileFinalTestDotGC22("Tests/database/Examen/grammar_check/output_loop.dot");
        Dot fileFinalTestDotGC23("Tests/database/Examen/grammar_check/reserved_words.dot");

        fileFinalTestDotGC1.lexer();
        fileFinalTestDotGC2.lexer();
        fileFinalTestDotGC3.lexer();
        fileFinalTestDotGC4.lexer();
        fileFinalTestDotGC5.lexer();
        fileFinalTestDotGC6.lexer();
        fileFinalTestDotGC7.lexer();
        fileFinalTestDotGC8.lexer();
        fileFinalTestDotGC9.lexer();
        fileFinalTestDotGC10.lexer();
        fileFinalTestDotGC11.lexer();
        fileFinalTestDotGC12.lexer();
        fileFinalTestDotGC13.lexer();
        fileFinalTestDotGC14.lexer();
        fileFinalTestDotGC15.lexer();
        fileFinalTestDotGC16.lexer();
        fileFinalTestDotGC17.lexer();
        fileFinalTestDotGC18.lexer();
        fileFinalTestDotGC19.lexer();
        fileFinalTestDotGC20.lexer();
        fileFinalTestDotGC21.lexer();
        fileFinalTestDotGC22.lexer();
        fileFinalTestDotGC23.lexer();

        //Test
        TC_Final_Tests_Dot.check(fileFinalTestDotGC1.parse()==18); //error : difference between GATE (declaration) and GaTe (connections), GaTe in connections is not declared
        TC_Final_Tests_Dot.check(fileFinalTestDotGC2.parse()==0); //no error
        TC_Final_Tests_Dot.check(fileFinalTestDotGC3.parse()==7); //error : double declaration <=> gateid already used
        TC_Final_Tests_Dot.check(fileFinalTestDotGC4.parse()==7); //error : double declaration <=> gateid already used
        TC_Final_Tests_Dot.check(fileFinalTestDotGC5.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotGC6.parse()==21); //error : empty file
        TC_Final_Tests_Dot.check(fileFinalTestDotGC7.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotGC8.lexer()==2); //error on lexer : label empty : [label=""]
        TC_Final_Tests_Dot.check(fileFinalTestDotGC9.parse()==12); //error : label not declared : [label=]
        TC_Final_Tests_Dot.check(fileFinalTestDotGC10.parse()==13); //error : missing ending label bracket
        TC_Final_Tests_Dot.check(fileFinalTestDotGC11.parse()==8); //error : missing starting label bracket
        TC_Final_Tests_Dot.check(fileFinalTestDotGC12.parse()==8); //error : label missing <=> error detected : missing starting label bracket
        TC_Final_Tests_Dot.check(fileFinalTestDotGC13.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotGC14.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotGC15.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotGC16.parse()==5); //error : after digraph missing starting accolade
        TC_Final_Tests_Dot.check(fileFinalTestDotGC17.parse()==13); //error : first error detected : ending label bracket missing
        TC_Final_Tests_Dot.check(fileFinalTestDotGC18.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotGC19.parse()==18); //error : I in connections is not declared
        TC_Final_Tests_Dot.check(fileFinalTestDotGC20.parse()==0); //no error
        TC_Final_Tests_Dot.check(fileFinalTestDotGC21.parse()==0); //no error
        TC_Final_Tests_Dot.check(fileFinalTestDotGC22.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotGC23.parse()==6); //error : keyword used <=> expecting an AnyWord

        //structure_check
        //Setup
        Dot fileFinalTestDotSC1("Tests/database/Examen/structure_check/comb_loop_long.dot");
        Dot fileFinalTestDotSC2("Tests/database/Examen/structure_check/comb_loop_simple.dot");
        Dot fileFinalTestDotSC3("Tests/database/Examen/structure_check/concatenation.dot");
        Dot fileFinalTestDotSC4("Tests/database/Examen/structure_check/dangling_gate.dot");
        Dot fileFinalTestDotSC5("Tests/database/Examen/structure_check/double_declaration_2.dot");
        Dot fileFinalTestDotSC6("Tests/database/Examen/structure_check/floating_loop.dot");
        Dot fileFinalTestDotSC7("Tests/database/Examen/structure_check/input_output_inversed.dot");
        Dot fileFinalTestDotSC8("Tests/database/Examen/structure_check/label_missing_bracket_1.dot");
        Dot fileFinalTestDotSC9("Tests/database/Examen/structure_check/label_missing_bracket_2.dot");
        Dot fileFinalTestDotSC10("Tests/database/Examen/structure_check/label_wrong.dot");
        Dot fileFinalTestDotSC11("Tests/database/Examen/structure_check/missing_connection_1.dot");
        Dot fileFinalTestDotSC12("Tests/database/Examen/structure_check/missing_input.dot");
        Dot fileFinalTestDotSC13("Tests/database/Examen/structure_check/missing_output.dot");
        Dot fileFinalTestDotSC14("Tests/database/Examen/structure_check/not_enough_ports.dot");
        Dot fileFinalTestDotSC15("Tests/database/Examen/structure_check/too_many_ports.dot");

        fileFinalTestDotSC1.lexer();
        fileFinalTestDotSC2.lexer();
        fileFinalTestDotSC3.lexer();
        fileFinalTestDotSC4.lexer();
        fileFinalTestDotSC5.lexer();
        fileFinalTestDotSC6.lexer();
        fileFinalTestDotSC7.lexer();
        fileFinalTestDotSC8.lexer();
        fileFinalTestDotSC9.lexer();
        fileFinalTestDotSC10.lexer();
        fileFinalTestDotSC11.lexer();
        fileFinalTestDotSC12.lexer();
        fileFinalTestDotSC13.lexer();
        fileFinalTestDotSC14.lexer();
        fileFinalTestDotSC15.lexer();

        //Test
        TC_Final_Tests_Dot.check(fileFinalTestDotSC1.parse()==0); //no error
        TC_Final_Tests_Dot.check(fileFinalTestDotSC2.parse()==0); //no error
        TC_Final_Tests_Dot.check(fileFinalTestDotSC3.parse()==0); //no error
        TC_Final_Tests_Dot.check(fileFinalTestDotSC4.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotSC5.parse()==7); //error : double declaration <=> gateid already used
        TC_Final_Tests_Dot.check(fileFinalTestDotSC6.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotSC7.parse()==18); //error : 1 in connections is not declared
        TC_Final_Tests_Dot.check(fileFinalTestDotSC8.parse()==13); //error : missing ending label bracket 
        TC_Final_Tests_Dot.check(fileFinalTestDotSC9.parse()==8); //error : missing starting label bracket
        TC_Final_Tests_Dot.check(fileFinalTestDotSC10.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotSC11.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotSC12.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotSC13.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotSC14.parse()==0); //no error for parser, managed in simulator
        TC_Final_Tests_Dot.check(fileFinalTestDotSC15.parse()==0); //no error for parser, managed in simulator
        
        /*//portes_elementaires
        //Setup
        Dot fileFinalTestDotPE1("Tests/database/Examen/portes_elementaires/and2.dot");
        
        map<string, string> addOptionsPE1;

        SchematicObject SO_PE1("I1","INPUT",addOptionsPE1);
        SchematicObject SO_PE2("I2","INPUT",addOptionsPE1);
        SchematicObject SO_PE3("GATE","AND2",addOptionsPE1);
        SchematicObject SO_PE4("O","OUTPUT",addOptionsPE1);

        SchematicObject* a = &SO_PE1;
        SchematicObject* b = &SO_PE2;
        SchematicObject* c = &SO_PE3;
        SchematicObject* d = &SO_PE4;

        map<string, SchematicObject*> schematicObjectsListPE;

        schematicObjectsListPE["I1"] = a;
        schematicObjectsListPE["I2"] = b;
        schematicObjectsListPE["GATE"] = c;
        schematicObjectsListPE["O"] = d;

        map<string, vector<string>> tempLinkToFillPE;

        vector<string> vPE1={"I1","I2"};
        vector<string> vPE2={"GATE"};

        tempLinkToFillPE["GATE"]=vPE1;
        tempLinkToFillPE["O"]=vPE2;

        file.fillIoList(schematicObjectsListPE,tempLinkToFillPE);

        fileFinalTestDotPE1.lexer();
        fileFinalTestDotPE1.parse();        

        cout << "On doit obtenir : " << endl;
        for(auto const& x : schematicObjectsListPE){
            x.second->print();
        }
        cout<<endl;

        cout << "Et on obtient : " << endl;
        for(auto const& x : fileFinalTestDotPE1.getSchematicObjectsList()){
            x.second->print();
        }
*/

    return 0;
}