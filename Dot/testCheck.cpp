#include "Dot.hpp"

int main() {

    Dot file1("INPUTS_FILE/testDot1.dot");
    // char c1 = '[';
    // char c2 = '\"';
    // char c3 = '`';
    string keyword1 = "label";
    string keyword2 = "bonjour";

    // cout << file1.checkType(c1, Dot::specialCharacter) << endl;
    // cout << file1.checkType(c2, Dot::stringStarter) << endl;
    // cout << file1.checkType(c3, Dot::forbiddenCharacter) << endl;
    // cout << file1.checkType(keyword1) << endl;
    // cout << file1.checkType(keyword2) << endl;
    // cout << "lexer" << endl;
    file1.lexer();
    cout << "lexer done" << endl;
    Token* current = file1.getFirstToken();
    while (current->getNextToken() != NULL) {
        cout << "Token: "<< current->getType() << ", Value: "<< current->getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;
        current = current->getNextToken();
    }
    cout << "Token: "<< current->getType() << ", Value: "<< current->getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;
    
    // cout << "parser" << endl;
    file1.parse();
    // cout << "parser done" << endl;


    cout << file1.getSchematicObjectsList().size() << endl;
    for(auto const& x : file1.getSchematicObjectsList()){
        x.second->print();
    }
    // string one = "A->B";
    // string two = "A-";
    // string three = "A-B";
    // cout << file1.CheckArrow(one,1) << endl;
    // cout << file1.CheckArrow(two,1) << endl;
    // cout << file1.CheckArrow(three,1) << endl;
    
}
