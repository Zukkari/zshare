//
// Created by zukkari on 5/16/18.
//

#include "../include/ZFileUpload.h"

using namespace std;

void ZFileUpload::parse(basic_json<> json) {
    this->access_code = json.at("access-code").get<string>();
    this->content_size = json.at("content_size").get<unsigned long>();
    this->content_type = json.at("content-type").get<string>();
    this->file_name = json.at("file_name").get<string>();
}

const string &ZFileUpload::getAccess_code() const {
    return access_code;
}

void ZFileUpload::setAccess_code(const string &access_code) {
    ZFileUpload::access_code = access_code;
}

unsigned long ZFileUpload::getContent_size() const {
    return content_size;
}

void ZFileUpload::setContent_size(unsigned long content_size) {
    ZFileUpload::content_size = content_size;
}

const string &ZFileUpload::getContent_type() const {
    return content_type;
}

void ZFileUpload::setContent_type(const string &content_type) {
    ZFileUpload::content_type = content_type;
}

const string &ZFileUpload::getFile_name() const {
    return file_name;
}

void ZFileUpload::setFile_name(const string &file_name) {
    ZFileUpload::file_name = file_name;
}