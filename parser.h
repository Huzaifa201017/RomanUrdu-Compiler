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
    
};
#endif