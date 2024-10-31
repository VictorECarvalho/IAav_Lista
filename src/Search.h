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

struct Uint64Hash {
    std::size_t operator()(const uint64_t& v) const {
        return std::hash<uint64_t>{}(v);
    }
};

struct astarFunct 
{
    bool operator()(const State& s1, const State& s2) 
    {
        if (s1.cost + s1.h != s2.cost + s2.h)
            return (s1.cost + s1.h) > (s2.cost + s2.h);
        else if (s1.h != s2.h)
            return s1.h > s2.h;
        else
            return s1.sequence < s2.sequence;
    }
};

struct astarFunct_15 
{
    bool operator()(const State& s1, const State& s2) 
    {
        if (s1.cost + manhattan_15(s1.packed_state) != s2.cost + manhattan_15(s1.packed_state))
            return (s1.cost + s1.h) > (s2.cost + s2.h);
        if (s1.h != s2.h)
            return manhattan_15(s1.packed_state) > manhattan_15(s1.packed_state);
        return s1.sequence < s2.sequence;
    }
};


struct gbfsFunct 
{
    bool operator()(const State& s1, const State& s2) 
    {
        if (s1.h != s2.h)
            return (s1.h) > (s2.h);
        if (s1.cost != s2.cost)
            return s1.cost < s2.cost;
        return s1.sequence < s2.sequence;
    }
};

class Search {
    public:     
        string algorithm;
        list<State> open;
        int expanded = 0;
        unordered_set<vector<int>, VectorHash> closed;  
        unordered_set<uint64_t, Uint64Hash> closed_15;  
        priority_queue<State, vector<State>, astarFunct> openAstar;
        priority_queue<State, vector<State>, astarFunct_15> openAstar_15;
        priority_queue<State, vector<State>, gbfsFunct> openGbfs;
        
        Search(){
            algorithm = "";
        }
        Search(string alg){
            algorithm = alg;
        }
        void start_search(vector<int> state);
        //void start_search_15(uint64_t init_state);
        void bfs_search(vector<int> state);
        void astar_search(vector<int> init_state);
        //void astar_search_15(uint64_t init_state);
        void idastar_search(vector<int> init_state);
        void gbfs_search(vector<int> init_state);
        void idfs_search(vector<int> init_state);
        void clear_search();
        void print_search(State init_state, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, State final_state, float avr);
        tuple<float, State> rec_search(State state, float limit);
        State depth_limit_search(State state, int limit);
        //void print_search_15(State init_state, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, State final_state,float avr);
};