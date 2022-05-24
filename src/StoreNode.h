#pragma once
#include "common.h"

class DataNode;
class BinaryTree;
class BinaryTrie;

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
    int id_store_node;

    // data structrure type
    // 0: array, 1:BST, 2: trie
    int type_store_structure = 0;

    int size = 0, capacity = 1;
    DataNode** data_list;

    DataNode* data_list_append(int key, int value);

    void transform();

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

    BinaryTree* tree;
    void bst_init();

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