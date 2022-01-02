#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declaration
int part1(int x, int y, int dir,  std::vector<std::string> grid);
int part2(int x, int y, int dir,  std::vector<std::string> grid);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_22", "");

    // large grid
    const int grid_size = 1000;
    std::vector<std::string> grid(grid_size,std::string(grid_size,'.'));

    // fill middle of large grid with input (not exactly in middle)
    const int start = grid_size/2;
    size_t y_max = input.size();
    size_t x_max = input[0].size();
    for (size_t y=0; y<y_max; y++){
        for (size_t x=0; x<x_max; x++){
            grid[y+start][x+start] = input[y][x];
        }
    }

    // virus pos and dir
    int y = start + (input.size()/2);
    int x = start + (input[0].size()/2);
    int dir = 90;
    
    std::cout << "Answer (part 1): " << part1(x,y,dir,grid) << std::endl;
    std::cout << "Answer (part 2): " << part2(x,y,dir,grid) << std::endl;

    return 0;
}

int part1(int x, int y, int dir,  std::vector<std::string> grid){

    // number of virus movements
    const int bursts = 10000;

    // number of nodes infected
    int count = 0;

    // move virus in bursts
    for (int i=0; i<bursts; i++){
        
        // if grid is infected turn right, clean node 
        if (grid[y][x]=='#'){
            dir = mod(dir-90,360);
            grid[y][x] = '.';
        }
        // else turn left and infect}
        else {
            dir = mod(dir+90,360);
            grid[y][x] = '#';
            count++;
        }

        // move forward in current direction
        switch(dir){
            case(0):
                x++;
                break;
            case(90):
                y--;
                break;
            case(180):
                x--;
                break;
            case(270):
                y++;
                break;
        }
    }

    return count;
}

int part2(int x, int y, int dir,  std::vector<std::string> grid){

    // number of virus movements
    const int bursts = 10000000;

    // number of nodes infected
    int count = 0;

    // move virus in bursts
    for (int i=0; i<bursts; i++){
        
        // if grid is infected turn right, flag node 
        if (grid[y][x]=='#'){
            dir = mod(dir-90,360);
            grid[y][x] = 'f';
        }
        // else if grid is clean turn left and weaken
        else if (grid[y][x]=='.'){
            dir = mod(dir+90,360);
            grid[y][x] = 'w';
        }
        // else if grid is weakened dont turn and infect
        else if (grid[y][x]=='w'){
            grid[y][x] = '#';
            count++;
        }
        // else if grid is flagged reverse direction and clean
        else if (grid[y][x]=='f'){
            switch(dir){
                case(0):
                    dir = 180;
                    break;
                case(90):
                    dir = 270;
                    break;
                case(180):
                    dir = 0;
                    break;
                case(270):
                    dir = 90;
                    break;
            }
            grid[y][x] = '.';
        }

        // move forward in current direction
        switch(dir){
            case(0):
                x++;
                break;
            case(90):
                y--;
                break;
            case(180):
                x--;
                break;
            case(270):
                y++;
                break;
        }
    }

    return count;
}