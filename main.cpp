#include <LRU.h>
using namespace LRU;
int main()
{
    LRUCache<int> * cache = new LRUCache<int>();
    cache->putValue(2, 2);
    cache->displayNodes();

    if(cache)
    {
        delete cache;
    }
    return 0;
}