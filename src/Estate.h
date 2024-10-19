#include <iostream>
#include <string>
#include <list>
using namespace std;

class Estate {
    public:     
        char *estate;
        int n;
        Estate();
        Estate(string init_estate){
            n = init_estate.length();
            estate = new char[n];
        }
        
};