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

    

}

bool parser :: E(){
    
}

bool parser :: _E(){
    
}

bool parser :: R(){
    
}

bool parser :: _R(){
    
}

bool parser :: T(){
    
}

bool parser :: F(){
    
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