#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>

using namespace std;

class Token {
    private:
        string value;
        string type;
        Token *previous_token, *next_token;
        unsigned int line;
        unsigned int column;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Token(string value, string type, Token *previous_token, Token *next_token,
            unsigned int line, unsigned int column);
        Token(string value, string type, Token *next_token, unsigned int line,
            unsigned int column);
        //~Token();



        // =======  GETTERS / SETTERS =======

        /** @brief Modifie le token qui précède
         * @param Token* next_token: pointeur vers le token précédent **/
        void setPreviousToken(Token* previous_token);

        /** @brief Renvoie le token qui précède le token occurant
         * @return Token*: pointeur vers le token **/
        Token* getPreviousToken(void) const;

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