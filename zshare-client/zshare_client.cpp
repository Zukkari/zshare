#include <iostream>

#include <cpr/cpr.h>
#include <json.hpp>
#include "include/ZInfo.h"
#include "include/ZShareClient.h"


int main(int argc, char** argv) {
    ZShareClient client;

    std::string key = "6-scruffy-actor";

    std::cout << client.fileInfo(key) << std::endl;
    std::cout << client.fileContent(key) << std::endl;
}
