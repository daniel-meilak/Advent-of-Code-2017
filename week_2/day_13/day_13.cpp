#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
void move_scanners(std::vector<std::vector<int>> &input);
void reset_scanners(std::vector<std::vector<int>> &input);
int part1(std::vector<std::vector<int>> input);
int part2(std::vector<std::vector<int>> &input);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", ":"};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    // add scanner starting position and current direction (+1/-1) to each gate
    for (auto &line : input){
        line.push_back(0);
        line.push_back(1);
    }

    std::cout << "Answer (part 1): " << part1(input) << std::endl;
    std::cout << "Answer (part 2): " << part2(input) << std::endl;

    return 0;
}

void move_scanners(std::vector<std::vector<int>> &input){

    // move each scanner
    for (auto &line : input){

        // check if direction needs to be reversed
        if ((line[2]==0 && line[3]==-1) || (line[2]+1==line[1] && line[3]==1)){ line[3] *= -1; }

        // move scanner
        line[2] += line[3]; 
    }
}

void reset_scanners(std::vector<std::vector<int>> &input){

    // reset each gate
    for (auto &line : input){
        line[2] = 0;
        line[3] = 1;
    }
}

int part1(std::vector<std::vector<int>> input){
    
    // severity and curresnt position;
    int severity = 0;
    int pos = 0;
    int gate = 0;

    // move through security
    const int size = input.back()[0];
    while (pos <= size){

        std::vector<int> &line = input[gate];

        // check if at gate
        if (line[0] != pos){
            pos++;
            move_scanners(input);
            continue;
        }

        // if scanner at our pos is at the top
        if (line[2] == 0){ severity += line[0]*line[1]; }

        // move forward and move gates
        pos++;
        move_scanners(input);
        gate++;
    }

    return severity;
}

int part2(std::vector<std::vector<int>> &input){
    
    // delay and curresnt position;
    int delay = 0;

    while ( part1(input) != 0 || input.front()[2] == 0 ){
        // increase delay
        delay++;

        // move gates
        move_scanners(input);
    }

    return delay;
}
