#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//all your tokens goes here
enum  TokenType
{

	END_OF_FILE = 0,
	ERROR=1,
	markazi=2,kaam=3,karo=4,rakho=5,jab=6,tak=7,bas=8,agar=9,to=10,warna=11,phir=12,
	dekhao=13,lo=14,chalao=15,wapas=16,bhaijo=17,adad=18,khali=19,khatam=20,
	LE=21,LT=22,GE=23,GT=24,EQ=25,NE=26,
	plus=27,minus=28,mul=29,div=30,mod=31,
	pipe=32,colon=33,semi_colon=34,at=35,backTick=36,openPara=37,closePara=38,
	ID=39,NUM=40,assign=41


};
//structure of a token 
struct token
{
	string lexeme;
	TokenType tokenType;//enum type
	//constructor
	token(string lexeme, TokenType tokenType);
	//constructor default
	token();
	void Print();
};


class lexer
{
	vector<char> stream;  //used for storing file sample_code.ol content
	vector<token> tokens; //vector to store all (tokens,lexeme) pairs
	void Tokenize();      //populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();                 //just print everything as it is present in file
	token getNextToken();            //get next token
	void resetPointer();             //reset pointer to start getting tokens from start
	int getCurrentPointer();         //get where current pointer in tokens vector is
	void setCurrentPointer(int pos); //move current pointer to wherever
	token peek(int);                 //peek the next token
};

#endif // !_LEXER_H
