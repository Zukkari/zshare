//
// Created by zukkari on 5/16/18.
//

#include "../include/ZInfo.h"

const std::string &ZInfo::getAccess_code() const {
    return access_code;
}

void ZInfo::setAccess_code(const std::string &access_code) {
    ZInfo::access_code = access_code;
}

unsigned long ZInfo::getContent_size() const {
    return content_size;
}

void ZInfo::setContent_size(unsigned long content_size) {
    ZInfo::content_size = content_size;
}

const std::string &ZInfo::getContent_type() const {
    return content_type;
}

void ZInfo::setContent_type(const std::string &content_type) {
    ZInfo::content_type = content_type;
}

const std::string &ZInfo::getFile_name() const {
    return file_name;
}

void ZInfo::setFile_name(const std::string &file_name) {
    ZInfo::file_name = file_name;
}

void ZInfo::parse(nlohmann::basic_json<>& json) {
    this->access_code = json.at("access-code").get<std::string>();
    this->content_size = json.at("content_size").get<unsigned long>();
    this->content_type = json.at("content-type").get<std::string>();
    this->file_name = json.at("file_name").get<std::string>();
}
