#include <bits/stdc++.h>
using namespace std;

class LRUCache
{
public:
    int size;
    list<int> order_of_keys;                                  // MRU ... LRU
    unordered_map<int, list<int>::iterator> position_of_keys; // key -> iterator
    unordered_map<int, int> dictionary;                       // key -> value

    LRUCache(int capacity) : size(capacity) {}
    int get(int key)
    {
        if (dictionary.find(key) == dictionary.end())
            return -1;
        updateLRU(key);
        return dictionary[key];
    }
    void put(int key, int value)
    {
        if (size == 0)
            return; //corner case
        if (dictionary.size() == size && dictionary.find(key) == dictionary.end())
            evict();
        updateLRU(key);
        dictionary[key] = value;
    }
    void updateLRU(int key)
    {
        if (dictionary.find(key) != dictionary.end())
            order_of_keys.erase(position_of_keys[key]);
        order_of_keys.push_front(key);
        position_of_keys[key] = order_of_keys.begin();
    }
    void evict()
    {
        position_of_keys.erase(order_of_keys.back());
        dictionary.erase(order_of_keys.back());
        order_of_keys.pop_back();
    }
};