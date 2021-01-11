#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"\t"};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    // tally
    int count1 = 0;
    int count2 = 0;

    // work through input
    for (std::vector<int> line : input){
        int min = *std::min_element(line.begin(), line.end());
        int max = *std::max_element(line.begin(), line.end());

        // part 2
        for (int x : line){
            for (int y : line){

                // dont compare a number to itself
                if (x == y){ continue; }

                // look for numbers that divide exactly
                if (x % y == 0){
                    count2 += x/y;
                }
            }
        }
        
        count1 += max-min;
    }

    std::cout << "Answer (part 1): " << count1 << std::endl;
    std::cout << "Answer (part 2): " << count2 << std::endl;

    return 0;
}
