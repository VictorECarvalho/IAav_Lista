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
    for(int i = 0; i < state.size() - 1; i++){
        if(state[i] > state[i+1]){
            return false;
        }
    }
    return true;
}

bool is_goal_15(uint64_t state) {
    return state == 18364758544493064720;
}


uint64_t pack15Puzzle(const std::vector<int> &puzzle)
{
    uint64_t packedNumber = 0;
    for (size_t i = 0; i < puzzle.size(); i++)
        packedNumber |= (uint64_t(puzzle[i]) & 0xF) << (i * 4);
    return packedNumber;
}

std::vector<int> unpack15Puzzle(uint64_t packedNumber)
{
    std::vector<int> puzzle(16);
    for (size_t i = 0; i < 16; i++)
        puzzle[i] = (packedNumber >> (i * 4)) & 0xF;

    std::cout << "Unpacked puzzle: [";
    for (size_t i = 0; i < puzzle.size(); ++i) {
        std::cout << puzzle[i];
        if (i < puzzle.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return puzzle;
}

int getTile(uint64_t state, int pos) {
    return (state >> (pos * 4)) & 0xF; 
}

int manhattan_15(uint64_t packed_state) {
    int distance = 0;
    int n = 4; 

    if(is_goal_15(packed_state))
        return distance;

    int current_col, current_row, goal_row, goal_col;

    for (int i = 0; i < 16; i++) {

        int tile = getTile(packed_state, i);

        if (tile != 0) {  
            int current_pos = i;
            int goal_pos = tile;
            current_row = current_pos / n;
            current_col = current_pos % n;
            goal_row = goal_pos / n;
            goal_col = goal_pos % n;
            distance += abs(current_row - goal_row) + abs(current_col - goal_col);
        }
    }

    return distance;
}