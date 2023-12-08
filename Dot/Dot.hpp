#ifndef _DOT_H_
#define _DOT_H_

#include "Token.hpp"
#include <fstream>
#include <string>

using namespace std;

class Dot {
    private:
        string file_path;
        Token* first_token;

    public:
        // ======= TOKEN CONTAINER ========
        //string anyWordLetter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_";
        static string specialCharacter;
        static string anyWordStarter;
        static string keyword[];
        static string forbiddenCharacter;


        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Dot(string file_path);
        //~Dot();



        // =======  GETTERS / SETTERS =======
        string get_filePath();
        Token* get_firstToken();



        // =======  OTHER FUNCTIONS =======
        int lexer(void);
        bool checkType(char c, const string container);
        bool checkType(string& word, const string keyword[]);
        // bool checkFirstToken(Token* token);


        /** @brief Run the lexer, and initiate first_token
         * @return unsigned int: status code **/
        int launchLexer(void);

        /** @brief Run the parser
         * @return int: status code **/
        int Dot::parse(void);


};

#endif