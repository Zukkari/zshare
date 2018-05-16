//
// Created by zukkari on 5/16/18.
//

#ifndef ZSHARE_CLIENT_ZFILECONTENT_H
#define ZSHARE_CLIENT_ZFILECONTENT_H


#include <string>
#include <ostream>

class ZFileContent {
private:
    std::string fileName;
    std::string content;

public:
    const std::string &getFileName() const;

    void setFileName(const std::string &fileName);

    const std::string &getContent() const;

    void setContent(const std::string &content);

    friend std::ostream &operator<<(std::ostream &os, const ZFileContent &content) {
        os << "fileName: " << content.fileName << " content: " << content.content;
        return os;
    }
};


#endif //ZSHARE_CLIENT_ZFILECONTENT_H
