#include <Includes.h>

#ifndef LRU_H
#define LRU_H

namespace LRU {

typedef unsigned char Byte;

// Declaration of a double linked list node
template <class DataType>
class CacheNode {
public:
    int key;
    DataType value;
    CacheNode * next; // next node
    CacheNode * pre; // previous node
};

// Declaration of LRU Cache
template <class DataType>
class LRUCache {  
      
public:  
      
    LRUCache(int cache_size = 10); // Constructor
    ~LRUCache(); // Destructor
    DataType getValue(int key);
    bool putValue(int key, DataType value);
    void displayNodes(); // For debugging
       
private:  
      
    int cache_size_;
    int cache_real_size_;
    CacheNode * p_cache_list_head;
    CacheNode * p_cache_list_tail;
    void detachNode(CacheNode<DataType> * node);
    void addToFront(CacheNode<DataType> * node);
};

}

#endif