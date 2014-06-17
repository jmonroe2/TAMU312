#include "basic_functions.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"
#include "p4.h"
#include "p5.h"
#include <iostream>

// problem 5 helper functions (real functions begin on line 423 (search PROBLEM 5))
void print16bDecimal(bool byte[8])
{
    int value = 0;
    
    value += byte[15]*1;
    value += byte[14]*2;
    value += byte[13]*4;
    value += byte[12]*8;
    value += byte[11]*16;
    value += byte[10]*32;
    value += byte[9]*64;
    value += byte[8]*128;
    value += byte[7]*256;
    value += byte[6]*512;
    value += byte[5]*1024;
    value += byte[4]*2048;
    value += byte[3]*4096;
    value += byte[2]*8192;
    value += byte[1]*16384;
    value += byte[0]*32768;
    
    std::cout<<"The value is " << value <<'\n';
    
}
void print16b(bool out[16])
{
    std::cout<<out[0]<<out[1]<<out[2]<<out[3]<<' '
    <<out[4]<<out[5]<<out[6]<<out[7]<<' '
    <<out[8]<<out[9]<<out[10]<<out[11]<<' '
    <<out[12]<<out[13]<<out[14]<<out[15]<<'\n';
    
}

bool* add16b(bool* output, bool input1[16], bool input2[16])
// a function to add 2 16bit numbers (helper for mult(u) )
{
    // go from right to left
    int index = 15;
    bool carry = 0;
    bool a,b;
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 14;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 13;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 12;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 11;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 10;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 9;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 8;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 7;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 6;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 5;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 4;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 3;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 2;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 1;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 0;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    bool carry_out = CarryOut(a,b,carry);
    bool exception = XOR(carry,carry_out); // carry_out or     carry_in != carry out
    exception = Or(exception,carry_out);
    
    
    if (exception){
        throw "\n";
    }
    
    return output;
    
}

bool* addu16b(bool* output, bool input1[16], bool input2[16])
// a function to add 2 16bit numbers (helper for mult(u) )
{
    // go from right to left
    int index = 15;
    bool carry = 0;
    bool a,b;
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 14;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 13;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 12;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 11;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 10;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 9;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 8;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 7;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 6;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 5;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 4;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 3;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 2;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 1;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    index = 0;
    carry = CarryOut(a,b,carry);
    a = input1[index]; b = input2[index];
    output[index] = Sum(a,b,carry);
    
    return output;
    
}

bool* Negate16b(bool* output, bool input[16])
{
    // fun count 8 + 115(addu) = 123
    // flip all bits
    bool* temp = new bool[8];
    int index = 15;
    temp[index] = Not(input[index]);
    
    //REPEAT FOr ALL INDICES
    index = 14;
    temp[index] = Not(input[index]);
    index = 13;
    temp[index] = Not(input[index]);
    index = 12;
    temp[index] = Not(input[index]);
    index = 11;
    temp[index] = Not(input[index]);
    index = 10;
    temp[index] = Not(input[index]);
    index = 9;
    temp[index] = Not(input[index]);
    index = 8;
    temp[index] = Not(input[index]);
    index = 7;
    temp[index] = Not(input[index]);
    
    index = 6;
    temp[index] = Not(input[index]);
    index = 5;
    temp[index] = Not(input[index]);
    index = 4;
    temp[index] = Not(input[index]);
    index = 3;
    temp[index] = Not(input[index]);
    index = 2;
    temp[index] = Not(input[index]);
    index = 1;
    temp[index] = Not(input[index]);
    index = 0;
    temp[index] = Not(input[index]);
    
    bool* one = new bool[16];
    one[15] = 1;
    output = addu16b(output,temp,one); //add 1 to flipped bits
    return output;
}

bool* subu16b(bool* output, bool input1[16], bool input2[16])
// return input1 - input2
{
    bool* negative = new bool[8];
    negative = Negate16b(negative, input2);
    
    output = addu16b(output, input1,negative);
    return output;
}


bool* sub16b(bool* output, bool input1[16], bool input2[16])
// return input1 - input2
{
    bool* negative = new bool[8];
    negative = Negate16b(negative, input2);
    
    output = add16b(output, input1,negative);
    return output;
}

bool* shiftLeft16b(bool* output, bool input[16])
// (shift left all bits, equivalent to multiplication with 2)
{
    // think of this as all pull start from most significant And pull value into promoted position
    int index = 0;
    output[index] = input[index+1];
    
    index = 1;
    output[index] = input[index+1];
    index = 2;
    output[index] = input[index+1];
    index = 3;
    output[index] = input[index+1];
    index = 4;
    output[index] = input[index+1];
    index = 5;
    output[index] = input[index+1];
    index = 6;
    output[index] = input[index+1];
    index = 7;
    output[index] = input[index+1];
    index = 8;
    output[index] = input[index+1];
    index = 9;
    output[index] = input[index+1];
    index = 10;
    output[index] = input[index+1];
    index = 11;
    output[index] = input[index+1];
    index = 12;
    output[index] = input[index+1];
    index = 13;
    output[index] = input[index+1];
    index = 14;
    output[index] = input[index+1];
    
    
    output[15] = 0; // fill in the last value with default 0
    
    return output;
}
bool* shiftRight16b(bool* output, bool input[16])
{
    int index = 15;
    output[index] = input[index-1];
    
    index = 14;
    output[index] = input[index-1];
    index = 13;
    output[index] = input[index-1];
    index = 12;
    output[index] = input[index-1];
    index = 11;
    output[index] = input[index-1];
    index = 10;
    output[index] = input[index-1];
    index = 9;
    output[index] = input[index-1];
    index = 8;
    output[index] = input[index-1];
    index = 7;
    output[index] = input[index-1];
    index = 6;
    output[index] = input[index-1];
    index = 5;
    output[index] = input[index-1];
    index = 4;
    output[index] = input[index-1];
    index = 3;
    output[index] = input[index-1];
    index = 2;
    output[index] = input[index-1];
    index = 1;
    output[index] = input[index-1]; // last index= 0; no seg fault
    
    output[0] = 0;
    
    return output;
}

bool* mux16b(bool* output, bool operation, bool input1[16], bool input2[16])
// used in div(u)
{
    // bitwise mux Or operation chooses input1 Or input2: given a single operatOr, it will alway choose input from a single option .: these are the same
    
    // fun count 32 = 8 * mux(4)
    
    int index = 15;
    output[index] = Mux(operation, input1[index], input2[index]);
    
    
    index = 14;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 13;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 12;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 11;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 10;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 9;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 8;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 7;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 6;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 5;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 4;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 3;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 2;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 1;
    output[index] = Mux(operation, input1[index], input2[index]);
    index = 0;
    output[index] = Mux(operation, input1[index], input2[index]);
    
    return output;
}

////// PROBLEM 5
bool* multu(bool* output, bool input1[8], bool input2[8])
{
    bool* addition = new bool[8];
    bool* zero = new bool[8];
    zero = expand_bool(0);
    
    // assume output 16 bits
    // double size of input1 (a)
    bool* double_in1 = new bool[16];
    double_in1[15] = input1[7];
    double_in1[14] = input1[6];
    double_in1[13] = input1[5];
    double_in1[12] = input1[4];
    double_in1[11] = input1[3];
    double_in1[10] = input1[2];
    double_in1[9] = input1[1];
    double_in1[8] = input1[0];
    
    
    addition = mux16b(addition, input2[7], double_in1, zero); //input2 stays 8 bits .: always b[7]
    output = addu16b(output, output, addition); //output+=addition
    double_in1 = shiftLeft16b(double_in1, double_in1); //sll(a,1)
    input2 = shiftRight( input2, input2); //don't care about losing bits- we're done with them
    
    //repeat 7 times
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = addu16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = addu16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = addu16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = addu16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = addu16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = addu16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = addu16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    return output;
}

bool* mult(bool* output, bool input1[8], bool input2[8])
{
    bool* addition = new bool[8];
    bool* zero = new bool[8];
    zero = expand_bool(0);
    
    // assume output 16 bits
    // double size of input1 (a)
    bool* double_in1 = new bool[16];
    double_in1[15] = input1[7];
    double_in1[14] = input1[6];
    double_in1[13] = input1[5];
    double_in1[12] = input1[4];
    double_in1[11] = input1[3];
    double_in1[10] = input1[2];
    double_in1[9] = input1[1];
    double_in1[8] = input1[0];
    
    
    addition = mux16b(addition, input2[7], double_in1, zero); //input2 stays 8 bits .: always b[7]
    output = add16b(output, output, addition); //output+=addition
    double_in1 = shiftLeft16b(double_in1, double_in1); //sll(a,1)
    input2 = shiftRight( input2, input2); //don't care about losing bits- we're done with them
    
    //repeat 7 times
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = add16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = add16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = add16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = add16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = add16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = add16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    addition = mux16b(addition, input2[7], double_in1, zero);
    output = add16b(output, output, addition);
    double_in1 = shiftLeft16b(double_in1, double_in1);
    input2 = shiftRight( input2, input2);
    
    return output;
}


bool* divu(bool* output, bool input1[8], bool input2[8])
{// assume this is in the form input1/input2 = dividend / divisor
    /*rem = dividend
     loop:
     srl(divisor) // always
     sll(output)
     if (rem> dividend)
     rem-= divisor
     ans+=1
     */
    
    // define useful arrays:
    bool* zero = expand_bool(0);
    
    bool* rem_return = new bool[16]; // amount to return to remainder
    bool lthanz;
    
    bool* divisor = new bool[16];
    // deep copy input2 so nothing is messed up
    divisor[15] = input2[7];
    divisor[14] = input2[6];
    divisor[13] = input2[5];
    divisor[12] = input2[4];
    divisor[11] = input2[3];
    divisor[10] = input2[2];
    divisor[9] = input2[1];
    divisor[8] = input2[0];
    
    // in order to subtract each element significance-wise of divisor, need to shift is 8 bits left.
    //sll(divisor, 8);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor); //half
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    
    bool* remainder = new bool[16]; //dividend deep copy
    remainder[15] = input1[7];
    remainder[14] = input1[6];
    remainder[13] = input1[5];
    remainder[12] = input1[4];
    remainder[11] = input1[3];
    remainder[10] = input1[2];
    remainder[9] = input1[1];
    remainder[8] = input1[0];
    // remainder[8:15] = 0;
    
    // begin loop:
    output = shiftLeft(output, output); // may need to move if ans = true*2
    divisor = shiftRight16b(divisor, divisor);// 16b divisor
    
    remainder = subu16b(remainder, remainder, divisor); //16b rem and divis
    lthanz = remainder[0];
    
    // if rem> 0 rem+=divisor
    rem_return = mux16b(rem_return, lthanz, divisor, zero); //16b divisor requires 16b mux
    remainder = addu16b(remainder, remainder, rem_return); //16b remainder
    //else: output+=1
    bool ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    // repeat 7 more times
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = subu16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = subu16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = subu16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = subu16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = subu16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = subu16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = subu16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    return output;
    
}

bool* div(bool* output, bool input1[8], bool input2[8])
{
    //ALMOST IDENTICAL TO DIVU EXCEPT LAST ADD
    //  if I go overflow on subtract, rem< 0 incorrect .: subu --> sub
    // impossible for addu to overflow b/c only possibly adding what's already subtracted .: don't hassle with extra throw candidates
    
    // define useful arrays:
    bool* zero = expand_bool(0);
    
    bool* rem_return = new bool[16]; // amount to return to remainder
    bool lthanz;
    
    bool* divisor = new bool[16];
    // deep copy input2 so nothing is messed up
    divisor[15] = input2[7];
    divisor[14] = input2[6];
    divisor[13] = input2[5];
    divisor[12] = input2[4];
    divisor[11] = input2[3];
    divisor[10] = input2[2];
    divisor[9] = input2[1];
    divisor[8] = input2[0];
    
    // in order to subtract each element significance-wise of divisor, need to shift is 8 bits left.
    //sll(divisor, 8);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor); //half
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    divisor = shiftLeft16b(divisor, divisor);
    
    bool* remainder = new bool[16]; //dividend deep copy
    remainder[15] = input1[7];
    remainder[14] = input1[6];
    remainder[13] = input1[5];
    remainder[12] = input1[4];
    remainder[11] = input1[3];
    remainder[10] = input1[2];
    remainder[9] = input1[1];
    remainder[8] = input1[0];
    // remainder[8:15] = 0;
    
    // begin loop:
    output = shiftLeft(output, output); // may need to move if ans = true*2
    divisor = shiftRight16b(divisor, divisor);// 16b divisor
    
    remainder = sub16b(remainder, remainder, divisor); //16b rem and divis
    lthanz = remainder[0];
    
    // if rem> 0 rem+=divisor
    rem_return = mux16b(rem_return, lthanz, divisor, zero); //16b divisor requires 16b mux
    remainder = addu16b(remainder, remainder, rem_return); //16b remainder
    //else: output+=1
    bool ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    // repeat 7 more times
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = sub16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = sub16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = sub16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = sub16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = sub16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = sub16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    output = shiftLeft(output, output);
    divisor = shiftRight16b(divisor, divisor);
    remainder = sub16b(remainder, remainder, divisor);
    lthanz = remainder[0];
    rem_return = mux16b(rem_return, lthanz, divisor, zero);
    remainder = addu16b(remainder, remainder, rem_return);
    ans_addition = Mux(Not(lthanz), 1, 0);
    output[7] = ans_addition;
    
    return output;
}
