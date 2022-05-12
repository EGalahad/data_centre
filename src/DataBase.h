#pragma once
#include "ComputeNode.h"
#include "StoreNode.h"

class DataBase {
   public:
    DataBase(int com_node, int sto_node, int cache_size);
    ~DataBase();
    // return 1 if exists
    int Insert(int key, int value, int time_stamp, int id);
    // return 1 if exists, 0 if not found
    int Query(int key, int& value, int time_stamp, int id);
    // insert if not found
    // remember to update others' cache as well
    int Update(int key, int& value, int time_stamp, int id);
    // display contents in store node
    int GetNode(int store_id, int time_stamp, int id);

   private:
    int com_node, sto_node;
    int cache_size;
    
    ComputeNode** computers;
    ComputeNode* get_min_ops();

    StoreNode** disks;

    void BroadCast_UpdateCache(int key, int value, int time_stamp);
};