#include "Node.h"

// nodes in the trie, with leaf nodes pointing to the data nodes
class BinaryTrieNode {
   public:
    BinaryTrieNode(bool key = 0, DataNode* data = nullptr);
    bool key;
    DataNode* data;
    BinaryTrieNode* child[2];
};

class BinaryTrie {
   public:
    BinaryTrie(DataNode* data_list, int initial_size);
    bool insert(DataNode* node, bool use_query_result = 0);
    // type 1: query 2: update
    bool operation(int key, int& value, int type);

   private:
    BinaryTrieNode *trie_list, *trie_root, *query_result;
    int trie_capacity = 1, trie_size = 0;
    BinaryTrieNode* trie_list_append(bool key, DataNode* data);
    bool trie_append(DataNode* data);
};
