//
// Created by zukkari on 5/16/18.
//

#include "../include/ZFileContent.h"

using namespace std;

const string &ZFileContent::getFileName() const {
    return fileName;
}

void ZFileContent::setFileName(const string &fileName) {
    ZFileContent::fileName = fileName;
}

const string &ZFileContent::getContent() const {
    return content;
}

void ZFileContent::setContent(const string &content) {
    ZFileContent::content = content;
}
