#pragma once
class DataNode {
   public:
    DataNode(int key = 0, int value = 0);

    int key, value, id;
    DataNode* child[2];
};