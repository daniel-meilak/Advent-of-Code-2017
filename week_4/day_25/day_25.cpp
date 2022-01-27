#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

int main(){

    // read input
    std::vector<std::vector<std::string>> input = read_input_2D("input_25",{" "});

    // total number of steps
    const int steps = std::stoi(input[1][5]);

    // tape initialised to 0
    std::vector<int> tape(100000,0);

    // current state
    char state = 'a';

    // start at middle of tape
    int x = tape.size()/2;

    // perform steps
    for (int i=0; i<steps; i++){

        int &cell = tape[x];

        // hardcode all the rules
        switch(state){
            case('a'):
                if (cell==0){
                    cell = 1;
                    x++;
                }
                else {
                    cell = 0;
                    x--;
                }
                state = 'b';
                break;
            case('b'):
                if (cell==0){
                    x++;
                    state = 'c';
                }
                else {
                    x--;
                }
                break;
            case('c'):
                if (cell==0){
                    cell = 1;
                    x++;
                    state = 'd';
                }
                else {
                    cell = 0;
                    x--;
                    state = 'a';
                }
                break;
            case('d'):
                if (cell==0){
                    cell = 1;
                    state = 'e';
                }
                else {
                    state = 'f';
                }
                x--;
                break;
            case('e'):
                if (cell==0){
                    cell = 1;
                    state = 'a';
                }
                else {
                    cell = 0;
                    state = 'd';
                }
                x--;
                break;
            case('f'):
                if (cell==0){
                    cell = 1;
                    x++;
                    state = 'a';
                }
                else {
                    x--;
                    state = 'e';
                }
                break;
        }
    }

    // count number of 1s in tape
    int count = 0;
    const int size = tape.size();
    for (int i=0; i<size; i++){
        if (tape[i]==1){ count++; }
    }

    std::cout << "Answer (part 1): " << count << std::endl;

    return 0;
}
