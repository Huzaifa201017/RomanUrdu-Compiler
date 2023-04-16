#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include <fstream>
class parser
{
   
public:
    lexer _lexer;
    ofstream fout1, fout2;
    int tabsCount;

    void syntax_error(TokenType t);
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    bool C();
    bool E(string &s);
    bool _E(string &s, string &i);
    bool R(string &s);
    bool _R(string &s, string &i);
    bool T(string &s);
    bool F();
    bool Func();
    bool Functype();
    bool P();
    bool A();
    bool Datatype();
    bool V();
    bool B(string& v);
    bool O(string& v);
    bool Y(string& v);
    bool FC(string& v);
    bool Z(int & c);
    bool U(int &c);
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
    bool K();
    bool Comment();
    bool W();
    string newTemp();
    

    /*Terminal functions goes here use peek and expect*/
    /*
    use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
    */
	//all your parser function goes here
};
#endif



// bool C();
//     void E();
//     void _E();
//     void R();
//     void _R();
//     void T();
//     bool F();
//     void Func();
//     void Functype();
//     void P();
//     void A();
//     void Datatype();
//     bool V();
//     void B();
//     void O();
//     bool FC();
//     void Z();
//     void U();
//     bool print();
//     void H();
//     void G();
//     bool input();
//     void I();
//     void Var();
//     void J();
//     bool Conditional();
//     void ElseIf();
//     void Else();
//     void While();
//     bool Stmts();
//     bool Stmt();
//     bool Start();
//     bool K();
//     bool Comment();