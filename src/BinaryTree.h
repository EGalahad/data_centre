#pragma once
#include "common.h"

class DataNode;

class BinaryTreeNode {
    DataNode* data;
    BinaryTreeNode* child[2];
    friend class BinaryTree;

   public:
    BinaryTreeNode(DataNode* data);
};

class BinaryTree {
   public:
    BinaryTree(DataNode** data_list, int initial_size);
    ~BinaryTree();
    bool insert(DataNode* data, bool use_update_base = 0);
    bool operation(int key, int& value, int type);
    bool query(int key, int& value);
    bool update(int key, int& value);
    int get_depth() const;
    void show();

   private:
    int depth;
    BinaryTreeNode **tree_list, *tree_root, *update_base;
    int tree_capacity = 1, tree_size = 1;
    BinaryTreeNode* tree_list_append(DataNode* data);
    bool tree_append(DataNode* data);
};