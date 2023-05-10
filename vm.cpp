#include "parser.h"
#include <sstream>

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

void tokenize(vector<string> Tac)
{
    vector<string> tokens;
    for (int x = 0; x < Tac.size(); x++)
    {
        stringstream check1(Tac[x]);

        string intermediate;

        // Tokenizing w.r.t. space ' '
        while (getline(check1, intermediate, ' '))
        {
            if (intermediate != " " && intermediate != "\n" && intermediate != "\t")
            {
                cout << intermediate << endl;
                tokens.push_back(intermediate);
            }
        }

        // for (int i = 0; i < tokens.size(); i++)
        // {
        //     cout << tokens[i] << endl;
        // }
        // cout << tokens.size() << endl;
        break;
    }
}

int main()
{
    vector<string> Tac = getTac();
    tokenize(Tac);
    // for (int x = 0; x < Tac.size(); x++)
    // {
    //     cout << Tac[x] << endl;
    // }
    return 0;
}