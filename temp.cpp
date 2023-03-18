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

bool parser :: E(){

    R();
    _E();
    


    return true;
}

bool parser :: _E(){


    if (_lexer.peek(1).tokenType == TokenType::plus){
        expect(TokenType::plus);
        R();
        _E();
        return true;

    }
    else if (_lexer.peek(1).tokenType == TokenType::minus) {
        
        expect(TokenType::minus);

        R();
        _E();
        return true;
    }
    else {

        return true;
    }
   
    
}

bool parser :: R(){

    T();
    _R();
    

    return true;


}

bool parser :: _R(){
    
    if (_lexer.peek(1).tokenType == TokenType::mul){

        expect(TokenType::mul);
        T();
        _R();
        return true;

    }
    else if (_lexer.peek(1).tokenType == TokenType::div) {
        
        expect(TokenType::div);

        T();
        _R();
        return true;
    }
    else if (_lexer.peek(1).tokenType == TokenType::mod) {
        
        expect(TokenType::mod);

        T();
        _R();
        return true;
    }
    else {

        return true;
    }
    
    
}

bool parser :: T() {

   if (_lexer.peek(1).tokenType == TokenType::ID){

       expect(TokenType::ID);
       return true;
   }
   else if (_lexer.peek(1).tokenType == TokenType::NUM){
        
        expect(TokenType::NUM);
        return true;

   }
   else if (_lexer.peek(1).tokenType == TokenType::openPara ){
     
        expect(TokenType::openPara);

        E();

        if (_lexer.peek(1).tokenType == TokenType::closePara ){
                
            expect(TokenType::closePara);
            return true;
        }
        else {
            expect(TokenType::closePara);
        }
        

   }else {
      expect(TokenType::ID);
      return false;
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

                            }else{
                                expect(TokenType::khatam);
                            }
                            
                            
                        }else{
                            expect(TokenType::kaam);
                        }

                        
                        
                        
                    }else {
                        expect(TokenType::karo);
                    }
                    
                    
                }else{
                    expect(TokenType::closePara);
                }

            }else{

                expect(TokenType::openPara);
            }

        }else{

            expect(TokenType::at);
        }

    
        
        
    }else{
        expect(TokenType::kaam);
    }

            
        
        
        
    
    return false;
    
}

bool parser :: Func() {

    
    if (_lexer.peek(1).tokenType == TokenType::markazi)
    {

        expect(TokenType::markazi);

        // if (_lexer.peek(1).tokenType == TokenType::at)
        // {
        //     expect(TokenType::at);

        //     if (_lexer.peek(1).tokenType == TokenType::khali)
        //     {
        //         expect(TokenType::khali);
        //         return true;
        //     }

            
        // }
        return true;
        
        
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        // if (_lexer.peek(1).tokenType == TokenType::at)
        // {
        //     expect(TokenType::at);

        //     if(Functype()){
        //         return true;
        //     }
            
        // }
       return true;
    }
    expect(TokenType::markazi);
    return false;
    
}

bool parser :: Functype() {
    
    if (_lexer.peek(1).tokenType == TokenType::adad)
    {
        expect(TokenType::adad);
        return true;
    }
    else if (_lexer.peek(1).tokenType == TokenType::khali)
    {
        expect(TokenType::khali);
        return true;
    }
    
    expect(TokenType::adad);
    return false;
    

}

bool parser :: P(){
    
    
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        if (_lexer.peek(1).tokenType == TokenType::at)
        {
            expect(TokenType::at);

            Datatype() ;
            A();

        
            return true;
            
           
        }else{
            expect(TokenType::at);
        }

        return false;
    }
    else
    {
       return true;
    }
    
}

bool parser :: A(){
    
    
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
                return true;
            
            }else{
                expect(TokenType::at);
            }

        
            
        }else{
            expect(TokenType::ID);
        }
        return false;
    }
    else
    {
       return true;
    }
    
}

bool parser :: Datatype(){

    if (_lexer.peek(1).tokenType == TokenType::adad ){
        expect(TokenType::adad);
        return true;

    }else{
        expect(TokenType::adad);
    }

    return false;
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

                    return true;

            
                      
                    
                    
                }else{
                    expect(TokenType::at);
                }

        

        }else{
            expect(TokenType::ID);
        }
    }

        

 }
        


bool parser :: B() {

    if (_lexer.peek(1).tokenType == TokenType::assign ){
        
        expect(TokenType::assign);
        O();
      
        return true;
        

        
    }else if(_lexer.peek(1).tokenType == TokenType::semi_colon)  {
        expect(TokenType::semi_colon);
         return true;
    }

    return false;
   
}

bool parser :: O() {
    
    FC();
    E();
    
    if(_lexer.peek(1).tokenType == TokenType::semi_colon)  {
        expect(TokenType::semi_colon);
        return true;
    }
   
    return true;
    
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

bool parser :: Z(){
    
    E();
    U();
   

    return true;
   
   
    
    
    
    
}

bool parser :: U(){
    
    
    if (_lexer.peek(1).tokenType == TokenType::pipe)
    {
        expect(TokenType::pipe);
        E();
        U();
        return true;
       
    }
    else {

        return true;
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

bool parser :: H(){
    
    
    if(_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        expect(TokenType::OUTPUT);
        G();
        H();
       
       return true;
        
    }
    else
    {
        return true;
    }

}

bool parser :: G(){
    
    // G -> str | E
    if (_lexer.peek(1).tokenType == TokenType::STR)
    {
        expect(TokenType::STR);
        return true;
    }
    else
    {
        E();
        return true;
    }
    
    
}

bool parser :: input(){

    // input -> lo H >> Var I ;
    if(_lexer.peek(1).tokenType == TokenType::lo)
    {
        expect(TokenType::lo);
       
        if (H() && _lexer.peek(1).tokenType == TokenType::INPUT)
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

bool parser :: I(){

    // I -> >> Var I | ^
    if (_lexer.peek(1).tokenType == TokenType::INPUT)
    {
        expect(TokenType::INPUT);

        if(Var() && I()){
            return true;
        }

        return false;

    }
    else
    {
        return true;
    }
    
}

bool parser :: Var(){

    // Var  -> ID | ID@DataTypef
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        J();
       
        return true;

        
       
    }
    return false;
    
}

bool parser :: J(){

    // J -> @DataType | ^
    if (_lexer.peek(1).tokenType == TokenType::at)
    {
        expect(TokenType::at);
        Datatype();
        return true;
        
    }
    else
    {
        return true;
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

    
}

bool parser :: ElseIf() {

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
                                return true;
                                
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

        return true;
    }
}

bool parser :: Else() {

    if(_lexer.peek(1).tokenType == TokenType::warna){
        expect(TokenType::warna);

        if(_lexer.peek(1).tokenType == TokenType::phir){
            expect(TokenType::phir);
            Stmts();
          

            return true;
            

        }else{
            expect(TokenType::phir);
        }

        
        
    }
    else{

        return true;
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


    
}
                            
bool parser :: K() {

    if (_lexer.peek(1).tokenType == TokenType::ID ) {

        B();
        

        if (_lexer.peek(1).tokenType == TokenType::semi_colon ){

            expect(TokenType::semi_colon);

            if (_lexer.peek(1).tokenType == TokenType::cmnt){
                expect(TokenType::cmnt);

            }
            return true;
            

        }else{

            expect(TokenType::semi_colon);
        }
        
    }


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


        // if(_lexer.peek(1).tokenType != TokenType::END_OF_FILE){
            
        //     //expect(TokenType::ERROR);
            
        //     return false;

        // }

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

// kaam calculateFib@adad (n@adad | c@adad) karo
// 	rakho x@adad := 0;
// 	rakho y@adad := 0;
// 	rakho z@adad;

// 	agar (n < 0) to phir karo
// 		dekhao << `munfi number daal diya\n`;
// 		wapas bhaijo 0; 
// 	warna agar (n = 0) to phir
// 		dekhao << `yar 0 hai!\n`;
// 		wapas bhaijo 0;
// 	warna phir
// 		dekhao << `\nfibonacci series: `;
// 		rakho i@adad := 1;
// 		jab tak (i-1 >= n) karo
// 			dekhao << x << ` `;
// 			rakho z := x + y;
// 			rakho x := y;
// 			rakho y := z;
// 			rakho i := i + 1;
// 		bas karo
// 	bas karo

// 	wapas bhaijo 0;
// kaam khatam

// ;fibonacci series ka hisaab karnay and dekhanay wala program
// kaam markazi@khali () karo
// 	rakho num@adad;
// 	lo << `Enter the number` >> num; input
// 	rakho result@adad := chalao calculateFib(arg1 | arg2);
// 	wapas bhaijo 0; halt
// kaam khatam