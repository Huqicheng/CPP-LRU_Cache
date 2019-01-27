#include <Includes.h>

#ifndef LRU_H
#define LRU_H

namespace LRU {

// definition of a double linked list node
typedef struct CacheNode {
    int key;
    int value;
    struct CacheNode * next; // next node
    struct CacheNode * pre; // previous node
} CacheNode;

class LRUCache {  
      
public:  
      
    LRUCache(int cache_size = 10); //Constructor
    ~LRUCache(); //Destructor
    int getValue(int key);
    bool putValue(int key, int value);
    void displayNodes(); // For debugging
       
private:  
      
    int cache_size_;
    int cache_real_size_;
    CacheNode * p_cache_list_head;
    CacheNode * p_cache_list_tail;
    void detachNode(CacheNode * node);
    void addToFront(CacheNode * node);
};

}

#endif