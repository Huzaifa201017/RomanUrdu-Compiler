#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"

class parser
{
    lexer _lexer;
public:
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    bool C();
    bool E();
    bool _E();
    bool R();
    bool _R();
    bool T();
    bool F();
    bool Func();
    bool Functype();
    bool P();
    bool A();
    bool Datatype();
    bool V();
    bool B();
    bool O();
    bool D();
    bool FC();
    bool Z();
    bool U();
    bool print();
    bool H();
    bool G();
    bool input();
    bool I();
    bool Var();
    bool J();
    bool Conditional();
    bool ElseIf();
    bool Else();
    bool While();
    bool Stmts();
    bool Stmt();
    bool Start();
    /*Terminal functions goes here use peek and expect*/
    /*
    use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
    */
	//all your parser function goes here
};
#endif
