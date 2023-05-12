#include "parser.h"
#include <sstream>
#include <iostream>
#include <unordered_map>
using namespace std;

int s_index = 2;

vector<string> getTac()
{
    vector<string> arr;
    ifstream fin1;
    fin1.open("TAC.txt", ios::in);
    string tp;
    while (getline(fin1, tp))
    {
        arr.push_back(tp);
    }
    fin1.close();
    return arr;
}

vector<vector<string> > getSymTab()
{
    vector<vector<string> > ST;

    vector<string> arr;
    ifstream fin2;
    fin2.open("symbol_table.txt", ios::in);
    string tp;
    while (getline(fin2, tp))
    {
        arr.push_back(tp);
    }
    fin2.close();

    vector<string> tokens;
    for (int x = 0; x < arr.size(); x++)
    {
        stringstream check1(arr[x]);
        string intermediate;

        // Tokenizing w.r.t. space ' '
        while (getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }

        ST.push_back(tokens);
        tokens.clear();
    }

    return ST;
}

vector<string> output(vector<string> instruction)
{

    vector<string> ins;
    ins.push_back("out");
    string s = instruction[1];
    
    if (int(s[0]) == 34){
        ins.push_back(s.substr(0,1));
        ins.push_back(s.substr(1,s.length()-2));
        ins.push_back(s.substr(s.length()-1,1));
    }
    else
        ins.push_back(s);

    return ins;
}

vector<string> input(vector<string> instruction)
{
    vector<string> ins;
    ins.push_back(instruction[0]);
    ins.push_back(instruction[1]);
    // cout << instruction[0] << " " << instruction[1] << endl;

    return ins;
}

vector<string> _goto(vector<string> instruction)
{
    vector<string> ins;
    ins.push_back(instruction[0]);
    ins.push_back(instruction[1]);
    // cout << instruction[0] << " " << instruction[1] << endl;

    return ins;
}

vector<string> variable(vector<string> instruction)
{
    vector<string> ins;

    if (instruction.size() == 5)
    {
        // t1 = x + y
        ins.push_back(instruction[3]);
        ins.push_back(instruction[2]);
        ins.push_back(instruction[4]);
        ins.push_back(instruction[0]);

        // cout << instruction[3] << " " << instruction[2] << " " << instruction[4] << " " << instruction[0] << endl;
    }
    else if (instruction.size() == 3)
    {
        // z = t1
        ins.push_back("mov");
        ins.push_back(instruction[0]);
        ins.push_back(instruction[2]);
        // cout <<  "mov " << instruction[0] << " " << instruction[2]  << endl;
    }

    return ins;
}

vector<string> _conditional(vector<string> instruction)
{

    vector<string> ins;
    ins.push_back(instruction[2]);
    ins.push_back(instruction[1]);
    ins.push_back(instruction[3]);
    ins.push_back(instruction[5]);

    // cout << instruction[2] << " " << instruction[1] << " " << instruction[3] << " " << instruction[5] << endl;

    return ins;
}

vector<string> ret(vector<string> instruction)
{
    vector<string> ins;
    ins.push_back(instruction[0]);
    ins.push_back(instruction[1]);
    // cout << instruction[0] << " " << instruction[1] << endl;

    return ins;
}

vector<string> convertToMachineCode(vector<string> instruction)
{

    if (instruction[0] == "out")
    {
        return output(instruction);
    }
    else if (instruction[0] == "in")
    {
        return input(instruction);
    }
    else if (instruction[0] == "goto")
    {
        return _goto(instruction);
    }
    else if (instruction[0] == "if")
    {
        return _conditional(instruction);
    }
    else if (instruction[0] == "ret")
    {
        return ret(instruction);
    }
    else
    {
        return variable(instruction);
    }
}

void tokenize(vector<string> Tac, vector<vector<string> > & machineCode)
{
    vector<string> tokens;
    for (int x = 0; x < Tac.size(); x++)
    {
        if (Tac[x].substr(0, 3) == "out")
        {

            tokens.push_back(Tac[x].substr(0, 3));
            tokens.push_back(Tac[x].substr(4, Tac[x].length() - 4));
        }
        else
        {

            stringstream check1(Tac[x]);
            string intermediate;

            // Tokenizing w.r.t. space ' '
            while (getline(check1, intermediate, ' '))
            {
                tokens.push_back(intermediate);
            }
        }

        machineCode.push_back(convertToMachineCode(tokens));
        tokens.clear();
    }
}

void fillmap(unordered_map<string, int> &map, vector<vector<string> > ST, vector<int> &ds)
{
    for (int i = 2, j = 0; i < ST.size(); i++, j++)
    {
        string var = ST[i][0];
        ds.push_back(stoi(ST[i][3]));
        map[ST[i][0]] = ds.size() - 1;
        // cout << ST[i][0] << " " << map[ST[i][0]] << " " << ds[map[ST[i][0]]] << endl;
    }
}
void checkVariableExistance(unordered_map<string, int> &map , string variable){
    if (map.find(variable) == map.end()){
        cout << "Semantic Error: '" << variable << "' not declared\n";
        exit(0);   
    }
}
bool isNumericString(string variable){

    for (char c : variable) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
int getOperandData(unordered_map<string, int> &map ,vector<int> & ds,string operand){
    // check whether this operand is number or variable
    if (isNumericString(operand)){
        // it is a number
        return stoi(operand);

    }else{
        // it is a variable
        checkVariableExistance(map , operand);
        int i = map[operand];
        return ds[i];
    }
}
void executeCode(vector<vector<string> > ST, vector<vector<string> > machineCode)
{
    unordered_map<string, int> map;
    vector<int> ds;
    fillmap(map, ST, ds);

    // for (auto it = map.begin(); it != map.end(); it++) {

    //     cout << it->first << " " << map[it->first] << " " << ds[map[it->first]] << endl;
    // }
    int pc = 0;
    for ( pc = 0; pc < machineCode.size() ; ++pc) {

        if (machineCode[pc][0] == "+"){
            
            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);

            // now for the detination memory location
            checkVariableExistance(map , machineCode[pc][3]);
            int k = map[machineCode[pc][3]];

            ds[k] = firstOperand + secondOperand;

        }else if (machineCode[pc][0] == "-"){
            
            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);

            // now for the detination memory location
            checkVariableExistance(map , machineCode[pc][3]);
            int k = map[machineCode[pc][3]];
            
            ds[k] = firstOperand - secondOperand;

        }
        else if (machineCode[pc][0] == "*"){
            
            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);

            // now for the detination memory location
            checkVariableExistance(map , machineCode[pc][3]);
            int k = map[machineCode[pc][3]];
            
            ds[k] = firstOperand * secondOperand;

        }
        else if (machineCode[pc][0] == "/"){
            
            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);

            // now for the detination memory location
            checkVariableExistance(map , machineCode[pc][3]);
            int k = map[machineCode[pc][3]];
            
            ds[k] = firstOperand / secondOperand;

        }
        else if (machineCode[pc][0] == "%"){
            
            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);

            // now for the detination memory location
            checkVariableExistance(map , machineCode[pc][3]);
            int k = map[machineCode[pc][3]];
            
            ds[k] = firstOperand * secondOperand;

        }
        else if(machineCode[pc][0] == "goto"){

            pc = stoi(machineCode[pc][1]) - 2;
        }
        else if(machineCode[pc][0] == "LE"){
            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);
            
            int nextLineToJumpOn = stoi(machineCode[pc][3]);

            if (firstOperand <= secondOperand)
                pc = nextLineToJumpOn - 2;
        }
         else if(machineCode[pc][0] == "GE"){

            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);
            
            int nextLineToJumpOn = stoi(machineCode[pc][3]);

            if (firstOperand >= secondOperand)
                pc = nextLineToJumpOn - 2;
        }
        else if(machineCode[pc][0] == "LT"){

            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);
            
            int nextLineToJumpOn = stoi(machineCode[pc][3]);

            if (firstOperand < secondOperand)
                pc = nextLineToJumpOn - 2;

        }
        
        else if(machineCode[pc][0] == "GT"){

            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);
            
            int nextLineToJumpOn = stoi(machineCode[pc][3]);
            if (firstOperand > secondOperand)
                pc = nextLineToJumpOn - 2;

        }
        
        else if(machineCode[pc][0] == "EQ"){

            int firstOperand = getOperandData(map,ds,machineCode[pc][1]);
            int secondOperand = getOperandData(map,ds,machineCode[pc][2]);
            
            int nextLineToJumpOn = stoi(machineCode[pc][3]);

            if (firstOperand == secondOperand)
                pc = nextLineToJumpOn - 2;

        }
        
        else if(machineCode[pc][0] == "in"){

            checkVariableExistance(map , machineCode[pc][1]);
            int i = map[machineCode[pc][1]];
            cin >> ds[i];
        

        }
        
        else if(machineCode[pc][0] == "out"){

            if (int(machineCode[pc][1][0]) == 34 ){
                cout << machineCode[pc][2];
                
            }else{
               
                int value = getOperandData(map,ds,machineCode[pc][1]);
                cout << value;
            }
        }
        
        else if (machineCode[pc][0] == "mov"){

            checkVariableExistance(map , machineCode[pc][1]);
            int i = map[machineCode[pc][1]];
            ds[i] = getOperandData(map,ds,machineCode[pc][2]);

        }
        
        else if (machineCode[pc][0] == "ret"){
        
            exit(0);
        }
    }
}

int main()
{
    vector<string> Tac = getTac();
    vector<vector<string> > ST = getSymTab();
    vector<vector<string> > machineCode;
    tokenize(Tac, machineCode);

    for (int i = 0; i < machineCode.size(); i++)
    {
        for (int j = 0; j < machineCode[i].size(); j++)
        {
            cout << machineCode[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Executing ...\n";
    executeCode(ST, machineCode);

    // for (int i = 0; i < ST.size(); i++)
    // {
    //     cout << ST[i][0] << endl;
    // }

    // cout << stoi("147") << endl;


    return 0;
}