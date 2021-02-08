#ifndef __READER_HEADER__
#define __READER_HEADER__

#include "../const/defs.h"
#include <string>
#include <vector>

#ifndef __IREADER_INTERFACE__
#define __IREADER_INTERFACE__
template<class T> interface IReader {
public:
    virtual T next() = 0;
    virtual T peek() = 0;
    virtual T last() = 0;
    virtual T jmp(int pos) = 0;
    virtual T skip(int num) = 0;
    virtual bool clr() = 0;
};
#endif

#ifndef __READER_CLASS__
#define __READER_CLASS__

abstract class IByteReader : implement IReader<byte> {
};

class FileByteReader : public IByteReader {
    std::vector<byte> datas;
    int cr_pos;
public:
    FileByteReader(std::string filename);
    byte next() override final;
    byte peek() override final;
    byte last() override final;
    byte jmp(int pos) override final;
    byte skip(int num) override final;
    bool clr() override final;
    bool load(std::string filename);
};

#endif

#endif