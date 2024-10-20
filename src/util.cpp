#include <aliases.h>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
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
    vector<int> goal = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int estate_int[estate.size()];

    for (int i = 0; i < estate.size(); i++)
        estate_int[i] = estate[i] - '0';

    int current_col, current_pos, current_row, goal_row, goal_col, goal_pos;
    for (int i = 0; i < estate.size(); i++)
    {
        if (estate_int[i] != 0)
        {
            current_pos = i;
            goal_pos = find(goal.begin(), goal.end(), estate_int[i]) - goal.begin();

            current_row = current_pos / 3;
            //cout << "Current row: " << current_row << "  Current pos: " << current_pos << "/n" << endl;
            current_col = current_pos % 3;
            //cout << "Current col: " << current_col << "  Current pos: " << current_pos << "/n" << endl;

            goal_row = goal_pos / 3;
            //cout << "goal_row: " << goal_row << "  goal_pos: " << goal_pos << "/n" << endl;
            goal_col = goal_pos % 3;
            //cout << "goal_col: " << goal_col << "  goal_pos: " << goal_pos << "/n" << endl;

            distance += abs((current_row + 1) - (goal_row + 1)) + abs((current_col + 1) - (goal_col + 1));
        }
    }

    return distance;
}
bool is_goal(vector<int> state){
    for(int i = 0; i < state.size() - 1; i++){
        if(state[i] > state[i+1]){
            return false;
        }
    }
    return true;
}