#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
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


bool parser :: C(){

    if (_lexer.peek(1).tokenType == TokenType::semi_colon){
        expect(TokenType::semi_colon);

        if(_lexer.peek(1).tokenType == TokenType::cmnt){
            expect(TokenType::semi_colon);
            return true;
        }
        else {
            return true;
        }
       
    }
    
    
    return false;
    

}

bool parser :: E(){
    
    if(R()) {

        return _E();

    }

    return false;
}

bool parser :: _E(){

    if (_lexer.peek(1).tokenType == TokenType::plus){
        expect(TokenType::plus);

        if (R()){

            return _E();

        }else{
            return false;
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::minus){
        
        expect(TokenType::minus);

        if (R()){

            return _E();

        }else{
            return false;
        }
    }
    
    return true;
    
}

bool parser :: R(){
    
    if (T()){
       return _R();
    }

    return false;


}

bool parser :: _R(){
    
    if (_lexer.peek(1).tokenType == TokenType::mul){

        expect(TokenType::mul);

        if (T()){

            return _R();

        }else{
            return false;
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::div) {
        
        expect(TokenType::div);

        if (T()) {

            return _R();

        }
        else{
            return false;
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::mod) {
        
        expect(TokenType::mod);

        if (T()) {

            return _R();

        }
        else {
            return false;
        }
    }
    
    return true;
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
     if (E()) {

        if (_lexer.peek(1).tokenType == TokenType::closePara ){
            
            expect(TokenType::closePara);
            return true;
        }

        expect(TokenType::closePara);

     }else {
        expect(TokenType::ERROR);
        return false;
     }

   }
   return false;
   
}

bool parser :: F() {

    //F -> kaam Func (P) karo Stmts kaam khatam
    if (_lexer.peek(1).tokenType==TokenType::kaam)
    {
        expect(TokenType::kaam);
        Func();
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
                        else
                        {
                            expect(TokenType::khatam);
                        }
                        
                    }
                    else
                    {
                        expect(TokenType::kaam);
                    }
                    
                    
                }
                else
                {
                    expect(TokenType::karo);
                }
                
            }
            else
            {
                expect(TokenType::closePara);
            }
            
            
        }
        else
        {
            expect(TokenType::openPara);
        }
        
    }
    return false;
    
}

bool parser :: Func(){

    //Func -> markazi@khali | ID@FuncType
    if (_lexer.peek(1).tokenType == TokenType::markazi)
    {
        expect(TokenType::markazi);
        if (_lexer.peek(1).tokenType == TokenType::at)
        {
            expect(TokenType::at);
            if (_lexer.peek(1).tokenType == TokenType::khali)
            {
                expect(TokenType::khali);
                return true;
            }
            else
            {
                expect(TokenType::khali);
            }
            
        }
        else
        {
            expect(TokenType::at);
        }
        
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        if (_lexer.peek(1).tokenType == TokenType::at)
        {
            expect(TokenType::at);
            Functype();
            return true;
        }
        else
        {
            expect(TokenType::at);
        }
    }
    else
    {
        return false;
    }
    
}

bool parser :: Functype(){
    
    //FuncType -> adad | khali
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
    else
    {
        return false;
    }

}

bool parser :: P(){
    
    // P -> ID@DataType A | ^
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        if (_lexer.peek(1).tokenType == TokenType::at)
        {
            expect(TokenType::at);
            Datatype();
            A();
            return true;
        }
        else
        {
            expect(TokenType::at);
        }
        
    }
    else
    {
        ;
    }
    
}

bool parser :: A(){
    
    // A -> | ID@DataType A | ^
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
            }
            else
            {
                expect(TokenType::at);
            }
            
        }
        else
        {
            expect(TokenType::ID);
        }
        
    }
    else
    {
        ;
    }
    
}

bool parser :: Datatype(){

    if (_lexer.peek(1).tokenType == TokenType::adad ){
        expect(TokenType::adad);
        return true;
    }
    expect(TokenType::adad);
    return false;
}

bool parser :: V() {

    if (_lexer.peek(1).tokenType == TokenType::rakho ){
        expect(TokenType::rakho);

         if (_lexer.peek(1).tokenType == TokenType::ID ){
            expect(TokenType::ID);

             if (_lexer.peek(1).tokenType == TokenType::at ){
                    expect(TokenType::at);

                    if (Datatype()){

                        if(B()){

                            if (_lexer.peek(1).tokenType == TokenType::semi_colon ){
                                expect(TokenType::semi_colon);

                                if (D()){

                                    return true;
                                }

                                

                            }
                        }
                    }


                    
             }

        

        }
    }

        

 }
        


bool parser :: B() {

    if (_lexer.peek(1).tokenType == TokenType::assign ){
        expect(TokenType::assign);

        if (O()) {
            return true;
        }

    }
    else{
        return true;
    }
}

bool parser :: O() {

    if (E() || FC()){
        return true;
    }
    return false;
}

bool parser :: D() {
    if (_lexer.peek(1).tokenType == TokenType::cmnt ){
        return true;
        
    }else{
        return false;
    }

    return false;
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
                        return true;
                    }
                    else
                    {
                        expect(TokenType::semi_colon);
                    }
                }
                else
                {
                    expect(TokenType::closePara);
                }
                
            }
            else
            {
                return false;
            }
            
            
        }
        else
        {
            return false;
        }
        
    }
    else
    {
        return false;
    }
    
}

bool parser :: Z(){
    
    // Z -> E U | ^
    if(E())
    {
        U();
        return true;
    }
    else
    {
        ;
    }
    
}

bool parser :: U(){
    
    // U -> | E U  | ^
    if (_lexer.peek(1).tokenType == TokenType::pipe)
    {
        E();
        U();
        return true;
    }
    else
    {
        ;
    }
    
}

bool parser :: print(){
    
    // print -> dekhao << G H ;
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
    
    // H -> << G H | ^
    if(_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        expect(TokenType::OUTPUT);
        G();
        H();
        return true;
    }
    else
    {
        ;
    }

}

bool parser :: G(){
    
    // G -> str | E
    if (_lexer.peek(1).tokenType == TokenType::STR)
    {
        expect(TokenType::STR);
        return true;
    }
    else if (E())
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool parser :: input(){

    // input -> lo H >> Var I ;
    if(_lexer.peek(1).tokenType == TokenType::lo)
    {
        expect(TokenType::lo);
        H();
        if (_lexer.peek(1).tokenType == TokenType::INPUT)
        {
            expect(TokenType::INPUT);
            Var();
            I();
            if (_lexer.peek(1).tokenType == TokenType::semi_colon)
            {
                expect(TokenType::semi_colon);
                return true;
            }
            else
            {
                expect(TokenType::semi_colon);
            }
        }
        else
        {
            expect(TokenType::INPUT);
        }
        
    }
    else
    {
        return false;
    }
    
}

bool parser :: I(){

    // I -> >> Var I | ^
    if (_lexer.peek(1).tokenType == TokenType::INPUT)
    {
        expect(TokenType::INPUT);
        Var();
        I();
        return true;
    }
    else
    {
        ;
    }
    
}

bool parser :: Var(){

    // Var  -> ID | ID@DataType
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        J();
        return true;
    }
    else
    {
        return false;
    }
    
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
        ;
    }
    
}

bool parser :: Conditional(){

    if (_lexer.peek(1).tokenType == TokenType::agar ){
        expect(TokenType::agar);

        if(_lexer.peek(1).tokenType == TokenType::openPara){

            expect(TokenType::openPara);

            if (E()){

                if(_lexer.peek(1).tokenType == TokenType::RO){ 
                    expect(TokenType::RO);

                    if (E()) {

                        if(_lexer.peek(1).tokenType == TokenType::closePara){

                            expect(TokenType::closePara);

                            if(_lexer.peek(1).tokenType == TokenType::to){
                                expect(TokenType::to);

                                if(_lexer.peek(1).tokenType == TokenType::phir){
                                    expect(TokenType::to);

                                    if(_lexer.peek(1).tokenType == TokenType::karo){
                                        expect(TokenType::karo);

                                        
                                        if(Stmts()){
                                            
                                            if (ElseIf()){

                                                if (Else()){

                                                    if(_lexer.peek(1).tokenType == TokenType::bas){
                                                        expect(TokenType::bas);

                                                        if(_lexer.peek(1).tokenType == TokenType::karo){
                                                            expect(TokenType::karo);

                                                            return true;
                                                        }
                                                    }
                                                }
                                            }

                                            
                                        }
                                                            
                                        

                                        
                                    }
                                        
                                }
                                
                            }
                        }


                    }
                }
            }

        }
    }

    return false;
    
}

bool parser :: ElseIf() {

    if(_lexer.peek(1).tokenType == TokenType::warna){
        expect(TokenType::warna);

        if(_lexer.peek(1).tokenType == TokenType::agar){
            expect(TokenType::agar);

            if(_lexer.peek(1).tokenType == TokenType::openPara){

                expect(TokenType::openPara);
                if ( E() ) {

                    if(_lexer.peek(1).tokenType == TokenType::RO){ 

                        expect(TokenType::RO);

                        if (E()) {

                            if(_lexer.peek(1).tokenType == TokenType::closePara){
                                expect(TokenType::closePara);

                                if(_lexer.peek(1).tokenType == TokenType::to){
                                
                                    expect(TokenType::to);


                                    if(_lexer.peek(1).tokenType == TokenType::phir){
                                        
                                        expect(TokenType::to);

                                        if(Stmts()){
                                            
                                            if (ElseIf()) {
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }

                           

                        }
                    }
                }

            }

        }

        return false;

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

            if (Stmts()){

                return true;
            }
        }

        return false;
        
    }
    else{

        return false;
    }

}

bool parser :: While() {

    if(_lexer.peek(1).tokenType == TokenType::jab) {

        expect(TokenType::jab);

        if(_lexer.peek(1).tokenType == TokenType::tak) {
            expect(TokenType::tak);

            if(_lexer.peek(1).tokenType == TokenType::openPara){

                expect(TokenType::openPara);

                if ( E() ) {

                    if(_lexer.peek(1).tokenType == TokenType::RO){ 

                        expect(TokenType::RO);

                        if (E()) {

                            if(_lexer.peek(1).tokenType == TokenType::closePara){
                                expect(TokenType::closePara);

                                if(_lexer.peek(1).tokenType == TokenType::karo){
                                
                                    expect(TokenType::karo);


                                    if(Stmts()) {
                                        
                                        if(_lexer.peek(1).tokenType == TokenType::bas){
                                            expect(TokenType::bas);

                                            if(_lexer.peek(1).tokenType == TokenType::karo){
                                                expect(TokenType::karo);
                                                return true;
                                            }
                                            
                                        }
                                        
                                    }
                                    
                                }
                            }

                        }
                    }
                }

            }
        }

    }

    return false;
    
    
}
                            


        

bool parser :: Stmts(){
    
}

bool parser :: Stmt(){
    
}
bool parser :: Start(){
    
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