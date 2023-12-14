#ifndef _DOT_H_
#define _DOT_H_

#include "Token.hpp"
#include "SchematicObject.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class Dot {
    private:
        string file_path;
        Token* first_token;
        map<string, SchematicObject*> schematicObjects;

    public:
        // ======= TOKEN CONTAINER ========
        //TODO: make 
        static string specialCharacter;
        static string stringStarter;
        static string statementKeywords[];
        static string starterKeywords[];
        static string forbiddenCharacter;
        static string lineCharacter;


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
        bool checkKeywords(string& word, int n, string Keywords[]);
        bool CheckArrow(string& line, int column_number);
        int jumpComments(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number);

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