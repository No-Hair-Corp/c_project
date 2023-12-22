#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>

using namespace std;

enum token_type {Assignment, SpecialCharacter, AnyWords, StatementKeyWords, StarterKeyWords, stringType};

class Token {
    private:
        string value;
        token_type type;
        Token *previous_token, *next_token;
        unsigned int line;
        unsigned int column;

    public:

        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Token(string value, token_type type, Token *previous_token, Token *next_token,
            unsigned int line, unsigned int column);

        Token(string value, token_type, Token *next_token, unsigned int line,
            unsigned int column);


        // =======  GETTERS / SETTERS =======
        /** @brief get the token value
         * @return string: token value **/
        string getValue(void) const;


        /** @brief get the token type
         * @return token_type: token type **/
        token_type getType(void) const;

        /** @brief get the token line
         * @return unsigned int: token line **/
        unsigned int getLine();

        /** @brief get the token column
         * @return unsigned int: token column **/
        unsigned int getColumn();

        /** @brief set the previous token
         * @param Token*: previous token **/
        void setPreviousToken(Token* previous_token);

        /** @brief get the token previous token
         * @return Token*: previous token **/
        Token* getPreviousToken(void) const;

        /** @brief get the n previous token
         * @return Token*: n previous token **/
        Token* getPreviousToken(unsigned int n) const;

        /** @brief get the next token
         * @return Token*: next token **/
        Token* getNextToken(void) const;


        /** @brief Modifie le token qui suit
         * @param Token* next_token: pointeur vers le token suivant **/
        void setNextToken(Token* next_token);



        // =======  OTHER FUNCTIONS =======

        /** @brief Indique si le token est le premier
         * @param Token* token: token a vérifier
         * @return: true si c'est le premier, false sinon **/
        bool isFirst(void);



};

#endif