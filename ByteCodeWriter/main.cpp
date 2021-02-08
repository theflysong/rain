#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
using namespace std;

void IntToBytes(int value, char* out) {
    out[3] = value & 0x000000FF;
    out[2] = (value & 0x0000FF00) >> 8;
    out[1] = (value & 0x00FF0000) >> 16;
    out[0] = (value & 0xFF000000) >> 24;
}

void ShortToBytes(short value, char* out) {
    out[1] = value & 0x000000FF;
    out[0] = (value & 0x0000FF00) >> 8;
}

int main(int argc, char** argv) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2], ios::binary);
    char ch;
    while (~(ch = fin.get())) {
        if (ch == '~') {
            char c_v;
            char value = 0;
            for (int i = 0 ; i < 2 ; i ++) {
                c_v = fin.get();
                value <<= 4;
                value |= isdigit(c_v) ? c_v - '0' : c_v - 'A' + 10;   
            }
            fout.write(&value, 1);
        }
        else if (ch == '!') {
            char c_v;
            short value = 0;
            for (int i = 0 ; i < 4 ; i ++) {
                c_v = fin.get();
                value <<= 4;
                value |= isdigit(c_v) ? c_v - '0' : c_v - 'A' + 10;
            }
            char bytes[2];
            ShortToBytes(value, bytes); 
            fout.write(bytes, 2);
        }
        else if (ch == '@') {
            char c_v;
            int value = 0;
            for (int i = 0 ; i < 8 ; i ++) {
                c_v = fin.get();
                value <<= 4;
                value |= isdigit(c_v) ? c_v - '0' : c_v - 'A' + 10;  
            }
            char bytes[4];
            IntToBytes(value, bytes); 
            fout.write(bytes, 4);
        }
        else if (ch == '"') {
            char c_v;
            while ('"' != (c_v = fin.get())) {
                fout.write(&c_v, 1);
            }
        }
    }
    return 0;
}