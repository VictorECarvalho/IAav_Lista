#include <iostream>
#include <string>
#include <list>
#include <unordered_set>
#include <vector>
#include "State.h"
#include <functional> // For hash

using namespace std;
// Custom hash function for vector<int>
struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        size_t seed = v.size();
        for (auto& i : v) {
            seed ^= hash<int>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

class Search {
    public:     
        string algorithm;
        list<State> open;
        unordered_set<vector<int>, VectorHash> closed;  
        Search(){
            algorithm = "";
        }
        Search(string alg){
            algorithm = alg;
        }
        void start_search(vector<int> state);
        void bfs_search(vector<int> state);
};