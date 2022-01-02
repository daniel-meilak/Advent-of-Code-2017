#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"../../Utils/utils.h"
#include"../../Utils/math_func.h"

// forward function declarations
void set(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg);
void sub(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg);
void mul(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg);
void jnz(const std::string &a, const std::string &b, int &i, std::unordered_map<std::string, long> &reg);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input_23", delimiters);

    // registers 
    std::unordered_map<std::string, long> reg;

    // vector of freq and rcv
    std::vector<int> freq, recv;

    // times mul is used
    int count = 0;

    // work through instructions
    const int size = input.size();
    for (int i=0; i<size; i++){
        std::vector<std::string> &line = input[i];

        //if      (line[0]=="snd"){ snd(line[1], freq, reg);       }
        if (line[0]=="set"){ set(line[1], line[2], reg);    }
        else if (line[0]=="sub"){ sub(line[1], line[2], reg);    }
        else if (line[0]=="mul"){
            mul(line[1], line[2], reg);
            count++;
        }
        else if (line[0]=="jnz"){ jnz(line[1], line[2], i, reg); }
    }

    std::cout << "Answer (part 1): " << count << std::endl;

    // looking at the assembly and seeing what it does:
    // starting from value of b
    // check if b is prime, if not inc counter
    // increment b by 17
    // loop 1001 times total
    int b = 109300;
    int composite = 0;
    for (int i=0; i<1001; i++){
        if (!is_prime(b)){ composite++; }
        b += 17;
    }

    std::cout << "Answer (part 2): " << composite << std::endl;

    return 0;
}

void set(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg){

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){
        reg[a] = reg[b];
    }
    else {
        reg[a] = std::stoi(b);
    }
}

void sub(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg){

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){
        reg[a] -= reg[b];
    }
    else {
        reg[a] -= std::stoi(b);
    }
}

void mul(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg){

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){
        reg[a] *= reg[b];
    }
    else {
        reg[a] *= std::stoi(b);
    }
}

void jnz(const std::string &a, const std::string &b, int &i, std::unordered_map<std::string, long> &reg){

    // check if a is a register or value
    if (a[0]>='a' && a[0]<='z'){
        if (reg[a]==0){ return; }
    }
    else {
        if (std::stoi(a)==0){ return; }
    }

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){
        i += reg[b]-1;
    }
    else {
        i += std::stoi(b)-1;
    }
}
