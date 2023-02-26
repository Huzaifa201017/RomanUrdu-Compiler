# Compiler For RomanUrdu Language

* File extension for this langiage would be .ru e.g sample_code.ru
* This language would be completely written in C++
* This would be a compiled language

## Phase 1(Lexical Analyzer):

In the phase 1 we have developed an Lexical Analyzer , which analyzes the source code and convert it 
into (token,lexime) pairs , which will be used by the parser(not yet developed)

### Files related to this phase are:
- lexer.h     (Utility classes for lexical analyzer)
- lexer.cpp   (Function definitions for above class member functions)
- main.cpp    (sample code to test above classes and functions etc)

### Problems Faced:
- We haven't faced any major issues while the development of this phase. There were some confusions regarding 
the syntax of the language and also the pattern of our (token , lexime) pairs for some of our language parts,
but we then got the solution ,after a little discussion with our Instructor and his assistant.

### Execution:

To run this project , you first have to load the project in the vscode.
- Open new terminal
- Enter command: 'g++ main.cpp -o a.out'
- This will make an executable file in your folder (a.out)
- Now execute it with the command:
- ./a.out path/to/sourceCode.ru

- e.g in this case it would be:
- ./a.out sample_code.ru

; where sample_code.ru is the file of the source code.

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


