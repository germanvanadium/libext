#include "ext.h"

#ifndef EXTFile
EXTFile::EXTFile(std::string name) {
    if(name.empty()) return;
    if(name.length() > MAXWORLDLENGTH) return;

    worldName = name;
}

EXTFile::~EXTFile() {

}

std::string EXTFile::getName() {
    return worldName;
}
#endif

EXTFile readExtFile(FILE* file) {
    if(!file) {
        return EXTFile(std::string());
    }

    std::string worldName = extractName(file, MAXWORLDLENGTH);
    EXTFile tempExt(worldName.c_str());
    return tempExt;
}

std::string extractName(FILE* file, int bufSize) {
    if(!file) {
        return NULL;
    }

    std::string tempString;
    char curChar, lastChar;

    for(int i = 0; i < bufSize; i++) {
        fseek(file, i, SEEK_SET);

        lastChar = curChar;
        curChar = fgetc(file);

        if(i > 0) {
            if(curChar == 0x00 && lastChar == 0x00) {
                break;
            } else if(curChar != 0x00 && lastChar != 0x00) { //If the EXT is somehow bugged, immediately stop reading
                break;
            }
        }

        if(curChar == 0x00) {
            continue;
        }

        tempString += curChar;
    }

    return tempString;
}