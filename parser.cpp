#include "parser.h"
int COUNT = 0;
string reserved1[] = {
    "END_OF_FILE",
	"ERROR",
	"markazi","kaam","karo","rakho","jab","tak","bas","agar","to","warna","phir",
	"dekhao","lo","chalao","wapas","bhaijo","adad","khali","khatam",
	"plus","minus","mul","div","mod",
	"pipe","colon","semi_colon","at","openPara","closePara",
	"ID","NUM","assign","STR","RO","INPUT","OUTPUT","cmnt"
};


void printTabs(int tabs){
    for(int i=0; i< tabs; i++){
        cout << "\t" ;
    }
}
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
    this->readAndPrintAllInput();
    _lexer.setCurrentPointer(0);

    fout1.open ("symbol_table.txt", ios::trunc); 
    fout1 << "ID    Type\n";

    fout2.open ("TAC.txt", ios::trunc); 
   
    tabsCount = 0;
    cout << "\n\nNow Parsing...\n\n";
}


void parser::readAndPrintAllInput() //read and print all inputs (provided)
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

    tabsCount++;
    printTabs(tabsCount);
    cout << "C\n";



    if (_lexer.peek(1).tokenType == TokenType::semi_colon){

        tabsCount++;
       
        printTabs(tabsCount);
        cout << ";\n";
       
        expect(TokenType::semi_colon);


        tabsCount--;
        Comment();
        tabsCount++;

        tabsCount--;
        tabsCount--;

        return true;
        
       
    }
    tabsCount--;
    return false;

}

bool parser :: Comment(){

    tabsCount++;
    printTabs(tabsCount);
    cout << "Comment\n";



    if (_lexer.peek(1).tokenType == TokenType::cmnt){
        tabsCount++;
        printTabs(tabsCount);
        cout << "Cmnt\n";
        expect(TokenType::cmnt);
        tabsCount--;
    }
    tabsCount--;
    return true;
}

bool parser ::E(string &s)
{

    tabsCount++;
    printTabs(tabsCount);
    cout << "E\n";

    if (R(s))
    {

        string i = s;
        if (_E(s, i))
        {
            tabsCount--;
            // fout2 << s << endl;
            return true;
        }
    }

    tabsCount--;
    return false;
}

bool parser ::_E(string &s, string &i)
{

    tabsCount++;
    printTabs(tabsCount);
    cout << "E'\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::plus)
    {

        printTabs(tabsCount);
        cout << "+\n";

        expect(TokenType::plus);
        tabsCount--;

        if (R(s))
        {
            string var = newTemp();
            fout2 << var << "=" << i << "+" << s << endl;
            i = var;

            if (_E(s, i))
            {
                tabsCount--;
                return true;
            }
            else
            {
                tabsCount--;
                return false;
            }
        }
        else
        {
            tabsCount--;
            expect(TokenType::plus);
            return false;
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::minus)
    {

        expect(TokenType::minus);

        printTabs(tabsCount);
        cout << "-\n";

        tabsCount--;

        if (R(s))
        {
            string var = newTemp();
            fout2 << var << "=" << i << "-" << s << endl;
            i = var;

            if (_E(s, i))
            {
                tabsCount--;
                return true;
            }
            else
            {
                tabsCount--;
                return false;
            }
        }
        else
        {
            tabsCount--;
            expect(TokenType::minus);
            return false;
        }
    }
    else
    {
        s = i;
        tabsCount--;
        tabsCount--;
        return true;
    }
}

bool parser ::R(string &s)
{

    tabsCount++;
    printTabs(tabsCount);
    cout << "R\n";

    if (T(s))
    {
        string i = s;
        if (_R(s, i))
        {
            tabsCount--;
            return true;
        }
    }
    tabsCount--;
    return false;
}

bool parser ::_R(string &s, string &i)
{

    tabsCount++;
    printTabs(tabsCount);
    cout << "R'\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::mul)
    {

        printTabs(tabsCount);
        cout << "*\n";

        tabsCount--;
        expect(TokenType::mul);
        T(s);

        string var = newTemp();
        fout2 << var << "=" << i << "*" << s << endl;
        i = var;

        _R(s, i);
        tabsCount++;
        tabsCount--;
        tabsCount--;
        return true;
    }
    else if (_lexer.peek(1).tokenType == TokenType::div)
    {
        printTabs(tabsCount);
        cout << "*\n";
        expect(TokenType::div);

        tabsCount--;
        T(s);

        string var = newTemp();
        fout2 << var << "=" << i << "/" << s << endl;
        i = var;

        _R(s, i);
        tabsCount++;
        tabsCount--;
        tabsCount--;
        return true;
    }
    else if (_lexer.peek(1).tokenType == TokenType::mod)
    {
        printTabs(tabsCount);
        cout << "*\n";

        expect(TokenType::mod);

        tabsCount--;
        T(s);

        string var = newTemp();
        fout2 << var << "=" << i << "%" << s << endl;
        i = var;

        _R(s, i);
        tabsCount++;
        tabsCount--;
        tabsCount--;
        return true;
    }
    else
    {
        s = i;
        tabsCount--;
        tabsCount--;
        return true;
    }
}

bool parser ::T(string &s)
{

    tabsCount++;
    printTabs(tabsCount);
    cout << "T\n";

    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::ID)
    {

        printTabs(tabsCount);
        cout << "ID\n";
        tabsCount--;
        tabsCount--;

        s = _lexer.peek(1).lexeme;

        expect(TokenType::ID);
        return true;
    }
    else if (_lexer.peek(1).tokenType == TokenType::NUM)
    {

        printTabs(tabsCount);
        cout << "NUM\n";
        tabsCount--;
        tabsCount--;

        s = _lexer.peek(1).lexeme;

        expect(TokenType::NUM);
        return true;
    }
    else if (_lexer.peek(1).tokenType == TokenType::openPara)
    {

        printTabs(tabsCount);
        cout << "openPara\n";

        tabsCount--;

        expect(TokenType::openPara);

        E(s);
        tabsCount++;

        if (_lexer.peek(1).tokenType == TokenType::closePara)
        {
            printTabs(tabsCount);
            cout << "closedPara\n";
            tabsCount--;
            tabsCount--;
            expect(TokenType::closePara);
            return true;
        }
        else
        {

            expect(TokenType::closePara);
        }
    }
    else
    {

        tabsCount--;
        tabsCount--;
        expect(TokenType::ID);
        return false;
    }
}

bool parser :: F() {    

    tabsCount++;
    printTabs(tabsCount);
    cout << "F\n";

    tabsCount++;

    if (_lexer.peek(1).tokenType==TokenType::kaam)
    {
    
        printTabs(tabsCount);
        cout << "Kaam\n";

        expect(TokenType::kaam);
        tabsCount--;
        Func();
        tabsCount++;

        if(_lexer.peek(1).tokenType==TokenType::at) {

            printTabs(tabsCount);
            cout << "at\n";

            expect(TokenType::at);
            tabsCount--;
            Functype();
            tabsCount++;

            if (_lexer.peek(1).tokenType==TokenType::openPara)
            {
                printTabs(tabsCount);
                cout << "openPara\n";

                expect(TokenType::openPara);
                tabsCount--;
                P();
                tabsCount++;

                
                if (_lexer.peek(1).tokenType==TokenType::closePara)
                {
                    printTabs(tabsCount);
                    cout << "closePara\n";

                    expect(TokenType::closePara);

                    if (_lexer.peek(1).tokenType==TokenType::karo)
                    {
                        printTabs(tabsCount);
                        cout << "karo\n";

                        expect(TokenType::karo);

                        tabsCount--;

                        Stmts();
                        tabsCount++;


                        if (_lexer.peek(1).tokenType==TokenType::kaam)
                        {
                            printTabs(tabsCount);
                            cout << "kaam\n";

                            expect(TokenType::kaam);

                            if (_lexer.peek(1).tokenType==TokenType::khatam)
                            {
                                printTabs(tabsCount);
                                cout << "Khatam\n";
                                tabsCount--;

                                expect(TokenType::khatam);
                                tabsCount--;
                                return true;

                            }else{
                                expect(TokenType::khatam);
                            }
                            
                            
                        }else {
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

        
    }
    tabsCount--;
    return false;
    
}

bool parser :: Func() {

    tabsCount++;
    printTabs(tabsCount);
    cout << "Func\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::markazi)
    {
        printTabs(tabsCount);
        cout << "markazi\n";
        tabsCount--;
        tabsCount--;
        this->id = "markazi";
        expect(TokenType::markazi);

        return true;
        
        
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        printTabs(tabsCount);
        cout << "ID\n";
        tabsCount--;
        tabsCount--;

        this->id = _lexer.peek(1).lexeme;
        expect(TokenType::ID);


       return true;
    }
    tabsCount--;
    tabsCount--;
    expect(TokenType::markazi);
    return false;
    
}

bool parser :: Functype() {

    tabsCount++;
    printTabs(tabsCount);
    cout << "Functype\n";
    tabsCount++;
    
    if (_lexer.peek(1).tokenType == TokenType::adad)
    {
        printTabs(tabsCount);
        cout << "adad\n";
        tabsCount--;
        tabsCount--;

         
        fout1 << id << " " << "adad\n";
    

       
        expect(TokenType::adad);

        return true;
    }
    else if (_lexer.peek(1).tokenType == TokenType::khali)
    {
        printTabs(tabsCount);
        cout << "khali\n";
        tabsCount--;
        tabsCount--;

        fout1 << id << " " << "khali\n";
        expect(TokenType::khali);
        return true;
    }
    
    tabsCount--;
    tabsCount--;
    expect(TokenType::adad);
    return false;
    

}

bool parser :: P(){
    
    
    tabsCount++;
    printTabs(tabsCount);
    cout << "P\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        printTabs(tabsCount);
        cout << "ID\n";
       

        this->id = _lexer.peek(1).lexeme;
        expect(TokenType::ID);

        if (_lexer.peek(1).tokenType == TokenType::at)
        {
            printTabs(tabsCount);
            cout << "at\n";

            expect(TokenType::at);
            tabsCount--;
            Datatype() ;
            A();
            tabsCount++;
            
            tabsCount--;
            tabsCount--;
        
            return true;
            
           
        }else{
            expect(TokenType::at);
        }

        return false;
    }
    else
    {
        tabsCount--;
        tabsCount--;
       return true;
    }
    
}


bool parser :: A(){
    
    tabsCount++;
    printTabs(tabsCount);
    cout << "A\n";
    tabsCount++;

    if(_lexer.peek(1).tokenType == TokenType::pipe)
    {
        expect(TokenType::pipe);

        printTabs(tabsCount);
        cout << "pipe\n";

        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            this->id = _lexer.peek(1).lexeme;
            expect(TokenType::ID);

            printTabs(tabsCount);
            cout << "ID\n";

            if (_lexer.peek(1).tokenType == TokenType::at)
            {
                printTabs(tabsCount);
                cout << "at\n";

                expect(TokenType::at);

                tabsCount--;
                Datatype();
                A();
                tabsCount++;

                tabsCount--;
                tabsCount--;
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
        printTabs(tabsCount);
        cout << "^\n";
        tabsCount--;
        tabsCount--;
        return true;
    }
    
}

bool parser :: Datatype(){

    tabsCount++;
    printTabs(tabsCount);
    cout << "Datatype\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::adad ){
        fout1 << id << " " << "adad\n";

        printTabs(tabsCount);
        cout << "adad\n";
        tabsCount--;
        tabsCount--;

        expect(TokenType::adad);
        return true;

    }else{
        expect(TokenType::adad);
    }

    tabsCount--;
    tabsCount--;
    return false;
}

bool parser :: V() {
    string v = "";
    tabsCount++;
    printTabs(tabsCount);
    cout << "V\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::rakho ){
        expect(TokenType::rakho);

        printTabs(tabsCount);
        cout << "rakho\n";

         if (_lexer.peek(1).tokenType == TokenType::ID ){

            this->id = _lexer.peek(1).lexeme;
            expect(TokenType::ID);

            printTabs(tabsCount);
            cout << "ID\n";

            if (_lexer.peek(1).tokenType == TokenType::at ){
                expect(TokenType::at);
                
                printTabs(tabsCount);
                cout << "at\n";

                tabsCount--;

                if (Datatype()){
                    

                    if(B(v)){

                        // intermediate code generation
                        if (v != ""){
                            fout2 << this->id << " " << v << endl;
                        }

                        tabsCount++;

                        
                            
                        tabsCount--;

                        Comment();

                        tabsCount++;

                        tabsCount--;
                        tabsCount--;
                        return true;


                        
                    }
                }


                    
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
        tabsCount--;
        tabsCount--;
        return false;
    }
    

        

}
        

bool parser :: B(string& v) {

    tabsCount++;
    printTabs(tabsCount);
    cout << "B\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::assign ){
        printTabs(tabsCount);
        cout << ":=\n";

        expect(TokenType::assign);
        tabsCount--;
        if ( O(v)) {
            // intermediate code generation
            v = "= " + v;

            tabsCount++;
            tabsCount--;
            tabsCount--;
            return true;
        }
        else
        {
            tabsCount--;
            tabsCount--;
            return false;
        }
        
    }
    else if(_lexer.peek(1).tokenType == TokenType::semi_colon)
    {
        printTabs(tabsCount);
        cout << ";\n";
        tabsCount--;
        tabsCount--;
        
        // intermediate code generation
        v = "";
        expect(TokenType::semi_colon);
        return true;
    }
    else
    {
        tabsCount--;
        tabsCount--;
        syntax_error(_lexer.peek(1).tokenType);
        return false;
    }
    
}

bool parser :: O(string& v) {

    tabsCount++;
    printTabs(tabsCount);
    cout << "O\n";
    

    if(FC(v))
    {
        tabsCount--;
        return true;

    }
    else if (E(v)) {

        tabsCount++;
        if (_lexer.peek(1).tokenType == TokenType::semi_colon)
        {
            printTabs(tabsCount);
            cout << ";\n";
            tabsCount--;
            tabsCount--;
            expect(TokenType::semi_colon);
            return true;
        }else
        {
            tabsCount--;
            tabsCount--;
            expect(TokenType::semi_colon);
        }
        
    }
    else
    {
        tabsCount--;
        return false;
    }
    
}


bool parser :: FC(string& v){
    int c = 0;
    string id_lex = "";

    tabsCount++;
    printTabs(tabsCount);
    cout << "FC\n";
    tabsCount++;
    
    if (_lexer.peek(1).tokenType == TokenType::chalao)
    {
        printTabs(tabsCount);
        cout << "chalao\n";
        expect(TokenType::chalao);
        
        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            printTabs(tabsCount);
            cout << "ID\n";
            id_lex = _lexer.peek(1).lexeme;

            expect(TokenType::ID);

            if (_lexer.peek(1).tokenType == TokenType::openPara)
            {
                printTabs(tabsCount);
                cout << "openPara\n";

                expect(TokenType::openPara);
                tabsCount--;
                Z(c);
                tabsCount++;

                if (_lexer.peek(1).tokenType == TokenType::closePara)
                {
                    expect(TokenType::closePara);

                    printTabs(tabsCount);
                    cout << "closePara\n";
                    
                    if (_lexer.peek(1).tokenType == TokenType::semi_colon)
                    {
                        printTabs(tabsCount);
                        cout << ";\n";
                        expect(TokenType::semi_colon);

                        tabsCount--;
                        
                        Comment();

                        tabsCount++;

                        tabsCount--;
                        tabsCount--;

                        // intermediate code generation
                        string var = newTemp();
                        fout2 << "call " << id_lex << " " << c << " " << var << endl;
                        v = var;

                        return true;
                    
                    } else{
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
    tabsCount--;
    tabsCount--;
    return false;
    
}

bool parser :: Z(int &c){
    string v = "";
    tabsCount++;
    printTabs(tabsCount);
    cout << "Z\n";
    
    if(_lexer.peek(1).tokenType != TokenType::closePara &&  E(v))
    {
        // intermediate code generation
        fout2 << "param " << v << endl;

        U(c);
        tabsCount--;
    }
    else
    {
        // intermediate code generation
        c = 0;
        tabsCount--;
        return true;
    }
   
}

bool parser :: U(int &c){
    
    int _c = 0;
    string v = "";

    tabsCount++;
    printTabs(tabsCount);
    cout << "U\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::pipe)
    {
        printTabs(tabsCount);
        cout << "|\n";
        expect(TokenType::pipe);
        tabsCount--;

        E(v);
        // intermediate code generation
        fout2 << "param " << v << endl;

        U(_c);
        // intermediate code generation
        c = _c + 1;

        tabsCount--;
        return true;
       
    }
    else {
        tabsCount--;
        tabsCount--;
        // intermediate code generation
        c = 1;
        return true;
    }
    
}

bool parser :: print(){
    
    tabsCount++;
    printTabs(tabsCount);
    cout << "print\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::dekhao)
    {
        printTabs(tabsCount);
        cout << "dekhao\n";

        expect(TokenType::dekhao);

        if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
        {
            printTabs(tabsCount);
            cout << "<<\n";
            expect(TokenType::OUTPUT);

            tabsCount--;

            if(G()) {

                if(H()) {
                    tabsCount++;

                    if (_lexer.peek(1).tokenType == TokenType::semi_colon)
                    {
                        printTabs(tabsCount);
                        cout << ";\n";

                        expect(TokenType::semi_colon);

                        tabsCount--;

                        Comment();

                        tabsCount++;

                        tabsCount--;
                        tabsCount--;


                        return true;
                        
                    }
                    else
                    {
              
                        expect(TokenType::semi_colon);
                    }

                }
            }
          
            
        }
        else
        {
            expect(TokenType::OUTPUT);
        }
        
    }
    else
    {
        tabsCount--;
        tabsCount--;
        return false;
    }
    
}

bool parser :: H(){
    
    tabsCount++;
    printTabs(tabsCount);
    cout << "H\n";
    tabsCount++;

    if(_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        printTabs(tabsCount);
        cout << "<<\n";
        expect(TokenType::OUTPUT);
        tabsCount--;
        if(G()){

            if(H()){
                tabsCount--;

                return true;
                
            }
        }
        
        tabsCount--;
       
       return false;
        
    }
    else
    {
        tabsCount--;
        tabsCount--;
        return true;
    }

}

bool parser :: G(){
    
    // G -> str | E
    string v = "";
    tabsCount++;
    printTabs(tabsCount);
    cout << "G\n";
    

    if (_lexer.peek(1).tokenType == TokenType::STR)
    {
        tabsCount++;
        printTabs(tabsCount);
        cout << "STR\n";
      
        // intermediate code generation
        fout2 << "out " << '"'<< _lexer.peek(1).lexeme << '"'<< endl;

        expect(TokenType::STR);
        tabsCount--;
        tabsCount--;

        return true;
    }
    else if (E(v))
    {
        // intermediate code generation
        fout2 << "out " << v << endl;

        tabsCount--;
        return true;
    }
    tabsCount--;
   
    return false;
    
    
}

bool parser :: input(){

    tabsCount++;
    printTabs(tabsCount);
    cout << "input\n";
    tabsCount++;

    // input -> lo H >> Var I ;
    if(_lexer.peek(1).tokenType == TokenType::lo)
    {
        printTabs(tabsCount);
        cout << "lo\n";
        expect(TokenType::lo);
       
        tabsCount--;
        if (H())
        {
            tabsCount++;

            if(_lexer.peek(1).tokenType == TokenType::INPUT){

                printTabs(tabsCount);
                cout << ">>\n";

                tabsCount--;
                expect(TokenType::INPUT);

                if(Var() && I()){
                    tabsCount++;

                  

                    if (_lexer.peek(1).tokenType == TokenType::semi_colon)
                    {
                        printTabs(tabsCount);
                        cout << ";\n";

                        expect(TokenType::semi_colon);

                        tabsCount--;

                        Comment();

                        tabsCount++;
                        
                        tabsCount--;
                        tabsCount--;
                        
                        return true;
                        

                    }
                    else
                    {
                        expect(TokenType::semi_colon);
                    }
                    
                    

                }
            }
          
            
        }
        else
        {
            expect(TokenType::INPUT);
        }
        
       
        
    }
    tabsCount--;
    tabsCount--;
    return false;
    
    
}

bool parser :: I(){


    tabsCount++;
    printTabs(tabsCount);
    cout << "I\n";

    if (_lexer.peek(1).tokenType == TokenType::INPUT)
    {
        tabsCount++;
        expect(TokenType::INPUT);
        tabsCount--;
        if(Var() && I()){
            tabsCount--;
            return true;
        }

        tabsCount--;

        return false;

    }
    else
    {
        tabsCount--;
        return true;
    }
    
}

bool parser :: Var(){

    tabsCount++;
    printTabs(tabsCount);
    cout << "Var\n";
    

    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        
        tabsCount++;
        printTabs(tabsCount);
        cout << "ID\n";

         // intermediate code generation
        fout2 << "in " << _lexer.peek(1).lexeme << endl;

        expect(TokenType::ID);
        tabsCount--;

    

        if(J()){
            tabsCount--;
            return true;

        }
       
    }
    tabsCount--;
    return false;
    
}

bool parser :: J(){

    tabsCount++;
    printTabs(tabsCount);
    cout << "J\n";
    
    
    if (_lexer.peek(1).tokenType == TokenType::at)
    {
        tabsCount++;
        printTabs(tabsCount);
        cout << "at\n";

        expect(TokenType::at);
        tabsCount--;
        if(Datatype()){
            
            tabsCount--;
            return true;
        }
        tabsCount--;
        return false;
    }
    else
    {
        tabsCount--;
        return true;
    }
    
}

bool parser :: Conditional() {
    string v = "";
    tabsCount++;
    printTabs(tabsCount);
    cout << "Conditional\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::agar ){
        
        printTabs(tabsCount);
        cout << "agar\n";

        expect(TokenType::agar);

        if(_lexer.peek(1).tokenType == TokenType::openPara){

            printTabs(tabsCount);
            cout << "openPara\n";

            expect(TokenType::openPara);

            tabsCount--;
            E(v);
            tabsCount++;
            

            if(_lexer.peek(1).tokenType == TokenType::RO){ 

                printTabs(tabsCount);
                cout << "RO\n";

                expect(TokenType::RO);

                tabsCount--;
                E(v);
                tabsCount++;
               

                if(_lexer.peek(1).tokenType == TokenType::closePara){

                    printTabs(tabsCount);
                    cout << "closePara\n";

                    expect(TokenType::closePara);

                    if(_lexer.peek(1).tokenType == TokenType::to){

                        printTabs(tabsCount);
                        cout << "to\n";

                        expect(TokenType::to);



                        if(_lexer.peek(1).tokenType == TokenType::phir) {

                            printTabs(tabsCount);
                            cout << "phir\n";

                            expect(TokenType::phir);

                            if(_lexer.peek(1).tokenType == TokenType::karo){
                                
                                printTabs(tabsCount);
                                cout << "karo\n";

                                expect(TokenType::karo);

                                tabsCount--;

                                Stmts();
                                ElseIf();
                                Else();

                                tabsCount++;
                               
                             

                                if(_lexer.peek(1).tokenType == TokenType::bas){

                                    printTabs(tabsCount);
                                    cout << "bas\n";

                                    expect(TokenType::bas);



                                    if(_lexer.peek(1).tokenType == TokenType::karo){

                                        printTabs(tabsCount);
                                        cout << "karo\n";

                                        expect(TokenType::karo);

                                        tabsCount--;
                                        tabsCount--;

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


                

            }else {

                expect(TokenType::RO);
            }
            

        }else{

            expect(TokenType::openPara);
        }
    }
    else
    {
        tabsCount--;
        tabsCount--;
        return false;
    }
    

    
}

bool parser :: ElseIf() {
    string v = "";
    tabsCount++;
    printTabs(tabsCount);
    cout << "ElseIf\n";
    tabsCount++;

    if(_lexer.peek(1).tokenType == TokenType::warna){

        printTabs(tabsCount);
        cout << "warna\n";

        expect(TokenType::warna);

        if(_lexer.peek(1).tokenType == TokenType::agar){

            printTabs(tabsCount);
            cout << "agar\n";

            expect(TokenType::agar);

            if(_lexer.peek(1).tokenType == TokenType::openPara){

                printTabs(tabsCount);
                cout << "openPara\n";

                expect(TokenType::openPara);

                tabsCount--;
                E(v);
                tabsCount++;
               

                if(_lexer.peek(1).tokenType == TokenType::RO){ 

                    printTabs(tabsCount);
                    cout << "RO\n";

                    expect(TokenType::RO);

                    tabsCount--;
                    E(v);
                    tabsCount++;
                 

                    if(_lexer.peek(1).tokenType == TokenType::closePara){

                        printTabs(tabsCount);
                        cout << "closePara\n";

                        expect(TokenType::closePara);

                        if(_lexer.peek(1).tokenType == TokenType::to){

                            printTabs(tabsCount);
                            cout << "to\n";
                        
                            expect(TokenType::to);


                            if(_lexer.peek(1).tokenType == TokenType::phir){

                                printTabs(tabsCount);
                                cout << "phir\n";

                                
                                expect(TokenType::phir);

                                tabsCount--;
                                Stmts();
                               
                                bool x = ElseIf();
                                tabsCount++;

                                tabsCount--;
                                tabsCount--;
                                return x;
                                
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
            tabsCount--;
            tabsCount--;
            _lexer.setCurrentPointer(_lexer.getCurrentPointer()-1);
            return false;
        }

        

    }
    else {

        tabsCount--;
        tabsCount--;


        return true;
    }
}

bool parser :: Else() {

    tabsCount++;
    printTabs(tabsCount);
    cout << "Else\n";
    tabsCount++;

    if(_lexer.peek(1).tokenType == TokenType::warna){

        printTabs(tabsCount);
        cout << "warna\n";

        expect(TokenType::warna);

        if(_lexer.peek(1).tokenType == TokenType::phir){

            printTabs(tabsCount);
            cout << "phir\n";

            expect(TokenType::phir);

            tabsCount--;
            Stmts();
            tabsCount++;
          
            tabsCount--;
            tabsCount--;

            return true;
            

        }else{
            expect(TokenType::phir);
        }

        
        
    }
    else{

        tabsCount--;
        tabsCount--;

        return true;
    }

}

bool parser :: While() {
    string v = "";
    tabsCount++;
    printTabs(tabsCount);
    cout << "While\n";
    tabsCount++;


    if(_lexer.peek(1).tokenType == TokenType::jab) {

        printTabs(tabsCount);
        cout << "Jab\n";

        expect(TokenType::jab);

        if(_lexer.peek(1).tokenType == TokenType::tak) {

            printTabs(tabsCount);
            cout << "tak\n";

            expect(TokenType::tak);

            if(_lexer.peek(1).tokenType == TokenType::openPara){

                printTabs(tabsCount);
                cout << "openPara\n";

                expect(TokenType::openPara);

                tabsCount--;
                E(v);
                tabsCount++;
               

                if(_lexer.peek(1).tokenType == TokenType::RO){ 

                    printTabs(tabsCount);
                    cout << "RO\n";

                    expect(TokenType::RO);

                    tabsCount--;
                    E(v);
                    tabsCount++;
                   

                    if(_lexer.peek(1).tokenType == TokenType::closePara){

                        printTabs(tabsCount);
                        cout << "closePara\n";

                        expect(TokenType::closePara);

                        if(_lexer.peek(1).tokenType == TokenType::karo){

                            printTabs(tabsCount);
                            cout << "karo\n";
                        
                            expect(TokenType::karo);

                            tabsCount--;
                            
                            Stmts();
                            tabsCount++;

                      
                                
                            if(_lexer.peek(1).tokenType == TokenType::bas){

                                printTabs(tabsCount);
                                cout << "bas\n";

                                expect(TokenType::bas);

                                if(_lexer.peek(1).tokenType == TokenType::karo){

                                    printTabs(tabsCount);
                                    cout << "karo\n";

                                    tabsCount--;
                                    tabsCount--;
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
    else
    {
        tabsCount--;
        tabsCount--;
        return false;
    }
    


    
}
                            
bool parser :: K() {
    string v = "" , id_lex = "";
    tabsCount++;
    printTabs(tabsCount);
    cout << "K\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::ID ) {

        printTabs(tabsCount);
        cout << "ID\n";
        id_lex = _lexer.peek(1).lexeme;

        expect(TokenType::ID);

        tabsCount--;
        Y(v);
        // intermediate code generation
        if (v != ""){
            fout2 << id_lex << " " << v << endl;
        }
        
        tabsCount++;
        
        if (_lexer.peek(1).tokenType == TokenType::cmnt){
            expect(TokenType::cmnt);

        }

        tabsCount--;
        tabsCount--;
        return true;
            
        
    }
    tabsCount--;
    tabsCount--;
    return false;
}


bool parser :: Stmts() {

    if(_lexer.peek(1).tokenType == TokenType::END_OF_FILE) {
        return true;
    }

    tabsCount++;
    printTabs(tabsCount);
    cout << "Stmts\n";
    

    if(Stmt()) {

       bool x = Stmts();
       tabsCount--;
       return x;
    }
    else {
        tabsCount--;
        return true;

    }
}

bool parser :: W(){

    tabsCount++;
    printTabs(tabsCount);
    cout << "W\n";
    string v = "";
    tabsCount++;

    if(_lexer.peek(1).tokenType == TokenType::wapas) {
        expect(TokenType::wapas);

        printTabs(tabsCount);
        cout << "wapas\n";

        if(_lexer.peek(1).tokenType == TokenType::bhaijo) {
            expect(TokenType::bhaijo);

            printTabs(tabsCount);
            cout << "bhaijo\n";

            tabsCount--;

            if(E(v)) {
                
                tabsCount++;

                if(_lexer.peek(1).tokenType == TokenType::semi_colon) {
                    expect(TokenType::semi_colon);

                    printTabs(tabsCount);
                    cout << "semi_colon\n";
                    
                    // intermediate code generation
                    fout2 << "ret " << v << endl;

                    tabsCount--;

                    Comment();

                    tabsCount++;

                    tabsCount--;
                    tabsCount--;

                    return true;
                    
                }else {
                    expect(TokenType::semi_colon);
                }

            }else{
                tabsCount++;
                syntax_error(_lexer.peek(1).tokenType);
                return false;
            }

           

        }else{
            expect(TokenType::bhaijo);
        }
    }
    tabsCount--;
    tabsCount--;
}
bool parser:: Y(string& v){

    tabsCount++;
    printTabs(tabsCount);
    cout << "Y\n";
    tabsCount++;

    if (_lexer.peek(1).tokenType == TokenType::assign ){
        printTabs(tabsCount);
        cout << ":=\n";

        expect(TokenType::assign);
        tabsCount--;
        if ( O(v)) {
             v = "= " + v;

            tabsCount++;
            tabsCount--;
            tabsCount--;
            return true;
        }
        else
        {
            tabsCount--;
            tabsCount--;
            syntax_error(_lexer.peek(1).tokenType);
            return false;
        }
        
    }else{
        tabsCount--;
        tabsCount--;
        syntax_error(_lexer.peek(1).tokenType);
        return false;
    }
}

string parser ::newTemp()
{
    string str = "t" + to_string(COUNT);
    COUNT++;
    return str;
}

bool parser :: Stmt() {
    string v = "";

    int i = _lexer.getCurrentPointer();
    tabsCount++;
    printTabs(tabsCount);
    cout << "Stmt\n";

    if(K()){
        tabsCount--;
        return true;
    }
    _lexer.setCurrentPointer(i);
    if( C() ) {
        tabsCount--;
        return true;
    }
     _lexer.setCurrentPointer(i);
    if( V() ) {
        tabsCount--;
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(FC(v)) {
        tabsCount--;
        return true;
    }

    if(W()){
        tabsCount--;
        return true;
    }
     _lexer.setCurrentPointer(i);

    if(print()){
        tabsCount--;
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(input()){
        tabsCount--;
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(Conditional()){
        tabsCount--;
        return true;
    }
     _lexer.setCurrentPointer(i);
    if(While()) {
        tabsCount--;
        return true;
    }
    _lexer.setCurrentPointer(i);
   

    tabsCount--;
    return false;
}


bool parser :: Start() {

    tabsCount++;
    printTabs(tabsCount);
    cout << "Start\n";

    if(_lexer.peek(1).tokenType == TokenType::END_OF_FILE) {
        
        fout1.close();
        return true;
    }
    if( F() ) {

       return Start();

    }else if(C()){
        return Start();
    }
    else {
        cout << "Syntax Error\n";
        exit(1);
    }

    
    

}
