#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declaration
std::vector<int> debugger(std::vector<int> input);

int main(){

    // read input into vector of strings.
    std::vector<int> input = input_to_int(read_input("input_06", "\t"));

    std::vector<int> answers = debugger(input);

    std::cout << "Answer (part 1): " << answers[0] << std::endl;
    std::cout << "Answer (part 2): " << answers[1] << std::endl;

    return 0;
}

std::vector<int> debugger(std::vector<int> input){

    // vector of seen states
    std::vector<std::vector<int>> states;

    // steps
    int steps = 0;

    while (std::find(states.begin(), states.end(), input) == states.end()){

        // add last state to states
        states.push_back(input);

        // increment step count
        steps++;

        // find the max element index 'i' and value 'max'
        auto it = std::max_element(input.begin(), input.end());
        int i   = std::distance(input.begin(), it);
        int max = input[i];

        // empty the max element
        input[i] = 0;

        // redistribute max element to get new state
        for (int j=0; j<max; j++){
            i++;
            input[(i)%input.size()]++;
        }
    }

    // find distance of repeat state to last seen in states
    int part2 = std::distance( std::find(states.begin(), states.end(), input), states.end());

    return {steps, part2};
}
