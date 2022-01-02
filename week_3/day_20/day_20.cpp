#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<ranges> // C++20
#include"../../Utils/utils.h"

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"p", "=", "<", ">", ",", "v", "a", " "};
    std::vector<std::vector<long long>> input = input_to_llint_2D(read_input_2D("input_20", delimiters));

    // no. of particles
    const int particles = input.size();
    
    // manhattan distance of each particle
    std::vector<long long> manhattan_vec(particles);

    // num of ticks
    const int ticks = 10000;

    // collided particles
    std::vector<bool> collided(particles, false);

    // simulate particles
    for (int i=0; i<ticks; i++){

        // move each particle
        for (int j=0; j<particles; j++){

            // inc velocity using acceleration
            input[j][3] += input[j][6];
            input[j][4] += input[j][7];
            input[j][5] += input[j][8];

            // inc position using velocity
            input[j][0] += input[j][3];
            input[j][1] += input[j][4];
            input[j][2] += input[j][5];

            // calculate manhattan distances
            manhattan_vec[j] = manhattan(input[j]);
        }

        // check for collisions
        for (int x=0; x<particles-1; x++){
            for (int y=x+1; y<particles; y++){
                if (input[x][0]==input[y][0] && input[x][1]==input[y][1] && input[x][2]==input[y][2]){
                    collided[x] = true;
                    collided[y] = true;
                }
            }
        }
    }

    // find particle closest to origin after simulation
    int closest = std::distance(manhattan_vec.begin(), std::ranges::min_element(manhattan_vec));

    // check how many particles did not collide
    int count = 0;
    for ( bool p : collided){
        if (!p){ count++; }
    }

    std::cout << "Answer (part 1): " << closest << std::endl;
    std::cout << "Answer (part 2): " << count   << std::endl;

    return 0;
}
