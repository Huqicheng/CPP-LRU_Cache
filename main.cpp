#include <LRU.h>

int main()
{
    LRU::LRUCache * cache = new LRU::LRUCache();
    cache->putValue(2, 2);
    cache->displayNodes();

    if(cache)
    {
        delete cache;
    }
    return 0;
}