#include "Dot.hpp"

int main() {

    Dot file1("testDot1.dot");
    char c1 = '[';
    char c2 = '\"';
    char c3 = '`';
    string keyword1 = "label";
    string keyword2 = "bonjour";

    // cout << file1.checkType(c1, Dot::specialCharacter) << endl;
    // cout << file1.checkType(c2, Dot::stringStarter) << endl;
    // cout << file1.checkType(c3, Dot::forbiddenCharacter) << endl;
    // cout << file1.checkType(keyword1) << endl;
    // cout << file1.checkType(keyword2) << endl;

    file1.lexer();
    Token* current = file1.getFirstToken();
    while (current->Token::getNextToken() != NULL) {
        cout << "Token :"<< current->Token::getType() << ", Value: "<< current->Token::getValue() <<endl;
        current = current->getNextToken();
    }
    cout << "Token :"<< current->Token::getType() << ", Value: "<< current->Token::getValue() <<endl;

    // string one = "A->B";
    // string two = "A-";
    // string three = "A-B";
    // cout << file1.CheckArrow(one,1) << endl;
    // cout << file1.CheckArrow(two,1) << endl;
    // cout << file1.CheckArrow(three,1) << endl;
    
}
