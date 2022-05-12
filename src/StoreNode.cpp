#include "StoreNode.h"
/*****************************
 * public API for store node
 *****************************/

StoreNode::StoreNode(int id) : id(id), data_list(new DataNode*[capacity]) {
#ifdef DEBUG
    cout << "initializing list of data node possessed by store node" << endl;
#endif  // DEBUG
    for (int i = 0; i < size; i++) {
        data_list[i] = new DataNode(i);
    }
    trie = nullptr;
}

bool StoreNode::insert(int key, int value, int time_stamp) {
    cout << "Visiting data node " << id << " at time " << time_stamp << endl;
    bool exist;
    if (type == 0) exist = array_operation(key, value, 0);
    if (type == 1) exist = bst_operation(key, value, 0);
    if (type == 2) exist = trie_operation(key, value, 0);
    transform(value);
    return exist;
}

bool StoreNode::query(int key, int& value, int time_stamp) {
    cout << "Visiting data node " << id << " at time " << time_stamp << endl;
    bool exist;
    if (type == 0) exist = array_operation(key, value, 1);
    if (type == 1) exist = bst_operation(key, value, 1);
    if (type == 2) exist = trie_operation(key, value, 1);
    return exist;
}

bool StoreNode::update(int key, int& value, int time_stamp) {
    cout << "Visiting data node " << id << " at time " << time_stamp << endl;
    bool exist;
    if (type == 0) exist = array_operation(key, value, 2);
    if (type == 1) exist = bst_operation(key, value, 2);
    if (type == 2) exist = trie_operation(key, value, 2);
    return exist;
}

void StoreNode::show(int time_stamp) {
    cout << "Visiting data node " << id << " at time " << time_stamp << endl;
    if (type == 0) array_show();
    if (type == 1) bst_show();
    if (type == 2) trie_show();
}

StoreNode::~StoreNode() {
    for (int i = 0; i < capacity; i++) {
        delete data_list[i];
    }
    delete[] data_list;
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

void StoreNode::transform(int depth) {
    if (type == 0) {
        if (size < 64) return;
        type = 1;
        bst_init();
        return;
    }
    if (type == 1) {
        if (depth < size / 6) return;
        type = 2;
        trie_init();
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
        k = key > cur->key;
        if (cur->child[k] == nullptr) {
            if (type == 1) return 0;
            cur->child[k] = data_list_append(key, value);
            value = depth;
            return 0;
        }
        cur = cur->child[k];
        continue;
    }
}

void StoreNode::bst_init() {
    bst_root = data_list[0];
    for (int i = 1; i < size; i++) {
#ifdef DEBUG_BST
        cout << "transfroming: appending the " << i << "th datanode in datalist" << endl;
#endif  // DEBUG_BST
        bst_append(data_list[i]);
    }
}

void StoreNode::bst_append(DataNode* node) {
    DataNode* cur = bst_root;
    int key = node->key;
    bool k = 0;
    int depth = 0;
    while (true) {
#ifdef DEBUG_BST
        cout << "traversing depth: " << depth++ << endl;
#endif  // DEBUG_BST
        k = key > cur->key;
        if (cur->child[k] == nullptr) {
            cur->child[k] = node;
            return;
        }
        cur = cur->child[k];
    }
}

void StoreNode::bst_show() {
    cout << "Binary Search Tree" << endl;
    bool* is_child0 = new bool[size];
    {
        for (int i = 0; i < size; i++) is_child0[i] = 0;
        for (int i = 0; i < size; i++) {
            auto& data = data_list[i];
            if (data->child[0]) {
                is_child0[data->child[0]->id] = 1;
            } else if (data->child[1]) {
                is_child0[data->child[1]->id] = 1;
            }
        }
    }
    // layer travese
    DataNode** layer = new DataNode*[size];
    {
        int cnt = 0;
        std::queue<DataNode*> Q;
        Q.push(bst_root);
        while (!Q.empty()) {
            DataNode* top = Q.front();
            Q.pop();
            layer[cnt++] = top;
            for (int i = 0; i < 2; i++) {
                if (top->child[i]) Q.push(top->child[i]);
            }
        }
    }

    for (int i = 0; i < size; i++) cout << layer[i]->key << " ";
    cout << endl;
    for (int i = 0; i < size; i++) cout << is_child0[layer[i]->id] << " ";
    cout << endl;
    for (int i = 0; i < size; i++) cout << !(layer[i]->child[0] || layer[i]->child[1]) << " ";
    cout << endl;
    delete[] is_child0;
    delete[] layer;
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
