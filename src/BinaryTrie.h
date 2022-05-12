#pragma once
#include "common.h"
#include "DataNode.h"
#include <queue>

// nodes in the trie, with leaf nodes pointing to the data nodes
class BinaryTrieNode {
    bool key;
    int id;
    int depth;
    DataNode* data;
    BinaryTrieNode* child[2];
    friend class BinaryTrie;
   public:
    BinaryTrieNode(int id, bool key = 0, int depth = 0, DataNode* data = nullptr);
};

class BinaryTrie {
   public:
    BinaryTrie(DataNode** data_list, int initial_size);
    ~BinaryTrie();
    bool insert(DataNode* node, bool use_query_result = 0);
    // type 1: query 2: update
    bool operation(int key, int& value, int type);
    void show();

   private:
    BinaryTrieNode **trie_list, *trie_root, *query_result;
    int trie_capacity = 1, trie_size = 1;
    BinaryTrieNode* trie_list_append(bool key, int depth, DataNode* data);
    bool trie_append(DataNode* data);
};
