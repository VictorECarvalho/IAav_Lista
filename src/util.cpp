#include <aliases.h>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
#include "util.h"
using namespace std;

vector<string> parse(string init_state)
{

    regex rgx(",");
    vector<string> vec;
    sregex_token_iterator iter(init_state.begin(),
                               init_state.end(),
                               rgx,
                               -1);
    sregex_token_iterator end;
    int l = 0;
    for (; iter != end; ++iter)
    {
        vec.push_back(*iter);
        l++;
    }
    return vec;
}
string get_parameter(int n, char *s[])
{
    string new_s;
    int i = 2;
    while (i < n)
    {
        new_s = new_s + s[i];
        i++;
    }
    return new_s;
}
vector<string> parse_entrance(int argv, char *argc[])
{
    vector<string> vec;
    vec = parse(get_parameter(argv, argc));
    return vec;
}

int manhattan(string estate)
{
    int distance = 0;
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
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