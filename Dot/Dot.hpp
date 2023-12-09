#ifndef _DOT_H_
#define _DOT_H_

#include "Token.hpp"
#include <iostream>
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
        static string stringStarter;
        static string keywords[];
        static string forbiddenCharacter;


        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Dot(string file_path);
        //~Dot();



        // =======  GETTERS / SETTERS =======
        string getFilePath();
        Token* getFirstToken();
        void setFirstToken(Token* currentToken);



        // =======  OTHER FUNCTIONS =======

        /** @brief Run the lexer, and initiate first_token
         * @return unsigned int: status code **/
        int lexer(void);
        bool checkType(char c, const string container);
        bool checkType(string& word);
        bool CheckArrow(string& line, int column_number);

        int registerString(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString);
        int registerKeywords(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString);
        

        /** @brief Run the parser
         * @return int: status code **/
        int parse(void);

        /** @brief Print error message and sotp the program
         * @param string error_message: error message to be printed **/
        void throwParseError(const string &error_message);
        /** @brief Print error message and sotp the program
         * @param string error_message: error message to be printed
         * @param int line: line of error
         * @param int column: column of error **/
        void throwParseError(const string &error_message, unsigned int line, unsigned int column);


};

#endif