#include "LinkedList.h"

LinkedListNode::LinkedListNode(ComputeNode* node) : node(node), next(nullptr), cnt(0) {
}

LinkedList::LinkedList(ComputeNode** node_list, int size) : size(size) {
    linked_list = (LinkedListNode**)malloc(size * sizeof(LinkedListNode*));
    for (int i = 0; i < size; i++) {
        linked_list[i] = new LinkedListNode(node_list[i]);
        linked_list[i]->next = linked_list[i + 1];
    }
    head = linked_list[0];
}

void LinkedList::incr(ComputeNode* node) {

    auto cur = head;
    if (head->node != node) {
        while (cur->next) {
            if (cur->next->node == node) break;
        }
    }

    auto old_cur = cur;
    auto match = cur->next;
    int match_cnt = match->cnt;
    int match_id = match->node->id;
    match->cnt++;

    while (cur->next) {
        if (cur->next->cnt > match_cnt)
            break;
        else if (cur->next->cnt == match_cnt && cur->next->node->id > match_id)
            break;
        cur = cur->next;
    }
    if (match == cur) return;

    old_cur->next = match->next;
    match->next = cur->next;
    cur->next = match;
}

ComputeNode* LinkedList::get_min() {
    return head->node;
}

LinkedList::~LinkedList() {
    for (int i = 0; i < size; i++) {
        linked_list[i]->~LinkedListNode();
    }
    free(linked_list);
}

// ComputeNode* LinkedList::get_min() {
//     auto worker = head->node;
//     incr(worker);
//     return worker;
// }
