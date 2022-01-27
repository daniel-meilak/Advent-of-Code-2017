#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"utils.h"

// forward function declaration
std::string dance(std::string prog, const std::vector<std::string> &input);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_16", {","});

    // program names
    std::string prog1 = "abcdefghijklmnop";
    std::string prog2 = prog1;
    
    // repeat dance and look for loop
    std::unordered_map<std::string, int> uniques;

    // total iter for part 2
    int iter = 1000000000;
    for (int i=1; i<iter; i++){

        // next iter
        prog2 = dance(prog2,input);

        // check if unique
        if (uniques.count(prog2) && (iter-i)%(i-uniques[prog2]) == 0){ break; }
        uniques[prog2] = i;
    }
    

    std::cout << "Answer (part 1): " << dance(prog1, input) << std::endl;
    std::cout << "Answer (part 2): " << prog2 << std::endl;

    return 0;
}

std::string dance(std::string prog, const std::vector<std::string> &input){
    
    // work through input
    for (std::string line : input){

        if (line[0]=='s'){
            // number of elements to rotate
            int n = std::stoi(line.substr(1));

            // rotate programs right n times
            std::rotate(prog.rbegin(), prog.rbegin()+n, prog.rend());
        }
        else if (line[0]=='x'){
            size_t pos = line.find('/');

            // the program indexes to swap
            int a = std::stoi(line.substr(1,pos-1));
            int b = std::stoi(line.substr(pos+1));

            // swap indexes
            std::swap(prog[a], prog[b]);
        }
        else if (line[0]=='p'){
            size_t pos = line.find('/');

            // the programs to swap
            std::string a = line.substr(1,pos-1);
            std::string b = line.substr(pos+1);

            // find program indexes
            size_t pos1 = prog.find(a);
            size_t pos2 = prog.find(b);

            // swap indexes
            std::swap(prog[pos1], prog[pos2]);
        }
    }

    return prog;
}