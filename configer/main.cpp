#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
using namespace std;

map<string, string> config;

void init(const char* file) {
    ifstream fin(file);
    char ch;
    string key = "";
    string value = "";
    while (fin.peek() != EOF && (!fin.eof())) {
        fin.get(ch);
        if (ch == '$') {
            config[key] = value;
            key = value = "";
            continue;
        }
        else if(ch == ':') {
            key = value;
            value = "";
            continue;
        }
        value += ch;
    }
    fin.close();
}

void save(const char* file) {
    ofstream fout(file);
    map<string, string>::iterator it = config.begin();
    while (it != config.end()) {
        fout << it->first << ':' << it->second << '$';
        it ++;
    }
    fout.close();
}

int main(int argc, char** argv) {
    string name = "configer.config";
    init(name.c_str());
    for (int i = 1 ; i < argc ; i ++) {
        string switcher = argv[i];
        if (switcher == "-f") {
            name = argv [++ i];
            init(name.c_str());
        }
        else if (switcher == "-c") {
            string key = argv [++ i], value = argv [++ i];
            config[key] = value;
        }
        else if (switcher == "-e") {
            string key = argv [++ i], value = argv [++ i], command1 = "", command2 = "";
            while (string(argv [++ i]) != "$") {
                command1 += argv[i];
                command1 += " ";
            }
            while (string(argv [++ i]) != "$") {
                command2 += argv[i];
                command2 += " ";
            }
            if (config[key] == value) {
                cout << config[value];
                system(command1.c_str());
            }
            else {
                cout << config[value];
                system(command2.c_str());
            }
        }
    }
    save(name.c_str());
    return 0;
}