#include <iostream>
#include <string>
#include <list>
#include <unordered_set>
#include <chrono>
#include "Search.h"
#include "util.h"

#include <iostream>

void Search::start_search(vector<int> init_state){
    if (this->algorithm == "-bfs") {
        cout << "-bfs" << endl;
        bfs_search(init_state);
    } else if (this->algorithm == "-idfs") {
    } else if (this->algorithm == "-astar") {
        cout << "-astar" << endl;
        astar_search(init_state);
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

void Search::astar_search(vector<int> init_state)
{
    this->openAstar.push(State(init_state, NONE, 0));

    int node_n = 0;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while (!this->openAstar.empty())
    {
        State current = this->openAstar.top();
        this->openAstar.pop();

        if (is_goal(current.state))
        {
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Time elapsed = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

            cout << "Goal cost: " << current.cost << endl;

            return;
        }

        this->closed.insert(current.state);

        for (State &next_state : current.succ())
        {
            if (this->closed.find(next_state.state) != this->closed.end())
                continue;
                
            this->openAstar.push(next_state);
        }
    }

    cout << "No solution" << endl;
}