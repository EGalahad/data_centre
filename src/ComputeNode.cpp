#include "ComputeNode.h"
/*****************************
 * public API for compute node
 *****************************/

ComputeNode::ComputeNode(int id, int cache_size) : id(id), k(cache_size) {
#ifdef DEBUG
    cout << "initializing compute node #" << id << endl;
#endif  // DEBUG
    cache = new Pair[k];
    rnk = new int[k];
    for (int i = 0; i < k; i++) {
        rnk[i] = i;
    }
}

bool ComputeNode::insert(int key, int value, StoreNode* sto) {
    cout << "Visiting Computing node " << id << endl;
    bool exist = sto->insert(key, value);
    if (!exist) {
        cache_insert(key, value);
    }
    return exist;
}

bool ComputeNode::query(int key, int& value, StoreNode* sto) {
    cout << "Visiting Computing node " << id << endl;
    int _;
    // if in cache
    if (cache_query(key, value, _)) {
        return 1;
    }
    return sto->query(key, value);
}

bool ComputeNode::update(int key, int& value, StoreNode* sto) {
    cout << "Visiting Computing node " << id << endl;
    return sto->update(key, value);
}

bool ComputeNode::update_cache(int key, int value) {
    cout << "Visiting Computing node " << id << endl;
    int pos, _;
    if (cache_query(key, _, pos)) {
        cache[pos].second = value;
        return 1;
    }
    return 0;
}

void ComputeNode::show(StoreNode* sto) {
    cout << "Visiting Computing node " << id << endl;
    sto->show();
}

/*****************************
 * private API for compute node
 *****************************/
void ComputeNode::rank_top(int cache_id) {
    int& old_rank = rnk[cache_id];
    for (int i = 0; i < k; i++) {
        rnk[i] += (rnk[i] < old_rank);
    }
    old_rank = 0;
}

// return 1 if exists in cache and update the rank
bool ComputeNode::cache_query(int key, int& value, int& pos) {
    for (int i = 0; i < k; i++) {
        if (cache[i].first == key) {
            value = cache[i].second;
            pos = i;
            rank_top(pos);
            return 1;
        }
    }
    return 0;
}

void ComputeNode::cache_insert(int key, int value) {
    int pos = 0, old_value = 0;
    // if key is in cache
    if (cache_query(key, old_value, pos)) {
        cache[pos].second = value;
        return;
    }
    // find least used and insert
    int victim_id = 0;
    while (true) {
        if (rnk[victim_id] == k - 1) break;
        ++victim_id;
    }
    cache[victim_id] = Pair(key, value);
    rank_top(victim_id);
}
