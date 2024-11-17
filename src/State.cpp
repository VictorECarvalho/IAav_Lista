#include "State.h"
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include "util.h"
using namespace std;
long double State::sum_h = 0;
long int State::n_opened = 0;
long int State::id = 0;

int State15::getTile(uint64_t state, int pos) const
{
    return (state >> (pos * 4)) & 0xF; 
}

uint64_t State15::setTile(uint64_t state, int pos, int value) const
{
    state &= ~(0xFULL << (pos * 4));              
    state |= (uint64_t(value & 0xF) << (pos * 4)); 
    return state;
}

list<State> State::succ(){
    list<State> succ_list;
    int i = 0;
    for(int d=0;d<this->state.size();d++){
        if(this->state[d] == 0){
            i = d;
            break;
            }
    }
    int d = sqrt(this->n);  
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

float State::idastar_f(){
    return this->cost + this->h; 
}

std::list<State15> State15::succ_15()
{
    std::list<State15> succ_list;
    int zero_pos = -1;
    int d = 4;
    for (int i = 0; i < 16; i++)
    {
        if (getTile(this->state, i) == 0)
        {
            zero_pos = i;
            //cout << "zeroposition" << i << endl;
            break;
        }
    }

    if (this->action != BAIXO)
    {
        if (zero_pos / d >= 1)
        {
            uint64_t new_packed_state = this->state;
            int above_pos = zero_pos - d;
            int above_tile = getTile(new_packed_state, above_pos);
            new_packed_state = setTile(new_packed_state, zero_pos, above_tile);
            new_packed_state = setTile(new_packed_state, above_pos, 0);
            succ_list.emplace_back(new_packed_state, CIMA, this->cost + 1);
        }
    }
    if (this->action != DIREITA)
    {
        if (zero_pos % d != 0)
        {
            uint64_t new_packed_state = this->state;
            int left_pos = zero_pos - 1;
            int left_tile = getTile(new_packed_state, left_pos);
            new_packed_state = setTile(new_packed_state, zero_pos, left_tile);
            new_packed_state = setTile(new_packed_state, left_pos, 0);
            succ_list.emplace_back(new_packed_state, ESQUERDA, this->cost + 1);
        }
    }
    if (this->action != ESQUERDA)
    {
        if (zero_pos % d != (d - 1))
        {
            uint64_t new_packed_state = this->state;
            int right_pos = zero_pos + 1;
            int right_tile = getTile(new_packed_state, right_pos);
            new_packed_state = setTile(new_packed_state, zero_pos, right_tile);
            new_packed_state = setTile(new_packed_state, right_pos, 0);
            succ_list.emplace_back(new_packed_state, DIREITA, this->cost + 1);
        }
    }
    if (this->action != CIMA)
    {
        if (zero_pos / d < (d - 1))
        {
            uint64_t new_packed_state = this->state;
            int below_pos = zero_pos + d;
            int below_tile = getTile(new_packed_state, below_pos);
            new_packed_state = setTile(new_packed_state, zero_pos, below_tile);
            new_packed_state = setTile(new_packed_state, below_pos, 0);
            succ_list.emplace_back(new_packed_state, BAIXO, this->cost + 1);
        }
    }

    return succ_list;
}