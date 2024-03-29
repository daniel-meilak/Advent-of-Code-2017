#pragma once

#include<vector>
#include<string>
#include<list>
#include<unordered_map>
#include"program.h"
#include"utils.h"

struct program{

    // instructions
    std::vector<std::vector<std::string>> instr;

    // position in instructions
    int pos = 0;

    // number of times sent value
    int sent = 0;

    // registers
    std::unordered_map<std::string, long long> reg;

    // recieve buffer
    std::list<long long> recv;

    // running
    bool running = false;
    bool lock    = false;

    // answer for part 1
    bool part_1;

    // constructor
    program(std::vector<std::vector<std::string>> instr, int p, bool part_1);

    // functions
    void run(program &prog);

    void snd(const std::string &a, program &prog);
    void set(const std::string &a, const std::string &b);
    void add(const std::string &a, const std::string &b);
    void mul(const std::string &a, const std::string &b);
    void modu(const std::string &a, const std::string &b);
    void rcv(const std::string &a);
    void jgz(const std::string &a, const std::string &b);
};

program::program(std::vector<std::vector<std::string>> instr, int p, bool part_1 = false){
        this->part_1 = part_1;
        this->instr = instr;
        reg["p"] = p;
}

void program::run(program &prog){

    // first check the pos is valid, else stop running
    if (pos >= (int)instr.size() || pos < 0){
        running = false;
        return;
    }

    // get current instruction
    std::vector<std::string> &line = instr[pos];
    
    // run instruction
    if      (line[0]=="snd"){ snd(line[1], prog);    }
    else if (line[0]=="set"){ set(line[1], line[2]); }
    else if (line[0]=="add"){ add(line[1], line[2]); }
    else if (line[0]=="mul"){ mul(line[1], line[2]); }
    else if (line[0]=="mod"){ modu(line[1], line[2]); }
    else if (line[0]=="rcv"){ rcv(line[1]);          } 
    else if (line[0]=="jgz"){ jgz(line[1], line[2]); }
}

void program::snd(const std::string &a, program &prog){

    if (a[0]>='a' && a[0]<='z'){ prog.recv.push_back(reg[a]); }
    else { prog.recv.push_back(std::stoi(a)); }

    pos++;

    // increment sent counter
    sent++;
}

void program::set(const std::string &a, const std::string &b){

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ reg[a] = reg[b];}
    else { reg[a] = std::stoi(b); }
    pos++;
}

void program::add(const std::string &a, const std::string &b){

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ reg[a] += reg[b]; }
    else { reg[a] += std::stoi(b); }
    pos++;
}

void program::mul(const std::string &a, const std::string &b){

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ reg[a] *= reg[b]; }
    else { reg[a] *= std::stoi(b); }
    pos++;
}

void program::modu(const std::string &a, const std::string &b){

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ reg[a] = mod(reg[a],reg[b]); }
    else { reg[a] = mod(reg[a],std::stoll(b)); }
    pos++;
}

void program::rcv(const std::string &a){

    // if recv vector is empty, halt until a value occurs
    if (recv.size()==0){ 
        lock = true;
        return; 
    }

    // no longer locked waiting for value
    lock = false;

    // get answer for part 1
    if (part_1){ running = false; }

    // put value in register and remove from recv stack
    reg[a] = recv.front();
    recv.pop_front();
    pos++;
}

void program::jgz(const std::string &a, const std::string &b){

    // check if a is a register or value
    if (a[0]>='a' && a[0]<='z'){
        if (reg[a]<=0){
            pos++;
            return;
        }
    }
    else {
        if (std::stoi(a)<=0){
            pos++;
            return;
        }
    }

    // check if b is a register or value
    if (b[0]>='a' && b[0]<='z'){ pos += reg[b]; }
    else { pos += std::stoi(b); }
}