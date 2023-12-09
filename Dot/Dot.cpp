#include "Dot.hpp"

// ======= TOKEN CONTAINER ========
string Dot::specialCharacter = "->/\\[]=;{}";
 string Dot::stringStarter = "\"";
 string Dot::keywords[3] = {"label", "sel", "digraph"};
 string Dot::forbiddenCharacter = "\'`";



// =======  CONSTRUCTOR / DESTRUCTOR =======
Dot::Dot(string file_path):
file_path(file_path), first_token(NULL) {
    
}



// =======  GETTERS / SETTERS =======
string Dot::getFilePath() {
    return this->file_path;
}

Token* Dot::getFirstToken() {
    return this->first_token;
}

void Dot::setFirstToken(Token* currentToken){
    this->first_token = currentToken;
}



// =======  OTHER FUNCTIONS =======
int Dot::lexer() {
    ifstream input_file(this->getFilePath());
    string line;
    string buffer = "";
    unsigned int line_number = 0;
    unsigned int column_number = 0;
    Token *previousToken = NULL;
    Token * currentToken;

    if (!input_file){
        return 1;
    }

    while(getline(input_file, line)){
        // cout << line << endl;
        column_number = 0;
        while(line[column_number] != '\0'){
            // cout << "break1" << endl;
            if (checkType(line[column_number], Dot::forbiddenCharacter )){
                return 2;

            } else if (checkType(line[column_number], Dot::specialCharacter)){
                // cout << line[column_number] << endl;
                if (CheckArrow(line, column_number)){
                    column_number+=2;
                    currentToken = new Token("->", "SpecialCharacter", previousToken, NULL, line_number, column_number);

                } else {
                    // cout << line[column_number] << endl;
                    buffer = line[column_number];
                    currentToken = new Token(buffer, "SpecialCharacter", previousToken, NULL, line_number, column_number);
                    // cout << currentToken->getValue();
                    column_number++;
                }

            } else if (checkType(line[column_number], Dot::stringStarter)){
                column_number++;
                buffer = "";
                Dot::registerString(input_file, line, column_number,line_number, buffer);
                currentToken = new Token(buffer, "AnyWords", previousToken, NULL, line_number, column_number);
                column_number++;


            } else {
                // cout << "break2" << endl;
                buffer = "";
                // cout << line[column_number] << endl;
                // cout << column_number << endl;
                Dot::registerKeywords(input_file, line, column_number, line_number, buffer);
                // cout << line[column_number] << endl;
                if (checkType(buffer)){
                    currentToken = new Token(buffer, "KeyWords", previousToken, NULL, line_number, column_number);
                } else {
                    currentToken = new Token(buffer, "UnknownKeyWords", previousToken, NULL, line_number, column_number);
                }
            }

            if (previousToken==NULL){
                // cout << line[column_number] << endl;
                this->setFirstToken(currentToken);
            } else {
                // cout << line[column_number] << endl;
                // cout << currentToken->getPreviousToken()->getType() << endl; //TODO: COMPRENDRE PK LE DERNIER CARACTERE N'APPARAIT PAS AU FINAL
                previousToken->setNextToken(currentToken);
            }
            previousToken = currentToken;
        }
        line_number++;
    }
    input_file.close();
    return 0;
} 


bool Dot::checkType(char c, const string specialCharacter) {
    return (specialCharacter.find(c) != string::npos);
}

bool Dot::checkType(string& word) {
    for(int i=0; i<3; i++){
        if (word == keywords[i]){
            return true;
        }
    }
    return false;
}


int Dot::registerString(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString) {
    while (line[column_number] != '"' && (column_number == 0 || line[column_number - 1] != '\\')) {
        while (line[column_number] != '\0') {
            if (line[column_number] == '"' && (column_number == 0 || line[column_number - 1] != '\\')) {
                return 0;  // End of the string is found
            } else {
                innerString.push_back(line[column_number]);  // Use push_back for efficient string concatenation
                column_number++;
            }
        }

        if (!getline(input_file, line)) {
            return 1;  // End of file is reached
        }

        line_number++;
        column_number = 0;  // Reset column_number for the new line
    }

    return 0;  // Successful completion
}


int Dot::parse() {
    Token* current_token = this->first_token;

    if(current_token->getType() == "keyword") {

    }
    return 0;
}

void Dot::throwParseError(const string &error_message) {
    cout << "Error: " << error_message << endl; 
}
void Dot::throwParseError(const string &error_message, unsigned int line, unsigned int column) {
     cout << "Error at line " << line << ", column " <<  column << ": " << error_message << endl; 
}


int Dot::registerKeywords(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString) {
    // cout << line << endl;
    // cout << column_number << endl;
    while (specialCharacter.find(line[column_number]) == string::npos && (column_number == 0 || line[column_number - 1] != '\\')) {
        // cout << "break3" << endl;
        while (line[column_number] != '\0') {
            // cout << "break4" << endl;
            if (specialCharacter.find(line[column_number]) != string::npos && (column_number == 0 || line[column_number - 1] != '\\')) {
                // cout << line[column_number] << endl;
                return 0;  // End of the keyword is found
            } else {
                innerString.push_back(line[column_number]);  // Use push_back for efficient string concatenation
                column_number++;
                // cout << line[column_number] << endl;
            }
            
        }

        if (!getline(input_file, line)) {
            return 1;  // End of file is reached
        }

        line_number++;
        column_number = 0;  // Reset column_number for the new line
    }

    return 0;  // Successful completion
}

bool Dot::CheckArrow(string& line, int column_number){
    // cout << line << endl;
    // cout << line[column_number] << endl;
    // cout << column_number << endl;
    return (line[column_number] == '>' && column_number != 0  && line[column_number - 1] == '-'); //&& line[column_number + 1] != 0
}

