#include "lexer.h"
using namespace std;

TokenType checkKeywords(string chars){
    if (chars == "agar"){
        return TokenType::agar;
    }
    else if(chars == "markazi") {
        return TokenType::markazi;
    }
    else if(chars == "kaam") {
       return TokenType::kaam;
    }
    else if(chars == "karo") {
        return TokenType::karo;
    }
    
    else if(chars == "rakho") {
        return TokenType::rakho;
    }
    else if(chars == "jab") {
        return TokenType::jab;
    }
    else if(chars == "tak") {
        return TokenType::tak;
    }
    else if(chars == "bas") {
        return TokenType::bas;
    }
    else if(chars == "to") {
        return TokenType::to;
    }
    else if(chars == "warna") {
        return TokenType::warna;
    }
    else if(chars == "phir") {
        return TokenType::phir;
    }
    else if(chars == "dekhao") {
        return TokenType::dekhao;
    }
    else if(chars == "lo") {
        return TokenType::lo;
    }
    else if(chars == "chalao") {
        return TokenType::chalao;
    }
    else if(chars == "wapas") {
        return TokenType::wapas;
    }
    else if(chars == "bhaijo") {
        return TokenType::bhaijo;
    }
    else if(chars == "adad") {
        return TokenType::adad;
    }
    else if(chars == "khali") {
        return TokenType::khali;
    }
    else if(chars == "khatam") {
        return TokenType::khatam;
    }else{
        return TokenType::ERROR;
    }

}

//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE",
	"ERROR",
	"markazi","kaam","karo","rakho","jab","tak","bas","agar","to","warna","phir",
	"dekhao","lo","chalao","wapas","bhaijo","adad","khali","khatam",
	"plus","minus","mul","div","mod",
	"pipe","colon","semi_colon","at","openPara","closePara",
	"ID","NUM","assign","STR","RO","INPUT","OUTPUT","cmnt"
};




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

void lexer::Tokenize()         //function that tokenizes your input stream
{
    
  
    int state = 1;
    string chars = "";
    int index = 0;

    for (index = 0; index < stream.size(); index++)
    {

        
        switch (state)
        {
            case 1:
                
                if(stream[index] == ' ' || stream[index] == '\t' || stream[index] == '\n'){
                    break;
                }

                if (isalpha(stream[index]) || stream[index] == '_'){

                    chars += stream[index];
                    state = 2;
                    
                }
                else if (stream[index] == ';') {
                    state = 3;
                }
                else if (stream[index] == '@'){
                    this->tokens.push_back(token("NULL",TokenType::at));
                }
                else if( stream[index] == '('){
                    this->tokens.push_back(token("NULL",TokenType::openPara));
                }
                else if( stream[index] == ')'){
                    this->tokens.push_back(token("NULL",TokenType::closePara));
                }
                else if( stream[index] == '|'){
                    this->tokens.push_back(token("NULL",TokenType::pipe));
                }
                else if( stream[index] == '='){
                    this->tokens.push_back(token("EQ",TokenType::RO));
                }
                else if (stream[index] == '>'){
                    state = 6;
                }
                else if (stream[index] == '<'){
                    state = 8;
                }
                else if (stream[index] == '+') {
                    this->tokens.push_back(token("NULL",TokenType::plus));
                }
                else if (stream[index] == '-'){
                    this->tokens.push_back(token("NULL",TokenType::minus));
                }
                else if (stream[index] == '*'){
                    this->tokens.push_back(token("NULL",TokenType::mul));
                }
                else if (stream[index] == '/'){
                    this->tokens.push_back(token("NULL",TokenType::div));
                }
                else if (stream[index] == '%'){
                    this->tokens.push_back(token("NULL",TokenType::mod));
                }
                else if (stream[index] == ':'){
                    state = 10;
                }
                else if (stream[index] == '`'){
                    state=12;
                }
                else if (isdigit(stream[index])){
                    chars += stream[index];
                    state=14;

                }else{
                    state = 20; // error state
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

                
            // transition for >= and > and >> operator
            case 6:


                if (stream[index] == '='){
                    this->tokens.push_back(token("GE",TokenType::RO));
                    state = 1;

                }
                else if (stream[index] == '>'){
                    this->tokens.push_back(token("NULL",TokenType::INPUT));
                    state = 1;
                }
                else{
                    state = 7;
                }
                break;


            // transition for <= ,<> and < and << operator
            case 8:


                if (stream[index] == '='){
                    this->tokens.push_back(token("LE",TokenType::RO));
                    state = 1;

                }
                else if (stream[index] == '>') {
                    this->tokens.push_back(token("NE",TokenType::RO));
                    state = 1;
                }
                else if (stream[index] == '<') {
                    this->tokens.push_back(token("NULL",TokenType::OUTPUT));
                    state = 1;
                }
                else{
                    state = 9;
                    
                }

                break;

            // transition for := operator
            case 10:
                if (stream[index] == '='){
                    this->tokens.push_back(token("NULL",TokenType::assign));
                    state = 1;
                }else{
                    state = 11;
                }
    
                 break;

             // transition for string
            case 12:


                if (stream[index] == '`'){
                    state = 13;
                }
                else{
                    chars += stream[index];
                }
                break;


            // transition for integer
            case 14:


                if (isdigit(stream[index])){
                    chars += stream[index];
                }
                else{
                    state = 15;
                }
                break;
            


            // 'other' transitions

            //// transition for identifier
            case 4:
               
                // check keywords
                
                if (reserved[(int)checkKeywords(chars)] != "ERROR"){
                    this->tokens.push_back(token("NULL",checkKeywords(chars)));

                }else {
                    this->tokens.push_back(token(chars,TokenType::ID));
                }
                
                chars = "";
                state = 1;
                index -= 2;
                break;

            //// transtition for comment or somehow simple semi-colon
            case 5:

                this->tokens.push_back(token("NULL",TokenType::semi_colon));

                if (chars.length() != 0){
                    this->tokens.push_back(token(chars,TokenType::cmnt));
                }

                chars = "";
                state = 1;
                index -= 2;
                break;

            //// transtition for string
            case 13:

                
                // if (chars.length() != 0){
                //     this->tokens.push_back(token(chars,TokenType::STR));
                // }
                this->tokens.push_back(token(chars,TokenType::STR));


                chars = "";
                state = 1;
                index -= 1;

                break;

            
            //// transition for > operator
            
            case 7:

                this->tokens.push_back(token("GT",TokenType::RO));

                state = 1;
                index -= 2;
                break;

            //// transition for < operator
            case 9:

                this->tokens.push_back(token("LT",TokenType::RO));
                state = 1;
                index -= 2;
                break;

            //// transition for : (Error)
            case 11:

                this->tokens.push_back(token("NULL",TokenType::colon));
                state = 1;
                index -= 2;
                break;

            //// transition for Integers
            case 15:
                this->tokens.push_back(token(chars,TokenType::NUM));
                chars="";
                state = 1;
                index -= 2;
                break;


            default:
                cout << "Yes\n";
                this->tokens.push_back(token("",TokenType::ERROR));
                index -= 1;
                state = 1;
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