#include "Node.h"

ComputeNode::ComputeNode(int id, int cache_size) : id(id), k(cache_size) {
    cache = new Pair[k];
}

bool ComputeNode::insert(int key, int value, StoreNode* sto) {
    cache_insert(key, value);
    return sto->insert(key, value);
}

bool ComputeNode::query(int key, int& value, StoreNode* sto) {
    // if in cache
    int _;
    if (cache_query(key, value, _)) {
        return 1;
    }
    return sto->query(key, value);
}

bool ComputeNode::update(int key, int& value, StoreNode* sto) {
    return sto->query(key, value);
}

void ComputeNode::update_cache(int key, int value) {
    int pos, _;
    if (cache_query(key, _, pos)) {
        cache[pos].second = value;
        return;
    }
}

void ComputeNode::show(StoreNode* sto) {
    sto->show();
}

bool ComputeNode::cache_query(int key, int& value, int& pos) {
    for (int i = cur; i < cur + k; i++) {
        if (cache[i % k].first == key) {
            value = cache[i % k].second;
            pos = i % k;
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
    cache[cur] = Pair(key, value);
    cur++;
    cur %= k;
}

DataNode::DataNode(int key = 0, int value = 0) : key(key), value(value){};

StoreNode::StoreNode(int id) : id(id), data_list(new DataNode[capacity]) {
    for (int i = 0; i < capacity; i++) {
        data_list[i].id = i;
    }
}

DataNode* StoreNode::list_append(int key, int value) {
    if (size == capacity) {
        capacity <<= 1;
        DataNode* new_list = new DataNode[capacity];
        for (int i = 0; i < size; i++) {
            new_list[i] = data_list[i];
        }
        for (int i = size; i < capacity; i++) {
            new_list[i].id = i;
        }
        delete[] data_list;
        data_list = new_list;
    }
    data_list[size].key = key;
    data_list[size].value = value;
    return data_list + size++;
}

void StoreNode::transform(int depth) {
    if (type == 0) {
        if (size < 64) return;
        type = 1;
        bst_init();
        return;
    }
    if (type == 1) {
        if (depth < size / 4) return;
        type = 2;
        trie_init();
    }
}

bool StoreNode::insert(int key, int value) {
    bool exist;
    if (type == 0) exist = array_operation(key, value, 0);
    if (type == 1) exist = bst_operation(key, value, 0);
    if (type == 2) exist = trie_operation(key, value, 0);
    transform(value);
    return exist;
}

bool StoreNode::query(int key, int& value) {
    bool exist;
    if (type == 0) exist = array_operation(key, value, 1);
    if (type == 1) exist = bst_operation(key, value, 1);
    if (type == 2) exist = trie_operation(key, value, 1);
    return exist;
}

bool StoreNode::update(int key, int& value) {
    bool exist;
    if (type == 0) exist = array_operation(key, value, 1);
    if (type == 1) exist = bst_operation(key, value, 1);
    if (type == 2) exist = trie_operation(key, value, 1);
    return exist;
}