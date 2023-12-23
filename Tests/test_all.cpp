#include "Test.hpp"
#include "../Dot/Token.hpp"
#include "../Dot/SchematicObject.hpp"
#include "../Simulator/Simulator.hpp"

using namespace std;

int main() {

    // === Tests Finaux : Structure ===
    cout << "Tests Finaux : Structure" << endl;
    //portes_elementaires
    Test TC1_Portes_Elementaires("Portes Elementaires (Structure)");
        //Setup
        Dot filePortesElementaires1("Tests/database/Examen/portes_elementaires/and2.dot");
        Dot filePortesElementaires2("Tests/database/Examen/portes_elementaires/direct_connection.dot");
        Dot filePortesElementaires3("Tests/database/Examen/portes_elementaires/FlipFlop.dot");
        Dot filePortesElementaires4("Tests/database/Examen/portes_elementaires/Mux_explicit.dot");
        Dot filePortesElementaires5("Tests/database/Examen/portes_elementaires/Mux_implicit.dot");
        Dot filePortesElementaires6("Tests/database/Examen/portes_elementaires/nand2.dot");
        Dot filePortesElementaires7("Tests/database/Examen/portes_elementaires/nor2.dot");
        Dot filePortesElementaires8("Tests/database/Examen/portes_elementaires/not.dot");
        Dot filePortesElementaires9("Tests/database/Examen/portes_elementaires/or2.dot");
        Dot filePortesElementaires10("Tests/database/Examen/portes_elementaires/xnor2.dot");
        Dot filePortesElementaires11("Tests/database/Examen/portes_elementaires/xor2.dot");

        filePortesElementaires1.lexer();
        filePortesElementaires2.lexer();
        filePortesElementaires3.lexer();
        filePortesElementaires4.lexer();
        filePortesElementaires5.lexer();
        filePortesElementaires6.lexer();
        filePortesElementaires7.lexer();
        filePortesElementaires8.lexer();
        filePortesElementaires9.lexer();
        filePortesElementaires10.lexer();
        filePortesElementaires11.lexer();

        //Test
        TC1_Portes_Elementaires.check(filePortesElementaires1.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires2.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires3.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires4.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires5.parse()==0); //no error for the moment but this way to describe a mux is not accepted by our simulator
        TC1_Portes_Elementaires.check(filePortesElementaires6.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires7.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires8.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires9.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires10.parse()==0);
        TC1_Portes_Elementaires.check(filePortesElementaires11.parse()==0);

    //grammar_check
    Test TC1_Grammar_Check("Grammar Check (Structure)");
        //Setup
        Dot fileGrammarCheck1("Tests/database/Examen/grammar_check/case_insentive.dot");
        Dot fileGrammarCheck2("Tests/database/Examen/grammar_check/direct_connection_inversed.dot");
        Dot fileGrammarCheck3("Tests/database/Examen/grammar_check/double_declaration_1.dot");
        Dot fileGrammarCheck4("Tests/database/Examen/grammar_check/double_declaration_2.dot");
        Dot fileGrammarCheck5("Tests/database/Examen/grammar_check/empty_graph.dot");
        Dot fileGrammarCheck6("Tests/database/Examen/grammar_check/empty.dot");
        Dot fileGrammarCheck7("Tests/database/Examen/grammar_check/input_loop.dot");
        Dot fileGrammarCheck8("Tests/database/Examen/grammar_check/label_empty.dot");
        Dot fileGrammarCheck9("Tests/database/Examen/grammar_check/label_incomplete.dot");
        Dot fileGrammarCheck10("Tests/database/Examen/grammar_check/label_missing_bracket_1.dot");
        Dot fileGrammarCheck11("Tests/database/Examen/grammar_check/label_missing_bracket_2.dot");
        Dot fileGrammarCheck12("Tests/database/Examen/grammar_check/label_missing.dot");
        Dot fileGrammarCheck13("Tests/database/Examen/grammar_check/label_wrong.dot");
        Dot fileGrammarCheck14("Tests/database/Examen/grammar_check/long_name_1.dot");
        Dot fileGrammarCheck15("Tests/database/Examen/grammar_check/long_name_2.dot");
        Dot fileGrammarCheck16("Tests/database/Examen/grammar_check/missing_bracket_1.dot");
        Dot fileGrammarCheck17("Tests/database/Examen/grammar_check/missing_bracket_2.dot");
        Dot fileGrammarCheck18("Tests/database/Examen/grammar_check/missing_connection.dot");
        Dot fileGrammarCheck19("Tests/database/Examen/grammar_check/missing_declaration.dot");
        Dot fileGrammarCheck20("Tests/database/Examen/grammar_check/missing_semicolomn_1.dot");
        Dot fileGrammarCheck21("Tests/database/Examen/grammar_check/missing_semicolomn_multiple.dot");
        Dot fileGrammarCheck22("Tests/database/Examen/grammar_check/output_loop.dot");
        Dot fileGrammarCheck23("Tests/database/Examen/grammar_check/reserved_words.dot");

        fileGrammarCheck1.lexer();
        fileGrammarCheck2.lexer();
        fileGrammarCheck3.lexer();
        fileGrammarCheck4.lexer();
        fileGrammarCheck5.lexer();
        fileGrammarCheck6.lexer();
        fileGrammarCheck7.lexer();
        fileGrammarCheck8.lexer();
        fileGrammarCheck9.lexer();
        fileGrammarCheck10.lexer();
        fileGrammarCheck11.lexer();
        fileGrammarCheck12.lexer();
        fileGrammarCheck13.lexer();
        fileGrammarCheck14.lexer();
        fileGrammarCheck15.lexer();
        fileGrammarCheck16.lexer();
        fileGrammarCheck17.lexer();
        fileGrammarCheck18.lexer();
        fileGrammarCheck19.lexer();
        fileGrammarCheck20.lexer();
        fileGrammarCheck21.lexer();
        fileGrammarCheck22.lexer();
        fileGrammarCheck23.lexer();

        //Test
        TC1_Grammar_Check.check(fileGrammarCheck1.parse()==18); //error : difference between GATE (declaration) and GaTe (connections), GaTe in connections is not declared
        TC1_Grammar_Check.check(fileGrammarCheck2.parse()==0); //no error
        TC1_Grammar_Check.check(fileGrammarCheck3.parse()==7); //error : double declaration <=> gateid already used
        TC1_Grammar_Check.check(fileGrammarCheck4.parse()==7); //error : double declaration <=> gateid already used
        TC1_Grammar_Check.check(fileGrammarCheck5.parse()==0); //no error for parser, managed in simulator
        TC1_Grammar_Check.check(fileGrammarCheck6.parse()==21); //error : empty file
        TC1_Grammar_Check.check(fileGrammarCheck7.parse()==0); //no error for parser, managed in simulator
        TC1_Grammar_Check.check(fileGrammarCheck8.lexer()==2); //error on lexer : label empty : [label=""]
        TC1_Grammar_Check.check(fileGrammarCheck9.parse()==12); //error : label not declared : [label=]
        TC1_Grammar_Check.check(fileGrammarCheck10.parse()==13); //error : missing ending label bracket
        TC1_Grammar_Check.check(fileGrammarCheck11.parse()==8); //error : missing starting label bracket
        TC1_Grammar_Check.check(fileGrammarCheck12.parse()==8); //error : label missing <=> error detected : missing starting label bracket
        TC1_Grammar_Check.check(fileGrammarCheck13.parse()==0); //no error for parser, managed in simulator
        TC1_Grammar_Check.check(fileGrammarCheck14.parse()==0); //no error for parser, managed in simulator
        TC1_Grammar_Check.check(fileGrammarCheck15.parse()==0); //no error for parser, managed in simulator
        TC1_Grammar_Check.check(fileGrammarCheck16.parse()==5); //error : after digraph missing starting accolade
        TC1_Grammar_Check.check(fileGrammarCheck17.parse()==13); //error : first error detected : ending label bracket missing
        TC1_Grammar_Check.check(fileGrammarCheck18.parse()==0); //no error for parser, managed in simulator
        TC1_Grammar_Check.check(fileGrammarCheck19.parse()==18); //error : I in connections is not declared
        TC1_Grammar_Check.check(fileGrammarCheck20.parse()==0); //no error
        TC1_Grammar_Check.check(fileGrammarCheck21.parse()==0); //no error
        TC1_Grammar_Check.check(fileGrammarCheck22.parse()==0); //no error for parser, managed in simulator
        TC1_Grammar_Check.check(fileGrammarCheck23.parse()==6); //error : keyword used <=> expecting an AnyWord

    //structure_ok
    Test TC1_Structure_Ok("Structure Ok (Structure)");
        //Setup
        Dot fileStructureOk1("Tests/database/Examen/structure_ok/and_not.dot");
        Dot fileStructureOk2("Tests/database/Examen/structure_ok/and_xor.dot");
        Dot fileStructureOk3("Tests/database/Examen/structure_ok/concatenation.dot");
        Dot fileStructureOk4("Tests/database/Examen/structure_ok/fan_out.dot"); 
        Dot fileStructureOk5("Tests/database/Examen/structure_ok/independent_paths.dot");
        Dot fileStructureOk6("Tests/database/Examen/structure_ok/not_and.dot");
        Dot fileStructureOk7("Tests/database/Examen/structure_ok/register.dot");
        Dot fileStructureOk8("Tests/database/Examen/structure_ok/shift_register.dot"); 
        Dot fileStructureOk9("Tests/database/Examen/structure_ok/two_outputs.dot");

        fileStructureOk1.lexer();
        fileStructureOk2.lexer();
        fileStructureOk3.lexer();
        fileStructureOk4.lexer();
        fileStructureOk5.lexer();
        fileStructureOk6.lexer();
        fileStructureOk7.lexer();
        fileStructureOk8.lexer();
        fileStructureOk9.lexer();

        //Test
        TC1_Structure_Ok.check(fileStructureOk1.parse()==0);
        TC1_Structure_Ok.check(fileStructureOk2.parse()==0);
        TC1_Structure_Ok.check(fileStructureOk3.parse()==0);
        TC1_Structure_Ok.check(fileStructureOk4.parse()==0);
        TC1_Structure_Ok.check(fileStructureOk5.parse()==0);
        TC1_Structure_Ok.check(fileStructureOk6.parse()==0);
        TC1_Structure_Ok.check(fileStructureOk7.parse()==0);
        TC1_Structure_Ok.check(fileStructureOk8.parse()==0);
        TC1_Structure_Ok.check(fileStructureOk9.parse()==0);

    //structure_check
    Test TC1_Structure_Check("Structure Check (Structure)");
        //Setup
        Dot fileStructureCheck1("Tests/database/Examen/structure_check/comb_loop_long.dot");
        Dot fileStructureCheck2("Tests/database/Examen/structure_check/comb_loop_simple.dot");
        Dot fileStructureCheck3("Tests/database/Examen/structure_check/concatenation.dot");
        Dot fileStructureCheck4("Tests/database/Examen/structure_check/dangling_gate.dot");
        Dot fileStructureCheck5("Tests/database/Examen/structure_check/double_declaration_2.dot");
        Dot fileStructureCheck6("Tests/database/Examen/structure_check/floating_loop.dot");
        Dot fileStructureCheck7("Tests/database/Examen/structure_check/input_output_inversed.dot");
        Dot fileStructureCheck8("Tests/database/Examen/structure_check/label_missing_bracket_1.dot");
        Dot fileStructureCheck9("Tests/database/Examen/structure_check/label_missing_bracket_2.dot");
        Dot fileStructureCheck10("Tests/database/Examen/structure_check/label_wrong.dot");
        Dot fileStructureCheck11("Tests/database/Examen/structure_check/missing_connection_1.dot");
        Dot fileStructureCheck12("Tests/database/Examen/structure_check/missing_input.dot");
        Dot fileStructureCheck13("Tests/database/Examen/structure_check/missing_output.dot");
        Dot fileStructureCheck14("Tests/database/Examen/structure_check/not_enough_ports.dot");
        Dot fileStructureCheck15("Tests/database/Examen/structure_check/too_many_ports.dot");

        fileStructureCheck1.lexer();
        fileStructureCheck2.lexer();
        fileStructureCheck3.lexer();
        fileStructureCheck4.lexer();
        fileStructureCheck5.lexer();
        fileStructureCheck6.lexer();
        fileStructureCheck7.lexer();
        fileStructureCheck8.lexer();
        fileStructureCheck9.lexer();
        fileStructureCheck10.lexer();
        fileStructureCheck11.lexer();
        fileStructureCheck12.lexer();
        fileStructureCheck13.lexer();
        fileStructureCheck14.lexer();
        fileStructureCheck15.lexer();

        //Test
        TC1_Structure_Check.check(fileStructureCheck1.parse()==0); //no error
        TC1_Structure_Check.check(fileStructureCheck2.parse()==0); //no error
        TC1_Structure_Check.check(fileStructureCheck3.parse()==0); //no error
        TC1_Structure_Check.check(fileStructureCheck4.parse()==0); //no error for parser, managed in simulator
        TC1_Structure_Check.check(fileStructureCheck5.parse()==7); //error : double declaration <=> gateid already used
        TC1_Structure_Check.check(fileStructureCheck6.parse()==0); //no error for parser, managed in simulator
        TC1_Structure_Check.check(fileStructureCheck7.parse()==18); //error : 1 in connections is not declared
        TC1_Structure_Check.check(fileStructureCheck8.parse()==13); //error : missing ending label bracket 
        TC1_Structure_Check.check(fileStructureCheck9.parse()==8); //error : missing starting label bracket
        TC1_Structure_Check.check(fileStructureCheck10.parse()==0); //no error for parser, managed in simulator
        TC1_Structure_Check.check(fileStructureCheck11.parse()==0); //no error for parser, managed in simulator
        TC1_Structure_Check.check(fileStructureCheck12.parse()==0); //no error for parser, managed in simulator
        TC1_Structure_Check.check(fileStructureCheck13.parse()==0); //no error for parser, managed in simulator
        TC1_Structure_Check.check(fileStructureCheck14.parse()==0); //no error for parser, managed in simulator
        TC1_Structure_Check.check(fileStructureCheck15.parse()==0); //no error for parser, managed in simulator
    
    //=== Tests Finaux : Simulation ===
    cout << "Tests Finaux : Simulation" << endl;
    //portes_elementaires
    Test TC2_Portes_Elementaires("Portes Elementaires (Simulation)");
        //Setup
        string dot_path1 = "Tests/database/Examen/portes_elementaires/and2.dot";
        string dot_path2 = "Tests/database/Examen/portes_elementaires/direct_connection.dot";
        string dot_path3 = "Tests/database/Examen/portes_elementaires/FlipFlop.dot";
        string dot_path4 = "Tests/database/Examen/portes_elementaires/Mux_explicit.dot";
        string dot_path5 = "Tests/database/Examen/portes_elementaires/nand2.dot";
        string dot_path6 = "Tests/database/Examen/portes_elementaires/nor2.dot";
        string dot_path7 = "Tests/database/Examen/portes_elementaires/not.dot";
        string dot_path8 = "Tests/database/Examen/portes_elementaires/or2.dot";
        string dot_path9 = "Tests/database/Examen/portes_elementaires/xnor2.dot";
        string dot_path10 = "Tests/database/Examen/portes_elementaires/xor2.dot";

        string json_path1 = "Tests/database/Examen/stimuli/one_input.json";
        string json_path2 = "Tests/database/Examen/stimuli/two_inputs.json";
        string json_path3 = "Tests/database/Examen/stimuli/three_inputs.json";
        string json_path4 = "Tests/database/Examen/stimuli/full_adder.json";

        Simulator and2(dot_path1,json_path2);
        Simulator direct_connection(dot_path2,json_path1);
        //Simulator FlipFlop(dot_path3,json_path1);
        Simulator Mux_explicit(dot_path4,json_path3);
        Simulator nand2(dot_path5,json_path2);
        Simulator nor2(dot_path6,json_path2);
        Simulator not_gate(dot_path7,json_path1);
        Simulator or2(dot_path8,json_path2);
        Simulator xnor2(dot_path9,json_path2);
        Simulator xor2(dot_path10,json_path2);

        //Test
        map<string, string> and2_expected_values = {
            {"O", "001110000"}
        }; //ouput names (gateid), output values
        map<string, string> direct_connection_expected_values = {
            {"O", "001110011"}
        }; 
        map<string, string> Mux_explicit_expected_values = {
            {"O", "001110000"}
        }; 
        map<string, string> nand2_expected_values = {
            {"O", "110001111"}
        }; 
        map<string, string> nor2_expected_values = {
            {"O", "000001100"}
        };
        map<string, string> not_gate_expected_values = {
            {"O", "110001100"}
        };
        map<string, string> or2_expected_values = {
            {"O", "111110011"}
        };
        map<string, string> xnor2_expected_values = {
            {"O", "001111100"}
        };
        map<string, string> xor2_expected_values = {
            {"O", "110000011"}
        };

        for(Gate* const& gate : and2.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == and2_expected_values[gate->getGateId()]);
        }
        for(Gate* const& gate : direct_connection.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == direct_connection_expected_values[gate->getGateId()]);
        }
        for(Gate* const& gate : Mux_explicit.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == Mux_explicit_expected_values[gate->getGateId()]);
        }
        for(Gate* const& gate : nand2.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == nand2_expected_values[gate->getGateId()]);
        }
        for(Gate* const& gate : nor2.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == nor2_expected_values[gate->getGateId()]);
        }
        for(Gate* const& gate : not_gate.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == not_gate_expected_values[gate->getGateId()]);
        }
        for(Gate* const& gate : or2.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == or2_expected_values[gate->getGateId()]);
        }
        for(Gate* const& gate : xnor2.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == xnor2_expected_values[gate->getGateId()]);
        }
        for(Gate* const& gate : xor2.getOutputGates()){
            TC2_Portes_Elementaires.check(gate->to_str() == xor2_expected_values[gate->getGateId()]);
        }
        
        

    //structure_ok
    Test TC2_Structure_OK("Structure Ok (Simulation)");
        //Setup
        string dot_path11 = "Tests/database/Examen/structure_ok/and_not.dot";
        string dot_path12 = "Tests/database/Examen/structure_ok/and_xor.dot";
        string dot_path13 = "Tests/database/Examen/structure_ok/concatenation.dot";
        string dot_path14 = "Tests/database/Examen/structure_ok/fan_out.dot"; 
        string dot_path15 = "Tests/database/Examen/structure_ok/independent_paths.dot";
        string dot_path16 = "Tests/database/Examen/structure_ok/not_and.dot";
        string dot_path17 = "Tests/database/Examen/structure_ok/register.dot";
        string dot_path18 = "Tests/database/Examen/structure_ok/shift_register.dot"; 
        string dot_path19 = "Tests/database/Examen/structure_ok/two_outputs.dot";

        Simulator and_not(dot_path11,json_path2);
        Simulator and_xor(dot_path12,json_path3);
        Simulator concatenation(dot_path13,json_path1);
        Simulator fan_out(dot_path14,json_path2);
        //Simulator independan_paths(dot_path15);
        Simulator not_and(dot_path16,json_path2);
        //Simulator reg(dot_path17);
        //Simulator shift_reg(dot_path18);
        Simulator two_outputs(dot_path19,json_path2);

        //Test

    //circuits
    Test TC2_Circuits("Circuit FA (Simulation)");
        //Setup
        string dot_path20 = "Tests/database/Examen/circuits/full_adder.dot";

        Simulator fa(dot_path20,json_path4);

        //Test

    /*// === Tests visuels ===
    // === Test Parser Dot ===
    cout << "Test Parser Dot" << endl;

    Dot fileTestParserDot("Tests/database/Examen/portes_elementaires/and2.dot");

    map<string, string> addOptionsPE;

    SchematicObject SO_PE1("I1","INPUT",addOptionsPE);
    SchematicObject SO_PE2("I2","INPUT",addOptionsPE);
    SchematicObject SO_PE3("GATE","AND2",addOptionsPE);
    SchematicObject SO_PE4("O","OUTPUT",addOptionsPE);

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

    fileTestParserDot.fillIoList(schematicObjectsListPE,tempLinkToFillPE);

    fileTestParserDot.lexer();
    fileTestParserDot.parse();        

    cout << "Avec notre parser dot on obtient :" << endl;
    for(auto const& x : fileTestParserDot.getSchematicObjectsList()){
        x.second->print();
    }

    cout << "Et on doit obtenir (avec le parser dot) :" << endl << endl;
    for(auto const& x : schematicObjectsListPE){
        x.second->print();
    }
    cout<<endl;

    //=== Test Parser Json ===
    cout << "Test Parser Json" << endl;
    
    Json fileTestParserJson("Tests/database/Examen/stimuli/three_inputs.json");
    RSJresource* array = fileTestParserJson.getJsonDict();
    
    cout << "Avec notre parser json on obtient :" << endl << array->as_str() << endl;

    eraseJsonCleanArray();
    array0 = fileTestParserJson.getJsonDict();

    cout << "Et on avait avant parsing :" << endl << array->as_str() << endl << endl;
    
    //=== Tests Simulateur ===
    //=== AND2 ===
    cout << "Test Simulateur AND2 :"<< endl;

    string dot_path0 = "Tests/database/dot/xtest_and2.dot";
    string json_path0 = "Tests/database/json/xtest_1.json";
    Dot fileDotTestSimulator0(dot_path0);
    Json fileJsonTestSimulator0(json_path0);
    Simulator sim_and2(dot_path0, json_path0);

    fileDotTestSimulator0.lexer();
    fileDotTestSimulator0.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator0.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array0 = fileJsonTestSimulator0.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array0->as_str() << endl;

    sim_and2.saveToJson("xtest_and2_output.json");

    Json fileResult0("./xtest_and2_output.json");
    RSJresource* arrayResult0 = fileResult0.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult0->as_str() << endl << endl;

    //=== OR2 ===
    cout << "Test Simulateur OR2 :"<< endl;

    string dot_path1 = "Tests/database/dot/xtest_or2.dot";
    string json_path1 = "Tests/database/json/xtest_1.json";
    Dot fileDotTestSimulator1(dot_path1);
    Json fileJsonTestSimulator1(json_path1);
    Simulator sim_or2(dot_path1, json_path1);

    fileDotTestSimulator1.lexer();
    fileDotTestSimulator1.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator1.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array1 = fileJsonTestSimulator1.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array1->as_str() << endl;

    sim_or2.saveToJson("xtest_or2_output.json");

    Json fileResult1("./xtest_or2_output.json");
    RSJresource* arrayResult1 = fileResult1.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult1->as_str() << endl << endl;
    
    //Not
    cout << "Test Simulateur NOT :"<< endl;

    string dot_path2 = "Tests/database/dot/xtest_not.dot";
    string json_path2 = "Tests/database/json/xtest_2.json";
    Dot fileDotTestSimulator2(dot_path2);
    Json fileJsonTestSimulator2(json_path2);
    Simulator sim_not(dot_path2, json_path2);

    fileDotTestSimulator2.lexer();
    fileDotTestSimulator2.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator2.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array2 = fileJsonTestSimulator2.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array2->as_str() << endl;

    sim_not.saveToJson("xtest_not_output.json");

    Json fileResult2("./xtest_not_output.json");
    RSJresource* arrayResult2 = fileResult2.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult2->as_str() << endl << endl;

    //NAND2
    cout << "Test Simulateur NAND2 :"<< endl;

    string dot_path3 = "Tests/database/dot/xtest_nand2.dot";
    string json_path3 = "Tests/database/json/xtest_1.json";
    Dot fileDotTestSimulator3(dot_path3);
    Json fileJsonTestSimulator3(json_path3);
    Simulator sim_nand2(dot_path3, json_path3);

    fileDotTestSimulator3.lexer();
    fileDotTestSimulator3.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator3.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array3 = fileJsonTestSimulator3.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array3->as_str() << endl;

    sim_nand2.saveToJson("xtest_nand2_output.json");

    Json fileResult3("./xtest_nand2_output.json");
    RSJresource* arrayResult3 = fileResult3.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult3->as_str() << endl << endl;

    //NOR2
    cout << "Test Simulateur NOR2 :"<< endl;

    string dot_path4 = "Tests/database/dot/xtest_nor2.dot";
    string json_path4 = "Tests/database/json/xtest_1.json";
    Dot fileDotTestSimulator4(dot_path4);
    Json fileJsonTestSimulator4(json_path4);
    Simulator sim_nor2(dot_path4, json_path4);

    fileDotTestSimulator4.lexer();
    fileDotTestSimulator4.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator4.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array4 = fileJsonTestSimulator4.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array4->as_str() << endl;

    sim_nor2.saveToJson("xtest_nor2_output.json");

    Json fileResult4("./xtest_nor2_output.json");
    RSJresource* arrayResult4 = fileResult4.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult4->as_str() << endl << endl;

    //XOR2
    cout << "Test Simulateur XOR2 :"<< endl;

    string dot_path5 = "Tests/database/dot/xtest_xor2.dot";
    string json_path5 = "Tests/database/json/xtest_1.json";
    Dot fileDotTestSimulator5(dot_path5);
    Json fileJsonTestSimulator5(json_path5);
    Simulator sim_xor2(dot_path5, json_path5);

    fileDotTestSimulator5.lexer();
    fileDotTestSimulator5.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator5.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array5 = fileJsonTestSimulator5.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array5->as_str() << endl;

    sim_xor2.saveToJson("xtest_xor2_output.json");

    Json fileResult5("./xtest_xor2_output.json");
    RSJresource* arrayResult5 = fileResult5.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult5->as_str() << endl << endl;

    //MUX2 //MUX explicite, un mux implicite ne fonctionnerait pas avec notre programme
    cout << "Test Simulateur MUX2 :"<< endl;

    string dot_path6 = "Tests/database/dot/xtest_mux2.dot";
    string json_path6 = "Tests/database/json/xtest_3.json";
    Dot fileDotTestSimulator6(dot_path6);
    Json fileJsonTestSimulator6(json_path6);
    Simulator sim_mux2(dot_path6, json_path6);

    fileDotTestSimulator6.lexer();
    fileDotTestSimulator6.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator6.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array6 = fileJsonTestSimulator6.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array6->as_str() << endl;

    sim_mux2.saveToJson("xtest_mux2_output.json");

    Json fileResult6("./xtest_mux2_output.json");
    RSJresource* arrayResult6 = fileResult6.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult6->as_str() << endl << endl;

    //Direct Connection
    cout << "Test Simulateur Direct Connection :"<< endl;

    string dot_path7 = "Tests/database/dot/xtest_direct_connection.dot";
    string json_path7 = "Tests/database/json/xtest_2.json";
    Dot fileDotTestSimulator7(dot_path7);
    Json fileJsonTestSimulator7(json_path7);
    Simulator sim_direct_connection(dot_path7, json_path7);

    fileDotTestSimulator7.lexer();
    fileDotTestSimulator7.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator7.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array7 = fileJsonTestSimulator7.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array7->as_str() << endl;

    sim_direct_connection.saveToJson("xtest_direct_connection_output.json");

    Json fileResult7("./xtest_direct_connection_output.json");
    RSJresource* arrayResult7 = fileResult7.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult7->as_str() << endl << endl;

    //Loop
    cout << "Test Simulateur Loop :"<< endl;

    string dot_path8 = "Tests/database/dot/xtest_loop.dot";
    string json_path8 = "Tests/database/json/xtest_2.json";
    Dot fileDotTestSimulator8(dot_path8);
    Json fileJsonTestSimulator8(json_path8);
    Simulator sim_loop(dot_path8, json_path8);

    fileDotTestSimulator8.lexer();
    fileDotTestSimulator8.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator8.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array8 = fileJsonTestSimulator8.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array8->as_str() << endl;

    sim_loop.saveToJson("xtest_loop_output.json");

    Json fileResult8("./xtest_loop_output.json");
    RSJresource* arrayResult8 = fileResult8.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult8->as_str() << endl << endl;

    //FlipFlop
    cout << "Test Simulateur FlipFlop :"<< endl;

    string dot_path9 = "Tests/database/dot/xtest_ff.dot";
    string json_path9 = "Tests/database/json/xtest_2.json";
    Dot fileDotTestSimulator9(dot_path9);
    Json fileJsonTestSimulator9(json_path9);
    Simulator sim_ff(dot_path9, json_path9);

    fileDotTestSimulator9.lexer();
    fileDotTestSimulator9.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator9.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array9 = fileJsonTestSimulator9.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array9->as_str() << endl;

    sim_ff.saveToJson("xtest_ff_output.json");

    Json fileResult9("./xtest_ff_output.json");
    RSJresource* arrayResult9 = fileResult9.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult9->as_str() << endl << endl;

    //Half Adder
    cout << "Test Simulateur Half Adder :"<< endl;

    string dot_path10 = "Tests/database/dot/xtest_ha.dot";
    string json_path10 = "Tests/database/json/xtest_1.json";
    Dot fileDotTestSimulator10(dot_path10);
    Json fileJsonTestSimulator10(json_path10);
    Simulator sim_ha(dot_path10, json_path10);

    fileDotTestSimulator10.lexer();
    fileDotTestSimulator10.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator10.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array10 = fileJsonTestSimulator10.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array10->as_str() << endl;

    sim_ha.saveToJson("xtest_ha_output.json");

    Json fileResult10("./xtest_ha_output.json");
    RSJresource* arrayResult10 = fileResult10.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult10->as_str() << endl << endl;

    //Full Adder
    cout << "Test Simulateur Full Adder :"<< endl;

    string dot_path11 = "Tests/database/dot/xtest_fa.dot";
    string json_path11 = "Tests/database/json/xtest_3.json";
    Dot fileDotTestSimulator11(dot_path11);
    Json fileJsonTestSimulator11(json_path11);
    Simulator sim_fa(dot_path11, json_path11);

    fileDotTestSimulator11.lexer();
    fileDotTestSimulator11.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator11.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array11 = fileJsonTestSimulator11.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array11->as_str() << endl;

    sim_fa.saveToJson("xtest_fa_output.json");

    Json fileResult11("./xtest_fa_output.json");
    RSJresource* arrayResult11 = fileResult11.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult11->as_str() << endl << endl;

    //Register
    cout << "Test Simulateur Register :"<< endl;

    string dot_path12 = "Tests/database/dot/xtest_reg.dot";
    string json_path12 = "Tests/database/json/xtest_3.json";
    Dot fileDotTestSimulator12(dot_path12);
    Json fileJsonTestSimulator12(json_path12);
    Simulator sim_reg(dot_path12, json_path12);

    fileDotTestSimulator12.lexer();
    fileDotTestSimulator12.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator12.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array12 = fileJsonTestSimulator12.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array12->as_str() << endl;

    sim_reg.saveToJson("xtest_reg_output.json");

    Json fileResult12("./xtest_reg_output.json");
    RSJresource* arrayResult12 = fileResult12.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult12->as_str() << endl << endl;

    //Shift Register
    cout << "Test Simulateur Shift Register :"<< endl;

    string dot_path13 = "Tests/database/dot/xtest_sr.dot";
    string json_path13 = "Tests/database/json/xtest_2.json";
    Dot fileDotTestSimulator13(dot_path13);
    Json fileJsonTestSimulator13(json_path13);
    Simulator sim_sr(dot_path13, json_path13);

    fileDotTestSimulator13.lexer();
    fileDotTestSimulator13.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator13.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array13 = fileJsonTestSimulator13.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array13->as_str() << endl;

    sim_sr.saveToJson("xtest_sr_output.json");

    Json fileResult13("./xtest_sr_output.json");
    RSJresource* arrayResult13 = fileResult13.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult13->as_str() << endl << endl;

    //NXOR2
    cout << "Test Simulateur NXOR2 :"<< endl;

    string dot_path14 = "Tests/database/dot/xtest_nxor2.dot";
    string json_path14 = "Tests/database/json/xtest_1.json";
    Dot fileDotTestSimulator14(dot_path14);
    Json fileJsonTestSimulator14(json_path14);
    Simulator sim_nxor2(dot_path14, json_path14);

    fileDotTestSimulator14.lexer();
    fileDotTestSimulator14.parse();        

    cout << "Avec notre parser dot on obtient le circuit :" << endl;
    for(auto const& x : fileDotTestSimulator14.getSchematicObjectsList()){
        x.second->print();
    }

    RSJresource* array14 = fileJsonTestSimulator14.getJsonDict();

    cout << "Avec notre parser json on obtient les stimulis :" << endl << array14->as_str() << endl;

    sim_nxor2.saveToJson("xtest_nxor2_output.json");

    Json fileResult14("./xtest_nxor2_output.json");
    RSJresource* arrayResult14 = fileResult14.getJsonDict();
    cout << "Le resultat est :" << endl << arrayResult14->as_str() << endl << endl;
*/

    return 0;
}