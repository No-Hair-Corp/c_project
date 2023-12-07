#include "Token.hpp"


// =======  CONSTRUCTOR / DESTRUCTOR =======
Token::Token(string value, string type, Token *previous_token, Token *next_token, unsigned int line, unsigned int column):
value(value), type(type), previous_token(previous_token), next_token(next_token), line(line), column(column) {

}

Token::Token(string value, string type, Token *next_token, unsigned int line, unsigned int column):
value(value), type(type), next_token(next_token), previous_token(NULL), line(line), column(column) {

}



// =======  GETTERS / SETTERS =======
void Token::setPreviousToken(Token* previous_token) {
    this->previous_token = previous_token;
}

Token* Token::getPreviousToken(void) const {
    return this->previous_token;
}

void Token::setNextToken(Token* next_token) {
    this->next_token = next_token;
}



// =======  OTHER FUNCTIONS =======
bool Token::isFirst(void) {
    return(this->previous_token == NULL);
}

