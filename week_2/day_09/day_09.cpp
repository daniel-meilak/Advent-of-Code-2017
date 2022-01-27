#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

int main(){

    // read input into vector of strings.
    std::string input = read_line("input_09", {});

    // flag for garbage region
    bool in_garbage = false;

    // score and current points per group
    int score = 0;
    int points = 0;

    // count all characters in garbage
    int garbage = 0;

    // work through input
    // '}' outside of garbage and not infront of '!' signals end of group
    const int size = input.size();
    for (int i=0; i<size; i++){

        // start of garbage section
        if (input[i]=='<' && !in_garbage){ in_garbage = true; }
        // end of garbage section
        else if (input[i]=='>' && in_garbage){ in_garbage = false; }
        // skip next character
        else if (input[i]=='!'){ i++; }
        //beginning of group
        else if (input[i]=='{' && !in_garbage){ points++; }
        // end of group
        else if (input[i]=='}' && !in_garbage){
            score += points;
            points--;
        }
        // count all garbage (not '<' or '>' or '!' and following character)
        else if (in_garbage){ garbage++; }
    }


    std::cout << "Answer (part 1): " << score   << std::endl;
    std::cout << "Answer (part 2): " << garbage << std::endl;

    return 0;
}
