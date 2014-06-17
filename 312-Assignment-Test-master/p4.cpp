#include "basic_functions.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"
#include "p4.h"

////////////////////////////////////// PROBLEM 4

bool* add(bool* output, bool input1[8], bool input2[8])
{
    int index = 7;
    bool carry = 0;
    bool a,b;
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

bool* sub(bool* output, bool input1[8], bool input2[8])
{
    // subtracting from negative number , result should be negative
    // subtracting from positive number: positive number: 1-127 = -126; 127 -1 = 126
    //                                  : negative number 127 - -127 = 254
    bool* negative = new bool[8];
    negative = negate(negative, input2);
    
    output = add(output, input1,negative); // add takes care of excpetion
    return output;
}
