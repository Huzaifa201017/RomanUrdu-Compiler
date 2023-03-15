#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
}
void parser::readAndPrintAllInput() //read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
}
void parser::resetPointer()
{
    _lexer.resetPointer();
}


bool parser :: C(){

    if (_lexer.peek(1).tokenType == TokenType::semi_colon){
        expect(TokenType::semi_colon);

        if(_lexer.peek(1).tokenType == TokenType::cmnt){
            expect(TokenType::semi_colon);
            return true;
        }
        else {
            return true;
        }
       
    }
    
    
    return false;
    

}

bool parser :: E(){
    
    if(R()) {

        return _E();

    }

    return false;
}

bool parser :: _E(){

    if (_lexer.peek(1).tokenType == TokenType::plus){
        expect(TokenType::plus);

        if (R()){

            return _E();

        }else{
            return false;
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::minus){
        
        expect(TokenType::minus);

        if (R()){

            return _E();

        }else{
            return false;
        }
    }
    
    return true;
    
}

bool parser :: R(){
    
    if (T()){
       return _R();
    }

    return false;


}

bool parser :: _R(){
    
    if (_lexer.peek(1).tokenType == TokenType::mul){

        expect(TokenType::mul);

        if (T()){

            return _R();

        }else{
            return false;
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::div) {
        
        expect(TokenType::div);

        if (T()) {

            return _R();

        }
        else{
            return false;
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::mod) {
        
        expect(TokenType::mod);

        if (T()) {

            return _R();

        }
        else {
            return false;
        }
    }
    
    return true;
}

bool parser :: T() {

   if (_lexer.peek(1).tokenType == TokenType::ID){
      expect(TokenType::ID);
      return true;
   }
   else if (_lexer.peek(1).tokenType == TokenType::NUM){
        expect(TokenType::NUM);
        return true;
   }
   else if (_lexer.peek(1).tokenType == TokenType::openPara ){
     
     expect(TokenType::openPara);
     if (E()) {

        if (_lexer.peek(1).tokenType == TokenType::closePara ){
            
            expect(TokenType::closePara);
            return true;
        }

        expect(TokenType::closePara);

     }else {
        expect(TokenType::ERROR);
        return false;
     }

   }
   return false;
   
}

bool parser :: F() {
    
}

bool parser :: Func(){
    
}

bool parser :: Functype(){
    
}

bool parser :: P(){
    
}

bool parser :: A(){
    
}

bool parser :: Datatype(){

    if (_lexer.peek(1).tokenType == TokenType::adad ){
        expect(TokenType::adad);
        return true;
    }
    expect(TokenType::adad);
    return false;
}

bool parser :: V(){
    
}

bool parser :: B(){
    
}

bool parser :: O(){
    
}

bool parser :: D(){
    
}

bool parser :: FC(){
    
}

bool parser :: Z(){
    
}

bool parser :: U(){
    
}

bool parser :: print(){
    
}

bool parser :: H(){
    
}

bool parser :: G(){
    
}

bool parser :: input(){
    
}

bool parser :: Var(){
    
}

bool parser :: Conditional(){

     if (_lexer.peek(1).tokenType == TokenType::agar ){
        expect(TokenType::agar);

        if(_lexer.peek(1).tokenType == TokenType::openPara){
            expect(TokenType::openPara);

            if (E()){
                if(_lexer.peek(1).tokenType == TokenType::RO){
                    expect(TokenType::RO);

                    if (E()) {
                        

                    }
                }
            }
        }
     }
    
}

bool parser :: ElseIf(){
    
}

bool parser :: Else(){
    
}

bool parser :: While(){
    
}

bool parser :: Stmts(){
    
}

bool parser :: Stmt(){
    
}
bool parser :: Start(){
    
}
//this function is for sample purposes only
/*
bool parser::statements()
{
    //statements-- > COLON LPAREN start RPAREN
    if (_lexer.peek(1).tokenType == TokenType::COLON)
    {
        expect(TokenType::COLON);
        if (_lexer.peek(1).tokenType == TokenType::LPAREN)
        {
            expect(TokenType::LPAREN);
            start();
            if (_lexer.peek(1).tokenType == TokenType::RPAREN)
            {
                expect(TokenType::RPAREN);
                return true;
            }
        }
    }
    return false;
}*/ 