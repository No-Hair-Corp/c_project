#ifndef _DOT_H_
#define _DOT_H_

#include "Token.hpp"
#include "SchematicObject.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;

class Dot {
    private:
        string file_path;
        Token* first_token;
        map<string, SchematicObject*> schematicObjectsList;

    public:
        // ======= TOKEN CONTAINER ========
        static string specialCharacter;  
        static string stringStarter;
        static string statementKeywords[];
        static string starterKeywords[];
        static string forbiddenCharacter;
        static string lineCharacter;


        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Dot(string file_path);
        ~Dot();



        // =======  GETTERS / SETTERS =======
        string getFilePath();
        Token* getFirstToken();
        void setFirstToken(Token* currentToken);
        map<string, SchematicObject*>& getSchematicObjectsList();



        // =======  OTHER FUNCTIONS =======

        /** @brief Run the lexer, and initiate first_token
         * @return unsigned int: status code **/
        int lexer(void);

        /** @brief check if the character is in the container
         * @return bool: yes or no corresponding to the character type **/
        bool checkType(char c, const string container);

        /** @brief check if the keyword is in the container
         * @return bool: yes or no corresponding to the keyword type **/
        bool checkKeywords(string& word, int n, string Keywords[]);

        /** @brief check if the  is the character is '->' or '--'
         * @return bool: yes or no corresponding to the character value **/
        bool CheckArrow(string& line, int column_number);

        /** @brief jump comments 
         * @return unsigned int: status code **/
        int jumpComments(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number);

        /** @brief concatenates characters to make string word
         * @return unsigned int: status code **/
        int registerString(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString);

        /** @brief concatenates characters to make keyword
         * @return unsigned int: status code **/
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
        
        /** @brief check if connected instance exist in the instance map
         * @return unsigned int: status code **/
        int checkExistence(map<string, SchematicObject*>& schematicObjectsList, map<string, vector<string>>& tempLink);

        /** @brief check if additionnal options instances exist in the instance map
         * @return unsigned int: status code **/
        int checkExistence(map<string, SchematicObject*>& schematicObjectsList);

        /** @brief fill InputList and outputList after checking existence
         * @return unsigned int: status code **/
        int fillIoList(map<string, SchematicObject*>& schematicObjectsList, map<string, vector<string>>& tempLink);

        /** @brief check if each instance has a type (corresponding to label)
         * @return unsigned int: status code **/
        int checkLabel(map<string, SchematicObject*>& schematicObjectsList);
};

#endif