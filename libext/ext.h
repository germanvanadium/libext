#include <iostream>
#include <cstring>

#define MAXWORLDLENGTH 50

class EXTFile {
private:
    std::string worldName;
public:
    EXTFile(std::string name);
    ~EXTFile();
    std::string getName();
};

EXTFile readExtFile(FILE* file);
std::string extractName(FILE* file, int bufSize);