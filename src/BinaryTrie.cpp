#include "BinaryTrie.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <queue>

BinaryTrieNode::BinaryTrieNode(int id, bool key /* = 0 */, DataNode* data /* = nullptr */)
    : id(id), key(key), data(data) {
    for (int i = 0; i < 2; i++) {
        child[i] = nullptr;
    }
}

BinaryTrie::BinaryTrie(DataNode** data_list, int initial_size) {
    trie_list = new BinaryTrieNode*[trie_capacity /* = 1 */];
    // use first node in list as the root, whose key does not matter
    trie_list[0] = new BinaryTrieNode(0);
    trie_root = trie_list[0];
    for (int i = 0; i < initial_size; i++) {
        trie_append(data_list[i]);
    }
}

BinaryTrieNode* BinaryTrie::trie_list_append(bool key, DataNode* data) {
    if (trie_size == trie_capacity) {
        trie_capacity <<= 1;
        BinaryTrieNode** new_trie_list = new BinaryTrieNode*[trie_capacity];
        for (int i = 0; i < trie_size; i++) {
            new_trie_list[i] = trie_list[i];
        }
        delete[] trie_list;
        trie_list = new_trie_list;
    }
    trie_list[trie_size] = new BinaryTrieNode(trie_size, key, data);
    return trie_list[trie_size++];
}

bool BinaryTrie::trie_append(DataNode* data) {
    BinaryTrieNode* cur = trie_root;
    int& key = data->key;
    int k, depth = 0;
    for (int i = 31; i >= 0; i--) {
        k = key >> i & 1, depth++;
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

bool BinaryTrie::insert(DataNode* node, bool use_query_result /* = 0 */) {
    if (!use_query_result) {
        return trie_append(node);
    } else {
        query_result->data = node;
        return 0;
    }
}

bool BinaryTrie::operation(int key, int& value, int type) {
    BinaryTrieNode* cur = trie_root;
    int k, depth = 0;
    for (int i = 31; i >= 0; i--) {
        k = key >> i & 1, depth++;
        if (!cur->child[k]) {
            if (type == 1) return 0;
            cur->child[k] = trie_list_append(k, nullptr);
        }
        cur = cur->child[k];
    }
    if (cur->data == nullptr) {
        // find no key when update, need to new a Datanode
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
    cout << "Trie" << endl;
    BinaryTrieNode** layer = new BinaryTrieNode*[trie_size];
    {
        int cnt = 0;
        std::queue<BinaryTrieNode*> Q;
        Q.push(trie_root);
        while (!Q.empty()) {
            BinaryTrieNode* top = Q.front();
            Q.pop();
            layer[cnt++] = top;
            for (int i = 0; i < 2; i++) {
                if (top->child[i]) Q.push(top->child[i]);
            }
        }
    }
    bool* is_child0 = new bool[trie_size];
    {
        for (int i = 0; i < trie_size; i++) is_child0[i] = 0;
        for (int i = 0; i < trie_size; i++) {
            auto& node = trie_list[i];
            if (node->child[0]) {
                is_child0[node->child[0]->id] = 1;
            } else if (node->child[1]) {
                is_child0[node->child[1]->id] = 1;
            }
        }
    }
    for (int i = 1; i < trie_size; i++) cout << layer[i]->key << " ";
    cout << endl;
    for (int i = 1; i < trie_size; i++) cout << is_child0[layer[i]->id] << " ";
    cout << endl;
    for (int i = 1; i < trie_size; i++) cout << !(layer[i]->child[0] || layer[i]->child[1]) << " ";
    cout << endl;
    delete[] is_child0;
    delete[] layer;
}

BinaryTrie::~BinaryTrie() {
    for (int i = 0; i < trie_size; i++) {
        delete trie_list[i];
    }
    delete[] trie_list;
}
