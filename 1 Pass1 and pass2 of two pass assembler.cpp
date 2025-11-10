#include <bits/stdc++.h>
using namespace std;

map<string, int> IS = {{"STOP", 0}, {"ADD", 1}, {"SUB", 2}, {"MULT", 3},
                       {"MOVER", 4}, {"MOVEM", 5}, {"DIV", 6},
                       {"READ", 7}, {"PRINT", 8}};
map<string, int> DL = {{"DC", 1}, {"DS", 2}};
map<string, int> AD = {{"START", 1}, {"END", 2}, {"LTORG", 5}};
map<string, int> REG = {{"AREG", 1}, {"BREG", 2}, {"CREG", 3}, {"DREG", 4}};

struct Symbol {
    string name;
    int address;
};
struct Literal {
    string value;
    int address;
};

vector<Symbol> symtab;
vector<Literal> littab;
vector<int> pooltab = {0};
vector<string> intermediate;

int LC = 0;

int getSymbolAddress(string name) {
    for (auto &s : symtab)
        if (s.name == name) return s.address;
    return -1;
}
int getLiteralAddress(string value) {
    for (auto &l : littab)
        if (l.value == value) return l.address;
    return -1;
}

void pass1(vector<string> code) {
    for (auto line : code) {
        stringstream ss(line);
        string label = "", opcode = "", op1 = "", op2 = "";
        ss >> label;

        if (IS.count(label) || DL.count(label) || AD.count(label)) {
            opcode = label;
            label = "";
        } else {
            ss >> opcode;
        }
        ss >> op1 >> op2;

        if (opcode == "START") {
            LC = stoi(op1);
            intermediate.push_back("(AD,01) (C," + op1 + ")");
            continue;
        }

        if (!label.empty()) {
            symtab.push_back({label, LC});
        }

        if (IS.count(opcode)) {
            string ic = "(IS," + to_string(IS[opcode]) + ")";
            if (!op1.empty() && REG.count(op1))
                ic += " (R," + to_string(REG[op1]) + ")";
            if (!op2.empty()) {
                if (op2[0] == '=') {
                    bool found = false;
                    for (auto &l : littab)
                        if (l.value == op2) found = true;
                    if (!found) littab.push_back({op2, -1});
                    ic += " (L," + to_string(littab.size()) + ")";
                } else {
                    bool found = false;
                    for (auto &s : symtab)
                        if (s.name == op2) found = true;
                    if (!found) symtab.push_back({op2, -1});
                    ic += " (S," + to_string(symtab.size()) + ")";
                }
            }
            intermediate.push_back(ic);
            LC++;
        }

        else if (DL.count(opcode)) {
            string ic = "(DL," + to_string(DL[opcode]) + ")";
            if (opcode == "DC") {
                ic += " (C," + op1 + ")";
                LC++;
            } else if (opcode == "DS") {
                LC += stoi(op1);
                ic += " (C," + op1 + ")";
            }
            intermediate.push_back(ic);
        }

        else if (opcode == "LTORG") {
            for (int i = pooltab.back(); i < littab.size(); i++) {
                littab[i].address = LC++;
            }
            pooltab.push_back(littab.size());
            intermediate.push_back("(AD,05)");
        }

        else if (opcode == "END") {
            for (int i = pooltab.back(); i < littab.size(); i++) {
                littab[i].address = LC++;
            }
            pooltab.push_back(littab.size());
            intermediate.push_back("(AD,02)");
            break;
        }
    }
}

void pass2() {
    cout << "\n--- MACHINE CODE ---\n";
    int lineLC = 200; // assuming program started at 200

    for (auto ic : intermediate) {
        if (ic.find("(IS") != string::npos) {
            stringstream ss(ic);
            string token;
            vector<string> parts;
            while (ss >> token) parts.push_back(token);

            int opcode = stoi(parts[0].substr(4, 1));
            int reg = 0, addr = 0;

            if (parts.size() > 1 && parts[1].find("(R,") != string::npos)
                reg = stoi(parts[1].substr(3, 1));

            if (parts.size() > 2) {
                string p = parts[2];
                if (p.find("(S,") != string::npos) {
                    int idx = stoi(p.substr(3, p.size() - 4)) - 1;
                    addr = symtab[idx].address;
                } else if (p.find("(L,") != string::npos) {
                    int idx = stoi(p.substr(3, p.size() - 4)) - 1;
                    addr = littab[idx].address;
                }
            }
            cout << lineLC++ << " : " << opcode << " " << reg << " " << addr << endl;
        }
    }
}

int main() {
    vector<string> code = {
        "START 200",
        "MOVER AREG,='5'",
        "ADD BREG,ONE",
        "SUB AREG,='1'",
        "MOVEM AREG,TEMP",
        "ONE DC 1",
        "TEMP DS 1",
        "LTORG",
        "END"
    };

    pass1(code);

    cout << "\n---- INTERMEDIATE CODE ----\n";
    for (auto s : intermediate) cout << s << endl;

    cout << "\n---- SYMBOL TABLE ----\n";
    for (int i = 0; i < symtab.size(); i++)
        cout << i + 1 << "\t" << symtab[i].name << "\t" << symtab[i].address << endl;

    cout << "\n---- LITERAL TABLE ----\n";
    for (int i = 0; i < littab.size(); i++)
        cout << i + 1 << "\t" << littab[i].value << "\t" << littab[i].address << endl;

    cout << "\n---- POOL TABLE ----\n";
    for (auto p : pooltab) cout << p << " ";
    cout << endl;

    pass2();

    return 0;
}
