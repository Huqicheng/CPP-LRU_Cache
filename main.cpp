#include <LRU.h>
using namespace LRU;
int main()
{
    LRUCache<int> cache;
    cache.putValue(2, 2);
    cache.displayNodes();
    return 0;
}