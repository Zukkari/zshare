//
// Created by zukkari on 5/16/18.
//

#ifndef ZSHARE_CLIENT_ZINFORESPONSE_H
#define ZSHARE_CLIENT_ZINFORESPONSE_H

#include <string>
#include <ostream>
#include <json.hpp>

using namespace nlohmann;

class ZInfo {
private:
    std::string access_code;
    std::string content_type;
    unsigned long content_size;
    std::string file_name;

public:
    const std::string &getAccess_code() const;

    void setAccess_code(const std::string &access_code);

    const std::string &getContent_type() const;

    void setContent_type(const std::string &content_type);

    unsigned long getContent_size() const;

    void setContent_size(unsigned long content_size);

    const std::string &getFile_name() const;

    void setFile_name(const std::string &file_name);

    void parse(nlohmann::basic_json<> &json);

    friend std::ostream &operator<<(std::ostream &os, const ZInfo &info) {
        os << "access_code: " << info.access_code << " content_type: " << info.content_type << " content_size: "
           << info.content_size << " file_name: " << info.file_name;
        return os;
    }
};

#endif //ZSHARE_CLIENT_ZINFORESPONSE_H
