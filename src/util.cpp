#include <aliases.h>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
#include <cmath>
#include "util.h"
using namespace std;

vector<vector<int>> parse(int n, char *s[])
{
    vector<vector<int>> vec;
    int k =0;
    int i = 2;
    vec.push_back(vector<int>());
    for(i=2; i<n;i++){
        string input = s[i];
        size_t pos = input.find(',') ;
        if(pos != string::npos){
            input.erase(pos, 1);
            vec[k].push_back(stoi(input));
            vec.push_back(vector<int>());
            k++;
        }
        else{
            vec[k].push_back(stoi(input));
        }
    }
    return vec;
}
vector<vector<int>> parse_entrance(int argv, char *argc[])
{
    vector<vector<int>> vec;
    vec = parse(argv, argc);
    return vec;
}

int manhattan(vector<int> estate)
{
    int distance = 0;
    int n = sqrt(estate.size());

    int current_col, current_pos, current_row, goal_row, goal_col, goal_pos;
    for (int i = 0; i < estate.size(); i++)
    {
        if(estate[i] != 0){
            current_pos = i;
            goal_pos = estate[i];
            current_row = round(current_pos / n);
            current_col = current_pos % n;
            goal_row = round(goal_pos / n);
            goal_col = goal_pos % n;
            distance += abs(current_row - goal_row) + abs(current_col - goal_col);
        }
    }
    return distance;
}
bool is_goal(vector<int> state){
    vector<int> goal = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    if(state == goal){
        return true;
    }
    for(int i = 0; i < state.size() - 1; i++){
        if(state[i] = state[i+1]){
            return false;
        }
    }
    return true;
}