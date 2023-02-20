#include "lexer.h"
using namespace std;

TokenType checkKeywords(string chars){
    if (chars == "agar"){
        return agar;
    }
    else if(chars == "markazi") {
        return markazi;
    }
    else if(chars == "kaam") {
       return kaam;
    }
    else if(chars == "karo") {
        return karo;
    }
    
    else if(chars == "rakho") {
        return rakho;
    }
    else if(chars == "jab") {
        return jab;
    }
    else if(chars == "tak") {
        return tak;
    }
    else if(chars == "bas") {
        return bas;
    }
    else if(chars == "to") {
        return to;
    }
    else if(chars == "warna") {
        return warna;
    }
    else if(chars == "phir") {
        return phir;
    }
    else if(chars == "dekhao") {
        return dekhao;
    }
    else if(chars == "lo") {
        return lo;
    }
    else if(chars == "chalao") {
        return chalao;
    }
    else if(chars == "wapas") {
        return wapas;
    }
    else if(chars == "bhaijo") {
        return bhaijo;
    }
    else if(chars == "adad") {
        return adad;
    }
    else if(chars == "khali") {
        return khali;
    }
    else if(chars == "khatam") {
        return khatam;
    }else{
        return ERROR;
    }

}

//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE",
	"ERROR",
	"markazi","kaam","karo","rakho","jab","tak","bas","agar","to","warna","phir",
	"dekhao","lo","chalao","wapas","bhaijo","adad","khali","khatam"
};

//  "LE","LT","GE","GT","EQ","NE",
// 	"plus","minus","mul","div","mod",
// 	"pipe","colon","semi_colon","at","backTick","openPara","closePara",
// 	"ID","NUM"
token::token()
{
    
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
        << reserved[(int)tokenType] << "}\n";
}
int lexer::getCurrentPointer()
{
    return index;
}
void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}

void lexer::Tokenize()//function that tokenizes your input stream
{
    
  
    int state = 1;
    string chars = "";
    int index = 0;

    for (index = 0; index < stream.size(); index++)
    {

        
        switch (state)
        {
            case 1:


                if (isalpha(stream[index]) || stream[index] == '_'){

                    chars += stream[index];
                    state = 2;
                    
                }
                else if (stream[index] == ';') {
                    state = 3;
                }
                else if (stream[index] == '@'){
                    cout << "@"<< "," << "NULL\n";
                }
                else if( stream[index] == '('){
                    cout << "("<< "," << "NULL\n";
                }
                else if( stream[index] == ')'){
                    cout << ")"<< "," << "NULL\n";
                }
                else if( stream[index] == '|'){
                    cout << "|"<< "," << "NULL\n";
                }
                else if( stream[index] == '='){
                    cout << "RO"<< "," << "=\n";
                }
                else if (stream[index] == '>'){
                    state = 6;
                }
                else if (stream[index] == '<'){
                    state = 8;
                }
                else if (stream[index] == '+') {
                    cout << "+"<< "," << "NULL\n";
                }
                else if (stream[index] == '-'){
                    cout << "-"<< "," << "NULL\n";
                }
                else if (stream[index] == '*'){
                    cout << "*"<< "," << "NULL\n";
                }
                else if (stream[index] == '/'){
                    cout << "/"<< "," << "NULL\n";
                }
                else if (stream[index] == '%'){
                    cout << "%"<< "," << "NULL\n";
                }
                else if (stream[index] == ':'){
                    state = 10;
                }
                break;


            // transition for identifier
            case 2:


                if (isalpha(stream[index]) || isdigit(stream[index]) || stream[index] == '_'){
                    chars += stream[index];
                }
                else {
                    state = 4;
                }
                break;
            

            // transition for comment
            case 3:


                if (stream[index] == '\n'){
                    state = 5;
                }
                else{
                    chars += stream[index];
                }
                break;

                
            // transition for >= and > operator
            case 6:


                if (stream[index] == '='){
                    cout << "RO" << "," << ">=\n";
                    state = 1;

                }
                else{
                    state = 7;
                }
                break;


            // transition for <= ,<> and < operator
            case 8:


                if (stream[index] == '='){
                    cout << "RO" << "," << "<=\n";
                    state = 1;

                }
                else if (stream[index] == '>') {
                    cout << "RO" << "," << "<>\n";
                    state = 1;
                }
                else{
                    state = 9;
                    
                }

                break;

            // transition for ;= operator
            case 10:
                if (stream[index] == '='){
                    cout << ":= , NULL\n"; 
                    state = 1;
                }else{
                    state = 11;
                }
    
                 break;


            // 'other' transitions

            // transition for identifier
            case 4:
               
                // check keywords
                
                if (reserved[checkKeywords(chars)] != "ERROR"){
                    cout << reserved[checkKeywords(chars)] << " , NULL\n";

                }else {
                    cout << "ID" << " , "<< chars << endl;
                }
                
                chars = "";
                state = 1;
                index -= 2;
                break;

            // transtition for comment or somehow simple semi-colon
            case 5:


                cout << "semi_colon , NULL" << endl;

                if (chars.length() != 0){
                    cout << chars << "," << "NULL" << endl;
                }
                chars = "";
                state = 1;
                index -= 2;
                break;

            
            // transition for > operator
            
            case 7:


                cout << "RO , >\n";
                state = 1;
                index -= 2;
                break;

            // transition for < operator
            case 9:


                cout << "RO , <\n";
                state = 1;
                index -= 2;
                break;

            // transition for : (Error)
            case 11:
                cout << ": , NULL\n";
                state = 1;
                index -= 2;
                break;



            default:
                break;
            

        }

    }
   
    

	//push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}


lexer::lexer(const char filename[])
{
    //constructors: takes file name as an argument and store all
    //the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) //if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { //store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back('\n');//dummy spaces appended at the end
        stream.push_back('\n');
        //Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        //assigning tokens to iterator::pointer
        index = 0;
    }
}
lexer::lexer()
{
    index = -1;
}
void lexer::printRaw()
{
    //helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
token lexer::getNextToken()
{
    //this function will return single (token,lexeme) pair on each call
    //this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}
void lexer::resetPointer()
{
    index = 0;
}
token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                                 // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}