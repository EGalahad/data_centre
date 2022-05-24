#pragma once
#include "common.h"
class ComputeNode;
class StoreNode;

class DataBase {
   public:
    DataBase(int com_node, int num_store_node, int cache_size);
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
    int num_compute_node, num_store_node;
    int cache_size;

    ComputeNode** computers;
    ComputeNode* get_min_ops();

    StoreNode** disks;

    void broadcast_update_cache(int key, int value, int time_stamp);
};