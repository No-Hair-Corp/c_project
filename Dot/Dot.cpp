#include "Dot.hpp"

#define KEYWORDSIZE 5


// Special characters that are recognized in the Dot language
string Dot::specialCharacter = "->/\\[]=;{}#";
string Dot::stringStarter = "\"";
string Dot::keywords[KEYWORDSIZE] = {"label", "sel", "digraph", "strict", "graph"};
string Dot::forbiddenCharacter = "\'`";
string Dot::lineCharacter = "\t\n\r "; 

// ======= CONSTRUCTOR / DESTRUCTOR =======

// Constructor: initializes file_path and first_token
Dot::Dot(string file_path) : file_path(file_path), first_token(NULL) {
}

// ======= GETTERS / SETTERS =======

// Getter for file_path
string Dot::getFilePath() {
    return this->file_path;
}

// Getter for first_token
Token* Dot::getFirstToken() {
    return this->first_token;
}

// Setter for first_token
void Dot::setFirstToken(Token* currentToken) {
    this->first_token = currentToken;
}

// ======= OTHER FUNCTIONS =======

// Lexer function to tokenize the input file
int Dot::lexer() { //TODO: understand ghost UnknownCharacter ???
    ifstream input_file(this->getFilePath());
    string line;
    string buffer = "";
    unsigned int line_number = 0;
    unsigned int column_number = 0;
    Token* previousToken = NULL;
    Token* currentToken;

    if (!input_file) {
        return 1; // Error: Unable to open input file
    }

    // Iterate through each line in the input file
    while (getline(input_file, line)) {
        column_number = 0;
        //TODO: HANDLE COMMENTS 
        // Iterate through each character in the line
        while (line[column_number] != '\0') {
            if (checkType(line[column_number], Dot::forbiddenCharacter)) {
                return 2; // Error: Forbidden character found
            } else if (checkType(line[column_number], Dot::specialCharacter)) {
                // Check if the current character is part of the "->" or "--" arrow
                if (CheckArrow(line, column_number)) {
                    buffer = {line[column_number], line[column_number+1]};
                    column_number += 2;
                    currentToken = new Token(buffer, "SpecialCharacter", previousToken, NULL, line_number + 1, column_number + 1);
                } else if (line[column_number] == '/' || line[column_number] == '#' ){
                    jumpComments(input_file, line, column_number, line_number);
                } else {
                    buffer = line[column_number];
                    currentToken = new Token(buffer, "SpecialCharacter", previousToken, NULL, line_number + 1, column_number + 1);
                    column_number++;
                }
            } else if (checkType(line[column_number], Dot::stringStarter)) {
                column_number++;
                buffer = "";
                // Register the string and create a token
                Dot::registerString(input_file, line, column_number, line_number, buffer);
                currentToken = new Token(buffer, "AnyWords", previousToken, NULL, line_number + 1, column_number);
                column_number++;
            } else if (checkType(line[column_number], Dot::lineCharacter)) {
                column_number++;
                continue;
            
            } else {
                buffer = "";
                // Register keywords and create tokens
                Dot::registerKeywords(input_file, line, column_number, line_number, buffer);
                if (checkKeywords(buffer, KEYWORDSIZE)) {
                    currentToken = new Token(buffer, "KeyWords", previousToken, NULL, line_number + 1, column_number);
                } else {
                    currentToken = new Token(buffer, "AnyWords", previousToken, NULL, line_number + 1, column_number);
                }
            }

            // Set the first token or link the current token to the previous token
            if (previousToken == NULL) {
                this->setFirstToken(currentToken);
            } else {
                previousToken->setNextToken(currentToken);
            }
            previousToken = currentToken;
        }
        line_number++;
    }

    input_file.close();
    return 0; // Successful completion
}

// Function to check if a character is in the set of special characters
bool Dot::checkType(char c, const string specialCharacter) {
    return (specialCharacter.find(c) != string::npos);
}

// Function to check if a word is one of the predefined keywords
bool Dot::checkKeywords(string& word, int n) {
    string copy = word;
    transform(copy.begin(), copy.end(), copy.begin(), ::tolower);

    for (int i = 0; i < n; i++) {
        if (copy == keywords[i]) {
            return true;
        }
    }
    return false;
}


// Function to register a string enclosed in double quotes
int Dot::registerString(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString) {
    while (line[column_number] != '"' && (column_number == 0 || line[column_number - 1] != '\\')) {
        while (line[column_number] != '\0') {
            if (line[column_number] == '"' && (column_number == 0 || line[column_number - 1] != '\\')) {
                return 0; // End of the string is found
            } else {
                if (line[column_number] != '\n' && line[column_number] != '\r' ){
                    innerString.push_back(line[column_number]); // Use push_back for efficient string concatenation
                    column_number++;
                } else {
                    column_number++;
                }
            }
        }

        if (!getline(input_file, line)) {
            return 1; // End of file is reached
        }

        line_number++;
        column_number = 0; // Reset column_number for the new line
    }

    return 0; // Successful completion
}

// Function to throw a parse error without position information
void Dot::throwParseError(const string& error_message) {
    cout << "Error: " << error_message << endl;
}

// Function to throw a parse error with position information
void Dot::throwParseError(const string& error_message, unsigned int line, unsigned int column) {
    cout << "Error at line " << line << ", column " << column << ": " << error_message << endl;
}

// Function to register keywords in the input file
int Dot::registerKeywords(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString) {
    while (specialCharacter.find(line[column_number]) == string::npos && (column_number == 0 || line[column_number - 1] != '\\')) {
        while (line[column_number] != '\0') {
            if (specialCharacter.find(line[column_number]) != string::npos && (column_number == 0 || line[column_number - 1] != '\\')) {
                return 0; // End of the keyword is found
            } else {
                if (line[column_number] != ' ' && line[column_number] != '\n' && line[column_number] != '\r' ) {
                    innerString.push_back(line[column_number]); // Use push_back for efficient string concatenation
                    column_number++;
                } else {
                    column_number++;
                    return 0;
                }
            }
        }

        if (!getline(input_file, line)) {
            return 1; // End of file is reached
        }

        line_number++;
        column_number = 0; // Reset column_number for the new line
    }

    return 0; // Successful completion
}

// Function to check if the characters form an arrow (->)
bool Dot::CheckArrow(string& line, int column_number) {
    if (line[column_number] == '-' && line[column_number + 1] != '\0' && line[column_number + 1] == '>') {
        return 1;
    } else if (line[column_number] == '-' && line[column_number + 1] != '\0' && line[column_number + 1] == '-') {
        return 1;
    } else return 0;
}


int Dot::jumpComments(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number){
    if ((line[column_number] == '/' && line[column_number + 1] == '/') || line[column_number] == '#'){
        while (line[column_number] != '\0'){
            column_number++;
        }
    } else if (line[column_number] == '/' && line[column_number + 1] == '*'){

        while(line[column_number] != '*' && line[column_number + 1] != '/'){

            while(line[column_number] != '\0'){

                if (line[column_number] == '*' && line[column_number + 1] == '/'){

                    column_number++;
                    return 0;
                } else {
                    column_number++;
                }
            } 
            
            if (!getline(input_file, line)) {
                return 1; // End of file is reached
            }
            line_number++;
            column_number = 0;
        }
            
    } else {
        column_number++;
        return 0;
    }
    return 0;
}

// Function to parse the tokens generated by the lexer
int Dot::parse() {
    Token* current_token = this->first_token;
    
    //if (current_token->getValue() == )

    // TODO: Implement parsing logic based on token types

    return 0;
}