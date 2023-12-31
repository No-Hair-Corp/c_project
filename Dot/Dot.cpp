#include "Dot.hpp"

// Size of keyword arrays
#define STATEMENTKEYWORDSIZE 176 
#define STARTERKEYWORDSIZE 3

// Special characters that are recognized in the Dot language
string Dot::specialCharacter = "->/\\[]=;{}*#";
string Dot::stringStarter = "\"";
string Dot::statementKeywords[STATEMENTKEYWORDSIZE] = {"_background","area","arrowhead","arrowsize","arrowtail","bb","beautify","bgcolor","center","charset","class","cluster","clusterrank","color","colorscheme","comment","compound","concentrate","constraint","Damping","decorate","defaultdist","dim","dimen","dir","diredgeconstraints","distortion","dpi","edgehref","edgetarget","edgetooltip","edgeURL","epsilon","esep","fillcolor","fixedsize","fontcolor","fontname","fontnames","fontpath","fontsize","forcelabels","gradientangle","group","head_lp","headclip","headhref","headlabel","headport","headtarget","headtooltip","headURL","height","href","id","image","imagepath","imagepos","imagescale","inputscale","K","label","label_scheme","labelangle","labeldistance","labelfloat","labelfontcolor"}; //,"labelfontname","labelfontsize","labelhref","labeljust","labelloc","labeltarget","labeltooltip","labelURL","landscape","layer","layerlistsep","layers","layerselect","layersep","layout","len","levels","levelsgap","lhead","lheight","linelength","lp","ltail","lwidth","margin","maxiter","mclimit","mindist","minlen","mode","model","newrank","nodesep","nojustify","normalize","notranslate","nslimit","nslimit1","oneblock","ordering","orientation","outputorder","overlap","overlap_scaling","overlap_shrink","pack","packmode","pad","page","pagedir","pencolor","penwidth","peripheries","pin","pos","quadtree","quantum","rank","rankdir","ranksep","ratio","rects","regular","remincross","repulsiveforce","resolution","root","rotate","rotation","samehead","sametail","samplepoints","scale","searchsize","sep","shape","shapefile","showboxes","sides","size","skew","smoothing","sortv","splines","start","style","stylesheet","tail_lp","tailclip","tailhref","taillabel","tailport","tailtarget","tailtooltip","tailURL","target","TBbalance","tooltip","truecolor","URL","vertices","viewport","voro_margin","weight","width","xdotversion","xlabel","xlp","z"};
string Dot::starterKeywords[STARTERKEYWORDSIZE] = {"digraph", "strict", "graph"};
string Dot::forbiddenCharacter = "\'`";
string Dot::lineCharacter = ",\t\n\r "; 

// ======= CONSTRUCTOR / DESTRUCTOR =======

// Constructor: initializes file_path and first_token
Dot::Dot(string file_path) : file_path(file_path), first_token(NULL) {
}

Dot::~Dot(){
    for(auto const& x : this->getSchematicObjectsList()){
        delete x.second;
    }
    this->schematicObjectsList.clear();

    Token* current_token = this->first_token;
    while (current_token) {
        Token* next_token = current_token->getNextToken();
        delete current_token;
        current_token = next_token;
    }


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

map<string, SchematicObject*>& Dot::getSchematicObjectsList(){
    return this->schematicObjectsList;
}

// ======= OTHER FUNCTIONS =======

// Lexer function to tokenize the input file
int Dot::lexer() { 
    ifstream input_file(this->getFilePath()); //open file
    string line;
    string buffer = ""; //string to stock token values during lexing step
    unsigned int line_number = 0;
    unsigned int column_number = 0;
    Token* previousToken = NULL; //ptr corresponding to the previous tokn of the current token
    Token* currentToken;//ptr corresponding to the current token

    if (!input_file) {
        return 1; // Error: Unable to open input file
    }

    // Iterate through each line in the input file
    while (getline(input_file, line)) {
    column_number = 0;
    // Iterate through each character in the line
    while (line[column_number] != '\0') { 
        // Check for forbidden characters
        if (checkType(line[column_number], Dot::forbiddenCharacter)) {
            throwParseError("Forbidden character used", line_number, column_number);
            return 1; // Error: Forbidden character found
        } else if (checkType(line[column_number], Dot::specialCharacter)) {
            // Check if the current character is part of the "->" or "--" arrow
            if (CheckArrow(line, column_number)) {
                buffer = {line[column_number], line[column_number+1]};
                column_number += 2;
                // Create a new Token for the arrow
                currentToken = new Token(buffer, Assignment, previousToken, NULL, line_number + 1, column_number + 1);
            } else if (line[column_number] == '/' || line[column_number] == '#' ){
                // Handle comments and skip to the next line or next */
                if (jumpComments(input_file, line, column_number, line_number))
                    break;
            } else {
                // Create a Token for other special characters
                buffer = line[column_number];
                currentToken = new Token(buffer, SpecialCharacter, previousToken, NULL, line_number + 1, column_number + 1);
                column_number++;
            }
        } else if (checkType(line[column_number], Dot::stringStarter)) {
            // Handle strings enclosed in double quotes
            column_number++;
            buffer = "";
            // Register the string and create a token
            Dot::registerString(input_file, line, column_number, line_number, buffer);
            if (buffer == ""){
                throwParseError("Empty string detected", line_number, column_number);
                return 2;
            } else {
                currentToken = new Token(buffer, stringType, previousToken, NULL, line_number + 1, column_number);
                column_number++;
            }
        } else if (checkType(line[column_number], Dot::lineCharacter)) {
            // Skip line characters
            column_number++;
            continue;
        } else {
            // Register keywords and create tokens
            buffer = "";
            unsigned int temp_col = column_number;
            Dot::registerKeywords(input_file, line, column_number, line_number, buffer);
            // Create a lowercase copy of the input word for case-insensitive comparison
            string copy = buffer;
            transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
            // Check if the buffer is a statement or starter keyword
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
return 0;   // Successful completion

}

// Function to check if a character is in the set of special characters
bool Dot::checkType(char c, const string specialCharacter) {
    return (specialCharacter.find(c) != string::npos);
}

// Function to check if a word is one of the predefined keywords
bool Dot::checkKeywords(string& word, int n, string Keywords[]) {
    // Create a lowercase copy of the input word for case-insensitive comparison
    string copy = word;
    transform(copy.begin(), copy.end(), copy.begin(), ::tolower);   

    // Iterate through the list of predefined keywords
    for (int i = 0; i < n; i++) {
        // Check if the lowercase copy matches the current keyword
        if (copy == Keywords[i]) {
            return true; // Match found, the word is a keyword
        }
    }

    // No match found, the word is not a keyword
    return false;
}


// Function to register a string enclosed in double quotes
int Dot::registerString(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString) {
    // Continue processing characters until the end of the string is found
    while (line[column_number] != '"' && (column_number == 0 || line[column_number - 1] != '\\')) {
        // Iterate through each character in the line
        while (line[column_number] != '\0') {
            // Check if the current character is the closing double quote
            if (line[column_number] == '"' && (column_number == 0 || line[column_number - 1] != '\\')) {
                return 0; // End of the string is found
            } else {
                // Append the character to the innerString while avoiding newline characters
                if (line[column_number] != '\n' && line[column_number] != '\r' ) {
                    innerString.push_back(line[column_number]); // Use push_back for efficient string concatenation
                    column_number++;
                } else {
                    column_number++;
                }
            }
        }

        // If the line ends, get the next line from the input file
        if (!getline(input_file, line)) {
            return 1; // End of file is reached
        }

        // Update line_number for the new line and reset column_number
        line_number++;
        column_number = 0;
    }

    // Successful completion, the string is registered
    return 0;
}

// Function to throw a parse error without position information
void Dot::throwParseError(const string& error_message) {
    Help::debug(DOT_DEBUG, ERROR_DEBUG, error_message);
}

// Function to throw a parse error with position information
void Dot::throwParseError(const string& error_message, unsigned int line, unsigned int column) {
    Help::debug(DOT_DEBUG, ERROR_DEBUG, "In dot file at line " + to_string(line) + ", column " + to_string(column) + ": " + error_message);
}

// Function to register keywords in the input file
int Dot::registerKeywords(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number, string& innerString) {
    // Continue processing characters until the end of the keyword is found
    while (specialCharacter.find(line[column_number]) == string::npos) {
        // Iterate through each character in the line
        while (line[column_number] != '\0') {
            // Check if the current character is part of the special characters
            if (specialCharacter.find(line[column_number]) != string::npos) {
                return 0; // End of the keyword is found
            } else {
                // If the current character is not in lineCharacter, append it to innerString
                if (!checkType(line[column_number], lineCharacter)) {
                    innerString.push_back(line[column_number]); // Use push_back for efficient string concatenation
                    column_number++;
                } else {
                    column_number++;
                    return 0; // End of the keyword is found
                }
            }
        }

        // If the line ends, get the next line from the input file
        if (!getline(input_file, line)) {
            return 1; // End of file is reached
        }

        // Update line_number for the new line and reset column_number
        line_number++;
        column_number = 0;
    }

    // Successful completion, the keyword is registered
    return 0;
}

// Function to check if the current character(s) form an arrow (-> or --)
bool Dot::CheckArrow(string& line, int column_number) {
    // Check if the current character is '-' and the next character is '>'
    if (line[column_number] == '-' && line[column_number + 1] != '\0' && line[column_number + 1] == '>') {
        return true;
    } else if (line[column_number] == '-' && line[column_number + 1] != '\0' && line[column_number + 1] == '-') {
        // Check if the current character is '-' and the next character is also '-'
        return true;
    } else {
        // If none of the conditions are met, return false
        return false;
    }
}


// Function to skip comments in the input file
int Dot::jumpComments(ifstream& input_file, string& line, unsigned int& column_number, unsigned int& line_number) {
    // Check if the current line begins with "//" or "#"
    if ((line[column_number] == '/' && line[column_number + 1] == '/') || line[column_number] == '#') {
        // Skip the entire line if it is a single-line comment
        if (!getline(input_file, line)) {
            return 0; // End of file is reached
        } else {
            column_number = 0;
            line_number++;
        }
    } else if (line[column_number] == '/' && line[column_number + 1] == '*') {
        // Skip the multi-line comment until "*/" is found
        while (line[column_number] != '*' && line[column_number + 1] != '/') {
            while (line[column_number] != '\0') {
                // Check if the current characters are "*/"
                if (line[column_number] == '*' && line[column_number + 1] == '/') {
                    column_number++;
                    return 0; // End of multi-line comment is found
                } else {
                    column_number++;
                }
            }
            // Move to the next line if the end of the line is reached
            if (!getline(input_file, line)) {
                return 1; // End of file is reached
            }
            line_number++;
            column_number = 0; // Reset column_number for the new line
        }
    } else {
        // Move to the next character if not in a comment
        column_number++;
        return 0;
    }
    return 0; // Successful completion
}


// Function to parse the tokens generated by the lexer
int Dot::parse() {
    enum parser_states {default_state,strict,graph_type,name,open_accolade,choose_declaration,statement,link,equal,statement_value,statement_end,link_end,unknown, assignment};
    parser_states current_state = default_state;
    parser_states next_state = unknown;

    map<string, vector<string>> tempLink; //temporary list to stock connexion
    SchematicObject* temp_schem = nullptr;//temporary SchematicObject to use new in the parser

    Token* current_token = this->first_token; //init current_token to the first_token

    //check if the file is empty
    if(current_token == nullptr){
        throwParseError("Empty file given");
        return 21;
    }


    do {
 
        switch (current_state)
        {
            
            case default_state: {
                // Get the value of the current token
                string copy = current_token->getValue();
                
                // Convert the value to lowercase for case-insensitive comparison
                transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
                
                // Check if the value is "strict"
                if (copy == "strict") {
                    next_state = strict;
                } 
                // Else, check if the value is "digraph" or "graph"
                else if (copy == "digraph" || copy == "graph") {
                    next_state = graph_type;
                } 
                // If none of the above conditions are satisfied, throw a syntax error
                else {
                    throwParseError("Syntax error: No starter keywords", current_token->getLine(), current_token->getColumn());
                    return 2;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case strict: {
                // Get the value of the current token
                string copy = current_token->getValue();
                
                // Convert the value to lowercase for case-insensitive comparison
                transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
                
                // Check if the value is "digraph" or "graph"
                if (copy == "digraph" || copy == "graph") {
                    next_state = graph_type;
                } 
                // If the value is not "digraph" or "graph", throw a syntax error
                else {
                    throwParseError("Syntax error: unexpected `" + current_token->getValue() + "` after `strict`, expecting a `digraph` or `graph`.", current_token->getLine(), current_token->getColumn());
                    return 3;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case graph_type: {
                // Check the type of the current token
                if (current_token->getType() == AnyWords) {
                    // If the type is AnyWords, transition to the 'name' state
                    next_state = name;
                } 
                // If the type is not AnyWords, check if the value is "{"
                else if (current_token->getValue() == "{") {
                    // If the value is "{", transition to the 'open_accolade' state
                    next_state = open_accolade;
                } 
                // If the type is not AnyWords and the value is not "{", throw a syntax error
                else {
                    throwParseError("Syntax error: unexpected `" + current_token->getValue() + "` after `digraph` or `graph`, expecting an `{`.", current_token->getLine(), current_token->getColumn());
                    return 4;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case name: {
                // Check if the value of the current token is "{"
                if (current_token->getValue() == "{") {
                    // If the value is "{", transition to the 'open_accolade' state
                    next_state = open_accolade;
                } 
                // If the value is not "{", throw a syntax error
                else {
                    throwParseError("Syntax error: unexpected `" + current_token->getValue() + "` after `digraph` or `graph`, expecting an `{`.", current_token->getLine(), current_token->getColumn());
                    return 5;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case open_accolade: {
                // Check the type of the current token
                if (current_token->getType() == AnyWords) {
                    // If the type is AnyWords, transition to the 'choose_declaration' state
                    next_state = choose_declaration;
                } 
                // If the value is "}", exit the loop
                else if (current_token->getValue() == "}") {
                    break;
                } 
                // If neither condition is met, throw a syntax error
                else {
                    throwParseError("Syntax error: unexpected `" + current_token->getValue() + "`, expecting a word.", current_token->getLine(), current_token->getColumn());
                    return 6;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case choose_declaration: {
                // Check if the current token's value is "["
                if (current_token->getValue() == "[") {
                    // If true, create a new SchematicObject and set its GateId
                    temp_schem = new SchematicObject();
                    // Check if the GateId is not already used
                    if (!(this->schematicObjectsList.count(current_token->getPreviousToken()->getValue()))) {
                        temp_schem->setGateId(current_token->getPreviousToken()->getValue());
                    } else {
                        // Throw an error if the GateId is already used
                        throwParseError("Syntax error: Gate Id `" + current_token->getPreviousToken()->getValue() + "` already used", current_token->getLine(), current_token->getColumn());
                        return 7;  // Return an error code to the calling function
                    }
                    // Move to the 'statement' state
                    next_state = statement;
                } 
                // Check if the current token's type is Assignment
                else if (current_token->getType() == Assignment) {
                    // If true, move to the 'link' state
                    next_state = link;
                } 
                // If neither condition is met, throw a syntax error
                else {
                    throwParseError("Syntax error: unexpected `" + current_token->getValue() + "`, expecting a `[` or `->`.", current_token->getLine(), current_token->getColumn());
                    return 8;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case statement: {
                // Check if the current token's type is StatementKeyWords or AnyWords
                if (current_token->getType() == StatementKeyWords || current_token->getType() == AnyWords) {
                    // If true, transition to the 'assignment' state
                    next_state = assignment;
                } else {
                    // If the type is neither StatementKeyWords nor AnyWords, throw a syntax error
                    throwParseError("Syntax error: Unexpected `" + current_token->getValue() + "` after `[`, expecting a word.", current_token->getLine(), current_token->getColumn());
                    return 9;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case assignment: {
                // Check if the current token's value is "="
                if (current_token->getValue() == "=") {
                    // If true, transition to the 'equal' state
                    next_state = equal;
                } else {
                    // If the value is not "=", throw a syntax error
                    throwParseError("Syntax error: Unexpected `" + current_token->getValue() + "`, expecting an `=`.", current_token->getLine(), current_token->getColumn());
                    return 10;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case equal: {
                // Check if the current token's type is stringType or AnyWords
                if (current_token->getType() == stringType || current_token->getType() == AnyWords) {
                    // Create a lowercase copy of the token two positions back
                    string copy = current_token->getPreviousToken(2)->getValue();
                    transform(copy.begin(), copy.end(), copy.begin(), ::tolower);

                    // Check if the token two positions back is not a StatementKeyWords
                    if (current_token->getPreviousToken(2)->getType() != StatementKeyWords) {
                        // Check if the additional options of temp_schem do not contain the key
                        if (!(temp_schem->getAdditionnalOptions().count(current_token->getPreviousToken(2)->getValue()))) {
                            // If not, add the additional option to temp_schem
                            temp_schem->addAdditionnalOptions(current_token->getPreviousToken(2)->getValue(), current_token->getValue());
                        } else {
                            // If the key is already present, throw a syntax error
                            throwParseError("Syntax error: SchematicsObject option already used", current_token->getLine(), current_token->getColumn());
                            return 11;  // Return an error code to the calling function
                        }
                    } else if (copy == "label") {
                        // If the key is "label", set the gate type of temp_schem
                        temp_schem->setGateType(current_token->getValue());
                    }
                } else {
                    // If the current token's type is not stringType or AnyWords, throw a syntax error
                    throwParseError("Syntax error: Unexpected `" + current_token->getValue() + "` after `=`, expecting a word.", current_token->getLine(), current_token->getColumn());
                    return 12;  // Return an error code to the calling function
                }

                // Transition to the 'statement_value' state
                next_state = statement_value;
                break;  // Exit the 'switch' block to move to the next case
            }

            case statement_value: {
                // Check if the current token's type is StatementKeyWords or AnyWords
                if (current_token->getType() == StatementKeyWords || current_token->getType() == AnyWords) {
                    // Transition to the 'assignment' state
                    next_state = assignment;
                } else if (current_token->getValue() == "]") {
                    // If the current token's value is ']', add temp_schem to schematicObjectsList
                    this->schematicObjectsList[temp_schem->getGateId()] = temp_schem;
                    // Transition to the 'statement_end' state
                    next_state = statement_end;
                } else {
                    // If the current token doesn't match the expected values, throw a syntax error
                    throwParseError("Syntax error: Unexpected `" + current_token->getValue() + "`, expecting `]`.", current_token->getLine(), current_token->getColumn());
                    return 13;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case statement_end: {
                // Check if the current token's type is AnyWords
                if (current_token->getType() == AnyWords) {
                    // Transition to the 'choose_declaration' state
                    next_state = choose_declaration;
                } else if (current_token->getValue() == ";") {
                    // If the current token's value is ';', transition to the 'open_accolade' state
                    next_state = open_accolade;
                } else {
                    // If the current token doesn't match the expected values, throw a syntax error
                    throwParseError("Syntax error: Unexpected `" + current_token->getValue() + "`, expecting new declaration after `]`.", current_token->getLine(), current_token->getColumn());
                    return 14;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case link: {
                // Check if the current token's type is AnyWords
                if (current_token->getType() == AnyWords) {
                    // Update the tempLink map with the current token's value and the previous token's value
                    tempLink[current_token->getValue()].push_back(current_token->getPreviousToken(2)->getValue());
                    // Transition to the 'link_end' state
                    next_state = link_end;
                } else {
                    // If the current token doesn't match the expected type, throw a syntax error
                    throwParseError("Syntax error: Unexpected `" + current_token->getValue() + "`, expecting word.", current_token->getLine(), current_token->getColumn());
                    return 15;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            case link_end: {
                // Check if the current token's type is AnyWords
                if (current_token->getType() == AnyWords) {
                    // Transition to the 'choose_declaration' state
                    next_state = choose_declaration;
                } else if (current_token->getValue() == ";") {
                    // Transition to the 'open_accolade' state
                    next_state = open_accolade;
                } else if (current_token->getType() == Assignment) {
                    // Transition to the 'link' state
                    next_state = link;
                } else if (current_token->getValue() == "}") {
                    // Break out of the loop if the current token is '}'
                    break;
                } else {
                    // If the current token doesn't match any expected values, throw a syntax error
                    throwParseError("Syntax error: Unexpected `" + current_token->getValue() + "`, expecting `->` or new instance.", current_token->getLine(), current_token->getColumn());
                    return 16;  // Return an error code to the calling function
                }
                break;  // Exit the 'switch' block to move to the next case
            }

            default:{
                return 17;
            }
        }
        current_state = next_state;
        if (current_token->getNextToken() == nullptr && current_token->getValue() != "}" ){
            throwParseError("Syntax error: Missing '}'", current_token->getLine(), current_token->getColumn());
            return 1;
        }

    //loop until we reach the last token
    } while ( (current_token = current_token->getNextToken()) ); 

    //check existence of the connexion instances
    if(checkExistence(this->schematicObjectsList, tempLink)){
        return 18;
    }

    //check existence of the additionnal option instances
    if(checkExistence(this->schematicObjectsList)){
        return 19;
    }

    //check if each gate has a type
    if (checkLabel(this->schematicObjectsList)){
        return 20;
    }

    //fill the I/O list after checking existence
    fillIoList(this->schematicObjectsList, tempLink);


    return 0;
}


// Function to check the existence of instances in schematicObjectsList and tempLink
int Dot::checkExistence(map<string, SchematicObject*>& schematicObjectsList, map<string, vector<string>>& tempLink) {
    // Iterate over each entry in tempLink
    for (auto const& x : tempLink) {
        // Check if the key (instance) exists in schematicObjectsList
        if (schematicObjectsList.count(x.first)) {
            // Iterate over the vector of linked instances
            for (auto const& y : x.second) {
                // Check if the linked instance exists in schematicObjectsList
                if (!schematicObjectsList.count(y)) {
                    // Throw an error if the linked instance doesn't exist
                    throwParseError("This instance doesn't exist: " + y);
                    return 1; // Return error code 1
                }

            }
        } else {
            // Throw an error if the key (instance) doesn't exist in schematicObjectsList
            throwParseError("This instance doesn't exist: " + x.first);
            return 2; // Return error code 2
        }
    }
    // Return 0 if all instances are found
    return 0;
}



// Function to check the existence of instances referenced in the additionnalOptions of schematicObjectsList
int Dot::checkExistence(map<string, SchematicObject*>& schematicObjectsList) {
    // Iterate over each entry in schematicObjectsList
    for (auto const& x : schematicObjectsList) {
        // Iterate over the additionnalOptions of the current schematic object
        for (auto const& y : x.second->getAdditionnalOptions()) {
            // Check if the referenced instance exists in schematicObjectsList
            if (!schematicObjectsList.count(y.second)) {
                // Throw an error if the referenced instance doesn't exist
                throwParseError("This instance doesn't exist: " + y.second);
                return 1; // Return error code 1
            }
        }
    }
    // Return 0 if all referenced instances are found
    return 0;
}



// Function to fill input and output lists of schematicObjectsList based on tempLink
int Dot::fillIoList(map<string, SchematicObject*>& schematicObjectsList, map<string, vector<string>>& tempLink) {
    // Iterate over each link in tempLink
    for (auto const& link : tempLink) {
        // Initialize iterator for input indices
        int it = 0;
        // Iterate over each input in the current link
        for (auto const& Inputs : link.second) {
            // Get the map of existing inputs for the target schematic object
            map<string, string> existingInputs = schematicObjectsList[link.first]->getInputs();

            // Find an available input index (i0, i1, i2, etc.)
            while (schematicObjectsList[link.first]->getInputs().count("i" + to_string(it))) {
                it++;
            }

            // Add the input to the target schematic object
            schematicObjectsList[link.first]->addInputs("i" + to_string(it), Inputs);

            // Add the target schematic object to the outputs of the source schematic object
            schematicObjectsList[Inputs]->addOutputs(link.first);
        }
    }

    // Iterate over each schematic object in schematicObjectsList
    for (auto const& SO : schematicObjectsList) {
        // Iterate over each additional option of the current schematic object
        for (auto const& option : schematicObjectsList[SO.first]->getAdditionnalOptions()) {
            // Add the additional option as an input to the current schematic object
            schematicObjectsList[SO.first]->addInputs(option.first, option.second);
        }
    }

    // Return 0 on successful completion
    return 0;
}


// Function to check if each schematic object in schematicObjectsList has a label (gate type) declared
int Dot::checkLabel(map<string, SchematicObject*>& schematicObjectsList) {
    // Iterate over each schematic object in schematicObjectsList
    for (auto const& x : schematicObjectsList) {
        // Check if the gate type is empty (not declared)
        if (x.second->getGateType() == "") {
            // Throw an error if no gate type is declared for the current instance
            throwParseError("No type declared for instance " + x.first + ", need to add a label.");
            return 1; // Return 1 indicating an error
        }
    }

    // Return 0 on successful completion (no error)
    return 0;
}
