#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"utils.h"
#include"program.h"

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input_18", delimiters);

    // part 1
    program part_1(input,0,true);

    part_1.running = true;
    while (part_1.running){ part_1.run(part_1); }

    // part 2: two programs
    program A(input,0), B(input,1);

    // turn on programs and run
    A.running = true;
    B.running = true;

    while( A.running || B.running ){

        // if both programs are locked end
        if (A.lock && B.lock){ break; }
        
        // run the next instruction for each program
        if (A.running){ A.run(B); }
        if (B.running){ B.run(A); }
    }

    std::cout << "Answer (part 1): " << part_1.recv.back() << std::endl;
    std::cout << "Answer (part 2): " << B.sent << std::endl;

    return 0;
}



