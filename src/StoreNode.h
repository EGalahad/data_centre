#pragma once
#include "BinaryTrie.h"
#include "DataNode.h"
#include "common.h"
#include <queue>

class StoreNode {
   public:
    StoreNode(int id);
    ~StoreNode();

    // if key exist, return 1, will not modify
    bool insert(int key, int value, int time_stamp);
    // if key exist, return 1, store in value
    bool query(int key, int& value, int time_stamp);
    // if key exist, return 1, old_value stored in value
    bool update(int key, int& value, int time_stamp);

    void show(int time_stamp);

   private:
    int id;

    // data structrure type
    // 0: array, 1:BST, 2: trie
    int type = 0;

    int size = 0, capacity = 1;
    DataNode** data_list;

    DataNode* data_list_append(int key, int value);

    void transform(int depth);

    /*****************
     * array structure
    *****************/

    // type: 0: insert, 1: query, 2, update
    // return 1 if key exists
    bool array_operation(int key, int& value, int type);
    void array_show();

    /*****************
     * bst structure
    *****************/

    // type: 0: insert, 1: query, 2, update
    // return 1 if key exists
    bool bst_operation(int key, int& value, int type);
    void bst_show();

    DataNode* bst_root;

    void bst_init();
    void bst_append(DataNode* node);

    /*****************
     * trie structure
    *****************/

    // type: 0: insert, 1: query, 2, update
    // return 1 if key exists
    bool trie_operation(int key, int& value, int type);
    void trie_show();

    BinaryTrie* trie;
    void trie_init();

};