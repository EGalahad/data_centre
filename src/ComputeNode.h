#pragma once
#include "StoreNode.h"
#include "common.h"

class ComputeNode {
   public:
    ComputeNode(int id, int cache_size);
    ~ComputeNode();
    // when doing operation
    // insert pair to cache

    // insert into key % n store node
    bool insert(int key, int value, StoreNode* sto, int time_stamp);
    // query key % n store node
    bool query(int key, int& value, StoreNode* sto, int time_stamp);
    // update in key % n store node
    bool update(int key, int& value, StoreNode* sto, int time_stamp);
    // change cache dur to dirty write
    bool update_cache(int key, int value, int time_stamp);
    void show(StoreNode* sto, int time_stamp);

    // node id
    int id;
    // most recent time stamp
    int time_stamp = -1;
    // is cache available
    bool busy = 0;
    // number of operations
    int ops = 0;

   private:
    /*****************
     * cache related
     *****************/
    // cache size
    int k;
    // array of cache
    Pair* cache;
    // rank of cache
    int* cache_time;
    // return 1 if exist
    bool cache_query(int key, int& value, int& pos, int time_stamp);
    // insert if not exist, update if key exist
    void cache_insert(int key, int value, int time_stamp);
};
