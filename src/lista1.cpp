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
    vector<vector<int>> init_estates; 
    init_estates = parse_entrance(argc, argv);
    vector<int> a;
    /*if (init_estates[1].size() == 16)
    {
        for (size_t i = 0; i < init_estates.size(); i++)
        {
            search.start_search_15(pack15Puzzle(init_estates[i]));
        }
        return 0;
    }*/

    for(size_t i = 0; i <init_estates.size(); i++){
        search.start_search(init_estates[i]);
    }
    
    
    return 0;
}