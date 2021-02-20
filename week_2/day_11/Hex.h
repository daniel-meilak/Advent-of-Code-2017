#ifndef HEX_H
#define HEX_H

//===================================================================
// Structs
//===================================================================

struct Hex{
    // coordinates
    int q, r, s;

    // constructor
    Hex(int q_, int r_, int s_);
};

//===================================================================
// Arithmetic
//===================================================================

bool operator==(const Hex &a, const Hex &b);

Hex operator+ (const Hex &lhs, const Hex &rhs);

Hex operator- (const Hex &lhs, const Hex &rhs);

//===================================================================
// Functions
//===================================================================
int hex_length(Hex hex);


#endif /* HEX_H */
