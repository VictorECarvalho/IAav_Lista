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
        int n;
        int cost;
        actions action;
        float h;
        static int sum_h;
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
        };
        State(const State& other){
            this->state = other.state;
            this->cost = other.cost;
            this->action = other.action;
            this->n = other.n;
            this->h = other.h;
        };
        State(vector<int> state, actions action, int cost){
            this->state = state;
            this->cost = cost;
            this->action = action;
            this->n = state.size();
            this->h = manhattan(state);
        };
        list<State> succ();
        float idastar_f();
        
};