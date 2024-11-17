#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "util.h"
using namespace std;
enum actions{ 
    NONE,
    CIMA,
    ESQUERDA,
    DIREITA,
    BAIXO

};

class State {
    public:     
        vector<int> state;
        uint64_t packed_state;
        int n;
        int cost;
        actions action;
        float h;
        static long double sum_h;
        static long int n_opened;
        static long int id;
        int sequence = 0;
        State(){
            this->cost = -1;
        };
        State(vector<int> init_estate){
            this->state = init_estate;
            this->cost = 0;
            this->action = NONE;
            this->n = init_estate.size();
            this->h = manhattan(init_estate);
            this->sequence = id;
            id++;
        };
        State(const State& other){
            this->state = other.state;
            this->cost = other.cost;
            this->action = other.action;
            this->n = other.n;
            this->h = other.h;
            this->sequence = other.sequence;
        };
        State(vector<int> state, actions action, int cost)
        {
            this->state = state;
            this->cost = cost;
            this->action = action;
            this->n = state.size();
            this->h = manhattan(state);
            this->sequence = id;
            id++;
        };
        State(uint64_t packed_state, actions action, int cost)
        {
            this->packed_state = packed_state;
            this->action = action;
            this->cost = cost;
        };
        list<State> succ();
        list<State> succ_15();
        float idastar_f();
        int getTile(uint64_t state, int pos) const;
        uint64_t setTile(uint64_t state, int pos, int value) const;
};

class State15 {
    public:     
        uint64_t state;
        int n;
        int cost;
        actions action;
        static long double sum_h;
        static long int n_opened;
        static long int id;
        int sequence = 0;
        float h;
        State15(){
            this->cost = -1;
        };
        State15(uint64_t init_estate){
            this->h = manhattan_15(state);
            this->state = init_estate;
            this->cost = 0;
            this->action = NONE;
            this->sequence = id;
            id++;
        };
        State15(const State15& other){
            this->state = other.state;
            this->cost = other.cost;
            this->action = other.action;
            this->n = other.n;
            this->h = other.h;
            this->sequence = other.sequence;
        };
        State15(uint64_t state, actions action, int cost)
        {
            this->h = manhattan_15(state);
            this->state = state;
            this->action = action;
            this->cost = cost;
            this->sequence = id;
            id++;
        };
        list<State15> succ_15();
        float idastar_f();
        int getTile(uint64_t state, int pos) const;
        uint64_t setTile(uint64_t state, int pos, int value) const;
};