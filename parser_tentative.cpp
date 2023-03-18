#include "parser.h"

string reserved1[] = {
    "END_OF_FILE",
	"ERROR",
	"markazi","kaam","karo","rakho","jab","tak","bas","agar","to","warna","phir",
	"dekhao","lo","chalao","wapas","bhaijo","adad","khali","khatam",
	"plus","minus","mul","div","mod",
	"pipe","colon","semi_colon","at","openPara","closePara",
	"ID","NUM","assign","STR","RO","INPUT","OUTPUT","cmnt"
};


void parser::syntax_error(TokenType t)
{
    
    cout << "SYNTAX ERROR: For word: " << reserved1[(int)t] << endl;
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error(t.tokenType);
    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
    
    cout << "\n\nNow Analyzer...\n\n";
    token t;
	t = _lexer.getNextToken();
		
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
    _lexer.setCurrentPointer(0);
    cout << "\n\nNow Parsing...\n\n";
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


bool parser :: C() {

    if (_lexer.peek(1).tokenType == TokenType::semi_colon){

        expect(TokenType::semi_colon);

        if (_lexer.peek(1).tokenType == TokenType::cmnt){
            expect(TokenType::cmnt);
        }
        
        return true;
        
       
    }
    
    return false;

}

bool parser :: Comment(){

    // if(_lexer.peek(1).tokenType == TokenType::cmnt){

    //     return true;

    // }else {

    // }

    // return false;
}

void parser :: E(){

    R();
    _E();

}

void parser :: _E(){


    if (_lexer.peek(1).tokenType == TokenType::plus){
        expect(TokenType::plus);
        R();
        _E();



    }
    else if (_lexer.peek(1).tokenType == TokenType::minus) {
        
        expect(TokenType::minus);

        R();
        _E();
    }
    else {
        ;
    }
   
    
}

void parser :: R() {

    T();
    _R();



}

void parser :: _R(){
    
    if (_lexer.peek(1).tokenType == TokenType::mul){

        expect(TokenType::mul);
        
        T();
        _R();

    }
    else if (_lexer.peek(1).tokenType == TokenType::div) {
        
        expect(TokenType::div);

        T();
        _R();
    }
    else if (_lexer.peek(1).tokenType == TokenType::mod) {
        
        expect(TokenType::mod);

        T();
        _R();

    }
    else {
        ;
    }
    
    
}

void parser :: T() {


   if (_lexer.peek(1).tokenType == TokenType::ID){

       expect(TokenType::ID);


   }
   else if (_lexer.peek(1).tokenType == TokenType::NUM){
        
        expect(TokenType::NUM);

   }
   else if (_lexer.peek(1).tokenType == TokenType::openPara ){
     
        expect(TokenType::openPara);

        E();

        if (_lexer.peek(1).tokenType == TokenType::closePara ){
                
            expect(TokenType::closePara);
        }
        else {
            expect(TokenType::closePara);
        }
        

   }
   
}

bool parser :: F() {    


    if (_lexer.peek(1).tokenType==TokenType::kaam)
    {
        expect(TokenType::kaam);
        Func();

        if(_lexer.peek(1).tokenType==TokenType::at){

            expect(TokenType::at);
            
            Functype();

            if (_lexer.peek(1).tokenType==TokenType::openPara)
            {
                expect(TokenType::openPara);

                P();


                if (_lexer.peek(1).tokenType==TokenType::closePara)
                {
                    expect(TokenType::closePara);

                    if (_lexer.peek(1).tokenType==TokenType::karo)
                    {
                        expect(TokenType::karo);

                        Stmts();


                        if (_lexer.peek(1).tokenType==TokenType::kaam)
                        {
                            expect(TokenType::kaam);

                            if (_lexer.peek(1).tokenType==TokenType::khatam)
                            {
                                expect(TokenType::khatam);
                                return true;

                            }
                            
                            
                        }
 
                        
                    }
                    
                    
                }

            }

        }

    
        
        
    }

    syntax_error(_lexer.peek(1).tokenType);
    
}

void parser :: Func() {

    
    if (_lexer.peek(1).tokenType == TokenType::markazi)
    {

        expect(TokenType::markazi);
        
        
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);

    }else{
        syntax_error(_lexer.peek(1).tokenType);
    }
   
    
}

void parser :: Functype() {
    
    if (_lexer.peek(1).tokenType == TokenType::adad)
    {
        expect(TokenType::adad);
    }
    else if (_lexer.peek(1).tokenType == TokenType::khali)
    {
        expect(TokenType::khali);

    }else{
        syntax_error(_lexer.peek(1).tokenType);
    }
    
   
    

}

void parser :: P(){
    
    
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        if (_lexer.peek(1).tokenType == TokenType::at)
        {
            expect(TokenType::at);

            Datatype() ;
            A();
            
           
        }else{
            expect(TokenType::at);
        }

    }
    else
    {
       ;
    }
    
}

void parser :: A(){
    
    
    if(_lexer.peek(1).tokenType == TokenType::pipe)
    {
        expect(TokenType::pipe);

        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            expect(TokenType::ID);

            if (_lexer.peek(1).tokenType == TokenType::at)
            {
                expect(TokenType::at);

                Datatype();
                A();

            
            }else {
                syntax_error(_lexer.peek(1).tokenType);
            }

        
            
        }else{
            syntax_error(_lexer.peek(1).tokenType);
        }

    }
    else
    {
        ;
    }
    
}

void parser :: Datatype(){

    if (_lexer.peek(1).tokenType == TokenType::adad ){
        expect(TokenType::adad);


    }else{
        syntax_error(_lexer.peek(1).tokenType);
    }
}

bool parser :: V() {

    if (_lexer.peek(1).tokenType == TokenType::rakho ){
        expect(TokenType::rakho);

        if (_lexer.peek(1).tokenType == TokenType::ID ){
             expect(TokenType::ID);

              if (_lexer.peek(1).tokenType == TokenType::at ){

                    expect(TokenType::at);

                    Datatype();
                    B();

                    if (_lexer.peek(1).tokenType == TokenType::cmnt ){
                        expect(TokenType::cmnt);
                    }
                    
                    
                }else{
                   syntax_error(_lexer.peek(1).tokenType);
                }

        

        }else{
            syntax_error(_lexer.peek(1).tokenType);
        }
    }

 }
        


void parser :: B() {

    if (_lexer.peek(1).tokenType == TokenType::assign ){
        
        expect(TokenType::assign);
        O();
        

        
    }else if(_lexer.peek(1).tokenType == TokenType::semi_colon)  {

        expect(TokenType::semi_colon);
    }
    else{
        ;
    }

    
   
}

void parser :: O() {

    if (!FC()){
        
         E();
    
        if(_lexer.peek(1).tokenType == TokenType::semi_colon)  {

            expect(TokenType::semi_colon);

        }else{
            syntax_error(_lexer.peek(1).tokenType);
        }

    }
   
   
   
    
}


bool parser :: FC(){
    
    
    if (_lexer.peek(1).tokenType == TokenType::chalao)
    {
        expect(TokenType::chalao);
        
        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            expect(TokenType::ID);

            if (_lexer.peek(1).tokenType == TokenType::openPara)
            {
                expect(TokenType::openPara);
                Z();
              

                if (_lexer.peek(1).tokenType == TokenType::closePara)
                {
                    expect(TokenType::closePara);
                    
                    if (_lexer.peek(1).tokenType == TokenType::semi_colon)
                    {
                        expect(TokenType::semi_colon);

                        if (_lexer.peek(1).tokenType == TokenType::cmnt){
                            expect(TokenType::cmnt);
                        }
                        return true;
                    
                    }else{
                        expect(TokenType::semi_colon);
                    }
                    
                }else{
                    expect(TokenType::closePara);
                }
                   
                
               
                
                
            }else{
                expect(TokenType::openPara);
            }
           
            
            
        }else{
            expect(TokenType::ID);
        }
        
    }
    
    return false;
    
}

void parser :: Z(){
    
    E();
    U();

}

void parser :: U(){
    
    
    if (_lexer.peek(1).tokenType == TokenType::pipe)
    {
        expect(TokenType::pipe);
        E();
        U();
       
    }
    else {

        ;
    }
    
}

bool parser :: print(){
    
   
    if (_lexer.peek(1).tokenType == TokenType::dekhao)
    {
        expect(TokenType::dekhao);
        if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
        {
            expect(TokenType::OUTPUT);
            G();
            H();
          
            if (_lexer.peek(1).tokenType == TokenType::semi_colon)
            {
                expect(TokenType::semi_colon);

                if (_lexer.peek(1).tokenType == TokenType::cmnt ){
                    expect(TokenType::cmnt);
                }

                return true;
                
            }
            else
            {
                expect(TokenType::semi_colon);
            }

            
        }
        else
        {
            expect(TokenType::OUTPUT);
        }
        
    }
    else
    {
        return false;
    }
    
}

void parser :: H(){
    
    
    if(_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        expect(TokenType::OUTPUT);
        G();
        H();
        
    }
    else
    {
       ;
    }

}

void parser :: G(){
    
    // G -> str | E
    if (_lexer.peek(1).tokenType == TokenType::STR)
    {
        expect(TokenType::STR);

    }
    else
    {
        E();

    }
    
    
}

bool parser :: input(){

    // input -> lo H >> Var I ;
    if(_lexer.peek(1).tokenType == TokenType::lo)
    {
        expect(TokenType::lo);
        H() ;
        if (_lexer.peek(1).tokenType == TokenType::INPUT)
        {
            expect(TokenType::INPUT);
            Var();
            I();
           

            if (_lexer.peek(1).tokenType == TokenType::semi_colon)
            {
                expect(TokenType::semi_colon);

                if (_lexer.peek(1).tokenType == TokenType::cmnt ){
                    expect(TokenType::cmnt);
                }

                return true;

            }else{
                expect(TokenType::semi_colon);
            }
                

            
          
            
        }else{
            expect(TokenType::INPUT);
        }
       
       
        
    }
    return false;
    
    
}

void parser :: I(){

    // I -> >> Var I | ^
    if (_lexer.peek(1).tokenType == TokenType::INPUT)
    {
        expect(TokenType::INPUT);
        Var();
        I();

    }
    else
    {
        ;
    }
    
}

void parser :: Var(){

    // Var  -> ID | ID@DataTypef
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        J();

    }
    
    
}

void parser :: J(){

    // J -> @DataType | ^
    if (_lexer.peek(1).tokenType == TokenType::at)
    {
        expect(TokenType::at);
        Datatype();
        
    }
    else
    {
       ;
    }
    
}

bool parser :: Conditional(){

    if (_lexer.peek(1).tokenType == TokenType::agar ){

        expect(TokenType::agar);

        if(_lexer.peek(1).tokenType == TokenType::openPara){

            expect(TokenType::openPara);
            E();
            

            if(_lexer.peek(1).tokenType == TokenType::RO){ 

                expect(TokenType::RO);
                E();
               

                if(_lexer.peek(1).tokenType == TokenType::closePara){

                    expect(TokenType::closePara);

                    if(_lexer.peek(1).tokenType == TokenType::to){
                        expect(TokenType::to);

                        if(_lexer.peek(1).tokenType == TokenType::phir){
                            expect(TokenType::to);

                            if(_lexer.peek(1).tokenType == TokenType::karo){
                                expect(TokenType::karo);

                                Stmts();
                                ElseIf();
                                Else();
                               
                             

                                if(_lexer.peek(1).tokenType == TokenType::bas){
                                    expect(TokenType::bas);

                                    if(_lexer.peek(1).tokenType == TokenType::karo){
                                        expect(TokenType::karo);

                                        return true;

                                    }else{
                                        expect(TokenType::karo);
                                    }

                                }else{
                                    expect(TokenType::bas);
                                }
                                        
                                    

                                    
                                
                                                    
                                

                                
                            }else{
                                expect(TokenType::karo);
                            }

                                
                        }else{
                            expect(TokenType::to);
                        }
                        
                    }else{

                        expect(TokenType::to);
                    }

                }else{
                    expect(TokenType::closePara);
                }


                

            }else{
                expect(TokenType::RO);
            }
            

        }else{

            expect(TokenType::openPara);
        }
    }

    return false;
    
}

void parser :: ElseIf() {

    if(_lexer.peek(1).tokenType == TokenType::warna){
        expect(TokenType::warna);

        if(_lexer.peek(1).tokenType == TokenType::agar){
            expect(TokenType::agar);

            if(_lexer.peek(1).tokenType == TokenType::openPara){

                expect(TokenType::openPara);
                E();
               

                if(_lexer.peek(1).tokenType == TokenType::RO){ 

                    expect(TokenType::RO);
                    E();
                 

                    if(_lexer.peek(1).tokenType == TokenType::closePara){
                        expect(TokenType::closePara);

                        if(_lexer.peek(1).tokenType == TokenType::to){
                        
                            expect(TokenType::to);


                            if(_lexer.peek(1).tokenType == TokenType::phir){
                                
                                expect(TokenType::to);
                                Stmts();
                                ElseIf();

                                
                            }else{
                                expect(TokenType::to);
                            }

                        }else{
                            expect(TokenType::to);
                        }

                    }else{
                        expect(TokenType::closePara);
                    }

                        

                    

                }else{
                    expect(TokenType::RO);
                }
                

            }
            else{
                expect(TokenType::openPara);
            }

        }
        else{
            expect(TokenType::agar);
        }

        

    }
    else {
        ;
    }
}

void parser :: Else() {

    if(_lexer.peek(1).tokenType == TokenType::warna){
        expect(TokenType::warna);

        if(_lexer.peek(1).tokenType == TokenType::phir){
            expect(TokenType::phir);
            Stmts();
        
            

        }else{
            expect(TokenType::phir);
        }

        
        
    }
    else{

       ;
    }

}

bool parser :: While() {

    if(_lexer.peek(1).tokenType == TokenType::jab) {

        expect(TokenType::jab);

        if(_lexer.peek(1).tokenType == TokenType::tak) {

            expect(TokenType::tak);

            if(_lexer.peek(1).tokenType == TokenType::openPara){

                expect(TokenType::openPara);
                E();
               

                if(_lexer.peek(1).tokenType == TokenType::RO){ 

                    expect(TokenType::RO);
                    E();
                   

                    if(_lexer.peek(1).tokenType == TokenType::closePara){
                        expect(TokenType::closePara);

                        if(_lexer.peek(1).tokenType == TokenType::karo){
                        
                            expect(TokenType::karo);
                            
                            Stmts();

                      
                                
                            if(_lexer.peek(1).tokenType == TokenType::bas){
                                expect(TokenType::bas);

                                if(_lexer.peek(1).tokenType == TokenType::karo){

                                    expect(TokenType::karo);
                                    return true;

                                }else{
                                    expect(TokenType::karo);
                                }
                                
                            }else{
                                expect(TokenType::bas);
                            }
                                
                            
                            
                        }else{
                             expect(TokenType::karo);
                        }

                    }else{
                        expect(TokenType::closePara);
                    }

                    

                }else{
                    expect(TokenType::RO);
                }
                

            }

        }else{
            expect(TokenType::tak);
        }

    }
    return false;


    
}
                            
bool parser :: K() {

    if (_lexer.peek(1).tokenType == TokenType::ID ) {

        B();

        if (_lexer.peek(1).tokenType == TokenType::cmnt){
            expect(TokenType::cmnt);

        }
        return true;
            


        
    }
    return false;

}


bool parser :: Stmts() {

    if(_lexer.peek(1).tokenType == TokenType::END_OF_FILE) {
        return true;
    }

    if(Stmt()) {
       return Stmts();
    }
    else {

        return true;

    }
}

bool parser :: Stmt() {

    int i = _lexer.getCurrentPointer();

    if( C() ) {
        return true;
    }
     _lexer.setCurrentPointer(i);
    if( V() ) {
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(FC()) {
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(print()){
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(input()){
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(Conditional()){
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(While()) {
        return true;
    }
    _lexer.setCurrentPointer(i);
    if(K()) {
        return true;
    }
    _lexer.setCurrentPointer(i);
   
    return false;
}


bool parser :: Start() {

    if(_lexer.peek(1).tokenType == TokenType::END_OF_FILE) {
        return true;
    }
    if( F() ) {
       return Start();

    }else {
        cout << "Syntax Error\n";
        exit(1);
    }

    
    

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