#include <Includes.h>
#include <LRU.h>
using namespace LRU;

template <class DataType>
LRUCache<DataType>::LRUCache(int cache_size):cache_size_(cache_size), cache_real_size_(0)
{
    // Create initial cache
    p_cache_list_head = new CacheNode<DataType>();
    p_cache_list_tail = new CacheNode<DataType>();
    p_cache_list_head->pre = NULL;
    p_cache_list_head->next = p_cache_list_tail;
    p_cache_list_tail->pre = p_cache_list_head;
    p_cache_list_tail->next = NULL;
}

template <class DataType>
LRUCache<DataType>::~LRUCache()
{
    // Delete and release all nodes from the LRU list
    CacheNode<DataType> * p;  
    p = p_cache_list_head->next;  
    while (p!=NULL)  
    {     
        delete p->pre;  
        p = p->next;  
    }
    delete p_cache_list_tail;  
}

template <class DataType>
DataType LRUCache<DataType>::getValue(int key)  
{  
    CacheNode<DataType> * p=p_cache_list_head->next;      
    while (p->next != NULL)
    {  
        // TODO: get node by HashTable
        if (p->key == key) // get the node
        {
            detachNode(p);
            addToFront(p);
            return p->value;
        }
        p = p->next;
    }  
    return -1;
} 

template <class DataType>
bool LRUCache<DataType>::putValue(int key, DataType value)  
{  
    CacheNode<DataType> * p = p_cache_list_head->next;
    while (p->next != NULL)
    { 
        if (p->key == key) //catch node 
        {
            p->value = value;
            getValue(key);
            return true;
        }
        p=p->next;
    }

    // kick out the last node
    if (cache_real_size_ >= cache_size_)
    {
        std::cout << "free last node" << std::endl;
        p = p_cache_list_tail->pre->pre;
        delete p->next;
        p->next = p_cache_list_tail;
        p_cache_list_tail->pre = p;
    }

    p = new CacheNode<DataType>();
    if (p == NULL)
    {
        return false;
    }
        
    addToFront(p);
    p->key = key;
    p->value = value;
    cache_real_size_ ++; // TODO: using linux atomic operations
    return true;
}  
  
template <class DataType>
void LRUCache<DataType>::displayNodes()
{  
    CacheNode<DataType> *p = p_cache_list_head->next;
    while (p->next!=NULL)
    {  
        std::cout << " Key : " << p->key << " Value : " << p->value << std::endl;
        p=p->next;
          
    }
    std::cout << std::endl;
      
}

// take node from the list, like 'delete' it from the list
template <class DataType>
void LRUCache<DataType>::detachNode(CacheNode<DataType> * node)  
{  
    node->pre->next = node->next;
    node->next->pre = node->pre;
}

// add node the front of the list
template <class DataType>
void LRUCache<DataType>::addToFront(CacheNode<DataType> * node)  
{  
    node->next = p_cache_list_head->next;  
    p_cache_list_head->next->pre = node;  
    p_cache_list_head->next = node; 
    node->pre = p_cache_list_head;  
}  