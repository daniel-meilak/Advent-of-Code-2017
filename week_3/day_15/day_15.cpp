#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declaration
unsigned int gen_a(const unsigned int &prev);
unsigned int gen_b(const unsigned int &prev);
int judge(unsigned int a, unsigned int b, const bool part2);

int main(){

    unsigned int start_a = 618;
    unsigned int start_b = 814;

    std::cout << "Answer (part 1): " << judge(start_a,start_b,false) << std::endl;
    std::cout << "Answer (part 2): " << judge(start_a,start_b,true) << std::endl;

    return 0;
}

int judge(unsigned int a, unsigned int b, const bool part2){

    // total comparisons
    int comp;
    if (part2){ comp = 5000000; }
    else { comp = 40000000; }

    // number of pairs found
    int pairs = 0;

    for (int i=0; i<comp; i++){

        // generate next values
        a = gen_a(a);
        b = gen_b(b);

        // for part 2 next values have extra req
        if (part2){
            while (a % 4 != 0){ a = gen_a(a); }
            while (b % 8 != 0){ b = gen_b(b); }
        }

        // check if lower 16 bits are the same
        if ( (a << 16) == (b << 16) ){ pairs++; }
    }

    return pairs;
}

// next value for generator a
unsigned int gen_a(const unsigned int &prev){
    return (prev * 16807UL) % 2147483647UL;
}

// next value for generator b
unsigned int gen_b(const unsigned int &prev){
    return (prev * 48271UL) % 2147483647UL;
}