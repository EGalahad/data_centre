#include "DataBase.h"

#include <iostream>
using std::cout;
using std::endl;

#include "ComputeNode.h"
#include "StoreNode.h"
/*****************************
 * public API for database
 *****************************/

DataBase::DataBase(int num_compute_node, int num_store_node, int cache_size)
    : num_compute_node(num_compute_node), num_store_node(num_store_node), cache_size(cache_size) {
    computers = new ComputeNode *[num_compute_node];
    disks = new StoreNode *[num_store_node];
    for (int id = 0; id < num_compute_node; id++) {
        computers[id] = new ComputeNode(id, cache_size);
    }
    for (int id = 0; id < num_store_node; id++) {
        disks[id] = new StoreNode(id);
    }
}

int DataBase::Insert(int key, int value, int time_stamp, int id) {
    auto worker = (id == -1) ? get_min_ops() : computers[id];
    if (worker->time_stamp == time_stamp) {
#ifdef DEBUG_REJECT
        cout << "[DataBase.insert]: operation rejected. worker #" << worker->id_compute_node
             << " timestamp = " << worker->time_stamp
             << " now time stamp = " << time_stamp << endl;
#endif  // DEBUG_REJECT
        return -1;
    }
    worker->ops++, worker->time_stamp = time_stamp;
    bool exist = worker->insert(key, value, disks[key % num_store_node], time_stamp);
    return exist;
}
int DataBase::Query(int key, int &value, int time_stamp, int id) {
    auto worker = (id == -1) ? get_min_ops() : computers[id];
    if (worker->time_stamp == time_stamp) {
#ifdef DEBUG_REJECT
        cout << "[DataBase.query]: operation rejected. worker #" << worker->id_compute_node
             << " timestamp = " << worker->time_stamp
             << " now time stamp = " << time_stamp << endl;
#endif  // DEBUG_REJECT
        return -1;
    }
    worker->ops++, worker->time_stamp = time_stamp;
    bool exist = worker->query(key, value, disks[key % num_store_node], time_stamp);
    return exist;
}
int DataBase::Update(int key, int &value, int time_stamp, int id) {
    auto worker = (id == -1) ? get_min_ops() : computers[id];
    if (worker->time_stamp == time_stamp) {
#ifdef DEBUG_REJECT
        cout << "[DataBase.getnode]: operation rejected. worker #" << worker->id_compute_node
             << " timestamp = " << worker->time_stamp
             << " now time stamp = " << time_stamp << endl;
        for (int i = 0; i < num_compute_node; i++) {
            cout << "\t\t" << i;
        }
        cout << endl;
        cout << "\ttime_stamp of computers" << endl;
        for (int i = 0; i < num_compute_node; i++) {
            cout << "\t" << computers[i]->time_stamp;
        }
        cout << endl;
        cout << "\tops of computers" << endl;
        for (int i = 0; i < num_compute_node; i++) {
            cout << "\t" << computers[i]->ops << "\t";
        }
        cout << endl;
#endif  // DEBUG_REJECT
        return -1;
    }
    worker->ops++, worker->time_stamp = time_stamp;
    int new_value = value;
    bool exist = worker->update(key, value, disks[key % num_store_node], time_stamp);
    if (exist) broadcast_update_cache(key, new_value, time_stamp);
    return exist;
}

int DataBase::GetNode(int store_id, int time_stamp, int id) {
    auto worker = (id == -1) ? get_min_ops() : computers[id];
    if (worker->time_stamp == time_stamp) {
#ifdef DEBUG_REJECT
        cout << "[DataBase.getnode]: operation rejected. worker #" << worker->id_compute_node
             << " timestamp = " << worker->time_stamp
             << " now time stamp = " << time_stamp << endl;
        for (int i = 0; i < num_compute_node; i++) {
            cout << "\t\t" << i;
        }
        cout << endl;
        cout << "\ttime_stamp of computers" << endl;
        for (int i = 0; i < num_compute_node; i++) {
            cout << "\t" << computers[i]->time_stamp;
        }
        cout << endl;
        cout << "\tops of computers" << endl;
        for (int i = 0; i < num_compute_node; i++) {
            cout << "\t" << computers[i]->ops << "\t";
        }
        cout << endl;
#endif  // DEBUG_REJECT
        return -1;
    }
    worker->ops++, worker->time_stamp = time_stamp;
    worker->show(disks[store_id], time_stamp);
    return 0;
}

/*****************************
 * private API for database
 *****************************/

void DataBase::broadcast_update_cache(int key, int value, int time_stamp) {
    for (int i = 0; i < num_compute_node; i++) {
        auto worker = computers[num_compute_node - 1 - i];
        bool exist = worker->update_cache(key, value, time_stamp);
        if (exist) worker->time_stamp = time_stamp;
    }
}

ComputeNode *DataBase::get_min_ops() {
    int index = 0, min_ops = computers[0]->ops, min_index = 0;
    while (index < num_compute_node) {
        if (computers[index]->ops < min_ops) min_ops = computers[index]->ops, min_index = index;
        index++;
    }
    return computers[min_index];
}
DataBase::~DataBase() {
    for (int i = 0; i < num_compute_node; i++) {
        delete computers[i];
        // computers[i]->~ComputeNode();
    }
    for (int i = 0; i < num_store_node; i++) {
        delete disks[i];
        // disks[i]->~StoreNode();
    }
    delete[] computers;
    delete[] disks;
}
