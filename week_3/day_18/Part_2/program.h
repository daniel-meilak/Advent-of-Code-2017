#ifndef PROGRAM_H
#define PROGRAM_H

#include<vector>
#include<list>
#include<string>
#include<unordered_map>

struct program{

    // instructions
    std::vector<std::vector<std::string>> instr;

    // position in instructions
    int pos = 0;

    // number of times sent value
    int sent = 0;

    // registers
    std::unordered_map<std::string, long> reg;

    // recieve buffer
    std::list<long> recv;

    // running
    bool running = false;
    bool lock    = false;

    // constructor
    program(std::vector<std::vector<std::string>> instr, int p);

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




#endif /* PROGRAM_H */