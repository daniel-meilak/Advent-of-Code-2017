#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declaration
std::unordered_map<int,int> find_group_map(std::unordered_map<int, std::vector<int>> &pipes, const int &n);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", "<->"};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input_12", delimiters));

    // map of connections
    std::unordered_map<int, std::vector<int>> pipes;

    // work through input
    for (auto line : input){
        
        int size = line.size();
        for (int i=1; i<size; i++){
            pipes[line[0]].push_back(line[i]);
        }
    }

    // group count
    int count = 0;

    // map to check if connection is in a group
    std::unordered_map<int,int> groups;

    // work through input
    for (auto line : input){
        int &current = line[0];

        if (groups[current] != 1){
            count++;
            groups.merge(find_group_map(pipes,current));
        } 
    }

    std::cout << "Answer (part 1): " << find_group_map(pipes,0).size() << std::endl;
    std::cout << "Answer (part 2): " << count                          << std::endl;

    return 0;
}

// finds all members of the group containing n
std::unordered_map<int,int> find_group_map(std::unordered_map<int, std::vector<int>> &pipes, const int &n){

    std::unordered_map<int,int> group;

    // start with connections of pipe 0;
    std::list<int> con = {n};

    while (con.size()){

        int current = con.front();
        con.pop_front();

        // if current con is new, inc num and add its connections to con
        if ( group[current] != 1 ){
            group[current] = 1;

            // add connections from current to con
            std::vector<int> &next = pipes[current];
            for (size_t i=0; i<next.size(); i++){
                con.push_back(next[i]);
            }
        }
    }

    return group;
}

