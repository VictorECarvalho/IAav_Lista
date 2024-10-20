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