/*
 * @Author: taobo
 * @Date: 2020-11-04 20:59:04
 * @LastEditTime: 2020-11-05 17:21:51
 */
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int key;
    int value;
    Node(int k, int v):key(k), value(v){}
};

class Lru {
private:
    int n;
    int capacity_;
    list<Node> nodes;
    unordered_map<int, list<Node>::iterator> maps;
public:
    Lru(int c): capacity_(c), n(0) {}
    void set(int k, int v) {
        if (maps.count(k)) {
            nodes.erase(maps[k]);
            nodes.emplace_front(k, v);
            maps[k] = nodes.begin();
        } else {
            if (capacity_ == n) {
                maps.erase((nodes.back()).key);
                nodes.pop_back();
                n--;
            }
            nodes.emplace_front(k, v);
            maps[k] = nodes.begin();
            n++;
        }
    }

    int get(int k) {
        if (n == 0 || maps.count(k) == 0) return -1;
        Node tmp = *maps[k];
        nodes.erase(maps[k]);
        nodes.emplace_front(tmp.key, tmp.value);
        maps[k] = nodes.begin();
        return tmp.value;
    }
};

class Solution {
public:
    /**
     * lru design
     * @param operators int整型vector<vector<>> the ops
     * @param k int整型 the k
     * @return int整型vector
     */
    vector<int> LRU(vector<vector<int> >& operators, int k) {
        // write code here
        vector<int> res;
        Lru objs(k);
        for (auto& vec: operators) {
            if (vec[0] == 1) {
                objs.set(vec[1], vec[2]);
            } else {
                res.push_back(objs.get(vec[1]));
            }
        }
        return res;
    }
};

int main() {
  // pass
}