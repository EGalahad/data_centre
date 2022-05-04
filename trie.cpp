#include "Node.h"

void StoreNode::trie_init() {
    trie = new BinaryTrie(data_list, size);
}


bool StoreNode::trie_operation(int key, int& value, int type) {
    if (type == 0) {
        return trie->insert(list_append(key, value));
    } else if (type == 1) {
        return trie->operation(key, value, 1);
    } else {
        bool exist = trie->operation(key, value, 2);
        if (!exist) trie->insert(list_append(key, value), true);
        return exist;
    }
}

BinaryTrieNode* StoreNode::trie_list_append(bool key, DataNode* data) {
    if (trie_size == trie_capacity) {
        trie_capacity <<= 1;
        BinaryTrieNode* new_trie = new BinaryTrieNode[trie_capacity];
        for (int i = 0; i < trie_size; i++) {
            new_trie[i] = trie_list[i];
        }
        delete[] trie_list;
        trie_list = new_trie;
    }
    trie_list[size].key = key;
    trie_list[size].data = data;
    return trie_list + size++;
}

void StoreNode::trie_append(DataNode* data) {
    BinaryTrieNode* cur = trie_root;
    int key = data->value;
    bool k;
    for (int i = 0; at(key, i, k); i++) {
        if (!cur->child[k]) {
            cur->child[k] = trie_list_append(k, nullptr);
        }
        cur = cur->child[k];
    }
    if (cur->data == nullptr) {
        cur->data = data;
        return;
    }
}

bool at(int n, int pos, bool& k) {
    if (n >> pos == 0) return 0;
    k = (n >> pos) & 1;
    return 1;
}

bool StoreNode::trie_operation(int key, int& value, int type) {
    BinaryTrieNode* cur = trie_root;
    bool k;
    for (int i = 0; at(key, i, k); i++) {
        if (!cur->child[k]) {
            if (type == 1) return 0;
            cur->child[k] = trie_list_append(k, nullptr);
        }
        cur = cur->child[k];
    }
    if (cur->data == nullptr) {
        cur->data = list_append(key, value);
        return 0;
    }
    if (type == 0) return 1;
    int old_value = cur->data->value;
    cur->data->value = value;
    value = old_value;
    return 1;
}

// void StoreNode::bst_show() {
//     cout << "Trie" << endl;
//     bool* is_child0 = new bool[size];
//     for (int i = 0; i < trie_size; i++) {
//         is_child0[trie_list[i].child[0]->id] = 1;
//         cout << data_list[i].key;
//         if (i < size - 1) {
//             cout << " ";
//         } else {
//             cout << endl;
//         }
//     }
//     for (int i = 0; i < size; i++) {
//         cout << is_child0[i];
//         if (i < size - 1) {
//             cout << " ";
//         } else {
//             cout << endl;
//         }
//     }
//     for (int i = 0; i < size; i++) {
//         auto& node = data_list[i];
//         cout << (!node.child[0] && !node.child[1]);
//         if (i < size - 1) {
//             cout << " ";
//         } else {
//             cout << endl;
//         }
//     }
// }