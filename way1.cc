#include <bits/stdc++.h>
using namespace std;
class LRUCache
{
public:
    int cap, nowtime = INT_MIN + 1;
    unordered_map<int, pair<int, int>> cache;
    map<int, int> track;
    LRUCache(int capacity)
    {
        cap = capacity;
    }
    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1; //not in the cache
        update(key);
        return cache[key].first;
    }
    void put(int key, int value)
    {
        if (cap == 0)
            return; //corner case
        if (cache.find(key) == cache.end())
        { //new element
            if (cache.size() == cap)
                evict(); //if overflow then evicting first
            cache[key] = pair<int, int>(value, INT_MIN);
        }
        else
        { //old element
            cache[key].first = value;
        }
        update(key);
    }
    void update(int key)
    {
        track.erase(cache[key].second); //wont throw exception even if it doesnt exist
        cache[key].second = nowtime;
        track[nowtime] = key;
        nowtime++;
    }
    void evict()
    {
        auto it = track.begin();
        cache.erase(it->second);
        track.erase(it);
    }
};
