#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<utility>
#include"../../Utils/utils.h"

struct port{
    int a;
    int b;
    bool used = false;

    port(int a, int b){
        this->a = a;
        this->b = b;
    }
};

// global variables for answeres
int max_strength = 0;
int max_length   = 0;
int strong_longest = 0;

// forward function declaration
void daisychain(int start, int length, int strength, std::vector<port> &ports);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"/"};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    // vector of ports
    std::vector<port> ports;

    // add connectors to map
    for (auto line : input){
        ports.push_back(port(line[0],line[1]));
    }

    // create daisychain
    daisychain(0,0,0,ports);

    std::cout << "Answer (part 1): " << max_strength   << std::endl;
    std::cout << "Answer (part 2): " << strong_longest << std::endl;

    return 0;
}

void daisychain(int start, int length, int strength, std::vector<port> &ports){

    // check for max strength and length
    max_strength = std::max(strength, max_strength);
    max_length   = std::max(length, max_length);

    if (max_length == length){ strong_longest = std::max(strength, strong_longest); }

    // if ports line up
    for (port &p : ports){
        if (!p.used && (p.a == start || p.b == start)){

            p.used = true;
            // link next port
            if (p.a == start){
                daisychain(p.b, length+1, strength+p.a+p.b, ports);
            }
            else {
                daisychain(p.a, length+1, strength+p.a+p.b, ports);
            }
            p.used = false;
        }
    }
}
