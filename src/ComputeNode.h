#pragma once
#include "common.h"
#include "StoreNode.h"

class ComputeNode {
   public:
    ComputeNode(int id, int cache_size);
    // when doing operation
    // insert pair to cache

    // insert into key % n store node
    bool insert(int key, int value, StoreNode* sto);
    // query key % n store node
    bool query(int key, int& value, StoreNode* sto);
    // update in key % n store node
    bool update(int key, int& value, StoreNode* sto);
    // change cache dur to dirty write
    bool update_cache(int key, int value);
    void show(StoreNode* sto);

    // node id
    int id;
   private:
    // cache size
    int k;
    // cache cursor
    int cur;
    // array of cache
    Pair* cache;
    // rank of cache
    int* rnk;
    void rank_top(int cache_id);
    // return 1 if exist
    bool cache_query(int key, int& value, int& pos);
    // insert if not exist, update if key exist
    void cache_insert(int key, int value);
};
