#include <aliases.h>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
#include "util.h"
#include "Search.h"

using namespace std;

int main(int argc, char* argv[])
{
    Search search(argv[1]);
    vector <string> init_estates; 
    init_estates = parse_entrance(argc, argv); 
    for(int i = 0; i <init_estates.size(); i++)
        cout << "initial states: " << search.algorithm << init_estates[i] << endl;
    
    return 0;
}