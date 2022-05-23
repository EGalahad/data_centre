#pragma once
#include "common.h"

class DataNode {
   public:
    DataNode(int id, int key = 0, int value = 0);

    int id, key, value;
};