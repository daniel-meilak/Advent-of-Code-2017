#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
int current_max(const std::unordered_map<std::string, int> &reg);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", "if"};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // map of registers
    std::unordered_map<std::string, int> reg;

    // hold overall max reg value
    int overall_max = 0;

    // work through input
    for (auto line : input){

        // conditions
        bool condition;

        if      (line[4] == "<" ){ condition = (reg[line[3]] <  std::stoi(line[5])); }
        else if (line[4] == ">" ){ condition = (reg[line[3]] >  std::stoi(line[5])); }
        else if (line[4] == ">="){ condition = (reg[line[3]] >= std::stoi(line[5])); }
        else if (line[4] == "<="){ condition = (reg[line[3]] <= std::stoi(line[5])); }
        else if (line[4] == "!="){ condition = (reg[line[3]] != std::stoi(line[5])); }
        else if (line[4] == "=="){ condition = (reg[line[3]] == std::stoi(line[5])); }

        // if condition is met
        if (condition){
            if (line[1] == "inc"){ reg[line[0]] += std::stoi(line[2]); }
            else                 { reg[line[0]] -= std::stoi(line[2]); }
        }

        // find overall max (part 2)
        int max = current_max(reg);
        if (max > overall_max){ overall_max = max; }

    }

    // find max at end (part 1)
    int final_max = current_max(reg);

    std::cout << "Answer (part 1): " << final_max   << std::endl;
    std::cout << "Answer (part 2): " << overall_max << std::endl;

    return 0;
}

// find largest register
int current_max(const std::unordered_map<std::string, int> &reg){
    int max = 0;

    for (const auto &pair : reg){
        if (pair.second > max){ max = pair.second; }
    }

    return max;
}

