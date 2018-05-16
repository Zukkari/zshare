//
// Created by zukkari on 5/16/18.
//

#include "../include/ZFileContent.h"

const std::string &ZFileContent::getFileName() const {
    return fileName;
}

void ZFileContent::setFileName(const std::string &fileName) {
    ZFileContent::fileName = fileName;
}

const std::string &ZFileContent::getContent() const {
    return content;
}

void ZFileContent::setContent(const std::string &content) {
    ZFileContent::content = content;
}
