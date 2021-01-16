#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // find starting pos
    int pos = input[0].find('|');

    // coordinates
    int x = pos;
    int y = 0;

    // directions
    enum dir {up, down, left, right};
    dir direction = down;

    // path
    std::string path;

    // start path finding
    bool pathfinding = true;

    // total steps
    int steps = 0;

    while(pathfinding){

        // move in current direction
        switch(direction){
            case (down):
                y += 1;
                break;
            case (up):
                y -= 1;
                break;
            case (left):
                x -= 1;
                break;
            case (right):
                x += 1;
                break;
        }

        // check current square
        char square = input[y][x];

        // found parth marker
        if (square>='A' && square <='Z'){
            path.push_back(square);
        }
        // change direction
        else if (square=='+'){
            // if moving up/down, move left/right
            if (direction==up || direction==down){
                if (input[y][x+1]==' '){ direction = left; }
                else { direction = right; }
            }
            // if moving left/right, move up/down
            else {
                if (input[y+1][x]==' '){ direction = up; }
                else { direction = down; }
            }
        }
        // reached end
        else if (square==' '){ pathfinding = false; }

        // increment step count
        steps++;
    }

    std::cout << "Answer (part 1): " << path  << std::endl;
    std::cout << "Answer (part 2): " << steps << std::endl;

    return 0;
}
