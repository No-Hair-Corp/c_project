#include "Dot.hpp"

 string Dot::specialCharacter = ">/\\[]=";
 string Dot::anyWordStarter = "\"";
 string Dot::keyword[3] = ["label", "sel", "digraph"];
 string Dot::forbidennCharacter; = "\'`";

Dot::Dot(string file_path):
file_path(file_path), first_token(*NULL) {
    
}

Dot::get_filePath(){
    return this->file_path;
}

Dot::get_firstToken(){
    return this->first_token;
}

Dot::lexer(){
    ifstream input_file(this->get_filePath());
    char c;
    string buffer;
    unsigned int line_number = 0;
    unsigned int column_number = 0;
    Token *previousToken;
    Token * currentToken;

    if (!input_file){
        return 1;

    } else {

        while(getline(input_file, line)){
            column_number = 0;
            while(line[column_number] != 0){

                if (checkType(c, specialCharacter)){

                    if (checkFirstToken()){
                        currentToken = new Token firstToken(str(c), "specialCharacter", *NULL, *NULL, line_number, column_number);
                    } else {
                        currentToken = new Token (str(c), "specialCharacter", &previousToken, *NULL, line_number, column_number);
                    }
                    i++;
                } else if(checkType(buffer, keyword[])){
                    if (checkFirstToken()){
                        currentToken = new Token firstToken(buffer, "anyWord", *NULL, *NULL, line_number, column_number);
                    } else {
                        currentToken = new Token (buffer, "anyWord", &previousToken, *NULL, line_number, column_number);
                    }
                    i++;
                } else {
                    if (c == '"'){
                        
                    }
                }
                *previousToken = &currentToken;
                }
            }
            column_number++;
        }
        line_number++;
    }

}

Dot::checkType(char c, string specialCharacter){
    if specialCharacer.find(c) != npos {
        return true;
    } else {
        return false;
    }
}

Dot::checkType(string keyword, string keyword[]){ /// vérifier pour la tailledu tableau 
    for(int i=0; i<=3; i++){
        if (!(strcmp(keyword, keyword[i]))){
            return true;
        }
    }
    return false;
}


bool checkFirstToken(Token *token){
    if (*token->getPreviousToken() == *NULL){
        return true;
    } else {
        return false;
    }
}


