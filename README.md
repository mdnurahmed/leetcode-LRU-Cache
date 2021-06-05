# [leetcode-LRU-Cache](https://leetcode.com/problems/lru-cache/)
## Problem Description 

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

```LRUCache(int capacity) ``` Initialize the LRU cache with positive size capacity.
```int get(int key)``` Return the value of the key if the key exists, otherwise return -1.
```void put(int key, int value)``` Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
### Follow up:
Could you do get and put in O(1) time complexity?

### Examples 
Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

### Explanation
```LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 ```

### Constraints:

- 1 <= capacity <= 3000
- 0 <= key <= 3000
- 0 <= value <= 104
At most 3 * 10^4 calls will be made to get and put.

## My Approach
I can have a hashtable for key-value look up for the cache in this problem.Lets call this hashtable dictionary.
I also need to have have some way/data structure to track the relative order of these keys which will be changed every time they are accessed like - get or set , so that when the cache reaches its capacity I know which item needs to be be evicted . 
I can do this 2 ways

### [Way 1](https://github.com/mdnurahmed/leetcode-LRU-Cache/blob/main/way1.cc) 
sorted map with keys = timestamps and values = keys of dictionary . 
Instead of having another lookup table for key - timestamp we can store timestamp in the cache/dictionary. 

Table 1 : (cache/dictionary) is a unordered map 

| key                | values                             | 
| -------------------|------------------------------------|
| keys of cache      | (values of cache,timestamp of keys)|


Table 2 : (track) is an ordered map. tracks least recently used keys as the keys are sorted by timestamps
| key                            | values                    | 
| -------------------------------|---------------------------|
| timestamp of keys in cache     | keys in cache             |

complexity : O(mlogn) time and O(n) space where m is number of operations and n is size of the cache 
caveat : Timestamp could overflow integer . As a contingency plan we could compress the timestamps when they overflow like this . This would take time complexity of O(n) but amortized complexity is O(1) 

```
void compress() {
    if (nowtime == INT_MAX) {
        unordered_map<int, int> timemap;
        int time = INT_MIN + 1;
        for (auto it = track.begin(); it != track.end(); it++) {
            if (timemap.find(it->ff) == timemap.end())
                timemap[it->ff] = time++;
            it->ff = timemap[it->ff];
            cache[it->ss].ss = it->ff;
        }
    }
}

```

### [way 2](https://github.com/mdnurahmed/leetcode-LRU-Cache/blob/main/way2.cc)
I can use a conatiner (linked list is more appropriate data structure for this) . Lets call this order_of_keys. Elements in this container are unique since keys are unique - 

```A-B-C-D // MRU ... LRU```

To maintain the order of the linked list, order_of_keys in O(1) we can have another lookup table .Lets call this position_of_keys
The linked list holds keys in the order they were accessed . So whenever our dictionary reaches capacity ,it will evict the key in rightmost of list and its corresponding value from dictionary . This key will also be removed from order_of_keys list and position_of_keys table 

complexity : O(n) time and O(n) space where n is number of operations.
