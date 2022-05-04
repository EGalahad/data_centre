#pragma once
#include "Node.h"

class DataBase {
   public:
    DataBase(int com_node, int sto_node, int cache_size);
    ~DataBase();
    // return 1 if exists
    bool Insert(int key, int value);
    // return 1 if exists, 0 if not found
    bool Query(int key, int& value);
    // insert if not found
    // remember to update others' cache as well
    bool Update(int key, int& value);
    // display contents in store node
    void show_store(int id);

   private:
    int com_node, sto_node;
    int cache_size;
    
    // use computers[cur++] to do the operation
    int cur = 0;
    ComputeNode** computers;
    StoreNode** disks;

    void UpdateCache(int key, int value);
};