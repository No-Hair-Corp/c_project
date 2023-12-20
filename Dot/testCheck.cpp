#include "Dot.hpp"

int main() {

    Dot file1("INPUTS_FILE/testDot1.dot");

    if (file1.lexer()){
        return 1;
    } else {
        // Token* current = file1.getFirstToken();
        // while (current->getNextToken() != NULL) {
        //     cout << "Token: "<< current->getType() << ", Value: "<< current->getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;
        //     current = current->getNextToken();
        // }
        // cout << "Token: "<< current->getType() << ", Value: "<< current->getValue() << ", Line Number: " << current->getLine() << ", Column number: " << current->getColumn() <<endl;
    }


    if (file1.parse()){
        return 2;
    } else {
        // cout << "Taille de la liste de SO: " << file1.getSchematicObjectsList().size() << endl;
        // for(auto const& x : file1.getSchematicObjectsList()){
        //     x.second->print();
        // }
    }

    return 0;
   
}
