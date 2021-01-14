#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<iomanip>
#include<numeric>
#include"../../Utils/utils.h"

// forward function declaration
std::string knot_hash(std::string input);

int main(){

    // read input into strings.
    std::string input = "jxqlasbh";

    // grid 
    std::vector<std::string> grid;

    for (int i=0; i<128; i++){

        grid.push_back("");

        // generate hash;
        std::string hash = knot_hash(input + "-" + std::to_string(i));

        // convert hash to bits
    }

    std::cout << "Answer (part 1): " << std::endl;
    std::cout << "Answer (part 2): " << std::endl;

    return 0;
}

std::string knot_hash(std::string input){

    // process input into ASCII codes
    std::vector<int> cycle;

    // convect char to ASCII value
    for (char c : input){
        cycle.push_back(c);
    }

    // create vector 0-255
    std::vector<int> hash(256);

    // fill with increasing numbers
    std::iota(hash.begin(), hash.end(), 0);

    // start with iterator to first pos
    auto current = hash.begin();

    // skip size
    int skip = 0;

    // do 64 rounds
    for (int r=0; r<64; r++){

        // work through cycle
        for (int length : cycle){

            // vector to hold range
            std::vector<int> range;

            // length must be 
            if (length > (int)hash.size()){ continue; }

            // save elements to be flipped
            auto next = current;
            for (int i=0; i<length; i++){
                range.push_back(*next);
                advance_cyclic(next,1,hash);
            }

            // flip elements in hash while moving current it forward
            for (int i=(int)range.size()-1; i>=0; i--){
                *current = range[i];
                advance_cyclic(current,1,hash);
            }

            // move current by skip size
            advance_cyclic(current,skip,hash);

            // increase skip
            skip++;
        }
    }

    // reduce sparce hash
    std::vector<int> dense_hash;
    for (int i=0; i<256; i+=16){
        
        // XOR 16 numbers in hash
        int comb = hash[i];
        for (int j=i+1; j<i+16; j++){
            comb = comb ^ hash[j];
        }

        // add result to dense hash
        dense_hash.push_back(comb);
    }

    // use stringstream to create hexadecimal hash
    std::stringstream ss;
    for (unsigned int i=0; i<dense_hash.size(); i++){
        ss << std::hex << dense_hash[i];
    }

    return ss.str();
}