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

vector<vector<string>> getSymTab()
{
    vector<vector<string>> ST;

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

    if (int(s[0]) == 34)
        ins.push_back(s.substr(1, s.length() - 2));
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

void tokenize(vector<string> Tac, vector<vector<string>> &machineCode)
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

void fillmap(unordered_map<string, int> &map, vector<vector<string>> ST, vector<int> &ds)
{
    for (int i = 2, j = 0; i < ST.size(); i++, j++)
    {
        string var = ST[i][0];
        ds.push_back(stoi(ST[i][3]));
        map[ST[i][0]] = ds.size() - 1;
        // cout << ST[i][0] << " " << map[ST[i][0]] << " " << ds[map[ST[i][0]]] << endl;
    }
}

void generateDS(vector<vector<string>> ST, vector<vector<string>> machineCode)
{
    unordered_map<string, int> map;
    vector<int> ds;

    fillmap(map, ST, ds);
}

int main()
{
    vector<string> Tac = getTac();
    vector<vector<string>> ST = getSymTab();
    vector<vector<string>> machineCode;
    tokenize(Tac, machineCode);
    generateDS(ST, machineCode);

    // for (int i = 0; i < ST.size(); i++)
    // {
    //     cout << ST[i][0] << endl;
    // }

    // cout << stoi("147") << endl;

    // for (int i = 0; i < machineCode.size(); i++)
    // {
    //     for (int j = 0; j < machineCode[i].size(); j++)
    //     {
    //         cout << machineCode[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}