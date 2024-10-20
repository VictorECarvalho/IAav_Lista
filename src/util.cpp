#include <aliases.h>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
#include "util.h"
using namespace std;


vector<string> parse(string init_state){

    regex rgx(",");
    vector <string> vec;
    sregex_token_iterator iter(init_state.begin(),
    init_state.end(),
    rgx,
    -1);    
    sregex_token_iterator end;
    int l = 0;
    for ( ; iter != end; ++iter){
        vec.push_back(*iter);
        l++;
        }
    return vec;
}
string get_parameter(int n,char* s[]){
    string new_s;
    int i = 2;
    while (i < n) {
        new_s = new_s + s[i];
         i++;
    }
    return new_s;
}
vector<string> parse_entrance(int argv,char* argc[]){
    vector<string> vec;
    vec = parse(get_parameter(argv,argc));
    return vec;
}