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
        ~Token();



        // =======  GETTERS / SETTERS =======

        /** @brief Renvoie le nombre de testcases créés
         * @return unsigned int: nombre de testcases créés **/
        static Token* getPreviousToken(void);

};

#endif