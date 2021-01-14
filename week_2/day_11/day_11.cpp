#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"Hex.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", ",");

    // hex at origin
    Hex current(0,0,0);

    // hold max distance
    int max_distance = 0;

    // work through input
    for (std::string dir : input){

        // process directions
        if      (dir == "n" ){ current = current + Hex( 0, 1,-1); }
        else if (dir == "ne"){ current = current + Hex( 1, 0,-1); }
        else if (dir == "nw"){ current = current + Hex(-1, 1, 0); }
        else if (dir == "s" ){ current = current + Hex( 0,-1, 1); }
        else if (dir == "se"){ current = current + Hex( 1,-1, 0); }
        else if (dir == "sw"){ current = current + Hex(-1, 0, 1); }

        // check current distance
        int current_d = hex_length(current);
        if (max_distance < current_d){ max_distance = current_d; }
    }

    std::cout << "Answer (part 1): " << hex_length(current) << std::endl;
    std::cout << "Answer (part 2): " << max_distance        << std::endl;

    return 0;
}

