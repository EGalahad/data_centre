#pragma once
#include "ComputeNode.h"

class LinkedListNode {
   public:
    LinkedListNode(ComputeNode* node);

    LinkedListNode* next;
   private:
    ComputeNode* node;
    int cnt;
    friend class LinkedList;
};

class LinkedList {
   public:
    LinkedList(ComputeNode** node_list, int size);
    ~LinkedList();
    void incr(ComputeNode* node);
    ComputeNode* get_min();

   private:
   int size;
    LinkedListNode* head;
    LinkedListNode** linked_list;
};
