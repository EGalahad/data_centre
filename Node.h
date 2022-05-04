#pragma once
#include <iostream>
using std::cout;
using std::endl;
#include <utility>
typedef std::pair<int, int> Pair;
#include "BinaryTrie.h"

class ComputeNode {
   public:
    ComputeNode(int id, int cache_size);
    // when doing operation
    // insert pair to cache

    // insert into key % n store node
    bool insert(int key, int value, StoreNode* sto);
    // query key % n store node
    bool query(int key, int& value, StoreNode* sto);
    // update in key % n store node
    bool update(int key, int& value, StoreNode* sto);
    // change cache dur to dirty write
    void update_cache(int key, int value);
    void show(StoreNode* sto);

   private:
    // node id
    int id;
    // cache size
    int k;
    // cache cursor
    int cur;
    // array of cache
    Pair* cache;
    // return 1 if exist
    bool cache_query(int key, int& value, int& pos);
    // insert if not exist, update if key exist
    void cache_insert(int key, int value);
};

class DataNode {
   public:
    DataNode(int key = 0, int value = 0);

    int key, value, id;
    DataNode* child[2];
};

// nodes in the trie, with leaf nodes pointing to the data nodes
class BinaryTrieNode {
   public:
    BinaryTrieNode(bool key = 0, DataNode* data = nullptr);
    bool key;
    DataNode* data;
    BinaryTrieNode* child[2];
};

class StoreNode {
   public:
    StoreNode(int id);

    // if key exist, return 1, will not modify
    bool insert(int key, int value);
    // if key exist, return 1, store in value
    bool query(int key, int& value);
    // if key exist, return 1, old_value stored in value
    bool update(int key, int& value);

    void show();

   private:
    int id;

    // data structrure type
    // 0: array, 1:BST, 2: trie
    int type = 0;

    int size = 0, capacity = 1;
    DataNode* data_list;

    DataNode* list_append(int key, int value);

    // type: 0: insert, 1: query, 2, update
    // return 1 if key exists
    bool array_operation(int key, int& value, int type);
    void array_show();

    // type: 0: insert, 1: query, 2, update
    // return 1 if key exists
    bool bst_operation(int key, int& value, int type);
    void bst_show();

    DataNode* bst_root;

    void bst_init();
    void bst_append(DataNode* node);

    // type: 0: insert, 1: query, 2, update
    // return 1 if key exists
    bool trie_operation(int key, int& value, int type);

    int trie_size = 0, trie_capacity = 1;
    BinaryTrieNode* trie_list;
    BinaryTrieNode* trie_list_append(bool key, DataNode* data);

    BinaryTrieNode* trie_root;

    BinaryTrie* trie;
    void trie_init();
    void trie_append(DataNode* data);

    void transform(int depth);
};