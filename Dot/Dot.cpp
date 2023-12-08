#include "Dot.hpp"

// ======= TOKEN CONTAINER ========
 string Dot::specialCharacter = ">/\\[]=";
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
    char c;
    string buffer = "";
    unsigned int line_number = 0;
    unsigned int column_number = 0;
    
    Token *previousToken = NULL;
    Token * currentToken;

    if (!input_file)
        return 1;


    while(getline(input_file, line)){
        column_number = 0;
        while(line[column_number] != 0){

            if (checkType(line[column_number], Dot::forbiddenCharacter )){
                return 2;

            } else if (checkType(line[column_number], Dot::specialCharacter)){
                currentToken = new Token(to_string(line[column_number]), "SpecialCharacter", previousToken, NULL, line_number, column_number);


            } else if (checkType(line[column_number], Dot::stringStarter)){
                column_number++;
                buffer = "";
                Dot::registerString(input_file, line, column_number,line_number, buffer);
                currentToken = new Token(buffer, "AnyWords", previousToken, NULL, line_number, column_number);


            } else {
                buffer = "";
                Dot::registerKeywords(input_file, line, column_number, line_number, buffer);
                if (checkType(buffer)){
                    currentToken = new Token(buffer, "KeyWords", previousToken, NULL, line_number, column_number);
                } else {
                    currentToken = new Token(buffer, "AnyWords", previousToken, NULL, line_number, column_number);
                }
            }

            if (previousToken==NULL){
                this->setFirstToken(currentToken);
            } else {
                previousToken->setNextToken(currentToken);
                previousToken = currentToken;
            }
            column_number++;
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
        if (word == Dot::keywords[i]){
            return true;
        }
    }
    return false;
}

int Dot::registerString(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString){
    while(line[column_number] && line[column_number - 1] != '\\' ){
        while(line[column_number] != 0){
            if (line[column_number] != '"' && line[column_number - 1] != '\\' ){
                return 0;
            } else {
                innerString = innerString + line[column_number];
            }
            column_number++;
        }
        getline(input_file, line);
        line_number++;
        column_number = 0;
        if (!getline(input_file, line)){ //if we don't find any '"' before the end of the file we return 2
            return 1; 
        }
    }
    return 0;
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

int Dot::registerKeywords(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString){
    while(specialCharacter.find(line[column_number]) != string::npos && line[column_number - 1] != '\\'){
        while(line[column_number] != 0){
            if (specialCharacter.find(line[column_number]) != string::npos && line[column_number - 1] != '\\'){
                return 0;
            } else {
                innerString = innerString + line[column_number];
            }
            column_number++;
        }
        getline(input_file, line);
        line_number++;
        column_number = 0;
        if (!getline(input_file, line)){ //if we don't find any '"' before the end of the file we return 2
            return 1; 
        }
    }
    return 0;
}