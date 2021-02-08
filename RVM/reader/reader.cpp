#include "reader.h"
#include <fstream>

FileByteReader::FileByteReader(std::string filename) {
    this->cr_pos = 0;
    this->load(filename);
}

byte FileByteReader::next(){
    return datas[++ cr_pos];
}

byte FileByteReader::peek(){
    return datas[cr_pos];
}

byte FileByteReader::last(){
    return datas[-- cr_pos];
}

byte FileByteReader::jmp(int pos){
    return datas[cr_pos = pos];
}

byte FileByteReader::skip(int num){
    return datas[cr_pos += num];
}

bool FileByteReader::clr(){
    datas.clear();
    return true;
}

bool FileByteReader::load(std::string filename){
    std::ifstream fin(filename.c_str());
    if (fin.bad()) {
        return false;
    }
    while (! fin.eof()) {
        datas.push_back(fin.get());
    }
    return true;
}