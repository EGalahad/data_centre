#include "BinaryTrie.h"

BinaryTrieNode::BinaryTrieNode(bool key /* = 0 */, DataNode* data /* = nullptr */) : key(key), data(data) {
    for (int i = 0; i < 2; i++) {
        child[i] = nullptr;
    }
}

BinaryTrie::BinaryTrie(DataNode* data_list, int initial_size) {
    #ifdef DEBUG
    cout << "constructing binary trie" << endl;
    #endif // DEBUG
    trie_list = new BinaryTrieNode[trie_capacity];
    // use first node in list as the root, whose key does not matter
    trie_root = &trie_list[0];
    trie_list[0].id = 0;
    for (int i = 0; i < initial_size; i++) {
        trie_append(data_list + i);
    }
}

BinaryTrieNode* BinaryTrie::trie_list_append(bool key, DataNode* data) {
    if (trie_size == trie_capacity) {
        trie_capacity <<= 1;
        BinaryTrieNode* new_trie = new BinaryTrieNode[trie_capacity];
        for (int i = 0; i < trie_size; i++) {
            new_trie[i] = trie_list[i];
        }
        delete[] trie_list;
        trie_list = new_trie;
    }
    trie_list[trie_size].key = key;
    trie_list[trie_size].data = data;
    trie_list[trie_size].id = trie_size;
    return trie_list + trie_size++;
}

// // return 0 iff key >> pos == 0
// inline bool at(int n, int pos, bool& k) {
//     if (n >> pos == 0) {
//         k = (n >> (pos - 1));
//         return 0;
//     }
//     k = (n >> pos) & 1;
//     return 1;
// }

bool BinaryTrie::trie_append(DataNode* data) {
    BinaryTrieNode* cur = trie_root;
    int key = data->key;
    int k;
    for (int i = 0; k = key >> i; i++) {
        k = k & 1;
        if (!cur->child[k]) {
            cur->child[k] = trie_list_append(k, nullptr);
        }
        cur = cur->child[k];
    }
    if (cur->data == nullptr) {
        cur->data = data;
        return 0;
    }
    // exists and do nothing
    return 1;
}

bool BinaryTrie::insert(DataNode* node, bool use_query_result /* = 0 */ ) {
    if (!use_query_result) {
        return trie_append(node);
    } else {
        query_result->data = node;
        return 0;
    }
}

bool BinaryTrie::operation(int key, int& value, int type) {
    BinaryTrieNode* cur = trie_root;
    int k;
    for (int i = 0; k = key >> i; i++) {
        k = k & 1;
        if (!cur->child[k]) {
            if (type == 1) return 0;
            cur->child[k] = trie_list_append(k, nullptr);
        }
        cur = cur->child[k];
    }
    if (cur->data == nullptr) {
        // used to update
        query_result = cur;
        return 0;
    } else {
        int old_value = cur->data->value;
        if (type == 2) cur->data->value = value;
        value = old_value;
        return 1;
    }
}

void BinaryTrie::show() {
    cout << "Binary Search Trie" << endl;
    bool* is_child0 = new bool[trie_size];
    for (int i = 0; i < trie_size; i++) {
        auto& node = trie_list[i];
        if (node.child[0]) {
            is_child0[node.child[0]->id] = 1;
        } else if (node.child[1]) {
            is_child0[node.child[1]->id] = 1;
        }
    }
    for (int i = 1; i < trie_size; i++) {
        cout << trie_list[i].key;
        if (i < trie_size - 1)
            cout << " ";
        else
            cout << endl;
    }
    for (int i = 1; i < trie_size; i++) {
        cout << is_child0[i];
        if (i < trie_size - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
    for (int i = 1; i < trie_size; i++) {
        cout << (trie_list[i].data != nullptr);
        if (i < trie_size - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}
