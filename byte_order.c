//
// Created by Jonas on 20.12.2015.
//

#include "byte_order.h"

short reverseShort(short s) {
    unsigned char c1, c2;

    c1 = (unsigned char) (s & 255);
    c2 = (unsigned char) ((s >> 8) & 255);

    return (c1 << 8) + c2;
}

int reverseInt24(int i) {
    unsigned char c1, c2, c3;

    c1 = (unsigned char) (i & 255);
    c2 = (unsigned char) ((i >> 8) & 255);
    c3 = (unsigned char) ((i >> 16) & 255);

    return (c1 << 16) + (c2 << 8) + c3;
}