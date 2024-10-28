#include <iostream>
#include <string>
#include <list>
#include <unordered_set>
#include <vector>
#include <chrono>
#include <utility>
#include "State.h"
#include "util.h"
#include <functional> // For hash
#include <queue>

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

struct astarFunct 
{
    bool operator()(const State& s1, const State& s2) 
    {
        if (s1.cost + manhattan(s1.state) != s2.cost + manhattan(s2.state))
            return (s1.cost + manhattan(s1.state)) > (s2.cost + manhattan(s2.state));
        if (manhattan(s1.state) != manhattan(s2.state))
            return manhattan(s1.state) > manhattan(s2.state);
        return s1.sequence > s2.sequence;
    }
};

class Search {
    public:     
        string algorithm;
        list<State> open;
        unordered_set<vector<int>, VectorHash> closed;  
        priority_queue<State, vector<State>, astarFunct> openAstar;
        Search(){
            algorithm = "";
        }
        Search(string alg){
            algorithm = alg;
        }
        void start_search(vector<int> state);
        void bfs_search(vector<int> state);
        void astar_search(vector<int> init_state);
        void idastar_search(vector<int> init_state);
        void gbfs_search(vector<int> init_state);
        void idfs_search(vector<int> init_state);
        void clear_search();
        void print_search(State init_state, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, State final_state);
        tuple<float, State> rec_search(State state, float limit);
        State depth_limit_search(State state, int limit);
};