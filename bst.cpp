#include "Node.h"

BinaryTrieNode::BinaryTrieNode(bool key = 0, DataNode* data = nullptr) : key(key), data(data) {
    for (int i = 0; i < 2; i++) {
        child[i] = nullptr;
    }
};

bool StoreNode::bst_operation(int key, int& value, int type) {
    DataNode* cur = bst_root;
    int depth = 0;
    bool k = 0;
    while (true) {
        depth++;
        // found same key
        if (cur->key == key) {
            // return depth if insert
            if (type == 0) value = depth;
            // query value
            if (type == 1) value = cur->value;
            // update value
            if (type == 2) {
                int old_value = cur->value;
                cur->value = value;
                value = old_value;
            }
            return 1;
        }
        k = key < cur->key;
        if (cur->child[k] == nullptr) {
            if (type == 1) return 0;
            cur->child[k] = list_append(key, value);
            value = depth;
            return 0;
        }
        cur = cur->child[k];
        continue;
    }
}

void StoreNode::bst_init() {
    bst_root = &data_list[0];
    for (int i = 1; i < size; i++) {
        bst_append(data_list + i);
    }
}

void StoreNode::bst_append(DataNode* node) {
    DataNode* cur = &data_list[0];
    int key = node->key;
    bool k = 0;
    while (true) {
        k = key < cur->key;
        if (cur->child[k] == nullptr) {
            cur->child[k] = node;
            return;
        }
        cur = cur->child[k];
    }
}

void StoreNode::bst_show() {
    cout << "Binary Search Tree" << endl;
    bool *is_child0 = new bool[size];
    for (int i = 0; i < size; i++) {
        is_child0[data_list[i].child[0]->id] = 1;
        cout << data_list[i].key;
        if (i < size - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
    for (int i = 0; i < size; i++) {
        cout << is_child0[i];
        if (i < size - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
    for (int i = 0; i < size; i++) {
        auto& node = data_list[i];
        cout << (!node.child[0] && !node.child[1]);
        if (i < size - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}
