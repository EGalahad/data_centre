#include "DataBase.h"

DataBase::DataBase(int com_node, int sto_node, int cache_size) : com_node(com_node), sto_node(sto_node), cache_size(cache_size) { 
    for (int i = 0; i < com_node; i++) {
        computers[i] = new ComputeNode(i, cache_size);
    }
    for (int i = 0; i < sto_node; i++) {
        disks[i] = new StoreNode(i);
    }
}

bool DataBase::Insert(int key, int value) {
    return computers[cur++]->insert(key / sto_node, value, disks[key % sto_node]);
}
bool DataBase::Query(int key, int& value) {
    return computers[cur++]->query(key / sto_node, value, disks[key % sto_node]);
}
bool DataBase::Update(int key, int& value) {
    int new_value = value;
    bool exist = computers[cur++]->update(key / sto_node, value, disks[key % sto_node]);
    if (exist) UpdateCache(key, new_value);
    return exist;
}

void DataBase::show_store(int id) {
    computers[cur++]->show(disks[id]);
}

void DataBase::UpdateCache(int key, int value) {
    for (int i = 0; i < com_node; i++) {
        computers[com_node - 1 - i]->update_cache(key, value);
    }
}
