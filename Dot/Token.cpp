#include "Token.hpp"


// =======  CONSTRUCTOR / DESTRUCTOR =======
Token::Token(string value,  token_type type, Token *previous_token, Token *next_token, unsigned int line, unsigned int column):
value(value), type(type), previous_token(previous_token), next_token(next_token), line(line), column(column) {

}

Token::Token(string value, token_type type, Token *next_token, unsigned int line, unsigned int column):
value(value), type(type), next_token(next_token), previous_token(NULL), line(line), column(column) {

}



// =======  GETTERS / SETTERS =======
string Token::getValue(void) const {
    return this->value;
}

token_type Token::getType(void) const {
    return this->type;
}

void Token::setPreviousToken(Token* previous_token) {
    this->previous_token = previous_token;
}

Token* Token::getPreviousToken(void) const {
    return this->previous_token;
}
Token* Token::getPreviousToken(unsigned int n) const {
    Token* token = this->previous_token;
    for(unsigned int i=1; i<n; i++){
        token = token->previous_token;
    }
    return token;
}

Token* Token::getNextToken(void) const {
    return this->next_token;
}

void Token::setNextToken(Token* next_token) {
    this->next_token = next_token;
}

unsigned int Token::getLine(){
    return this->line;
}

unsigned int Token::getColumn(){
    return this->column;
}



// =======  OTHER FUNCTIONS =======
bool Token::isFirst(void) {
    return(this->previous_token == NULL);
}

