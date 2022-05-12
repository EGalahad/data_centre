#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <sstream>
using std::stringstream;
#include <string>
using std::getline;
using std::stoi;
using std::string;
#include "DataBase.h"

int main(int argc, char const* argv[]) {
    int m, n, k, N;
    cin >> m >> n >> k >> N;
    DataBase base(m, n, k);
#ifdef DEBUG
    cout << "init data base in main.cpp over" << endl;
#endif  // DEBUG
    string line, token;
    string operation;
    int key, value, computer_id, time_stamp = 0;
    int res;
    while (N--) {
        while (getline(cin, line), line.empty())
            ;
        std::stringstream X(line);
        std::getline(X, token, ' '), operation = token;
        if (operation == "Insert") {
            std::getline(X, token, ' '), key = stoi(token);
            std::getline(X, token, ' '), value = stoi(token);
            computer_id = (std::getline(X, token)) ? stoi(token) : -1;
            res = base.Insert(key, value, time_stamp, computer_id);
            if (res == -1) {
                cout << "REJECT" << endl;
            } else if (res == 1) {
                cout << "EXIST" << endl;
            } else {
                cout << "Successfully Inserted" << endl;
            }
        } else if (operation == "Query") {
            std::getline(X, token, ' '), key = stoi(token);
            computer_id = (std::getline(X, token)) ? stoi(token) : -1;
            res = base.Query(key, value, time_stamp, computer_id);
            if (res == -1) {
                cout << "REJECT" << endl;
            } else if (res == 1) {
                cout << value << endl;
            } else {
                cout << "NOT FOUND" << endl;
            }
        } else if (operation == "Update") {
            std::getline(X, token, ' '), key = stoi(token);
            std::getline(X, token, ' '), value = stoi(token);
            int new_value = value;
            computer_id = (std::getline(X, token)) ? stoi(token) : -1;
            res = base.Update(key, value, time_stamp, computer_id);
            if (res == -1) {
                cout << "REJECT" << endl;
            } else if (res == 1) {
#ifdef DEBUG_UPDATE
                cout << "[updated] old value, new value" << endl;
#endif  // DEBUG_UPDATE
                cout << value << " " << new_value << endl;
            } else {
                cout << "Successfully Inserted" << endl;
            }
        } else if (operation == "GetNode") {
            int node_id;
            std::getline(X, token, ' '), node_id = stoi(token);
            computer_id = (std::getline(X, token)) ? stoi(token) : -1;
            res = base.GetNode(node_id, time_stamp, computer_id);
            if (res == -1) {
                cout << "REJECT" << endl;
            }
        } else {
            time_stamp = stoi(operation);
        }
    }

    return 0;
}
