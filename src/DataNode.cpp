#include "DataNode.h"
/*****************************
 * public API for data node
 *****************************/

DataNode::DataNode(int id, int key /* = 0*/, int value /* = 0*/)
    : id(id), key(key), value(value) {
    for (int i = 0; i < 2; i++) {
        child[i] = nullptr;
    }
};
