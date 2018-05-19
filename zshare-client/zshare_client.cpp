#include <iostream>

#include <cpr/cpr.h>
#include <json.hpp>
#include "include/ZInfo.h"
#include "include/ZShareClient.h"


int main(int argc, char** argv) {
    ZShareClient client;

    string fPath = "/home/zukkari/Downloads/testFile.json";
    string fName = "resultFile.json";

    auto uploadRes = client.upload(fPath, fName);
    string access_code = uploadRes.getAccess_code();

    std::cout << client.fileInfo(access_code) << std::endl;
    std::cout << client.fileContent(access_code) << std::endl;
}
