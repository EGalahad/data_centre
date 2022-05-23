#include "StoreNode.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <queue>

/*****************************
 * public API for store node
 *****************************/

StoreNode::StoreNode(int id) : id_store_node(id), data_list(new DataNode*[capacity]) {
    // for (int i = 0; i < size; i++) {
    //     data_list[i] = new DataNode(i);
    // }
    trie = nullptr;
    // tree = nullptr;
}

bool StoreNode::insert(int key, int value, int time_stamp) {
    cout << "Visiting data node " << id_store_node << " at time " << time_stamp << endl;
    bool exist;
    if (type_store_structure == 0) exist = array_operation(key, value, 0);
    if (type_store_structure == 1) exist = bst_operation(key, value, 0);
    if (type_store_structure == 2) exist = trie_operation(key, value, 0);
    transform();
    return exist;
}

bool StoreNode::query(int key, int& value, int time_stamp) {
    cout << "Visiting data node " << id_store_node << " at time " << time_stamp << endl;
    bool exist;
    if (type_store_structure == 0) exist = array_operation(key, value, 1);
    if (type_store_structure == 1) exist = bst_operation(key, value, 1);
    if (type_store_structure == 2) exist = trie_operation(key, value, 1);
    return exist;
}

bool StoreNode::update(int key, int& value, int time_stamp) {
    cout << "Visiting data node " << id_store_node << " at time " << time_stamp << endl;
    bool exist;
    if (type_store_structure == 0) exist = array_operation(key, value, 2);
    if (type_store_structure == 1) exist = bst_operation(key, value, 2);
    if (type_store_structure == 2) exist = trie_operation(key, value, 2);
    transform();
    return exist;
}

void StoreNode::show(int time_stamp) {
    cout << "Visiting data node " << id_store_node << " at time " << time_stamp << endl;
    if (type_store_structure == 0) array_show();
    if (type_store_structure == 1) bst_show();
    if (type_store_structure == 2) trie_show();
}

StoreNode::~StoreNode() {
   for (int i = 0; i < size; i++) {
        delete data_list[i];
    }
    delete[] data_list;
    if (tree) delete tree;
    if (trie) delete trie;
}

/*****************************
 * private API for store node
 *****************************/

DataNode* StoreNode::data_list_append(int key, int value) {
    if (size == capacity) {
        capacity <<= 1;
        DataNode** new_list = new DataNode*[capacity];
        for (int i = 0; i < size; i++) {
            new_list[i] = data_list[i];
        }
        delete[] data_list;
        data_list = new_list;
    }
    data_list[size] = new DataNode(size, key, value);
    return data_list[size++];
}

void StoreNode::transform() {
    if (type_store_structure == 0) {
        if (size < 64) return;
        type_store_structure = 1;
        bst_init();
        return;
    }
    if (type_store_structure == 1) {
        if (tree->get_depth() <= size / 6) return;
        type_store_structure = 2;
#ifdef DEBUG_TRANS
        cout << "[StoreNode.transform]: store node #" << id_store_node << " transforming to trie" << endl;
#endif  // DEBUG_TRANS
        trie_init();
        delete tree, tree = nullptr;
    }
}

/*****************************************
 * private APIs for array structure
 **********************************************/
bool StoreNode::array_operation(int key, int& value, int type) {
    for (int i = 0; i < size; i++) {
        if (data_list[i]->key == key) {
            // if insert(type == 0), not successful, return 1
            if (type == 1) value = data_list[i]->value;
            if (type == 2) {
                int old_value = data_list[i]->value;
                data_list[i]->value = value;
                value = old_value;
            }
            return 1;
        }
    }
    // not found
    if (type == 1) return 0;
    data_list_append(key, value);
    return 0;
}

void StoreNode::array_show() {
    cout << "Array" << endl;
    for (int i = 0; i < size; i++) {
        cout << data_list[i]->key;
        if (i < size - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}

/*****************************************
 * private APIs for binary tree structure
 **********************************************/

void StoreNode::bst_init() {
    tree = new BinaryTree(data_list, size);
}

bool StoreNode::bst_operation(int key, int& value, int type) {
    if (type == 0) return tree->insert(data_list_append(key, value));
    if (type == 1) return tree->operation(key, value, 1);
    if (type == 2) {
        bool exist = tree->operation(key, value, 2);
        if (!exist) tree->insert(data_list_append(key, value), true);
        return exist;
    }
}

void StoreNode::bst_show() {
    tree->show();
}

/*****************************************
 * private APIs for trie structure
 **********************************************/

void StoreNode::trie_init() {
    trie = new BinaryTrie(data_list, size);
}

bool StoreNode::trie_operation(int key, int& value, int type) {
    if (type == 0) return trie->insert(data_list_append(key, value));
    if (type == 1) return trie->operation(key, value, 1);
    if (type == 2) {
        bool exist = trie->operation(key, value, 2);
        if (!exist) trie->insert(data_list_append(key, value), true);
        return exist;
    }
}

void StoreNode::trie_show() {
    trie->show();
}
