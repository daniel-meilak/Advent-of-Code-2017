#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int part1(const int &step);
int part2(const int &step);

int main(){

    // step
    const int step = 370;

    std::cout << "Answer (part 1): " << part1(step) << std::endl;
    std::cout << "Answer (part 2): " << part2(step) << std::endl;

    return 0;
}

int part1(const int &step){

    // list to store positions
    std::list<int> spin = {0};

    // iterator to current pos
    auto it = spin.begin();

    // part 1
    for (int i=1; i<2018; i++){

        // calculate reduced step
        int red = step % spin.size();

        // advance
        advance_cyclic(it,red,spin);

        // inset next element
        std::advance(it,1);
        it = spin.insert(it,i);
    }

    return *next_cyclic(it,1,spin);
}

int part2(const int &step){

    // instead of copnstructing vector, kep track of pos
    int pos = 0;
    int after_zero = 0;

    for (int i=1; i<50000001; i++){

        // can calculate pos after each step
        pos = (pos + 1 + step) % i;

        // 0 stays at the beginning, check if inserting value after beginning
        if (pos==0){ after_zero=i; }
    }

    return after_zero;
}
