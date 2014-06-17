#include "basic_functions.h"
#include "p1.h"
#include "p2.h"
////DEFINE HELPER FUNCTIONS: (see line of // for demarcation)
bool* populate_new_array( bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8)
{
    bool* new_array = new bool[8];
    // bit of confusing notation: b_i goes in new_array[i-1] (for indexing)
    new_array[0] = b1;
    new_array[1] = b2;
    new_array[2] = b3;
    new_array[3] = b4;
    new_array[4] = b5;
    new_array[5] = b6;
    new_array[6] = b7;
    new_array[7] = b8;
    
    return new_array;
}

bool all_zero (bool input[8])
{
    // returns true (1) for all 0
    // fun count 8
    int index = 7;
    bool result = input[index];
    
    index = 6;
    result = Or(result,input[index]); // 1s permeate result
    
    index = 5;
    result = Or(result,input[index]);
    index = 4;
    result = Or(result,input[index]);
    index = 3;
    result = Or(result,input[index]);
    index = 2;
    result = Or(result,input[index]);
    index = 1;
    result = Or(result,input[index]);
    index = 0;
    result = Or(result,input[index]);
    
    return Not(result);
}

bool all_one (bool input[8] )
{
    // if any value is 0 this returns 0
    // AKA, returns 1 for all 1
    
    int index = 7;
    bool result = input[index];
    
    index = 6;
    result = And(result,input[index]); // 0s permeate result
    
    index = 5;
    result = And(result,input[index]);
    index = 4;
    result = And(result,input[index]);
    index = 3;
    result = And(result,input[index]);
    index = 2;
    result = And(result,input[index]);
    index = 1;
    result = And(result,input[index]);
    index = 0;
    result = And(result,input[index]);
    
    return result;
}

//////////////////////////////////////////////////

bool* mux(bool* output, bool operation, bool input1[8], bool input2[8])
{
    // bitwise mux or operation chooses input1 or input2: given a single operator, it will alway choose input from a single option .: these are the same
    
    // fun count 32 = 8 * mux(4)
    
    int index = 7;
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

bool* addu(bool* output, bool input1[8], bool input2[8])
{
    // fun count = 115
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
    
    return output;
}


bool* negate(bool* output, bool input[8])
//(create the 2's complement version of this number - make sure that a value negated twice is itself)
{
    // fun count 8 + 115(addu) = 123
    // flip all bits
    bool* temp = new bool[8];
    int index = 7;
    temp[index] = Not(input[index]);
    
    //REPEAT FOR ALL INDICES
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
    
    bool* one = populate_new_array(0,0,0,0, 0,0,0,1);
    
    output = addu(output,temp,one); //add 1 to flipped bits
    return output; // what prevents me from Not assigning anything to internal output?
}

bool* subu(bool* output, bool input1[8], bool input2[8])
// return input1 - input2
{
    // fun count 238 ??- How so many
    bool* negative = new bool[8];
    negative = negate(negative, input2);
    
    output = addu(output, input1,negative);
    
    bool* tmp = new bool[8];
    tmp[0] = output[7];
    tmp[1] = output[6];
    tmp[2] = output[5];
    tmp[3] = output[4];
    tmp[4] = output[3];
    tmp[5] = output[2];
    tmp[6] = output[1];
    tmp[7] = output[0];

    output = tmp;
    return tmp;
}

bool equal(bool input1[8], bool input2[8])
//(return 0 if two values are different)
{
    // if output equal all 1, return true
    // fun count 55
    bool* bit_equal = new bool[8];
    
    int index = 7;
    bit_equal[index] = Equal(input1[index],input2[index]);
    
    index = 6;
    bit_equal[index] = Equal(input1[index],input2[index]);
    index = 5;
    bit_equal[index] = Equal(input1[index],input2[index]);
    index = 4;
    bit_equal[index] = Equal(input1[index],input2[index]);
    index = 3;
    bit_equal[index] = Equal(input1[index],input2[index]);
    index = 2;
    bit_equal[index] = Equal(input1[index],input2[index]);
    index = 1;
    bit_equal[index] = Equal(input1[index],input2[index]);
    index = 0;
    bit_equal[index] = Equal(input1[index],input2[index]);
    
    return all_one(bit_equal);
    
}

bool lessthan(bool input1[8], bool input2[8])
// (return 0 if false)
// return 1 for input1 < input2
{
    // fun count 238
    // for a false result we need the sign bit to be 0 .: subtract in reverse
    //ie supposed_less (input1) - supposed_great(input 2); if s_less > s_great sign bit 0 >> return all zeros
    bool* diff = new bool[8];
    diff = subu(diff, input1, input2);
    
    return diff[0];  // return sign bit
}

bool greaterthan(bool input1[8], bool input2[8])
// (return 0 if false)
// return 1 for input1 > input2
{
    // fun count 238
    // for a true result we want 1 as sign bit .: need negative answer .: reverse expected
    // ie supposed_less (input2) - supposed_greater (input1)
    bool* diff = new bool[8];
    diff = subu(diff,input2,input1);
    
    return diff[0]; // return sign bit
    
}

bool* equal(bool* output, bool input1[8], bool input2[8])
// (return 00000000 if two values are different)
//return 1111 1111 if values same

{
    // fun count 55
    bool result = equal(input1,input2);
    output[7] = result;
    output[6] = result;
    output[5] = result;
    output[4] = result;
    output[3] = result;
    output[2] = result;
    output[1] = result;
    output[0] = result;
    
    return output;
}

bool* lessthan(bool* output, bool input1[8], bool input2[8])
// (return 00000000 if false)
// return 1111 1111 for input1 < input2
{
    // fun count 238
    // for a false result we need the sign bit to be 0 .: subtract in reverse
    //ie supposed_less (input1) - supposed_great(input 2); if s_less > s_great sign bit 0 >> return all zeros
    bool result = lessthan(input1,input2);
    output[7] = result;
    output[6] = result;
    output[5] = result;
    output[4] = result;
    output[3] = result;
    output[2] = result;
    output[1] = result;
    output[0] = result;
    
    return output;
    
}

bool* greaterthan(bool* output, bool input1[8], bool input2[8])
// (return 00000000 if false)
// return 1111 1111 for input1 > input2
{
    // fun count 238
    // for a true result we want 1 as sign bit .: need negative answer .: reverse expected
    // ie supposed_less (input2) - supposed_greater (input1)
    
    bool result = greaterthan(input1,input2);
    output[7] = result;
    output[6] = result;
    output[5] = result;
    output[4] = result;
    output[3] = result;
    output[2] = result;
    output[1] = result;
    output[0] = result;
    
    return output;
    
}

bool* and8(bool* output, bool input1[8], bool input2[8])
// (bitwise And)
{
    // fun count 8
    int index = 7;
    output[index] = And(input1[index],input2[index]);
    
    index = 6;
    output[index] = And(input1[index],input2[index]);
    index = 5;
    output[index] = And(input1[index],input2[index]);
    index = 4;
    output[index] = And(input1[index],input2[index]);
    index = 3;
    output[index] = And(input1[index],input2[index]);
    index = 2;
    output[index] = And(input1[index],input2[index]);
    index = 1;
    output[index] = And(input1[index],input2[index]);
    index = 0;
    output[index] = And(input1[index],input2[index]);
    
    return output;
}

bool* or8(bool* output, bool input1[8], bool input2[8])
// (bitwise or)
{
    // fun count 8
    int index = 7;
    output[index] = Or(input1[index],input1[index]);
    
    index = 6;
    output[index] = Or(input1[index],input2[index]);
    index = 5;
    output[index] = Or(input1[index],input2[index]);
    index = 4;
    output[index] = Or(input1[index],input2[index]);
    index = 3;
    output[index] = Or(input1[index],input2[index]);
    index = 2;
    output[index] = Or(input1[index],input2[index]);
    index = 1;
    output[index] = Or(input1[index],input2[index]);
    index = 0;
    output[index] = Or(input1[index],input2[index]);
    
    return output;
}

bool* shiftLeft(bool* output, bool input[8])
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
    output[index] = input[index+1]; //last index 7: no seg fault
    
    output[7] = 0; // fill in the last value with default 0
    
    return output;
}

bool* shiftRight(bool* output, bool input[8])
// (shift right all bits including the sign bit)(shift in same value as MSB)
{
    // starting from right, copy value from left into current And move to more significant index (decrease sequentially)
    
    int index = 7;
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
