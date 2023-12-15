#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>

using namespace std;

enum token_type {Assignment, SpecialCharacter, AnyWords, StatementKeyWords, StarterKeyWords};

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
        //~Token();



        // =======  GETTERS / SETTERS =======
        string getValue(void) const;

        token_type getType(void) const;

        unsigned int getLine();

        unsigned int getColumn();

        void setPreviousToken(Token* previous_token);
        Token* getPreviousToken(void) const;
        Token* getPreviousToken(unsigned int n) const;
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