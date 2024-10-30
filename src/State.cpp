#include "State.h"
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include "util.h"
using namespace std;

list<State> State::succ(){
    list<State> succ_list;
    int i = 0;
    for(int d=0;d<this->state.size();d++){
        if(this->state[d] == 0){
            i = d;
            break;
            }
    }
    int d = sqrt(this->state.size());   
    if (this->action != BAIXO) {
        if(i/d >= 1){
            vector<int> temp = this->state;
            temp[i-d] =this->state[i];
            temp[i] =this->state[i-d];
            State new_state(temp, CIMA, this->cost + 1);
            succ_list.push_back(new_state);
        }
    } 
    if (this->action != DIREITA) {
        if((i % d) != 0){     
            vector<int> temp = this->state;
            temp[i-1] =this->state[i];
            temp[i] =this->state[i-1];
            State new_state(temp, ESQUERDA, this->cost + 1);
            succ_list.push_back(new_state);
        }
    } 
    if (this->action != ESQUERDA) {
        if((i % d) != (d - 1)){       
            vector<int> temp = this->state;
            temp[i+1] =this->state[i];
            temp[i] =this->state[i+1];
            State new_state(temp, DIREITA, this->cost + 1);
            succ_list.push_back(new_state);
        }
    } 
    if (this->action != CIMA) {
        if(i/d < (d - 1)){        
            vector<int> temp = this->state;
            temp[i+d] =this->state[i];
            temp[i] =this->state[i+d];
             State new_state(temp, BAIXO, this->cost + 1);
            succ_list.push_back(new_state);
        }
    } 
   /*
    cout << "state in: "<<"i: " << i<< " d: "<< d << endl;
    for(auto i : this->state){
        cout << i << " ";
    }
   cout << "\nsucc_list" << endl;
    for(auto i : succ_list){
        for(auto j : i.state){
            cout << j << " ";
        }
        cout << "cost: " << i.action << " ";
       cout << endl;
    }
   cout << "end succ_list" << endl; //*/
    return succ_list;
}

