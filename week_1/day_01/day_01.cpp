#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// Forward function declaration
int part(const std::string &input, const bool part2);

int main(){

    // read input into vector of strings.
    std::string input = read_line("input", {});

    std::cout << "Answer (part 1): " << part(input,false) << std::endl;
    std::cout << "Answer (part 2): " << part(input,true)  << std::endl;

    return 0;
}

int part(const std::string &input, const bool part2){

    // tally 
    int count = 0;
    
    // compare neighbours
    size_t size = input.size();
    for (size_t i=0; i<size; i++){

        // compare number after input 1, % allows wrap around
        if (!part2){
            if (input[i] == input[(i+1)%size]){ count += input[i]-'0'; }
        }
        // compare number half way along int using %
        else {
            char c = input[(i+size/2)%size];
            if (input[i] == c){ count += c-'0'; }
        }     
    }

    return count;
}
