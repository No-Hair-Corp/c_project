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
        Token(string value, string type, Token *next_token, Token *previous_token,
            unsigned int line, unsigned int column);
        Token(string value, string type, Token *next_token, unsigned int line,
            unsigned int column);
        ~Token();



        // =======  GETTERS / SETTERS =======

        /** @brief Renvoie le token qui précède le token occurant
         * @return Token*: pointeur vers le token **/
        Token* getPreviousToken(void);

};

#endif