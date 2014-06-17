// Functions required by Problem 5.
//
// In your p5.cpp, you should include basic_functions.h, p1.h, and so on, if you
// want to use previously built functions.
//
// Note that you can only use functions you have built so far.

#ifndef P5_H
#define P5_H

// Unsigned and signed versions of multiplier and divider.
// Note that you should integrate them into the ALU you built in p3.

bool* multu(bool* output, bool input1[8], bool input2[8]);
bool* mult(bool* output, bool input1[8], bool input2[8]);

bool* divu(bool* output, bool input1[8], bool input2[8]);
bool* div(bool* output, bool input1[8], bool input2[8]);


// additions
void print16bDecimal(bool byte[8]);
void print16b(bool out[16]);
bool* add16b(bool* output, bool input1[16], bool input2[16]);
bool* addu16b(bool* output, bool input1[16], bool input2[16]);
bool* Negate16b(bool* output, bool input[16]);
bool* subu16b(bool* output, bool input1[16], bool input2[16]);
bool* sub16b(bool* output, bool input1[16], bool input2[16]);
bool* shiftLeft16b(bool* output, bool input[16]);
bool* shiftRight16b(bool* output, bool input[16]);
bool* mux16b(bool* output, bool operation, bool input1[16], bool input2[16]);

#endif // P5_H

