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
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    if(is_goal(init_state.state)){
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        print_search(init_state, begin, end, init_state);
        clear_search();
        return;
    }
    int w =0;
    this->open.push_back(init_state);
    while(!open.empty()){
        State opened = this->open.front();
        this->closed.insert(opened.state);
        this->open.pop_front();

        if(is_goal(opened.state)){
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            print_search(init_state, begin, end, opened);
            clear_search();
            return;
        }
        for (State &next_state : opened.succ())
        {
            if (this->closed.find(next_state.state) != this->closed.end())
                continue;
            this->open.push_back(next_state);
        }
        /*
        if(w < 10){
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

void Search::clear_search(){
    this->open.clear();
    this->closed.clear();
    this->openAstar = priority_queue<State, vector<State>, astarFunct>();
    return;
}
void Search::print_search(State init_state, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, State final_state){
    cout << this->open.size() + this->closed.size() << ",";
    cout << final_state.cost << ",";
    cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << ",";
    cout << "0" << ",";
    cout << manhattan(init_state.state) << endl;
    return;
}