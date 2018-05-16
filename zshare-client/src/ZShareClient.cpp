//
// Created by zukkari on 5/16/18.
//

#include <cpr/cpr.h>
#include "../include/ZInfo.h"
#include "../include/ZShareClient.h"

using namespace cpr;

ZFileUpload ZShareClient::upload(std::string fileName) {
    return ZFileUpload();
}

ZInfo ZShareClient::fileInfo(std::string accessKey) {
    auto resp = cpr::Get(cpr::Url ENDPOINT("info"),
                         cpr::Header{{ZAUTH, API_KEY}},
                         cpr::Parameters{{FILE_KEY, accessKey}});

    auto code = resp.status_code;

    if (code == 400) {
        throw std::runtime_error{"Bad request"};
    } else if (code == 204) {
        throw std::runtime_error{"No content for such key: '" + accessKey + "'"};
    }

    auto json = nlohmann::json::parse(resp.text);

    auto *info = new ZInfo();
    info->parse(json);

    return *info;
}

ZFileContent ZShareClient::fileContent(std::string accessKey) {
    auto resp = cpr::Get(cpr::Url ENDPOINT("files"),
                         cpr::Header{{ZAUTH, API_KEY}},
                         cpr::Parameters{{FILE_KEY, accessKey}});

    if (resp.status_code == 200) {
        // OK
        std::string fileName = resp.header[FILE_NAME];
        std::string content = resp.text;

        auto* cont = new ZFileContent();
        cont->setFileName(fileName);
        cont->setContent(content);

        return *cont;
    } else {
        throw std::runtime_error("Bad response code: " + std::to_string(resp.status_code) + " " + resp.text);
    }
}
