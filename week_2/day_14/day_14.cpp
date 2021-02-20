#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<iomanip>
#include<unordered_map>
#include<bitset>
#include<numeric>
#include"../../Utils/utils.h"

// forward function declaration
std::string knot_hash(std::string input);
std::string hash_to_binary(const std::string &hash);
void group_fill(const int &i, const int &j, std::vector<std::string> &grid, std::vector<std::vector<bool>> &seen);

int main(){

    // read input into strings.
    std::string input = "jxqlasbh";

    // grid 
    std::vector<std::string> grid;

    // pad top of grid
    grid.push_back(std::string(130,0));

    // fill grid
    for (int i=0; i<128; i++){

        // hash input
        std::string value = input + "-" + std::to_string(i);

        // generate hash;
        std::string hash = knot_hash(value);

        // convert hash to bits
        grid.push_back("0"+hash_to_binary(hash)+"0");
    }

    // pad end of grid
    grid.push_back(std::string(130,0));

    // count number of used squares (1)
    int count = 0;
    for (size_t i=0; i<grid.size(); i++){
        for (const char &c : grid[i]){
            if (c == '1'){ count++; }
        }
    }

    // count groups
    int groups = 0;
    
    // map of squares already in a group
    std::vector<std::vector<bool>> seen(130, std::vector<bool>(130,false));

    // check all squares
    for (size_t i=1; i<grid.size()-1; i++){
        for (size_t j=1; j<grid[0].size()-1; j++){

            // if used (1) and not already in seen group
            if (grid[i][j]=='1' && !seen[i][j]){

                // find all parts of group
                group_fill(i,j,grid,seen);

                // increment group count
                groups++;
            }
        }
    }

    std::cout << "Answer (part 1): " << count  << std::endl;
    std::cout << "Answer (part 2): " << groups << std::endl;

    return 0;
}

// from a starting position in a group, finds all other
// squares in the group (BFS)
void group_fill(const int &i, const int &j, std::vector<std::string> &grid, std::vector<std::vector<bool>> &seen){

    seen[i][j] = true;

    std::list<std::vector<int>> stack = {{i,j}};

    while (stack.size()){

        // move to next member of stack
        std::vector<int> c = stack.front();
        stack.pop_front();

        // check neighbours 
        std::vector<int> a = {1,-1, 0, 0};
        std::vector<int> b = {0, 0, 1,-1};

        // 4 possible directions
        for (int i=0; i<4; i++){
            int x = c[0]+a[i];
            int y = c[1]+b[i];
            
            // check if group (1) and not seen already
            if (grid[x][y] == '1' && !seen[x][y]){
                stack.push_back({x,y});
                seen[x][y] = true;
            }
        }
    }
}

// converts hash to binary representation (string)
std::string hash_to_binary(const std::string &hash){

    std::string binary;

    for (const char &c : hash){

        // use string stream to handle hash
        // conversion to int
        std::stringstream ss;
        ss << std::hex << c;

        // convert to int
        unsigned n;
        ss >> n;

        // convert int to binary
        std::bitset<4> b(n);
        binary += b.to_string();
    }

    return binary;
}

// returns knot hash using input
std::string knot_hash(std::string input){

    // process input into ASCII codes
    std::vector<int> cycle;

    // convect char to ASCII value
    for (char c : input){
        cycle.push_back(c);
    }

    // add extra values at end
    cycle.push_back(17);
    cycle.push_back(31);
    cycle.push_back(73);
    cycle.push_back(47);
    cycle.push_back(23);

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
    for (size_t i=0; i<dense_hash.size(); i++){
        ss << std::setfill ('0') << std::setw(2) << std::hex << dense_hash[i];
    }

    return ss.str();
}