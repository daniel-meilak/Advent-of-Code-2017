#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<cstdlib>
#include<list>
#include"utils.h"

struct node{
    std::string name;
    int weight;
    int total_weight;
    std::vector<std::string> holding;
    std::string held_by;
};

// custom sort operations
bool sortbyweight( const node &lhs, const node &rhs){
    return (lhs.total_weight < rhs.total_weight);
}

// node comparators
bool operator==( const node &lhs, const node &rhs){
    return (lhs.total_weight == rhs.total_weight);
}

bool operator!=( const node &lhs, const node &rhs){
    return (lhs.total_weight != rhs.total_weight);
}

// forward function declaration
std::string part1(std::map<std::string, node> &towers);
int tot_weight(std::map<std::string, node> &towers, const std::string &start);
bool balanced(const std::vector<node> &branch);
int part2(std::map<std::string, node> &towers, std::string start);


int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", "(" , ")", "->", ","};
    std::vector<std::vector<std::string>> input = read_input_2D("input_07", delimiters);

    // tree of nodes
    std::map<std::string, node> towers;

    // build tree from input
    for (auto line : input){

        std::string current = line[0];

        // add weight
        towers[current].weight = std::stoi(line[1]);
        towers[current].name   = current;

        // if node is connected to others
        if (line.size() > 2){
    
            // build connections
            for (unsigned int i=2; i<line.size(); i++){
                // this node holds:
                towers[current].holding.push_back(line[i]);

                // these nodes are held by:
                towers[line[i]].held_by = current;
            }
        }
    }

    std::string root = part1(towers);
    tot_weight(towers, root);

    std::cout << "Answer (part 1): " << root                << std::endl;
    std::cout << "Answer (part 2): " << part2(towers, root) << std::endl;

    return 0;
}

// calculate total weight at root and assign total weights at each node
int tot_weight(std::map<std::string, node> &towers, const std::string &start){

    node &current = towers[start];

    // end condition, hitting end of branch
    if (current.holding.size() == 0){ current.total_weight = current.weight; }
    // when above end, sum weights of branches
    else {
        int sum = 0;
        for (const auto &s : current.holding){
            sum += tot_weight(towers, s);
        }

        current.total_weight = sum + current.weight;
    }

    return current.total_weight;
}

int part2(std::map<std::string, node> &towers, std::string start){

    std::vector<node> branch;

    // hold the correct weight
    int answer{0};

    // expand the root of the tree
    for (const std::string &s : towers[start].holding){
       branch.push_back(towers[s]);
    }

    // while branch contains an imbalance, reduce to imbalance
    while (!balanced(branch)){

        // sort the branch to put the odd one out on an edge
        std::sort(branch.begin(), branch.end(), sortbyweight);

        // find the imbalance on one side of the vector
        if (branch[0] == branch[1]){
            answer = branch.back().weight - (branch.back().total_weight - branch.front().total_weight);
            branch  = {branch.back()};
        }
        else {
            answer = branch.front().weight - (branch.front().total_weight - branch.back().total_weight);
            branch  = {branch.front()};
        }

        // expand imbalance into its branches
        std::vector<std::string> next = branch[0].holding;
        branch.clear();
        for (const std::string &s : next){
            branch.push_back(towers[s]);
        }
    }

    // at the end of the loop the last imbalance is isolated
    return answer;
}

// check if all the values in a vector are equal
bool balanced(const std::vector<node> &branch){

    auto it1 = branch.begin();
    for (auto it2=++branch.begin(); it2!=branch.end(); it2++){
        if (*it2 != *it1){ return false; }
    }

    return true;
}

std::string part1(std::map<std::string, node> &towers){

    // get any (first) element of tree
    std::string start = towers.begin()->second.held_by;

    std::string end;

    // work way up the tree
    while (start != ""){
        end = start;
        start = towers[start].held_by;
    }

    return end;
}