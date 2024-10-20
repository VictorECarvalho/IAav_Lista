#include "State.h"
#include <iostream>
#include <string>
#include <list>
#include <cmath>
using namespace std;

list<State> State::succ(){
    list<State> succ_list;
    if (this->action != CIMA) {
        succ_list.push_back(make_succ(CIMA));
    } 
    if (this->action != ESQUERDA) {
        succ_list.push_back(make_succ(ESQUERDA));
    } 
    if (this->action != DIREITA) {
        succ_list.push_back(make_succ(DIREITA));
    } 
    if (this->action != BAIXO) {
        succ_list.push_back(make_succ(BAIXO));
    } 
    return succ_list;
}
State State::make_succ(actions action){
    int i = 0;
    for(int d=0;d<this->state.size();d++){
        if(this->state[d] == 0)
            i = d;
    }
    vector<int> temp = this->state;
    int s = this->state.size();
    int d = sqrt(s);   
    if (this->action == CIMA) {
        if(i/d > 1){
            temp[i-d] =this->state[i];
            temp[i] =this->state[i-d];
        }
    } else if (this->action == ESQUERDA) {
        if((i % d) != 0){
            temp[i-1] =this->state[i];
            temp[i] =this->state[i-1];
        }

    } else if (this->action == DIREITA) {
        if((i % d) != (d - 1)){
            temp[i+1] =this->state[i];
            temp[i] =this->state[i+1];
        }
    } else if (this->action == BAIXO) {
        if(i/d < (d - 1)){
            temp[i+d] =this->state[i];
            temp[i] =this->state[i+d];
        }
    }
    State new_state(temp, action, this->cost + 1);
    return new_state;
}