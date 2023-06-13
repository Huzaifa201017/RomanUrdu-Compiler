# Compiler For RomanUrdu Language

* File extension for this langiage would be .ru e.g sample_code.ru
* This language would be completely written in C++
* This would be a compiled language

## Phase 1(Lexical Analyzer):

In the phase 1 we have developed an Lexical Analyzer , which analyzes the source code and convert it into (token,lexime) pairs , which will be used by the parser(not yet developed)

### Files related to this phase are:
- lexer.h     (Utility classes for lexical analyzer)
- lexer.cpp   (Function definitions for above class member functions)
- DFA.pdf      (DFA of the language)
- definition.txt  (Regular exxpressions of the language)

### Problems Faced:
- We haven't faced any major issues while the development of this phase. There were some confusions regarding 
the syntax of the language and also the pattern of our (token , lexime) pairs for some of our language parts,
but we then got the solution ,after a little discussion with our Instructor and his assistant.

### Note:
In the attached DFA diagram :

- At the final state q5 , in the returned (token,lexime) = (cmnt,comment) , the comment is 
actually a string comment which you have actually written e.g 

; This is phase 1

so in the case:  comment = "This is phase 1"
and our (token,lexime) = (cmnt,"This is phase 1")

- Similarly at  state  q13 , in the returned (token,lexime) = (str,string), the string is the actual string
defined in the language e.g in

`dekhao << This is phase 1`;

string = "This is phase 1"
so our (token,lexime) = (str,"This is phase 1")

- At state q2 , in the returned (token,lexime) = (ID,identifierName), the identifierName is the actual name of your identifier
defined in the language by you e.g  in

`rakho variableName1@adad;`

identifierName = "variableName1"
so our (token,lexime) = (ID,"variableName1")

- At state q15 , , in the returned (token,lexime) = (NUM,Integer), the Integer is actually the actual integer value
defined in the language by you e.g  in

`rakho variableName1@adad = 23;`

integer = 23 

so our (token,lexime) = (NUM,23)

## Phase 2 (Parser):
In this phase, we have developed a syntax analyzer , which verifies the syntax according to the CFG given in the file grammar.txt and gives error, in case the syntax is not followed.

### Files related to this phase are:
- parser.h     (Utility classes and functions for parser based on CFG)
- parser.cpp   (Function definitions for above class member functions)
- grammar.txt  (CFG of the language + Corresponding Actions)


## Phase 3 (Intermediate Code Generator):
In this phase, we have developed an Intermediate code generator, which generates the intermediate code on the basis of CFG actions given in grammar.txt.

### Files related to this phase are:
- parser.h   (Utility classes and functions for parser based on CFG)
- parser.cpp   (Function definitions for above class member functions)
- grammar.txt  (CFG of the language + Corresponding Actions)
- TAC.txt (created on runtime and contains the intermediate code for the language)
- symbol_table.txt (created on runtime and contains the information of variables and functions)

## Phase 4 (Machine Code Generator):
In this phase, we have developed a Machine code generator using the intermediate code generated above in TAC.txt and symbol_table.txt, and in that same phase , we have used this machine code to execute the code (basically developed a virtual machine to execute it).

### Files related to this phase are:
- vm.cpp (a kind of virtual machine , which converts the TAC code to machine code using symbol table and execute it directly then.)
- TAC.txt (created on runtime and contains the intermediate code for the language)
- symbol_table.txt (created on runtime and contains the information of variables and functions)

### Execution:

To run this project , you first have to load the project in the vscode.
- Open new terminal
- Enter command: 'g++ main.cpp -o main'
- This will make an executable file in your folder (main)
- Now execute it with the command:
- ./main path/to/sourceCode.ru
- e.g in this case it would be:
- ./a.out sample_code.ru

; where sample_code.ru is the file of the source code.

Now after this we'll have machine code in TAC.txt with symbol table (symbol_table.txt).

- Enter command: 'g++ vm.cpp -o vm' to get a executable for our virtual machine.
- Now Enter: vm TAC.txt
- After that your code will be executed finally and the task of your compiler ends here.