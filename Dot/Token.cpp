#include "Token.hpp"

Token::Token(string value, string type, Token *next_token, Token *previous_token, unsigned int line, unsigned int column):
value(value), type(type), next_token(next_token), previous_token(previous_token), line(line), column(column) {

}

Token::Token(string value, string type, Token *next_token, unsigned int line, unsigned int column):
value(value), type(type), next_token(next_token), previous_token(NULL), line(line), column(column) {

}

Token* Token::getPreviousToken(void) {
    return this->previous_token;
}
