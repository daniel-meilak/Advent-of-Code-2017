#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
int jump(std::vector<int> input, const bool part2);

int main(){

    // read input into vector of ints.
    std::vector<int> input = input_to_int(read_input("input", ""));

    std::cout << "Answer (part 1): " << jump(input,false) << std::endl;
    std::cout << "Answer (part 2): " << jump(input,true)  << std::endl;

    return 0;
}

int jump(std::vector<int> input, const bool part2){

    // number of steps
    int steps = 0;

    // start at instruction 0
    int i = 0;

    const int size = input.size();
    while ( i>=0 && i<size){

        int j = i;

        // jump 
        i += input[i];

        // increment last jump
        if (!part2){ input[j]++; }
        // increment or decriment depending on value
        else {            
            if (input[j] > 2){ input[j]--; }
            else { input[j]++; }
        }

        steps++;
    }

    return steps;
}
