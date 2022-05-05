#include "DataBase.h"

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
    lst = new LinkedList(computers, com_node);
}

bool DataBase::Insert(int key, int value) {
    auto worker = lst->get_min();
    lst->incr(worker);
    return worker->insert(key / sto_node, value, disks[key % sto_node]);
}
bool DataBase::Query(int key, int &value) {
    auto worker = lst->get_min();
    lst->incr(worker);
    return worker->query(key / sto_node, value, disks[key % sto_node]);
}
bool DataBase::Update(int key, int &value) {
    auto worker = lst->get_min();
    lst->incr(worker);
    int new_value = value;
    bool exist = worker->update(key / sto_node, value, disks[key % sto_node]);
    if (exist) UpdateCache(key, new_value);
    return exist;
}

void DataBase::show_store(int id) {
    auto worker = lst->get_min();
    lst->incr(worker);
    worker->show(disks[id]);
}

void DataBase::UpdateCache(int key, int value) {
    for (int i = 0; i < com_node; i++) {
        auto worker = computers[com_node - 1 - i];
        if (worker->update_cache(key, value)) lst->incr(worker);
    }
}

DataBase::~DataBase() {
    for (int i = 0; i < com_node; i++) {
        delete computers[i];
    }
    for (int i = 0; i < sto_node; i++) {
        delete disks[i];
    }
    free(computers);
    free(disks);
}
