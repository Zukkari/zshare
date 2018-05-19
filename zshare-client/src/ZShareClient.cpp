//
// Created by zukkari on 5/16/18.
//

#include <fstream>
#include <cpr/cpr.h>
#include <json.hpp>
#include "../include/ZInfo.h"
#include "../include/ZShareClient.h"

using namespace cpr;
using namespace std;
using namespace nlohmann;

ZFileUpload ZShareClient::upload(string &absFilePath, string &fName) const {

    ifstream stream(absFilePath, ios::in|ios::binary|ios::ate);
    if (stream.is_open()) {
        streampos size;
        char *block;

        size = stream.tellg();
        block = new char[size];

        stream.seekg(0, ios::beg);
        stream.read(block, size);
        stream.close();

        auto resp = Post(Url ENDPOINT("files"),
                              Header{{ZAUTH, API_KEY},
                                          {"zfile_name", fName},
                                     {"Content-Type", "text/plain"}},
                              Body{block});

        delete[] block;

        if (resp.status_code == 200) {
            // OK
            auto* upload_res = new ZFileUpload();
            auto json = json::parse(resp.text);

            upload_res->parse(json);

            return *upload_res;
        } else {
            throw runtime_error("Status code was not 200: " + resp.status_code);
        }
    } else {
        throw runtime_error("Unable to open a file: '" + absFilePath + "'");
    }
}

ZInfo ZShareClient::fileInfo(string &accessKey) const {
    auto resp = Get(Url ENDPOINT("info"),
                         Header{{ZAUTH, API_KEY}},
                         Parameters{{FILE_KEY, accessKey}});

    auto code = resp.status_code;

    if (code == 400) {
        throw runtime_error{"Bad request"};
    } else if (code == 204) {
        throw runtime_error{"No content for such key: '" + accessKey + "'"};
    }

    auto json = json::parse(resp.text);

    auto *info = new ZInfo();
    info->parse(json);

    return *info;
}

ZFileContent ZShareClient::fileContent(string &accessKey) const {
    auto resp = Get(Url ENDPOINT("files"),
                         Header{{ZAUTH, API_KEY}},
                         Parameters{{FILE_KEY, accessKey}});

    if (resp.status_code == 200) {
        // OK
        string fileName = resp.header[FILE_NAME];
        string content = resp.text;

        auto *cont = new ZFileContent();
        cont->setFileName(fileName);
        cont->setContent(content);

        return *cont;
    } else {
        throw runtime_error("Bad response code: " + to_string(resp.status_code) + " " + resp.text);
    }
}
