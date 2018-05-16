//
// Created by zukkari on 5/16/18.
//

#ifndef ZSHARE_CLIENT_ZSHARECLIENT_H
#define ZSHARE_CLIENT_ZSHARECLIENT_H

#include "ZInfo.h"
#include "ZFileUpload.h"
#include "ZFileContent.h"

#define API_KEY "7f00534ba1ec107e17131bc63e37d805"
#define ENDPOINT(end) {std::string("http://127.0.0.1:8080/")+(std::string(end))}
#define FILE_KEY "file_key"
#define ZAUTH "zauth"
#define FILE_NAME "content-disposition"

class ZShareClient {
public:
    ZFileUpload upload(std::string fileName);

    ZInfo fileInfo(std::string accessKey);

    ZFileContent fileContent(std::string accessKey);
};

#endif //ZSHARE_CLIENT_ZSHARECLIENT_H
