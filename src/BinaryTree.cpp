#include "BinaryTree.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <queue>
#include <unordered_map>

BinaryTreeNode::BinaryTreeNode(DataNode* data)
    : data(data) {
    for (int i = 0; i < 2; i++) {
        child[i] = nullptr;
    }
}

BinaryTree::BinaryTree(DataNode** data_list, int initial_size) {
    tree_list = new BinaryTreeNode*[tree_capacity /* = 1 */];
    tree_root = tree_list[0] = new BinaryTreeNode(data_list[0]);
    int _;
    for (int i = 1; i < initial_size; i++) {
        tree_append(data_list[i], _);
    }
    update_base = nullptr;
}

BinaryTree::~BinaryTree() {
#ifdef DEBUG_BST
    cout << "[Binary_tree.~BinaryTree()]: destructing bst" << endl;
#endif  // DEBUG_BST
    for (int i = 0; i < tree_size; i++) {
        delete tree_list[i];
    }
    delete[] tree_list;
}

BinaryTreeNode* BinaryTree::tree_list_append(DataNode* data) {
    if (tree_size == tree_capacity) {
        tree_capacity <<= 1;
        BinaryTreeNode** new_tree_list = new BinaryTreeNode*[tree_capacity];
        for (int i = 0; i < tree_size; i++) {
            new_tree_list[i] = tree_list[i];
        }
        delete[] tree_list;
        tree_list = new_tree_list;
    }
    tree_list[tree_size] = new BinaryTreeNode(data);
    return tree_list[tree_size++];
}

bool BinaryTree::tree_append(DataNode* data, int& depth) {
    BinaryTreeNode* cur = tree_root;
    int key = data->key;
    depth = 0;
    while (true) {
        depth++;
        if (key == cur->data->key) {
            return 1;
        }
        bool k = key > cur->data->key;
        if (cur->child[k] == nullptr) {
            cur->child[k] = tree_list_append(data);
            return 0;
        }
        cur = cur->child[k];
    }
}

bool BinaryTree::insert(DataNode* data, int& depth, bool use_update_base) {
    if (use_update_base) {
#ifdef DEBUG
        assert(update_base != nullptr);
        assert(update_base->child[data->key > update_base->data->key] == nullptr);
#endif  // DEBUG
        update_base->child[data->key > update_base->data->key] = tree_list_append(data);
        update_base = nullptr;
        return 0;
    }
    return tree_append(data, depth);
}

bool BinaryTree::operation(int key, int& value, int type) {
    BinaryTreeNode* cur = tree_root;
    int depth = 0;
    bool k = 0;
    while (true) {
        depth++;
        if (key == cur->data->key) {
            if (type == 1) value = cur->data->value;
            if (type == 2) {
                int old_value = cur->data->value;
                cur->data->value = value;
                value = old_value;
            }
            return 1;
        }
        k = key > cur->data->key;
        if (cur->child[k] == nullptr) {
#ifdef DEBUG
            assert(update_base == nullptr);
#endif  // DEBUG
            if (type == 2) update_base = cur;
            return 0;
        }
        cur = cur->child[k];
    }
}

void BinaryTree::show() {
    cout << "Binary Search Tree" << endl;
    BinaryTreeNode** layer = new BinaryTreeNode*[tree_size];
#ifdef DEBUG_BST
    cerr << "[BinaryTree.show]: initializing layer" << endl;
#endif  // DEBUG_BST
    {
        int cnt = 0;
        std::queue<BinaryTreeNode*> Q;
        Q.push(tree_root);
        while (!Q.empty()) {
            BinaryTreeNode* top = Q.front();
            Q.pop();
            layer[cnt++] = top;
            for (int i = 0; i < 2; i++) {
                if (top->child[i]) Q.push(top->child[i]);
            }
        }
    }
#ifdef DEBUG_BST
    cerr << "[BinaryTree.show]: initialized layer" << endl;
#endif  // DEBUG_BST
    std::unordered_map<int, bool> is_child0;
    {
        for (int i = 0; i < tree_size; i++) {
            auto& node = tree_list[i];
            is_child0[node->data->id] = 0;
        }
#ifdef DEBUG_BST
        cerr << "[BinaryTree.show]: initialized is_child0" << endl;
#endif  // DEBUG_BST
        for (int i = 0; i < tree_size; i++) {
            auto& node = tree_list[i];
            if (node->child[0]) {
                is_child0[node->child[0]->data->id] = 1;
            } else if (node->child[1]) {
                is_child0[node->child[1]->data->id] = 1;
            }
        }
    }
    for (int i = 1; i < tree_size; i++) cout << layer[i]->data->key << " ";
    cout << endl;
    for (int i = 1; i < tree_size; i++) cout << is_child0[layer[i]->data->id] << " ";
    cout << endl;
    for (int i = 1; i < tree_size; i++) cout << !(layer[i]->child[0] || layer[i]->child[1]) << " ";
    cout << endl;
    delete[] layer;
}
