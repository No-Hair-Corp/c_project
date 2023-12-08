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

            if (checkType(c, specialCharacter)){
                currentToken = new Token(to_string(c), "specialCharacter", previousToken, NULL, line_number, column_number);
                column_number++;

            // } else if(checkType(buffer, keyword)){
            //     if (currentToken->isFirst()){
            //         currentToken = new Token(buffer, "anyWord", NULL, NULL, line_number, column_number);
            //     } else {
            //         currentToken = new Token(buffer, "anyWord", previousToken, NULL, line_number, column_number);
            //     }
            } else if (c == '"'){

            }

            if (previousToken==NULL) this->first_token = currentToken; // TODO: use setter
            else previousToken->setNextToken(currentToken); 
            previousToken = currentToken;
        }
        line_number++;
        }
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

int registerString(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString){
    while(line[column_number] != '"' && line[column_number - 1] != '\\' ){

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
}

void Dot::throwParseError(const string &error_message) {
    cout << "Error: " << error_message << endl; 
}
void Dot::throwParseError(const string &error_message, unsigned int line, unsigned int column) {
     cout << "Error at line " << line << ", column " <<  column << ": " << error_message << endl; 
}