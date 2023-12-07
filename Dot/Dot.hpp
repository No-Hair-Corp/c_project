#ifndef _DOT_H_
#define _DOT_H_

#include "Token.hpp"
#include <string>

using namespace std;

class Dot {
    private:
        string file_path;
        Token* first_token;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Dot(string file_path);
        ~Dot();



        // =======  GETTERS / SETTERS =======

        /** @brief Run the lexer, and initiate first_token
         * @return unsigned int: status code **/
        int launchLexer(void);

};

#endif