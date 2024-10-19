#include <aliases.h>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
#include "Search.h"

using namespace std;

int main(int argc, char* argv[])
{
    Search search;
    search.algorithm = argv[1];
    cout << "You chose: " << search.algorithm << endl;

    string init_estate = "";
    vector <string> init_estates;
    // Using a while loop to iterate through arguments
    int i = 2;
    while (i < argc) {
        init_estate = init_estate + argv[i];
         i++;
    }
    cout << init_estate << endl;
    regex rgx(",");
    sregex_token_iterator iter(init_estate.begin(),
    init_estate.end(),
    rgx,
    -1);    
    sregex_token_iterator end;
    int l = 0;
    for ( ; iter != end; ++iter){
        init_estates.push_back(*iter);
        cout << "initial states: " << init_estates[l] << endl;
        l++;
        }
    return 0;
}