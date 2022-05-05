#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "DataBase.h"

int main(int argc, char const *argv[]) {
    int m, n, k, N;
    cin >> m >> n >> k >> N;
    DataBase base(m, n, k);
    string operation;
    int key, value;
    bool exist = 0;
    while (N--) {
        cin >> operation;
        if (operation == "Insert") {
            cin >> key >> value;
            if (base.Insert(key, value)) {
                cout << "EXIST" << endl;
            } else {
                cout << "Successfully Inserted" << endl;
            }
        }
        if (operation == "Query") {
            cin >> key;
            if (base.Query(key, value)) {
                cout << value << endl;
            } else {
                cout << "NOT FOUND" << endl;
            }
        }
        if (operation == "Update") {
            cin >> key >> value;
            int new_value = value;
            if (base.Update(key, value)) {
                cout << value << " " << new_value << endl;
            } else {
                cout << "Successfully Inserted" << endl;
            }
        }
        if (operation == "GetNode") {
            int node_id;
            cin >> node_id;
            base.show_store(node_id);
            
        }
    }

    return 0;
}
