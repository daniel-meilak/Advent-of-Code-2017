#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"../utils.h"

// forward function declarations
void snd(const std::string &a, std::vector<int> &freq, std::unordered_map<std::string, long> &reg);
void set(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg);
void add(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg);
void mul(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg);
void mod(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg);
void rcv(const std::string &a, std::vector<int> &freq, std::vector<int> &recv, std::unordered_map<std::string, long> &reg);
void jgz(const std::string &a, const std::string &b, int &i, std::unordered_map<std::string, long> &reg);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("../input_18", delimiters);

    // registers 
    std::unordered_map<std::string, long> reg;

    // vector of freq and rcv
    std::vector<int> freq, recv;

    // work through instructions
    const int size = input.size();
    for (int i=0; i<size; i++){
        std::vector<std::string> &line = input[i];

        if      (line[0]=="snd"){ snd(line[1], freq, reg);       }
        else if (line[0]=="set"){ set(line[1], line[2], reg);    }
        else if (line[0]=="add"){ add(line[1], line[2], reg);    }
        else if (line[0]=="mul"){ mul(line[1], line[2], reg);    }
        else if (line[0]=="mod"){ mod(line[1], line[2], reg);    }
        else if (line[0]=="rcv"){ rcv(line[1], freq, recv, reg); }
        else if (line[0]=="jgz"){ jgz(line[1], line[2], i, reg); }
    }

    std::cout << "Answer (part 1): " << recv.front() << std::endl;


    return 0;
}

void snd(const std::string &a, std::vector<int> &freq, std::unordered_map<std::string, long> &reg){
    // add new freq
    freq.push_back(reg[a]);
}

void set(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg){
    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ reg[a] = reg[b]; }
    else { reg[a] = std::stoi(b); }
}

void add(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg){
    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ reg[a] += reg[b]; }
    else { reg[a] += std::stoi(b); }
}

void mul(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg){
    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ reg[a] *= reg[b]; }
    else { reg[a] *= std::stoi(b); }
}

void mod(const std::string &a, const std::string &b, std::unordered_map<std::string, long> &reg){
    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ reg[a] = mod(reg[a],reg[b]); }
    else { reg[a] = mod(reg[a],std::stol(b)); }
}

void rcv(const std::string &a, std::vector<int> &freq, std::vector<int> &recv, std::unordered_map<std::string, long> &reg){
    // check if a is a register or value
    if (a[0]>='a' && a[0]<='z'){ 
        if (reg[a]==0){ return; }
    }
    else if (std::stoi(a)==0){ return; }

    recv.push_back(freq.back());
}

void jgz(const std::string &a, const std::string &b, int &i, std::unordered_map<std::string, long> &reg){
    // check if a is a register or value
    if (a[0]>='a' && a[0]<='z'){
        if (reg[a]<=0){ return; }
    }
    else if (std::stoi(a)<=0){ return; }

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ i += reg[b]-1; }
    else { i += std::stoi(b)-1; }
}
