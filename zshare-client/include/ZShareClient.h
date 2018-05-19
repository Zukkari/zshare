//
// Created by zukkari on 5/16/18.
//

#ifndef ZSHARE_CLIENT_ZSHARECLIENT_H
#define ZSHARE_CLIENT_ZSHARECLIENT_H

#include "ZInfo.h"
#include "ZFileUpload.h"
#include "ZFileContent.h"

#define API_KEY "7f00534ba1ec107e17131bc63e37d805"
#define ENDPOINT(end) {string("http://127.0.0.1:8080/")+(string(end))}
#define FILE_KEY "file_key"
#define ZAUTH "zauth"
#define FILE_NAME "content-disposition"

using namespace std;

class ZShareClient {
public:
    ZFileUpload upload(string &absFilePath, string &fName) const;

    ZInfo fileInfo(string &accessKey) const;

    ZFileContent fileContent(string &accessKey) const;
};

#endif //ZSHARE_CLIENT_ZSHARECLIENT_H
