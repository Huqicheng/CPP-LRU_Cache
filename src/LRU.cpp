#include <Includes.h>
#include <LRU.h>
using namespace LRU;

LRUCache::LRUCache(int cache_size):cache_size_(cache_size), cache_real_size_(0)
{
    // Create initial cache
    p_cache_list_head = new CacheNode();
    p_cache_list_tail = new CacheNode();
    p_cache_list_head->pre = NULL;
    p_cache_list_head->next = p_cache_list_tail;
    p_cache_list_tail->pre = p_cache_list_head;
    p_cache_list_tail->next = NULL;
}

LRUCache::~LRUCache()
{
    // Delete and release all nodes from the LRU list
    CacheNode *p;  
    p = p_cache_list_head->next;  
    while (p!=NULL)  
    {     
        delete p->pre;  
        p = p->next;  
    }
    delete p_cache_list_tail;  
}

int LRUCache::getValue(int key)  
{  
    CacheNode *p=p_cache_list_head->next;      
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

bool LRUCache::putValue(int key, int value)  
{  
    CacheNode *p = p_cache_list_head->next;
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

    p = new CacheNode();
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
  
  
void LRUCache::displayNodes()
{  
    CacheNode *p = p_cache_list_head->next;
    while (p->next!=NULL)
    {  
        std::cout << " Key : " << p->key << " Value : " << p->value << std::endl;
        p=p->next;
          
    }
    std::cout << std::endl;
      
}

// take node from the list, like 'delete' it from the list
void LRUCache::detachNode(CacheNode * node)  
{  
    node->pre->next = node->next;
    node->next->pre = node->pre;
}

// add node the front of the list
void LRUCache::addToFront(CacheNode * node)  
{  
    node->next = p_cache_list_head->next;  
    p_cache_list_head->next->pre = node;  
    p_cache_list_head->next = node; 
    node->pre = p_cache_list_head;  
}  