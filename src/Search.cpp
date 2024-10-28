#include <iostream>
#include <string>
#include <list>
#include <unordered_set>
#include <chrono>
#include <utility>
#include <optional>
#include <iomanip> 
#include "Search.h"
#include "util.h"
#include <iostream>
#include <limits>
using namespace std;
float inf = numeric_limits<float>::infinity();
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
        cout << "-gbfs" << endl;
        gbfs_search(init_state);
    } 
    return;
}
void Search::bfs_search(vector<int> state){
    State init_state(state);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    if(is_goal(init_state.state)){
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        print_search(init_state, begin, end, init_state, 0);
        clear_search();
        return;
    }
    int w =0;
    this->open.push_back(init_state);
    while(!open.empty()){
        State opened = this->open.front();
        this->open.pop_front();
        list<State> succ = opened.succ();
        //succ.reverse();
        for (State &next_state : succ)
            {
            if(is_goal(next_state.state)){
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                print_search(init_state, begin, end, next_state, 0);
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
    int sequence = 0;
    State initial_state(init_state, NONE, 0);
    initial_state.sequence = sequence;
    this->openAstar.push(initial_state);
    float sum = 0;


    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while (!this->openAstar.empty())
    {
        State current = this->openAstar.top();
        this->openAstar.pop();
        

        if (is_goal(current.state))
        {
            chrono::steady_clock::time_point end = chrono::steady_clock::now();

            this->closed.insert(current.state);

            print_search(State(init_state), begin, end, current, sum/sequence);

            this->clear_search();
            return;
        }

        sum = sum + sequence;
        this->closed.insert(current.state);

        for (State& next_state : current.succ())
        {
            sequence++;
            next_state.sequence = sequence;
            this->openAstar.push(next_state);
        }
    }

    cout << "No solution" << endl;
}

void Search::idastar_search(vector<int> init_state){
    State init(init_state);
    float limit = manhattan(init.state);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(limit != inf){
        auto result = rec_search(init, limit);
        limit = get<0>(result);
        if(get<1>(result).cost != -1){
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            print_search(init, begin, end, get<1>(result), 0);
            clear_search();
            return;
        }
    }
}
tuple<float, State> Search::rec_search(State state, float limit){
    this->closed.insert(state.state);
    if(state.cost > limit){
        return make_tuple(state.cost, State());
    }
    if(is_goal(state.state)){
        return make_tuple(0, state);
    }
    float next_limit = inf;
    list<State> succ = state.succ();
    succ.reverse();    
    for(State &next_state : succ){
        if(manhattan(next_state.state) < inf){            
            auto result = rec_search(next_state, limit);
            if(get<1>(result).cost != -1){
                return make_tuple(0, get<1>(result));
            }
            next_limit = min(get<0>(result), next_limit);
        }
        
    }
    return make_tuple(next_limit, State());
}
void Search::gbfs_search(vector<int> init_state){
    int sequence = 0;
    State initial_state(init_state, NONE, 0);
    initial_state.sequence = sequence;
    this->openGbfs.push(initial_state);
    float sum = 0;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while (!this->openGbfs.empty())
    {
        State current = this->openGbfs.top();
        this->openGbfs.pop();

        if (is_goal(current.state))
        {
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            this->closed.insert(current.state);
            print_search(State(init_state), begin, end, current, sum/sequence);
            this->clear_search();
            return;
        }

        sum = sum + manhattan(current.state);
        this->closed.insert(current.state);

        for (State& next_state : current.succ())
        {
            if (closed.find(next_state.state) != closed.end()) 
                continue;

            sequence++;
            next_state.sequence = sequence;
            //cout << sequence << endl;
            this->openGbfs.push(next_state);
        }
    }

    cout << "No solution" << endl;
    return;
}


void Search::idfs_search(vector<int> init_state){
    float limit = 0;
    State init(init_state);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(limit != -1){
        State result = depth_limit_search(init, limit);
        if(result.cost != -1){
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            print_search(State(init_state), begin, end, result,0);
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
        list<State> succ = init_state.succ();
        succ.reverse();   
        for(State &next_state : succ){
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
    this->openGbfs = priority_queue<State, vector<State>, gbfsFunct>();
    return;
}
void Search::print_search(State init_state, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, State final_state,float avr){
    //expanded nodes
    cout <<  this->closed.size() << ",";
    //cout << this->open.size() << ",";
    //cout << this->open.size() + this->closed.size() << ",";
    cout << final_state.cost << ",";
    double time = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    time = time/100000;
    cout << fixed << setprecision(6) << time << ",";
    cout << avr << ",";
    cout << manhattan(init_state.state) << endl;
    return;
}