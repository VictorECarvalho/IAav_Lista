#include <iostream>
#include <string>
#include <list>
#include <vector>
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
        static int sum_h;
        int sequence = 0;
        State(){
            this->cost = -1;
        };
        State(vector<int> init_estate){
            this->n = init_estate.size();
            this->state = init_estate;
            this->cost = 0;
            this->action = NONE;
            this->sequence = sequence++; 
        };
        State(const State& other){
            this->state = other.state;
            this->cost = other.cost;
            this->action = other.action;
            this->n = other.n;
            this->sequence = sequence++;
        };
        State(vector<int> state, actions action, int cost){
            this->state = state;
            this->cost = cost;
            this->action = action;
            this->sequence = sequence++;

        };
        list<State> succ();
        
};