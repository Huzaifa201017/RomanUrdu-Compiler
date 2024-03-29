#include <iostream>
#include "parser.h"
#include "lexer.h"
#include "lexer.cpp"
#include "parser.cpp"
using namespace std;

int main(int argc, char* argv[])
{ 

	//asking for file name as command line arguments
	if (argc == 2)
	{  
		parser p(argv[1]);
		p.Start();

	}
	else if (argc > 2)
	{ //argument limit exceeds
		cout << "Too many arguments" << endl;
	}
	else //if file name is'nt given
	{
		cout << "Please provide a file name" << endl;
	}
	return 0;
}
