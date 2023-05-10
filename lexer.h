#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// all your tokens goes here
enum class TokenType
{
	END_OF_FILE = 0,
	ERROR = 1,
	markazi = 2,
	kaam = 3,
	karo = 4,
	rakho = 5,
	jab = 6,
	tak = 7,
	bas = 8,
	agar = 9,
	to = 10,
	warna = 11,
	phir = 12,
	dekhao = 13,
	lo = 14,
	chalao = 15,
	wapas = 16,
	bhaijo = 17,
	adad = 18,
	khali = 19,
	khatam = 20,
	plus = 21,
	minus = 22,
	mul = 23,
	div = 24,
	mod = 25,
	pipe = 26,
	colon = 27,
	semi_colon = 28,
	at = 29,
	openPara = 30,
	closePara = 31,
	ID = 32,
	NUM = 33,
	assign = 34,
	STR = 35,
	RO = 36,
	INPUT = 37,
	OUTPUT = 38,
	cmnt = 39
};

// structure of a token
struct token
{
	string lexeme;
	TokenType tokenType; // enum type
	// constructor
	token(string lexeme, TokenType tokenType);
	// constructor default
	token();
	void Print();
};

class lexer
{
	vector<char> stream;  // used for storing file sample_code.ol content
	vector<token> tokens; // vector to store all (tokens,lexeme) pairs
	void Tokenize();	  // populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();				 // just print everything as it is present in file
	token getNextToken();			 // get next token
	void resetPointer();			 // reset pointer to start getting tokens from start
	int getCurrentPointer();		 // get where current pointer in tokens vector is
	void setCurrentPointer(int pos); // move current pointer to wherever
	token peek(int);				 // peek the next token
};

#endif // !_LEXER_H
