#include <aliases.h>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
using namespace std;
vector<string> parse(string init_state);
string get_parameter(int n,char* s[]);
vector<string> parse_entrance(int argv,char* argc[]);