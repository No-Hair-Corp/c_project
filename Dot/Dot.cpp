#include "Dot.hpp"

#define STATEMENTKEYWORDSIZE 67
#define STARTERKEYWORDSIZE 3

// Special characters that are recognized in the Dot language
string Dot::specialCharacter = "->/\\[]=;{}#";
string Dot::stringStarter = "\"";
string Dot::statementKeywords[STATEMENTKEYWORDSIZE] = {"_background","area","arrowhead","arrowsize","arrowtail","bb","beautify","bgcolor","center","charset","class","cluster","clusterrank","color","colorscheme","comment","compound","concentrate","constraint","Damping","decorate","defaultdist","dim","dimen","dir","diredgeconstraints","distortion","dpi","edgehref","edgetarget","edgetooltip","edgeURL","epsilon","esep","fillcolor","fixedsize","fontcolor","fontname","fontnames","fontpath","fontsize","forcelabels","gradientangle","group","head_lp","headclip","headhref","headlabel","headport","headtarget","headtooltip","headURL","height","href","id","image","imagepath","imagepos","imagescale","inputscale","K","label","label_scheme","labelangle","labeldistance","labelfloat","labelfontcolor"}; //,"labelfontname","labelfontsize","labelhref","labeljust","labelloc","labeltarget","labeltooltip","labelURL","landscape","layer","layerlistsep","layers","layerselect","layersep","layout","len","levels","levelsgap","lhead","lheight","linelength","lp","ltail","lwidth","margin","maxiter","mclimit","mindist","minlen","mode","model","newrank","nodesep","nojustify","normalize","notranslate","nslimit","nslimit1","oneblock","ordering","orientation","outputorder","overlap","overlap_scaling","overlap_shrink","pack","packmode","pad","page","pagedir","pencolor","penwidth","peripheries","pin","pos","quadtree","quantum","rank","rankdir","ranksep","ratio","rects","regular","remincross","repulsiveforce","resolution","root","rotate","rotation","samehead","sametail","samplepoints","scale","searchsize","sep","shape","shapefile","showboxes","sides","size","skew","smoothing","sortv","splines","start","style","stylesheet","tail_lp","tailclip","tailhref","taillabel","tailport","tailtarget","tailtooltip","tailURL","target","TBbalance","tooltip","truecolor","URL","vertices","viewport","voro_margin","weight","width","xdotversion","xlabel","xlp","z"};
string Dot::starterKeywords[STARTERKEYWORDSIZE] = {"digraph", "strict", "graph"};
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
int Dot::lexer() { 
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
                    currentToken = new Token(buffer, Assignment, previousToken, NULL, line_number + 1, column_number + 1);
                } else if (line[column_number] == '/' || line[column_number] == '#' ){
                    jumpComments(input_file, line, column_number, line_number);
                } else {
                    buffer = line[column_number];
                    currentToken = new Token(buffer, SpecialCharacter, previousToken, NULL, line_number + 1, column_number + 1);
                    column_number++;
                }
            } else if (checkType(line[column_number], Dot::stringStarter)) {
                column_number++;
                buffer = "";
                // Register the string and create a token
                Dot::registerString(input_file, line, column_number, line_number, buffer);
                currentToken = new Token(buffer, stringType, previousToken, NULL, line_number + 1, column_number);
                column_number++;
            } else if (checkType(line[column_number], Dot::lineCharacter)) {
                column_number++;
                continue;
            
            } else {
                buffer = "";
                // Register keywords and create tokens
                unsigned int temp_col = column_number;
                Dot::registerKeywords(input_file, line, column_number, line_number, buffer);
                cout << "1" << endl;
                if (checkKeywords(buffer, STATEMENTKEYWORDSIZE, statementKeywords)) {
                    currentToken = new Token(buffer, StatementKeyWords, previousToken, NULL, line_number + 1, temp_col);
                } else if (checkKeywords(buffer, STARTERKEYWORDSIZE, starterKeywords)){
                    currentToken = new Token(buffer, StarterKeyWords, previousToken, NULL, line_number + 1, temp_col);
                } else {
                    currentToken = new Token(buffer, AnyWords, previousToken, NULL, line_number + 1, temp_col);
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
bool Dot::checkKeywords(string& word, int n, string Keywords[]) {
    string copy = word;
    transform(copy.begin(), copy.end(), copy.begin(), ::tolower);   
    for (int i = 0; i < n; i++) {
        if (copy == Keywords[i]) {
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
    exit(1);
}

// Function to throw a parse error with position information
void Dot::throwParseError(const string& error_message, unsigned int line, unsigned int column) {
    cout << "Error at line " << line << ", column " << column << ": " << error_message << endl;
    exit(1);
}

// Function to register keywords in the input file
int Dot::registerKeywords(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString) {
    while (specialCharacter.find(line[column_number]) == string::npos) {
        while (line[column_number] != '\0') {
            if (specialCharacter.find(line[column_number]) != string::npos) {
                return 0; // End of the keyword is found
            } else {
                if (!checkType(line[column_number], lineCharacter)) {
                    innerString.push_back(line[column_number]); // Use push_back for efficient string concatenation
                    column_number++;
                } else {
                    column_number++;
                    return 0;
                }
            }
        }
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
        getline(input_file, line);
        column_number=0;
        line_number++;
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
//TODO: implémenter la creation des objets schem.
int Dot::parse() {
    enum parser_states {default_state,strict,graph_type,name,open_accolade,choose_declaration,statement,link,equal,statement_value,statement_end,link_end,unknown, assignment};
    parser_states current_state = default_state;
    parser_states next_state = unknown;
    SchematicObject* temp_schem = nullptr;
    Token* current_token = this->first_token;
    map<string, vector<string>> tempLink;

    do {
        
        switch (current_state)
        {
            case default_state:{
                string copy = current_token->getValue();
                transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
                if (copy == "strict"){
                    next_state = strict ;
                } else if (copy == "digraph" || copy == "graph"){
                    next_state= graph_type;
                } else {
                    throwParseError("Syntax error: No starter keywords", current_token->getLine(), current_token->getColumn());
                }
                cout << "default_state" << endl;
                break;
            }


            case strict:{
                string copy = current_token->getValue();
                transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
                if (copy == "digraph" || copy == "graph"){
                    next_state = graph_type;
                } else {
                    throwParseError("Syntax error: \"digraph\" or \"graph\" needed after \"strict\" keyword", current_token->getLine(), current_token->getColumn());
                }
                cout << "strict" << endl;
                break;
            }

            case graph_type:{
                if (current_token->getType() == AnyWords){
                    next_state = name;
                } else if (current_token->getValue() == "{") {
                    next_state = open_accolade;
                } else {
                    throwParseError("Syntax error: Missing word or '{' after starter keyword", current_token->getLine(), current_token->getColumn());
                }
                cout << "graph_type" << endl;
                break;
            }

            case name:{
                if (current_token->getValue() == "{"){
                    next_state = open_accolade;
                } else {
                    throwParseError("Syntax error: Missing '{'", current_token->getLine(), current_token->getColumn());
                }
                cout << "name" << endl;
                break;
            }

            case open_accolade:{
                cout << current_token->getType() << endl;
                cout << current_token->getValue() << endl;
                if(current_token->getType() == AnyWords){
                    temp_schem = new SchematicObject();
                    next_state = choose_declaration ;
                } else if (current_token->getValue() == "}") {
                    return 0;
                } else {
                    throwParseError("Syntax error: Missing word after '{'", current_token->getLine(), current_token->getColumn());
                }
                cout << "open_accolade" << endl;
                break;
            }

            case choose_declaration:{
                if(current_token->getValue() == "["){
                    if (!(this->schematicObjectsList.count(current_token->getValue()))){
                        temp_schem->setGateId(current_token->getPreviousToken()->getValue());
                    } else {
                        throwParseError("Syntax error: Gate Id already used", current_token->getLine(), current_token->getColumn());
                    }
                    next_state = statement;
                } else if (current_token->getType() == Assignment) {
                    next_state = link;
                } else {
                   throwParseError("Syntax error: Missing word after '[' or '->", current_token->getLine(), current_token->getColumn());
                }
                cout << "choose_declaration" << endl;
                break;
            }

            case statement:{
                if(current_token->getType() == StatementKeyWords || current_token->getType() == AnyWords){
                    next_state = assignment;
                } else {
                    throwParseError("Syntax error: Unknown keyword", current_token->getLine(), current_token->getColumn());
                }
                cout << "statement" << endl;
                break;
            }

            case assignment:{
                if(current_token->getValue() == "="){
                    next_state = equal;
                } else {
                    throwParseError("Syntax error: Missing '=' after statement keyword", current_token->getLine(), current_token->getColumn());
                }
                cout << "assignment" << endl;
                break;
            }


            case equal:{
                if(current_token->getType() == stringType){
                    if (current_token->getPreviousToken(2)->getType() != StatementKeyWords){
                        if (!(temp_schem->getAdditionnalOptions().count(current_token->getPreviousToken(2)->getValue()))){
                            temp_schem->addAdditionnalOptions(current_token->getPreviousToken(2)->getValue(), current_token->getValue());
                        } else {
                            throwParseError("Syntax error: SchematicsObject option already used", current_token->getLine(), current_token->getColumn());
                        }
                    } else if (current_token->getPreviousToken(2)->getValue() == "label") {
                        temp_schem->setGateType(current_token->getValue());
                    }
                } else {
                    throwParseError("Syntax error: Missing '\"' after '=' statement", current_token->getLine(), current_token->getColumn());
                }
                next_state = statement_value;
                cout << "equal" << endl;
                break;
            }

            case statement_value:{
                if(current_token->getType() == StatementKeyWords || current_token->getType() == AnyWords){
                    next_state = assignment;
                } else if (current_token->getValue() == "]"){
                    next_state = statement_end;
                } else {
                    throwParseError("Syntax error: Missing ']' or unknown keyword", current_token->getLine(), current_token->getColumn());
                }
                cout << "statement_value" << endl;
                break;
            }

            case statement_end:{
                if(current_token->getType() == AnyWords){
                    next_state = choose_declaration;
                } else if (current_token->getValue() == ";") {
                    next_state = open_accolade;
                } else {
                    throwParseError("Syntax error: Missing ';' or new erroneous statement", current_token->getLine(), current_token->getColumn());
                }
                cout << "statement_end" << endl;
                break;
            }

            case link:{
                if (current_token->getType() == AnyWords){
                    tempLink[current_token->getValue()].push_back(current_token->getPreviousToken(2)->getValue());
                    next_state = link_end;
                } else {
                    throwParseError("Syntax error: Missing '->'", current_token->getLine(), current_token->getColumn());
                }
                cout << "link" << endl;
                break;
            }

            case link_end:{
                if (current_token->getType() == AnyWords){
                    next_state = choose_declaration;
                } else if (current_token->getValue() == ";") {
                    next_state = open_accolade;
                } else if (current_token->getValue() == "->"){
                    next_state = link;
                } else {
                    throwParseError("Syntax error: Missing '->' or ';', or new erroneous statement", current_token->getLine(), current_token->getColumn());
                }
                cout << "link_end" << endl;
                break;
            }

            default:{
                cout << "default" << endl;
                return -1;
            }
        }
        current_state = next_state;
        cout << "Value: " << current_token -> getValue() << " , Type: "<< current_token -> getType() << endl;
    } while ( (current_token = current_token->getNextToken()) );

    
    cout << "Liste de link: " << endl;
    for (map<string, vector<string>>::const_iterator it = tempLink.begin(); it != tempLink.end(); ++it) {
        cout << "Clé : " << it->first << ", Valeur : "<< endl;
        for (const auto& element : it->second) {
        std::cout << element << std::endl;
        }
    }

    cout << "Liste d'additionnal options: " << endl;
    for (map<string, string>::const_iterator it = temp_schem->getAdditionnalOptions().begin(); it != temp_schem->getAdditionnalOptions().end(); ++it) {
        cout << "Clé : " << it->first << ", Valeur : " << it->second << endl;
    }

    return 0;//TODO: function that verify link and add input output and error decalage
}