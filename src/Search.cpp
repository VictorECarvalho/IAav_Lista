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
        bfs_search(init_state);
    } else if (this->algorithm == "-idfs") {
        idfs_search(init_state);
    } else if (this->algorithm == "-astar") {
        astar_search(init_state);
    } else if (this->algorithm == "-idastar") {
        idastar_search(init_state);
    } else if (this->algorithm == "-gbfs") {
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
        this->expanded++;
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
            if(this->closed.find(next_state.state) == this->closed.end()){
                    this->open.push_back(next_state);
                    this->closed.insert(next_state.state);
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
    State initial_state(init_state);
    if(initial_state.h < inf){
        this->openAstar.push(initial_state);
        
    }
    initial_state.sequence = sequence;
    State::sum_h += initial_state.h;
    State::n_opened++;
    //float sum = 0;


    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(!this->openAstar.empty())
    {
        State current = this->openAstar.top();
        this->openAstar.pop();      
        this->expanded++;
        //cout << "Expanding node: " << current.state[0] << current.state[1] << current.state[2] << current.state[3] << current.state[4] << current.state[5] << current.state[6] << current.state[7] << current.state[8] << ", Cost: " << current.cost << endl;
        if (this->closed.find(current.state) == this->closed.end())
        {
            //sum = sum + current.cost + current.h;
            this->closed.insert(current.state);
            if (is_goal(current.state))
            {
                chrono::steady_clock::time_point end = chrono::steady_clock::now();

                this->closed.insert(current.state);
                print_search(State(init_state), begin, end, current, 0);

                this->clear_search();
                return;
            }
            list<State> succ = current.succ();
            //succ.reverse();
            for (State &next_state : succ)
            {
                if (next_state.h + next_state.cost < std::numeric_limits<int>::max()) 
                {
                    sequence++;
                    next_state.sequence = sequence;

                    //cout << "Adding node to open list: " << next_state.state[0] << next_state.state[1] << next_state.state[2] << next_state.state[3] << next_state.state[4] << next_state.state[5] << next_state.state[6] << next_state.state[7] << next_state.state[8] << ", Cost: " << next_state.cost << ", h: " << manhattan(next_state.state) << ", Sequence:" << sequence << endl;

                    this->openAstar.push(next_state);
                    State::sum_h += next_state.h;
                    State::n_opened++;
                }
            }
        }
    }
}


void Search::idastar_search(vector<int> init_state){
    State init(init_state);
    State::sum_h += init.h;
    State::n_opened++;
    float limit = init.h;
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
    State::sum_h += state.h;
    State::n_opened++;
    if(state.idastar_f() > limit){
        return make_tuple(state.idastar_f(), State());
    }
    if(is_goal(state.state)){
        return make_tuple(0, state);
    }
    float next_limit = inf;
    list<State> succ = state.succ();
    this->expanded++;
    //succ.reverse();    
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

void Search::gbfs_search(vector<int> init_state)
{
    int sequence = 0;
    State initial_state(init_state);
    initial_state.sequence = sequence;
    this->openGbfs.push(initial_state);
    float sum = 0;


    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(!this->openGbfs.empty())
    {
        State current = this->openGbfs.top();
        this->openGbfs.pop();
        this->expanded++;
        //cout << "Expanding node: " << current.state[0] << current.state[1] << current.state[2] << current.state[3] << current.state[4] << current.state[5] << current.state[6] << current.state[7] << current.state[8] << ", Cost: " << current.cost << endl;
        if (this->closed.find(current.state) == this->closed.end())
        {
            sum = sum + current.cost + current.h;
            this->closed.insert(current.state);
            if (is_goal(current.state))
            {
                chrono::steady_clock::time_point end = chrono::steady_clock::now();

                this->closed.insert(current.state);
                print_search(State(init_state), begin, end, current, sum / sequence);

                this->clear_search();
                return;
            }
            for (State &next_state : current.succ())
            {
                if (next_state.h + next_state.cost < std::numeric_limits<int>::max()) 
                {
                    sequence++;
                    next_state.sequence = sequence;

                    //cout << "Adding node to open list: " << next_state.state[0] << next_state.state[1] << next_state.state[2] << next_state.state[3] << next_state.state[4] << next_state.state[5] << next_state.state[6] << next_state.state[7] << next_state.state[8] << ", Cost: " << next_state.cost << ", h: " << manhattan(next_state.state) << ", Sequence:" << sequence << endl;

                    this->openGbfs.push(next_state);
                }
            }
        }
    }
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
    if(is_goal(init_state.state)){
        return init_state;
    }
    if(limit > 0){     
        this->expanded++;
        list<State> succ = init_state.succ();
        //succ.reverse();   
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
    this->expanded = 0;
    State::n_opened = 0;
    State::sum_h = 0;
    this->openAstar_15 = priority_queue<State15, vector<State15>, astarFunct_15>();
    this->closed_15.clear();
    return;
}
void Search::print_search(State init_state, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, State final_state,float avr){
    //expanded nodes
    //cout <<  this->closed.size() << ",";
    cout << this->expanded << ",";
    cout << final_state.cost << ",";
    double time = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    time = time/100000;
    cout << fixed << setprecision(6) << time << ",";
    //cout << avr << ",";
    if(State::n_opened != 0 && State::sum_h != 0)
        cout << State::sum_h/State::n_opened << ",";
    else
        cout << 0 << ",";
    cout << manhattan(init_state.state) << endl;
    return;
}


void Search::start_search_15(uint64_t init_state){

    if (this->algorithm == "-astar") {
        cout << "-astar" << endl;
        astar_search_15(init_state);
    }

    return;
}


void Search::print_search_15(State15 init_state, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, State15 final_state,float avr){
    //expanded nodes
    //cout <<  this->closed.size() << ",";
    cout << this->expanded << ",";
    cout << final_state.cost << ",";
    double time = chrono::duration_cast<chrono::microseconds>(end - begin).count();
    time = time/1000000;
    cout << fixed << setprecision(6) << time << ",";
    cout << avr << ",";
    cout << manhattan_15(init_state.state) << endl;
    return;
}


void Search::astar_search_15(uint64_t init_state)
{
    int sequence = 0;
    State15 initial_state(init_state, NONE, 0);
    initial_state.sequence = sequence;
    this->openAstar_15.push(initial_state);
    float sum = 0;

    State15 current2 = this->openAstar_15.top();

    //unpack15Puzzle(current2.state);


    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(!this->openAstar_15.empty())
    {
        State15 current = this->openAstar_15.top();
        //unpack15Puzzle(current.state);
        this->openAstar_15.pop();
        //cout << "current" << endl;
        //unpack15Puzzle(current.state);
        //cout << "Expanding node: " << current.state[0] << current.state[1] << current.state[2] << current.state[3] << current.state[4] << current.state[5] << current.state[6] << current.state[7] << current.state[8] << ", Cost: " << current.cost << endl;
        if (this->closed_15.find(current.state) == this->closed_15.end())
        {
            this->expanded++;
            sum = sum + current.cost + manhattan_15(current.state);
            this->closed_15.insert(current.state);
            if (is_goal_15(current.state))
            {
                chrono::steady_clock::time_point end = chrono::steady_clock::now();

                this->closed_15.insert(current.state);
                print_search_15(State15(init_state,NONE,0), begin, end, current, sum / sequence);

                this->clear_search();
                return;
            }
            for (State15 &next_state : current.succ_15())
            {
                if (manhattan_15(current.state) + next_state.cost < std::numeric_limits<int>::max()) 
                {
                    sequence++;
                    next_state.sequence = sequence;
                    
                    //cout << "Adding node to open list: " << next_state.state[0] << next_state.state[1] << next_state.state[2] << next_state.state[3] << next_state.state[4] << next_state.state[5] << next_state.state[6] << next_state.state[7] << next_state.state[8] << ", Cost: " << next_state.cost << ", h: " << manhattan(next_state.state) << ", Sequence:" << sequence << endl;
                    
                    //cout << "succ" << endl;
                    //unpack15Puzzle(next_state.state);
                    //cout << "Heuristic + Cost:" << manhattan_15(next_state.state) + next_state.cost << endl;
                    
                    this->openAstar_15.push(next_state);
                }
            }
        }
    }
    this->clear_search();
}