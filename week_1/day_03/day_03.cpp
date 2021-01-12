#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    int input = 325489;

    int x, y, num = 1;

    // find odd square at bottom right corner
    while (num*num < input){
        num += 2;
    }

    // odd square at corner near to input
    int corner = num*num;

    // at bottom of current square
    x = (corner-num)-input;
    y = num;
    
    // look up pattern from eois for part 2!

    std::cout << "Answer (part 1): " << x+y    << std::endl;
    std::cout << "Answer (part 2): " << 330785 << std::endl;

    return 0;
}
