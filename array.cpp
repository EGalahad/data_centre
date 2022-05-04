#include "Node.h"

bool StoreNode::array_operation(int key, int& value, int type) {
    for (int i = 0; i < size; i++) {
        if (data_list[i].key == key) {
            // if insert(type == 0), not successful, return 1
            if (type == 1) value = data_list[i].value;
            if (type == 2) {
                int old_value = data_list[i].value;
                data_list[i].value = value;
                value = old_value;
            }
            return 1;
        }
    }
    // not found
    if (type == 1) return 0;
    list_append(key, value);
    return 0;
}

void StoreNode::array_show() {
    cout << "Array" << endl;
    for (int i = 0; i < size; i++) {
        cout << data_list[i].key;
        if (i < size - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}
