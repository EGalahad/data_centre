#include "ComputeNode.h"
/*****************************
 * public API for compute node
 *****************************/

ComputeNode::ComputeNode(int id, int cache_size) : id(id), k(cache_size) {
#ifdef DEBUG
    cout << "initializing compute node #" << id << endl;
#endif  // DEBUG
    cache = new Pair[k];
    cache_time = new int[k];
    for (int i = 0; i < k; i++) {
        cache_time[i] = -1;
    }
}

bool ComputeNode::insert(int key, int value, StoreNode* sto, int time_stamp) {
    cout << "Visiting Computing node " << id << " at time " << time_stamp << endl;
    bool exist = sto->insert(key, value, time_stamp);
    if (!exist) cache_insert(key, value, time_stamp);
    return exist;
}

bool ComputeNode::query(int key, int& value, StoreNode* sto, int time_stamp) {
    cout << "Visiting Computing node " << id << " at time " << time_stamp << endl;
    int _;
    if (cache_query(key, value, _, time_stamp)) {
        if (value == -1) return 0;
        return 1;
    }
    bool exist = sto->query(key, value, time_stamp);
    if (exist) cache_insert(key, value, time_stamp);
    if (!exist) cache_insert(key, -1, time_stamp);
    return exist;
}

bool ComputeNode::update(int key, int& value, StoreNode* sto, int time_stamp) {
    cout << "Visiting Computing node " << id << " at time " << time_stamp << endl;
    return sto->update(key, value, time_stamp);
}

bool ComputeNode::update_cache(int key, int value, int time_stamp) {
    int pos, _;
    if (cache_query(key, _, pos, time_stamp)) {
        cout << "Visiting Computing node " << id << " at time " << time_stamp << endl;
        cache[pos].second = value;
#ifdef DEBUG_UPDATE
        cout << "[update cache] [compute node" << id << "]";
#endif  // DEBUG_UPDATE
        return 1;
    }
    return 0;
}

void ComputeNode::show(StoreNode* sto, int time_stamp) {
    cout << "Visiting Computing node " << id << " at time " << time_stamp << endl;
    sto->show(time_stamp);
}

/*****************************
 * private API for compute node
 *****************************/

// return 1 if exists in cache and update the cache_time
bool ComputeNode::cache_query(int key, int& value, int& pos, int time_stamp) {
    for (int i = 0; i < k; i++) {
        if (cache[i].first == key) {
            value = cache[i].second;
            pos = i;
            cache_time[i] = time_stamp;
            return 1;
        }
    }
    return 0;
}

void ComputeNode::cache_insert(int key, int value, int time_stamp) {
    int pos = 0, old_value = 0;
    // if key is in cache
    if (cache_query(key, old_value, pos, time_stamp)) {
        cache[pos].second = value;
        return;
    }
    // find least used and insert
    int victim_id = 0, min = cache_time[0];
    for (int i = 0; i < k; i++) {
        if (cache_time[i] < min) min = cache_time[i], victim_id = i;
    }
    cache[victim_id] = Pair(key, value);
    cache_time[victim_id] = time_stamp;
}
ComputeNode::~ComputeNode() {
    delete[] cache;
    delete[] cache_time;
}
