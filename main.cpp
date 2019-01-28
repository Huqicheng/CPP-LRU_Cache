#include <LRU.h>

int main()
{
    LRU::LRUCache<int> * cache = new LRU::LRUCache<int>();
    cache->putValue(2, 2);
    cache->displayNodes();

    if(cache)
    {
        delete cache;
    }
    return 0;
}