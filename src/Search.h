#include <iostream>
#include <string>
#include <list>
#include "Estate.h"
using namespace std;

class Search {
    public:     
        string algorithm;
        list <string> open;
        list <string> closed;  
        Search(){
            algorithm = "";
        }
        Search(string alg){
            algorithm = alg;
        }
};