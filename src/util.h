#include <aliases.h>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
using namespace std;
vector<vector<int>> parse(int n, char *s[]);
vector<vector<int>> parse_entrance(int argv,char* argc[]);
int manhattan(vector<int> state);
bool is_goal(vector<int> state);
uint64_t pack15Puzzle(const std::vector<int>& puzzle);
std::vector<int> unpack15Puzzle(uint64_t packedNumber);
int manhattan_15(uint64_t estate);
bool is_goal_15(uint64_t state);
int getTile(uint64_t state, int pos);