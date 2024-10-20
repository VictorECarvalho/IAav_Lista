#include <iostream>
#include <string>
#include <list>
#include <unordered_set>
#include "Search.h"
#include "util.h"

#include <iostream>

void Search::start_search(vector<int> init_state){
    if (this->algorithm == "-bfs") {
        cout << "-bfs" << endl;
        bfs_search(init_state);
    } else if (this->algorithm == "-idfs") {
    } else if (this->algorithm == "-astar") {
    } else if (this->algorithm == "-idastar") {
    } else if (this->algorithm == "-gbfs") {
    } 
    return;
}
void Search::bfs_search(vector<int> state){
    State init_state(state);
    this->open.push_back(init_state);
    while(!open.empty()){
        State opened = this->open.front();
        this->open.pop_front();
        if(is_goal(opened.state)){
            cout << "achei :)" << endl;
        }
        open.splice(open.end(), opened.succ());
    }
    return;
}