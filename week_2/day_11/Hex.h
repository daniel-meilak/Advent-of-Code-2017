#pragma once

#include<cmath>

//===================================================================
// Structs
//===================================================================

struct Hex{
    // coordinates
    int q, r, s;

    // constructor
    Hex(int q_, int r_, int s_): q(q_), r(r_), s(s_){}
};

//===================================================================
// Arithmetic
//===================================================================

bool operator== (const Hex &a, const Hex &b){
    return a.q == b.q && a.r == b.r && a.s == b.s;
}

Hex operator+ (const Hex &lhs, const Hex &rhs){
    return Hex(lhs.q + rhs.q, lhs.r + rhs.r, lhs.s + rhs.s);
}

Hex operator- (const Hex &lhs, const Hex &rhs){
    return Hex(lhs.q - rhs.q, lhs.r - rhs.r, lhs.s - rhs.s);
}
//===================================================================
// Functions
//===================================================================
int hex_length(Hex hex);int hex_length(Hex hex) {
    return int((std::abs(hex.q) + std::abs(hex.r) + std::abs(hex.s))/2);
}

