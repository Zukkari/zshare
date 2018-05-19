

#include <fstream>
#include <list>
#include "../include/ZShareClient.h"

#define COMMAND_SEND "send"
#define COMMAND_RECEIVE "receive"

using namespace std;

void get_file_name(string &path, string &res) {
    stringstream ss(path);
    list<string> items;
    string item;

    while (getline(ss, item, '/')) {
        items.emplace_back(string(item));
    }

    auto it = items.end();
    it--;

    res = *it;
}

int main(int argc, char **args) {
    if (argc > 2) {
        string command = args[1];

        if (command == COMMAND_SEND) {
            if (argc > 4) {
                cout << "Invalid number of arguments for command "
                     << COMMAND_SEND
                     << " expected 3 but got "
                     << argc - 1
                     << endl;
                return EXIT_FAILURE;
            }

            string f_path = args[2];
            string f_name = argc == 4 ? args[3] : "";
            if (f_name.empty()) {
                get_file_name(f_path, f_name);
            }

            ZShareClient client;
            auto res = client.upload(f_path, f_name);

            cout << "Your file '" << res.getFile_name() << "' has been successfully uploaded." << endl;
            cout << "The code is => " << res.getAccess_code() << endl;
        } else if (command == COMMAND_RECEIVE) {
            if (argc != 3) {
                cout << "Invalid number of arguments for command "
                     << COMMAND_RECEIVE <<
                     "expected 2 arguments but got"
                     << argc - 1
                     << "instead. "
                     << endl;
            }

            string code = args[2];
            ZShareClient client;

            auto info = client.fileInfo(code);
            cout <<
                 "You are about to receive a file: "
                 << endl;

            cout <<
                 "File name: "
                 << info.getFile_name()
                 << endl;

            cout <<
                 "File size: "
                 << info.getContent_size()
                 << " bytes."
                 << endl;

            cout << "Do you want to proceed? (y/N)" << endl;
            bool got_answer = false;

            string resp;
            getline(cin, resp);
            if (resp == "y" || resp == "yes") {
                auto content = client.fileContent(code);
                cout <<
                     "Received file: "
                     << content.getFileName()
                     << endl;

                ofstream f;
                f.open(content.getFileName());

                if (f.is_open()) {
                    f << content.getContent();
                    f.close();
                } else {
                    cout << "Cannot access file with name " << content.getFileName() << endl;
                }
            }
            return EXIT_SUCCESS;
        } else {
            cout << "Unknown command: " << command << endl;
            return EXIT_FAILURE;
        }
    } else {
        cout << "Expecting more than 2 arguments, got " << argc - 1 << " instead." << endl;
        return EXIT_FAILURE;
    }
}