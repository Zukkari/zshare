//
// Created by zukkari on 5/16/18.
//

#ifndef ZSHARE_CLIENT_ZINFORMATION_H
#define ZSHARE_CLIENT_ZINFORMATION_H

#include <json.hpp>
#include <ostream>

using namespace std;
using namespace nlohmann;

class ZFileUpload {
private:
    string access_code;
    unsigned long content_size;
    string content_type;
    string file_name;

public:
    void parse(basic_json<> json);

    const string &getAccess_code() const;

    void setAccess_code(const string &access_code);

    unsigned long getContent_size() const;

    void setContent_size(unsigned long content_size);

    const string &getContent_type() const;

    void setContent_type(const string &content_type);

    const string &getFile_name() const;

    void setFile_name(const string &file_name);

    friend ostream &operator<<(ostream &os, const ZFileUpload &upload) {
        os << "access_code: " << upload.access_code << " content_size: " << upload.content_size << " content_type: "
           << upload.content_type << " file_name: " << upload.file_name;
        return os;
    }
};


#endif //ZSHARE_CLIENT_ZINFORMATION_H
