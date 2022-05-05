#include "DataBase.h"
/*****************************
 * public API for database
 *****************************/

DataBase::DataBase(int com_node, int sto_node, int cache_size)
    : com_node(com_node), sto_node(sto_node), cache_size(cache_size) {
    computers = (ComputeNode **)malloc(com_node * sizeof(ComputeNode *));
    disks = (StoreNode **)malloc(sto_node * sizeof(StoreNode *));
// computers = new ComputeNode*[com_node];
#ifdef DEBUG
    cout << "initializing database" << endl;
#endif  // DEBUG
    for (int id = 0; id < com_node; id++) {
        computers[id] = new ComputeNode(id, cache_size);
    }
    for (int id = 0; id < sto_node; id++) {
        disks[id] = new StoreNode(id);
    }
}

int DataBase::Insert(int key, int value, int time_stamp, int id) {
    auto worker = (id == -1) ? get_min_ops() : computers[id];
    if (worker->busy || worker->time_stamp == time_stamp) return -1;
    worker->ops++, worker->time_stamp = time_stamp;
#ifdef DEBUG
    cout << "ops: ";
    for (int i = 0; i < com_node; i++) {
        cout << computers[i]->ops << " ";
    }
    cout << endl;
#endif  // DEBUG
    bool exist = worker->insert(key, value, disks[key % sto_node], time_stamp);
    return exist;
}
int DataBase::Query(int key, int &value, int time_stamp, int id) {
    auto worker = (id == -1) ? get_min_ops() : computers[id];
    if (worker->busy || worker->time_stamp == time_stamp) return -1;
    worker->ops++, worker->time_stamp = time_stamp;
    bool exist = worker->query(key, value, disks[key % sto_node], time_stamp);
    return exist;
}
int DataBase::Update(int key, int &value, int time_stamp, int id) {
    auto worker = (id == -1) ? get_min_ops() : computers[id];
    if (worker->busy || worker->time_stamp == time_stamp) return -1;
    worker->ops++, worker->time_stamp = time_stamp;
    int new_value = value;
    bool exist = worker->update(key, value, disks[key % sto_node], time_stamp);
    if (exist) UpdateCache(key, new_value, time_stamp);
    return exist;
}

int DataBase::GetNode(int store_id, int time_stamp, int id) {
    auto worker = (id == -1) ? get_min_ops() : computers[id];
    if (worker->busy || worker->time_stamp == time_stamp) return -1;
    worker->ops++, worker->time_stamp = time_stamp;
    worker->show(disks[store_id], time_stamp);
}

/*****************************
 * private API for database
 *****************************/

void DataBase::UpdateCache(int key, int value, int time_stamp) {
    for (int i = 0; i < com_node; i++) {
        auto worker = computers[com_node - 1 - i];
        worker->busy = 1;
        worker->update_cache(key, value, time_stamp);
        worker->busy = 0;
        // if (worker->update_cache(key, value)) worker->ops++;
    }
}

ComputeNode *DataBase::get_min_ops() {
    int index = 0, min_ops = computers[0]->ops, min_index = 0;
    while (index < com_node) {
        if (computers[index]->ops < min_ops) min_ops = computers[index]->ops, min_index = index;
        index++;
    }
    return computers[min_index];
}
DataBase::~DataBase() {
    for (int i = 0; i < com_node; i++) {
        delete computers[i];
        // computers[i]->~ComputeNode();
    }
    for (int i = 0; i < sto_node; i++) {
        delete disks[i];
        // disks[i]->~StoreNode();
    }
    free(computers);
    free(disks);
}
