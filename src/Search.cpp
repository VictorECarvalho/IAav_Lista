#include <iostream>
#include <string>
#include <list>
#include <unordered_set>
#include <chrono>
#include <utility>
#include <optional>
#include "Search.h"
#include "util.h"
#include <iostream>
using namespace std;
void Search::start_search(vector<int> init_state){
    if (this->algorithm == "-bfs") {
        cout << "-bfs" << endl;
        bfs_search(init_state);
    } else if (this->algorithm == "-idfs") {
        cout << "-idfs" << endl;
        idfs_search(init_state);
    } else if (this->algorithm == "-astar") {
        cout << "-astar" << endl;
        astar_search(init_state);
    } else if (this->algorithm == "-idastar") {
        cout << "-idastar" << endl;
        idastar_search(init_state);
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
        this->open.pop_front();

        for (State &next_state : opened.succ())
            {
            if(is_goal(next_state.state)){
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                print_search(init_state, begin, end, next_state);
                clear_search();
                return;
            }
            if (this->closed.find(next_state.state) == this->closed.end()){
                    this->open.push_back(next_state);
                    this->closed.insert(opened.state);
            }
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
            print_search(State(init_state), begin, end, current);

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
void Search::idastar_search(vector<int> init_state){
    State init(init_state);
    int limit = manhattan(init.state);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(limit != -1){
        auto result = rec_search(init, limit);
        limit = get<0>(result);
        if(get<1>(result).cost != -1){
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            print_search(init, begin, end, get<1>(result));
            clear_search();
            return;
        }
    }
}
tuple<int, State> Search::rec_search(State state, int limit){
    if(manhattan(state.state) > limit){
        return make_tuple(manhattan(state.state), State());
    }
    if(is_goal(state.state)){
        return make_tuple(0, state);
    }
    int next_limit = -1;
    for(State &next_state : state.succ()){
        optional result = rec_search(next_state, limit);
        
    }
    return make_tuple(next_limit, State());
}
void Search::gbfs_search(vector<int> init_state){
    return;
}
void Search::idfs_search(vector<int> init_state){
    int limit = 0;
    State init(init_state);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(limit != -1){
        State result = depth_limit_search(init, limit);
        if(result.cost != -1){
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            print_search(State(init_state), begin, end, result);
            clear_search();
            return;
        }
        limit++;
    }
    return;
}
State Search::depth_limit_search(State init_state, int limit){
    closed.insert(init_state.state);
    if(limit < 0){
        return State();
    }
    if(is_goal(init_state.state)){
        return init_state;
    }
    if(limit > 0){        
        for(State &next_state : init_state.succ()){
            State result = depth_limit_search(next_state, limit - 1);
            if(result.cost != -1){                
                return result;
            }
        }
    }
    return State();

}







void Search::clear_search(){
    this->open.clear();
    this->closed.clear();
    this->openAstar = priority_queue<State, vector<State>, astarFunct>();
    return;
}
void Search::print_search(State init_state, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, State final_state){
    //expanded nodes
    cout <<  this->closed.size() << ",";
    cout << this->open.size() << ",";
    cout << this->open.size() + this->closed.size() << ",";
    cout << final_state.cost << ",";
    cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << ",";
    cout << "0" << ",";
    cout << manhattan(init_state.state) << endl;
    return;
}