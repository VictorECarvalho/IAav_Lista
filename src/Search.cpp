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
    int w =0;
    this->open.push_back(init_state);
    while(!open.empty()){
        int l=0;
        State opened = this->open.back();
        this->closed.insert(opened.state);
        this->open.pop_back();
        l++;

        if(is_goal(opened.state)){
            cout << open.size() + closed.size() << endl;
            return;
        }
        open.splice(open.end(), opened.succ()); 
        /*
        if(w < 10){
            cout << open.size() << endl;
        w++;
            //w = 0;
        }
        cout << "opened" << endl;
            cout << "state: ";
        for(auto i : opened.state){
            cout << i << " ";
            
        }
            cout << endl;
        cout << "open" << endl;
        for(auto i : open){
            cout << "state: " << i.action << "- ";
            for(auto j : i.state){
                cout << j << " ";
            }
            cout << endl;
        }
        //*/
    }
    return;
}