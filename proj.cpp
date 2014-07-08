#include "master.h"

//#######################################################
//       think logically, step through things
//  DO:     do p7
//          do p8
//
//
//#######################################################
// QUESTIONS:
//      initialize(): for loops?
//      setRegistryValue() throw expception for write to zero ($0 := 0)
//      search for ? marks for unstated/forgotten questions
/*
g++ proj.cpp -o run // to compile
*/

// MAIN BEGINS ON LINE 574 (sorry I didn't define functions then use them below, let me know if this is too much af a hassle)
int function_count = 0;
void print(bool a)
{
	if (a)  std::cout<< "true" <<'\n';
	else std::cout<< "false" <<'\n';
}

void print_function_count()
{
    std::cout<< "Functions run: "<<function_count <<'\n';
    return;
}

void reset_function_count()
{
	function_count = 0;
    std::cout<<"Reseting function count\n";
    return;
}
/////////////////////////////////////////// BASE FUNCTIONS
bool And(bool a, bool b)
{
	function_count+=1;
	if (a && b) return true;
	else return false;
}

bool Or(bool a, bool b)
{
	function_count+=1;
	return (a || b);
}

bool Not(bool a)
{
	function_count+=1;
	return  !(a);
}
////////////////////////////////////// PROBLEM 1

bool XOr(bool a, bool b)
{
    // (~A)*B + A*(~B)
    //function count 5
    bool nab = And(Not(a),b);
    bool anb = And(a,Not(b));
    return Or(nab, anb);
}

bool Mux(bool operation, bool output_if_true, bool output_if_false)
{
    // let c = op, a = ifTrue; b = ifFalse;
    // return ca + ~cb
    // fun count 4
    bool if_true = And(operation,output_if_true);
    bool if_false = And(Not(operation), output_if_false);
    return Or(if_true, if_false);
}

bool Sum(bool a, bool b)
{
    //fun count 5
    return XOr(a,b);
}

bool Sum(bool a, bool b, bool c)
{
    // fun count 10
    bool apb = Sum(a,b);
    return Sum(apb,c);
}

bool CarryOut(bool a, bool b, bool c)
{
    // need at least two true: ab + bc + ac
    // fun count 5
    bool ab = And(a,b);
    bool bc = And(b,c);
    bool ac = And(a,c);
    bool first = Or(ab,bc);
    return Or(first,ac);
}

bool Equal(bool a, bool b)
//(Returns 1 if two values are equal)
{
    // fun count 6
    return Not(Sum(a,b));
    
    /* ? fun count 5:
    ab = And(a,b);
    na = Not(a);
    nb = Not(b);
    nanb = And(na,nb);
    return Or(ab,nanb);
    */
}

////////////////////////////////////// PROBLEM 2- HELPERS
bool getValue(bool byte[8], int offset)
{
    return byte[offset];
}

void writeValue(bool* byte, int offset, bool value)
{
    byte[offset] = value;
}

void printValue(bool byte[8])
{
    cout<<byte[0]<<byte[1]<<byte[2]<<byte[3];
    cout<<' ';
    cout<<byte[4]<<byte[5]<<byte[6]<<byte[7]<<'\n';
}

void printValueInDecimal(bool byte[8])
{
    int value = 0;
    value += byte[7]*1;
    value += byte[6]*2;
    value += byte[5]*4;
    value += byte[4]*8;
    value += byte[3]*16;
    value += byte[2]*32;
    value += byte[1]*64;
    value += byte[0]*128;
    
    cout << value <<'\n';

}

bool* populate_new_array( bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8)
{
    bool* new_array = new bool[8];
    // bit of confusing Notation: b_i goes in new_array[i-1] (for indexing)
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
////////////////////////////////////// PROBLEM 2

bool* mux(bool* output, bool operation, bool input1[8], bool input2[8])
{
    // bitwise mux Or operation chooses input1 Or input2: given a single operatOr, it will alway choose input from a single option .: these are the same

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


bool* Negate(bool* output, bool input[8])
//(create the 2's complement version of this number - make sure that a value negated twice is itself)
{
    // fun count 8 + 115(addu) = 123
    // flip all bits
    bool* temp = new bool[8];
    int index = 7;
    temp[index] = Not(input[index]);
    
    //REPEAT for ALL INDICES
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
    negative = Negate(negative, input2);
    
    output = addu(output, input1,negative);
    return output;
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
/*
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
    
    result = all_one(bit_equal); // if inputs are equal, all bits must be equal (all true)
*/
    //////////
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
// (bitwise Or)
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
    // starting from right, copy value from left into current And move to mOre significant index (decrease sequentially)
    
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

////////////////////////////////////// MAIN
// should all functions which take output as arugment return void- needless reassignment..?
////////////////////////////////////// PROBLEM 3 HELPER
bool* expand_bool(bool input)
{
    bool* output = new bool[8];
    output[0] = input;
    output[1] = input;
    output[2] = input;
    output[3] = input;
    output[4] = input;
    output[5] = input;
    output[6] = input;
    output[7] = input;
    
    return output;

    
    // could use populate_new array but I want fewer dependencies
}

bool* and16(bool* output, bool input1[16], bool input2[16])
{
    int index = 15;
    output[index] = And(input1[index],input2[index]);

    index = 14;
    output[index] = And(input1[index],input2[index]);
    index = 13;
    output[index] = And(input1[index],input2[index]);
    index = 12;
    output[index] = And(input1[index],input2[index]);
    index = 11;
    output[index] = And(input1[index],input2[index]);
    index = 10;
    output[index] = And(input1[index],input2[index]);
    index = 9;
    output[index] = And(input1[index],input2[index]);
    index = 8;
    output[index] = And(input1[index],input2[index]);
    index = 7;
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
bool* or16(bool* output, bool input1[16], bool input2[16])
{
    int index = 15;
    output[index] = Or(input1[index],input2[index]);
    
    index = 14;
    output[index] = Or(input1[index],input2[index]);
    index = 13;
    output[index] = Or(input1[index],input2[index]);
    index = 12;
    output[index] = Or(input1[index],input2[index]);
    index = 11;
    output[index] = Or(input1[index],input2[index]);
    index = 10;
    output[index] = Or(input1[index],input2[index]);
    index = 9;
    output[index] = Or(input1[index],input2[index]);
    index = 8;
    output[index] = Or(input1[index],input2[index]);
    index = 7;
    output[index] = Or(input1[index],input2[index]);
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
////////////////////////////////////// PROBLEM 3
bool* alu(bool op_code[8], bool* output, bool input1[8], bool input2[8])

{
    
    //bool* i = new bool[8];
    bool* i = op_code; // redefine for code clarity
    
    // DEFINE DECODER for SIGNAL INTERPRETATION
    ////////////////////////////////////
    // let signal be denoted 01234567
    // only one of sig1-18 will be 1111,1111 all others 0000,0000
    bool fhb = Or(Or(i[0],i[1]),Or(i[2],i[3])); //0*1*2*3*4 //First half byte
    
    //sig0
    bool tmp = Or(i[4],i[5]); //4,5
    tmp = Or(tmp,i[6]) ; //4,5,6
    tmp = Or(tmp,i[7]); //4,5,6,7
    bool* sig0 = expand_bool(And(Not(tmp),Not(fhb))); //NOr(0-7)
    
    // sig1
    tmp = Or(i[4],i[5]); //4,5
    tmp = Or(tmp,i[6]) ; //4,5,6
    tmp = And(Not(tmp),i[7]); //NOr (4,5,6)7
    bool* sig1 = expand_bool(And(tmp,Not(fhb)));  // ~4 ~5 ~6 7
    
    // sig2
    tmp = Or(i[4],i[5]); //4,5
    tmp = Or(tmp,i[7]); //4,5,7
    tmp = And(Not(tmp),i[6]); //NOr(4,5,7)6
    bool* sig2 = expand_bool(And(tmp,Not(fhb))); // ~4 ~5 6 ~7
    
    //sig3
    tmp = Or(i[4],i[5]); //4,5
    tmp = And(Not(tmp),i[6]);// NOr(4,5)6
    tmp = And(tmp,i[7]); //NOr(4,5)67
    bool* sig3 = expand_bool(And(tmp,Not(fhb))); // ~4 ~5 6 7
    
    //sig4
    tmp = Or(i[4],i[6]); //4,6
    tmp = Or(tmp,i[7]); //4,6,7
    tmp = And(Not(tmp),i[5]); //NOr(4,6,7)5
    bool* sig4 = expand_bool(And(tmp,Not(fhb)));
    
    //sig5
    tmp = Or(i[4],i[6]); //4,6
    tmp = And(Not(tmp),i[5]); //NOr(4,6)5
    tmp = And(tmp,i[7]); //NOr(4,6)57
    bool* sig5 = expand_bool(And(tmp,Not(fhb)));
    
    //sig6
    tmp = Or(i[4],i[7]); //4,7
    tmp = And(Not(tmp),i[5]); //NOr(4,7)5
    tmp = And(tmp,i[6]); //Not(4,7)56
    bool* sig6 = expand_bool(And(tmp,Not(fhb)));
    
    //sig7
    tmp = And(Not(i[4]),i[5]); //Not(4)5
    tmp = And(tmp,i[6]); //Not(4)56
    tmp = And(tmp,i[7]); //Not(4)567
    bool* sig7 = expand_bool(And(tmp,Not(fhb)));
    
    //sig8
    tmp = Or(i[5],i[6]); //5,6
    tmp = Or(tmp,i[7]); //5,6,7
    tmp = And(Not(tmp),i[4]); //NOr(567)4
    bool* sig8 = expand_bool(And(tmp,Not(fhb)));
    
    //sig9
    tmp = Or(i[5],i[6]); //56
    tmp = And(Not(tmp),i[4]); //NOr(56)4
    tmp = And(tmp,i[7]); //NOr(56)47
    bool* sig9 = expand_bool(And(tmp,Not(fhb)));
    
     //sig10
     tmp = Or(i[5],i[7]); //57
     tmp = And(Not(tmp),i[4]); //NOr(57)4
     tmp = And(tmp,i[6]);
     bool* sig10 = expand_bool(And(tmp,Not(fhb)));

     //sig11 1111
     tmp = And(Not(i[5]),i[4]); //4*Not(5)
     tmp = And(tmp,i[6]);    //4*Not(5)6
     tmp = And(tmp,i[7]);    //4*Not(5)6
     bool* sig11 = expand_bool(And(tmp,Not(fhb)));
     
     //sig12
     tmp = Or(i[6],i[7]);    //6,7
     tmp = And(Not(tmp),i[4]); //4*NOr(6,7)
     tmp = And(tmp,i[5]);    //45*NOr(6,7)
     bool* sig12 = expand_bool(And(tmp,Not(fhb)));
     
     //sig13     1101
     tmp = And(Not(i[6]),i[4]); //.64
     tmp = And(tmp,i[5]);    //45.6
     tmp = And(tmp,i[7]);    //45.67
     bool* sig13 = expand_bool(And(tmp,Not(fhb)));
     
     //sig14
     tmp = And(Not(i[7]),i[6]); //6.7
     tmp = And(tmp,i[5]);       //56.7
     tmp = And(tmp,i[4]);        //456.7
     bool* sig14 = expand_bool(And(tmp,Not(fhb)));
     
     //sig15
     tmp = And(i[4],i[5]);       //45
     tmp = And(tmp,i[6]);        //456
     tmp = And(tmp,i[7]);        //4567
     bool* sig15 = expand_bool(And(tmp,Not(fhb)));

    
    //sig16
    tmp = Or(i[0],i[1]); //0,1
    tmp = Or(tmp,i[2]); //0,1,2
    tmp = Or(tmp,i[4]); //0,1,2,4
    tmp = Or(tmp,i[5]); //0,1,2,4,5
    tmp = Or(tmp,i[6]); //0,1,2,4,5,6
    tmp = Or(tmp,i[7]); //0,1,2,4,5,6,7
    bool* sig16 = expand_bool(And(Not(tmp),i[3])); //NOr( 0,1,2,4,5,6,7) 3
    
    //sig17
    tmp = Or(i[0],i[1]); //0,1
    tmp = Or(tmp,i[2]); //0,1,2
    tmp = Or(tmp,i[4]); //0,1,2,4
    tmp = Or(tmp,i[5]); //0,1,2,4,5
    tmp = Or(tmp,i[6]); //0,1,2,4,5,6
    tmp = And(Not(tmp),i[3]); //NOr(0,1,2,4,5,6)3
    bool* sig17 = expand_bool(And(tmp,i[7]));//NOr(0,1,2,4,5,6) 37
    
    
    //testing:
    /*
    cout<<"in alu run : ";
    if (all_one(sig0))      cout<<"add \n";
    if (all_one(sig1))      cout<<"sub \n";
    if (all_one(sig2))		cout<<"negate \n";
	if (all_one(sig3)) 		cout<<"equal \n";
    if (all_one(sig4)) 		cout<<"less than \n";
    if (all_one(sig5)) 		cout<<"greater than \n";
    if (all_one(sig6)) 		cout<<"And \n";
    if (all_one(sig7)) 		cout<<"Or \n";
    if (all_one(sig8)) 		cout<<"sll \n";
    if (all_one(sig9)) 		cout<<"srl \n";
    if (all_one(sig10)) 	cout<<"multu \n";
    if (all_one(sig11)) 	cout<<"mult \n";
    if (all_one(sig12)) 	cout<<"divu \n";
    if (all_one(sig13)) 	cout<<"div \n";
    if (all_one(sig14)) 	cout<<"sig14 \n";
    if (all_one(sig15))		cout<<"sig15  \n";
    if (all_one(sig16))		cout<<"addu \n";
    if (all_one(sig17))		cout<<"subu \n";
    */
    // CREATE INPUT OPTIONS
    ////////////////////////////////////
    // find a better way to implement (this calls all functions)
    bool* addu_out = new bool[8];
    bool* subu_out = new bool[8];
    bool* neg_out = new bool[8];
    bool* equal_out = new bool[8];
    bool* lessthan_out = new bool[8];
    bool* greaterthan_out = new bool[8];
    bool* and_out = new bool[8];
    bool* or_out = new bool[8];
    bool* sll_out = new bool[8];
    bool* srl_out = new bool[8];
    
    // additions for problem 5
    bool* add_out = new bool[8];
    bool* sub_out = new bool[8];
    bool* multu_out = new bool[16];
    bool* mult_out = new bool[16];
    bool* divu_out = new bool[16];
    bool* div_out = new bool[16];

    
    addu_out = addu(    addu_out,   input1,  input2);
    neg_out = Negate(   neg_out,    input1); //cOrrect assumption?
    sll_out = shiftLeft( sll_out, input1);  //cOrrect assumption?
    srl_out = shiftRight( srl_out, input1); //cOrrect assumption?
    subu_out = subu(    subu_out,   input1,  input2);
    equal_out = equal(  equal_out,  input1,  input2);
    lessthan_out = lessthan(   lessthan_out,  input1,  input2);
    greaterthan_out = greaterthan(  greaterthan_out,  input1,  input2);
    and_out = and8(     and_out,    input1,  input2);
    or_out = or8(       or_out,     input1,  input2);

    add_out = add( add_out, input1, input2);
    sub_out = sub( sub_out, input1, input2);
    multu_out = multu( multu_out, input1, input2);
    mult_out = mult( mult_out, input1, input2);
    divu_out = divu(divu_out, input1, input2);
    div_out = div(div_out, input1, input2);
    
    
    // SELECT OUTPUT
    ////////////////////////////////////
    // and8 with signals (either all 0 Or all 1) copies all *_outs to *_option (for code/logic clarity)
    bool* addu_option = new bool[8];
    addu_option = and8(addu_option, sig16, addu_out);
    bool* subu_option = new bool[8];
    subu_option = and8(subu_option, sig17, subu_out);
    bool* neg_option = new bool[8];
    neg_option = and8(neg_option, sig2, neg_out);
    bool* equal_option = new bool[8];
    equal_option = and8(equal_option, sig3, equal_out);
    bool* lessthan_option = new bool[8];
    lessthan_option = and8(lessthan_option, sig4, lessthan_out);
    bool* greaterthan_option = new bool[8];
    greaterthan_option = and8(greaterthan_option, sig5, greaterthan_out);
    bool* and_option = new bool[8];
    and_option = and8(and_option, sig6, and_out);
    bool* or_option = new bool[8];
    or_option = and8(or_option, sig7, or_out);
    bool* sll_option = new bool[8];
    sll_option = and8(sll_option, sig8, sll_out);
    bool* srl_option = new bool[8];
    srl_option = and8(srl_option, sig9, srl_out);
    
    // problem 5 additions
    bool* add_option = new bool[8];
    add_option = and8(and_option, sig0, add_out);
    bool* sub_option = new bool[8];
    sub_option = and8(sub_option, sig1, sub_out);
    bool* multu_option = new bool[8];
    multu_option = and16(multu_option, sig10, multu_out);
    bool* mult_option = new bool[8];
    mult_option = and16(mult_option, sig11, mult_out);
    bool* divu_option = new bool[8];
    divu_option = and16(divu_option, sig12, divu_out);
    bool* div_option = new bool[8];
    div_option = and16(div_option, sig13, div_out);
    
    
    //// create OUTPUT
    ////////////////////////////////////
    // from above step, all pointers NULL except 1 lucky winner
    // this step essentially adds several NULLS to the correct pointer
    // if no signals are 11.. then original output permeates
    
    output = or8(output, addu_option, subu_option);
    output = or8(output, output, neg_option); //~ output+=neg_option
    output = or8(output, output, equal_option);
    output = or8(output, output, lessthan_option);
    output = or8(output, output, greaterthan_option);
    output = or8(output, output, and_option);
    output = or8(output, output, or_option);
    output = or8(output, output, sll_option);
    output = or8(output, output, srl_option);
    //problem 5 additions
    output = or8(output, output, add_option);
    output = or8(output, output, sub_option);
    output = or16(output, output, multu_option);
    output = or16(output, output, mult_option);
    output = or16(output, output, divu_option);
    output = or16(output, output, div_option);
    
    return output;
                            
}

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
    bool exception = XOr(carry,carry_out); // carry_out Or     carry_in != carry out
    exception = Or(exception,carry_out);
    

    if (exception){
        cout<<"ADDITION OVERFLOW \n";
        //throw "\n";
    }
    
    return output;
}

bool* sub(bool* output, bool input1[8], bool input2[8])
{
    // subtracting from negative number , result should be negative
    // subtracting from positive number: positive number: 1-127 = -126; 127 -1 = 126
    //                                  : negative number 127 - -127 = 254
    bool* negative = new bool[8];
    negative = Negate(negative, input2);
    
    output = add(output, input1,negative); // add takes care of excpetion
    return output;
}

////////////////////////////////////// PROBLEM 5
// problem 5 helper functions
void print16bDecimal(bool byte[16])
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
    
    cout<<"The value is " << value <<'\n';
}
void print16b(bool out[16])
{
    cout<<out[0]<<out[1]<<out[2]<<out[3]<<' '
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
    bool exception = XOr(carry,carry_out); // carry_out Or     carry_in != carry out
    exception = Or(exception,carry_out);
    
    
    if (exception){
        cout<<"16bit ADDITION OVERFLOW \n";
        //throw "\n";
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
    
    //REPEAT for ALL INDICES
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

bool* multu(bool* output, bool input1[8], bool input2[8])
{
    bool* addition = new bool[8];
    bool* zero = new bool[8];
    zero = expand_bool(0);
    
    bool* input2_copy = new bool[8]; // preserve input2 (consider alu)
    copy_8bit(input2_copy, input2, 0);
    
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
    
    copy_8bit(input2, input2_copy, 0); // reset input2
    return output;
}

bool* mult(bool* output, bool input1[8], bool input2[8])
{
    bool* addition = new bool[8];
    bool* zero = new bool[8];
    zero = expand_bool(0);
    
    bool* input2_copy = new bool[8]; // preserve input2 (consider alu)
    copy_8bit(input2_copy, input2, 0);
    
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
    
    copy_8bit(input2, input2_copy, 0); // reset input2
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
    // deep copy input2 so Nothing is messed up
    divisor[15] = input2[7];
    divisor[14] = input2[6];
    divisor[13] = input2[5];
    divisor[12] = input2[4];
    divisor[11] = input2[3];
    divisor[10] = input2[2];
    divisor[9] = input2[1];
    divisor[8] = input2[0];
    
    // in Order to subtract each element significance-wise of divisor, need to shift is 8 bits left.
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
        
        remainder = subu16b(remainder, remainder, divisor); //16b rem And divis
        lthanz = remainder[0];
        
        // if rem> 0 rem+=divisor
        rem_return = mux16b(rem_return, lthanz, divisor, zero); //16b divisor requires 16b mux
        remainder = addu16b(remainder, remainder, rem_return); //16b remainder
        //else: output+=1
        bool ans_addition = Mux(lthanz, 0, 1);
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
    //  if I go overflow on subtract, rem< 0 incOrrect .: subu --> sub
    // impossible for addu to overflow b/c only possibly adding what's already subtracted .: don't hassle with extra throw cAndidates
    
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
    
    // in Order to subtract each element significance-wise of divisor, need to shift is 8 bits left.
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
        
        remainder = sub16b(remainder, remainder, divisor); //16b rem And divis
        lthanz = remainder[0];
        
        // if rem> 0 rem+=divisor
        rem_return = mux16b(rem_return, lthanz, divisor, zero); //16b divisor requires 16b mux
        remainder = addu16b(remainder, remainder, rem_return); //16b remainder
        //else: output+=1
        bool ans_addition = Mux(Not(lthanz), 1, 0);
        output[7] = ans_addition;
    
    // repeat 7 mOre times
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
////////////////////////////////////// PROBLEM 6

////////////////// DEFINE REGISTERS, COUNTERS, ETC for PROBLEM 6
 bool registry[16][8];
 bool instructionMemory[256][8]; // list of <64 instructions to be run
 bool dataMemory[16][8];
 bool PC[8]; // program counter keeps track of index in instructionMemory
// can set PC = expand_bool(0); // here so it always defaults to zero, irrespecitive of if its called in main
 bool IR[32]; // holds current 32b instruction in form 8b each of: operation number, output registry, input1 registry, input2 registry

////////////////// HELPER FUNCTIONS
bool* decToBin(int dec)
{
    bool* output = expand_bool(0); // initialize new array with all 0s

    if (dec >= 128)
    {
        output[0] = 1;
        dec-= 128;
    }
    if (dec >= 64)
    {
        output[1] = 1;
        dec-= 64;
    }
    if (dec >= 32)
    {
        output[2] = 1;
        dec-= 32;
    }
    if (dec >= 16)
    {
        output[3] = 1;
        dec-= 16;
    }
    if (dec >= 8)
    {
        output[4] = 1;
        dec-= 8;
    }
    if (dec >= 4)
    {
        output[5] = 1;
        dec-= 4;
    }
    if (dec >= 2)
    {
        output[6] = 1;
        dec-= 2;
    }
    if (dec >= 1)
    {
        output[7] = 1;
        dec-= 1;
    }
    if (dec) // by this point we should have covered everything
        cout<<"ERROR CONVERTING DECIMAL TO BINARY"<<endl;
    return output;
    
    /* tested with:
     bool* test;
     for (int i = 0; i<256; i+=1)
     {  test = decToBin(i);
     if ( toDecimal(test) != i)
     cout<<i<<endl;         }
     */
}

void printRegistry()
{
    cout<<"Registry:"<<endl;
    int height = 16; int width = 8;
    for(int i=0; i<height; i++)
	{
        cout<< i << ": ";
        for(int j=0; j<width; j++)
        {
            if (j%4==0 )    cout<<' ';
            cout << registry[i][j];
        }
        cout << endl;
	}
}
void printInstructionMemory()
{
    cout<<"Instruction Memory:"<<endl;
    int height = 256; int width = 8;
    for(int i=0; i<height; i++)
	{
        if (i%4==0) cout<< i/4 << ": ";
        for(int j=0; j<width; j++)
        {
            if (j%4==0 )    cout<<' ';
            if (j%8==0 )    cout<<' ';
            cout << instructionMemory[i][j];
        }
		if (i%4==3) cout << endl;
	}
}

void printDataMemory()
{
    cout<<"Data Memory:"<<endl;
    int height = 32; int width = 8;
    for(int i=0; i<height; i++)
	{
        cout<< i << ": ";
        for(int j=0; j<width; j++)
        {
            if (j%4==0 )    cout<<' ';
            cout << dataMemory[i][j];
        }
        cout << endl;
	}
}

void assignPC(bool* assignment)
{
    PC[0] = assignment[0];
    PC[1] = assignment[1];
    PC[2] = assignment[2];
    PC[3] = assignment[3];
    PC[4] = assignment[4];
    PC[5] = assignment[5];
    PC[6] = assignment[6];
    PC[7] = assignment[7];
    
}

vector<string> split(string input)
{ // successfully tested with test_program.s
    string entry;
    stringstream ss(input);
    
    vector<string> output;
    while (ss >> entry)
        output.push_back(entry);
    
    return output;
}

void copy_8bit(bool* input1, bool* input2, int offset) // is this too much C?
{// a function to copy 8 bits from one to another (to save code)
    input1[0] = input2[0 + offset];
    input1[1] = input2[1 + offset];
    input1[2] = input2[2 + offset];
    input1[3] = input2[3 + offset];
    input1[4] = input2[4 + offset];
    input1[5] = input2[5 + offset];
    input1[6] = input2[6 + offset];
    input1[7] = input2[7 + offset];
}

bool* push_instruction(bool first[8],bool second[8],bool third[8],bool fourth[8], int index)
{

    // first line of distinct instructions at line 0, 4, 8, 12, etc (32/8=4)
    bool* instruction = new bool[32];
    copy_8bit(instructionMemory[index*4], first,0);
    copy_8bit(instructionMemory[index*4 +1], second,0);
    copy_8bit(instructionMemory[index*4 +2], third,0);
    copy_8bit(instructionMemory[index*4 +3], fourth,0);
        return instruction;
}
bool* decToBin_16b(int dec)
{
    bool* output = new bool;
    output[15]=0;
    output[14]=0;
    output[13]=0;
    output[12]=0;
    output[11]=0;
    output[10]=0;
    output[9]=0;
    output[8]=0;
    output[7]=0;
    output[6]=0;
    output[5]=0;
    output[4]=0;
    output[3]=0;
    output[2]=0;
    output[1]=0;
    output[0]=0;
    if (dec >= 32768)
    {
        output[0] = 1;
        dec-= 32768;
    }
    if (dec >= 16384)
    {
        output[1] = 1;
        dec-= 16384;
    }
    if (dec >= 8192)
    {
        output[2] = 1;
        dec-= 8192;
    }
    if (dec >= 4096)
    {
        output[3] = 1;
        dec-= 4096;
    }
    if (dec >= 2048)
    {
        output[4] = 1;
        dec-= 2048;
    }
    if (dec >= 1024)
    {
        output[5] = 1;
        dec-= 1024;
    }
    if (dec >= 512)
    {
        output[6] = 1;
        dec-= 512;
    }

    if (dec >= 256)
    {
        output[7] = 1;
        dec-= 256;
    }
    ////////// last byte
    if (dec >= 128)
    {
        output[8] = 1;
        dec-= 128;
    }
    if (dec >= 64)
    {
        output[9] = 1;
        dec-= 64;
    }
    if (dec >= 32)
    {
        output[10] = 1;
        dec-= 32;
    }
    if (dec >= 16)
    {
        output[11] = 1;
        dec-= 16;
    }
    if (dec >= 8)
    {
        output[12] = 1;
        dec-= 8;
    }
    if (dec >= 4)
    {
        output[13] = 1;
        dec-= 4;
    }
    if (dec >= 2)
    {
        output[14] = 1;
        dec-= 2;
    }
    if (dec >= 1)
    {
        output[15] = 1;
        dec-= 1;
    }
    if (dec) // by this point we should have covered everything
        cout<<"ERROR CONVERTING DECIMAL TO BINARY"<<endl;
    return output;
}

bool is_rtype(bool* name)
{
    // i type constitutes lw (14) sw(15) and li(30)
    bool* fourteen = decToBin(14);
    bool* fifteen = decToBin(15);
    bool* thirty = decToBin(30);
    
    //bool equal(bool input1[8], bool input2[8])
    bool is_lw = equal(name, fourteen);
    bool is_sw = equal(name, fifteen);
    bool is_li = equal(name, thirty);
    
    bool output = Or(is_lw, is_sw);
    output = Or(output, is_li);
    
    return Not(output);
}
///////////////// PROBlEM 6 assigned functions
void initialize()
{// please excuse these for loops, 2176 assignments seems like too much
    // initialize registry:
    // could use copy_8bit
    int height = 16; int width = 8;
    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            registry[i][j] = 0;
    
    // initialize instructionMemory
    // could say copy_8bit(instructionMemory[i], zero,0) 256 times
    height = 256; width = 8;
    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            instructionMemory[i][j] = 0;
    
    // initialize PC
    for (int i=0; i<8; i+=1)
        PC[i] = 0;
    /*
    PC[0] = 0;    PC[1] = 0;    PC[2] = 0;    PC[3] = 0;
    PC[4] = 0;    PC[5] = 0;    PC[6] = 0;    PC[7] = 0;
    */
    // initialize IR
    for (int i=0; i<32; i+=1)
        IR[i] = 0;
    /*
    IR[0]=0; IR[1]=0; IR[2]=0; IR[3]=0; IR[4]=0; IR[5]=0; IR[6]=0; IR[7]=0;
    IR[8]=0; IR[9]=0; IR[10]=0; IR[11]=0; IR[12]=0; IR[13]=0; IR[14]=0; IR[15]=0;
    IR[16]=0; IR[17]=0; IR[18]=0; IR[19]=0; IR[20]=0; IR[21]=0; IR[22]=0; IR[23]=0;
    IR[24]=0; IR[25]=0; IR[26]=0; IR[27]=0; IR[28]=0; IR[29]=0; IR[30]=0; IR[31]=0;
     */
    height = 45; width = 8;
    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            pipelineStore[i][j] = 0;
    
}
bool* getRegistryValue(bool* output, bool registerNum[8])
{
    int indexDec = toDecimal(registerNum);
    //output = registry[indexDec]; // if I don't know size of output, is this acceptable? // don't want shallow copy
    copy_8bit(output, registry[indexDec], 0);
    return output;
}

void setRegistryValue(bool registerNum[8], bool value[8])
{
    //check index less than max
    int registrySize = 16;
    bool* max_reg = new bool[8];
    max_reg = decToBin(registrySize - 1); // subtract 1 for indexing
    bool exception;
    exception = lessthan(max_reg, registerNum);
    if (exception){
        cout<< toDecimal(registerNum) <<" ---REGISTRY DOES NOT EXIST"<<endl;
        throw;
    }
    
    bool* zero = expand_bool(0);
    bool write_to_zero = equal( registerNum, zero);
    if (write_to_zero)
    {
        cout<< "ATTEMPTING TO WRITE TO REGISTRY 0, RESERVED \n\n";
        //throw;
    }
    
    /* 32 bit registers
    bool* index = new bool[8];
    index = shiftLeft(index, registerNum);
    index = shiftLeft(index, index); // index = 4*registerNum
    */
    int regDecimal = toDecimal(registerNum);
    copy_8bit(registry[regDecimal], value, 0);
    
    cout<<"Reg " << toDecimal(registerNum) << " = " ;
    printValue(registry[regDecimal]);
}

int toDecimal (bool registerNum[8])
{
    int value = 0;
    value += registerNum[7]*1;
    value += registerNum[6]*2;
    value += registerNum[5]*4;
    value += registerNum[4]*8;
    value += registerNum[3]*16;
    value += registerNum[2]*32;
    value += registerNum[1]*64;
    value += registerNum[0]*128;
    return value;
    /* tested with:
     bool* test;
     for (int i = 0; i<256; i+=1)
     {  test = decToBin(i);
        if ( toDecimal(test) != i)
            cout<<i<<endl;         }
     */
}

void incrementPC()
{
    // function to set PC = PC +4
    bool* step = new bool[8];
    step = decToBin(4);
    bool* PC_addition = new bool[8];
    PC_addition = addu(PC_addition, &PC[0], step);
    // I don't fully understAnd why this assignment is necessary. In other words, why would fix of second argument Not wOrk for everything?
    assignPC(PC_addition);

}

void addPC( bool addressOffset[8] )
{
    bool* PC_addition = new bool[8];
    PC_addition = addu(PC_addition, &PC[0], addressOffset);
    assignPC(PC_addition);
}


void instructionFetch()
{// function to take current PC and loads this index of instruction memory into IR
/*
    bool* index_bin = new bool[8];
    // index must be multiplied by 4 to accomodate 32 bit instructions
    index_bin = shiftLeft(index_bin, PC);
    index_bin = shiftLeft(index_bin, index_bin);
*/

    int index = toDecimal(PC); // 8b PC to index number
    bool* first_byte  = instructionMemory[index + 0];
    bool* second_byte = instructionMemory[index + 1];
    bool* third_byte  = instructionMemory[index + 2];
    bool* fourth_byte = instructionMemory[index + 3];
    
    copy_8bit(IR, first_byte,0); // eg IR[3] = fb[3]
    IR[8] = second_byte[0];
    IR[9] = second_byte[1];
    IR[10] = second_byte[2];
    IR[11] = second_byte[3];
    IR[12] = second_byte[4];
    IR[13] = second_byte[5];
    IR[14] = second_byte[6];
    IR[15] = second_byte[7];
    
    IR[16] = third_byte[0];
    IR[17] = third_byte[1];
    IR[18] = third_byte[2];
    IR[19] = third_byte[3];
    IR[20] = third_byte[4];
    IR[21] = third_byte[5];
    IR[22] = third_byte[6];
    IR[23] = third_byte[7];
    
    IR[24] = fourth_byte[0];
    IR[25] = fourth_byte[1];
    IR[26] = fourth_byte[2];
    IR[27] = fourth_byte[3];
    IR[28] = fourth_byte[4];
    IR[29] = fourth_byte[5];
    IR[30] = fourth_byte[6];
    IR[31] = fourth_byte[7];
}

void parseInstructionInIR(bool* name, bool* reg_out, bool* reg_in1, bool* reg_in2, bool* imm16) // issues with choose r_type
{// get instruction from IR, split into 4 Or 3 parts, stOre in respective inputs
    // R types have all zeros in name .: use all_zero as mux opertor
    // input respective bits into name And reg_out
    // current instruction stored in IR
    
    // name always first
    copy_8bit(name, IR, 0);     // eg name[0] = IR[0]
    //reg_out always second
    copy_8bit(reg_out, IR, 8);  // eg reg_out[0] = IR[8]

    bool r_type = is_rtype(name);

    bool* reg_in1_copy = new bool[8];
    bool* reg_in1_new = new bool[8];
    copy_8bit(reg_in1_copy, reg_in1, 0); // reg_in1_copy = reg_in1
    copy_8bit(reg_in1_new, IR, 16);     // eg reg_in1[0] = IR[16]
    
    // if R-type: use new input (from IR) else use a copy of Original (ie don't change it)
    reg_in1 = mux(reg_in1, r_type, reg_in1_new, reg_in1_copy);
    
    
    bool* reg_in2_copy = new bool[8];
    bool* reg_in2_new = new bool[8];
    copy_8bit(reg_in2_copy, reg_in2, 0); // reg_in2_copy = reg_in2
    copy_8bit(reg_in2_new, IR, 24);     // eg reg_in2[0] = IR[24]
    
    reg_in2 = mux(reg_in2, r_type, reg_in2_new, reg_in2_copy);
    
    // handle i type case
    bool* imm16_1_copy = new bool[8];   // used for first half of imm16
    bool* imm16_2_copy = new bool[8];   // second half
    bool* imm16_1_new = new bool[8];
    bool* imm16_2_new = new bool[8];
    copy_8bit(imm16_1_copy, imm16, 0);
    copy_8bit(imm16_2_copy, imm16, 8);
    copy_8bit(imm16_1_new, IR, 16);     // get appropriate portions from IR
    copy_8bit(imm16_2_new, IR, 24);
    
    bool* imm16_1_input = new bool[8];
    bool* imm16_2_input = new bool[8];
    // if instruction r_type: assign original, else assign new
    imm16_1_input = mux(imm16_1_input, r_type, imm16_1_copy, imm16_1_new);
    imm16_2_input = mux(imm16_2_input, r_type, imm16_2_copy, imm16_2_new);
    
    copy_8bit(imm16, imm16_1_input, 0);
    //second doesn't work because copy_8bit doesn't offset first
    imm16[8] = imm16_2_input[0];
    imm16[9] = imm16_2_input[1];
    imm16[10] = imm16_2_input[2];
    imm16[11] = imm16_2_input[3];
    imm16[12] = imm16_2_input[4];
    imm16[13] = imm16_2_input[5];
    imm16[14] = imm16_2_input[6];
    imm16[15] = imm16_2_input[7];
}

void initializeinstructionMemory(ifstream& fp) // issues with i-type instructions
{// function loads <64 lines of *fp into instructionMemory
    string word;
    // create vector with list of instrucitons
    vector<string> command_list;
    while (getline( fp, word ))
        command_list.push_back(word);

    if (command_list.size() > 64 ) //this would overflow instruction memory (seg error)
        throw;
    
    bool* name = new bool[8];
    for (int i = 0; i < command_list.size(); i+=1) // could make i<64 and remove throw from above, this forces loop to run 64 times
    {
        vector<string> parts = split(command_list[i]); // vector with string values of commands
        name = getInstructionValue(name, parts[0]);
        parts.erase(parts.begin()); // remove name field
        
        bool r_type = (parts.size() == 3); // b/c only have sw,lw,li, always 2 regs
        if (r_type) // then r-type command
        {
            bool* rd = new bool[8];
            bool* rs = new bool[8];
            bool* rt = new bool[8];
            rd = expand_bool(0); // initialize to 0
            rs = expand_bool(0);
            rt = expand_bool(0);
            
            int first, second, third;
            // get rid of commas in first and second numbers
            parts[0] = parts[0].substr(0, parts[0].size()-1 );
            parts[1] = parts[1].substr(0, parts[1].size()-1 );
            
            first = atoi(parts[0].c_str());
            second = atoi(parts[1].c_str());
            third = atoi(parts[2].c_str());
            
            rd = decToBin(first);
            rs = decToBin(second);
            rt = decToBin(third);
            
            push_instruction(name,rd,rs,rt, i); // creates command with 4 bytes onto ith location of IR
        } // end r-type if
        
        else // then i_type command
        { // only options are lw, sw, li ...
            // ^ .: allowed to hard code if statements?? (esp for li, only use of 16b)
            bool* rs = new bool[8];
            bool* rt = new bool[8]; //effective rd
            bool* imm = new bool[16];
            rs = expand_bool(0); // initialize to 0
            rt = expand_bool(0);
            imm = expand_bool(0); // take care if imm[0:7]
            imm[8] = 0; imm[9] = 0; imm[10] = 0; imm[11] = 0;
            imm[12] = 0; imm[13] = 0; imm[14] = 0; imm[15] = 0;
            
            int first, second;
            // get rid of commas in first and second numbers
            parts[0] = parts[0].substr(0, parts[0].size()-1 );
            ////////////////////////// li issues with this...
            // how is li compatible with eg addi? li rs imm  || addi rs rt imm

            first = atoi(parts[0].c_str()); // type set char to int
            second = atoi(parts[1].c_str());
            
            bool load_imm = (second==30);
            rs = decToBin(first);
            if (load_imm) //determine if we can use rt or imm
            {
                imm = decToBin_16b(second);
                bool* imm_second = new bool[8]; // second byte of imm
                copy_8bit(imm_second, imm, 8);
                // push_instruction grabs first 8 bits (ignores rest)
                push_instruction(name,rs,imm, imm_second, i);
            }
            // define 4 bytes and pass to push_instruction
            else
            {
                rt = decToBin(second);
                bool* zero = expand_bool(0);
                push_instruction(name, rs, zero, rt, i );
            }

        } // end i_type (if) else
    } // end command_list for loop

    
}
bool* getInstructionValue(bool* output, string instructionName)
{
    // assume name is upper case
    bool* value = new bool[8];
    if (instructionName=="ADD")     value = decToBin(0);
    if (instructionName=="SUB")     value = decToBin(1);
    if (instructionName=="NEG")     value = decToBin(2);
    if (instructionName=="EQUAL")   value = decToBin(3);
    if (instructionName=="LT")      value = decToBin(4);
    if (instructionName=="GT")      value = decToBin(5);
    if (instructionName=="AND")     value = decToBin(6);
    if (instructionName=="OR")      value = decToBin(7);
    if (instructionName=="SLL")     value = decToBin(8);
    if (instructionName=="SRL")     value = decToBin(9);
    if (instructionName=="MULTU")   value = decToBin(10);
    if (instructionName=="MULT")    value = decToBin(11);
    if (instructionName=="DIVU")    value = decToBin(12);
    if (instructionName=="DIV")     value = decToBin(13);
    if (instructionName=="LW")      value = decToBin(14);
    if (instructionName=="SW")      value = decToBin(15);
    if (instructionName=="ADDU")    value = decToBin(16);
    if (instructionName=="SUBU")    value = decToBin(17);
    if (instructionName=="LI")      value = decToBin(30);
    
    copy_8bit(output, value,0); //output = value
    return output;
}

void mem(bool registerNum[8], bool memlocation[16], bool read, bool write)
{
    if (read)
        lw(registerNum, memlocation);
    if (write)
        sw(registerNum, memlocation);
}
void lw(bool registerNum[8], bool memlocation[16])
{
    bool* value = new bool[8]; // populate new array with memory value
    readMem(value, memlocation);
    setRegistryValue(registerNum, value);
}
void sw(bool registerNum[8], bool memlocation[16])
{
    bool* value = new bool[8];
    value = getRegistryValue( value, registerNum);
    writeMem(value, memlocation);
    cout<<"Mem(" << toDecimal(memlocation) << ") = ";
    printValue(value);
}

void readOrWriteMem(bool value[8], bool memlocation[8], bool read, bool write)
{
    int mem_dec = toDecimal(memlocation);
    bool* memloc_16b = decToBin_16b(mem_dec);
    
    if (read)
        readMem(value, memloc_16b);
    if (write)
        writeMem(value, memloc_16b);
}
void readMem(bool value[8], bool memlocation[16])
{// reads array at memlocation into value
    // ignore first 8 bits of memlocation
    bool* memloc_8b = new bool[8];
    copy_8bit(memloc_8b, memlocation,8);
   
    int memInt = toDecimal(memloc_8b);
    copy_8bit(value, dataMemory[memInt],0);
}
void writeMem(bool value[8], bool memlocation[16])
{
    // ignore first 8 bits of memlocation
    bool* memloc_8b = new bool[8];
    copy_8bit(memloc_8b, memlocation,8);
    
    int memInt = toDecimal(memloc_8b);
    copy_8bit(dataMemory[memInt], value,0);
}

////////////////////////////////////// PROBLEM 7
////////////////////////////////////// PROBLEM 7 Helpers
void fetch_instruction(bool* name, bool* reg_out, bool* reg_in1, bool* reg_in2, bool* imm, bool* output, bool* input1, bool* input2)
{
    instructionFetch(); // load instructionMem[PC] into IR
    incrementPC(); // now that it's loaded, move to next
    
}

void instruction_decode(bool* name, bool* reg_out, bool* reg_in1, bool* reg_in2, bool* imm, bool* output, bool* input1, bool* input2)
{
    // if used(!reg_in1, imm) change these arrays to store registry indicies
    parseInstructionInIR(name, reg_out, reg_in1, reg_in2, imm);
}

void execute(bool* name, bool* reg_out, bool* reg_in1, bool* reg_in2, bool* imm, bool* output, bool* input1, bool* input2)
{
    input1 = getRegistryValue(input1, reg_in1);
    input2 = getRegistryValue(input2, reg_in2);
    // how to operate on imm: unrecognized signals doesn't modify output
    output = alu(name, output, input1, input2);
    

}

void run_memory(bool* name, bool* reg_out, bool* reg_in1, bool* reg_in2, bool* imm, bool* output, bool* input1, bool* input2)
{
    bool rtype = is_rtype(name);
    if (!rtype)
    {
        bool* fourteen = decToBin(14);
        bool* fifteen = decToBin(15);
        bool* thirty = decToBin(30);
        bool is_lw = equal(name, fourteen); // load word
        bool is_li = equal(name, thirty);
        
        bool is_sw = equal(name, fifteen); // store word

        mem(reg_out, imm, is_lw, is_sw);
        if (is_li)
        {
            bool* value = new bool[8];
            copy_8bit(value, imm, 8); // convert imm to 8 bits
            setRegistryValue(reg_out, value);
        }
        
    }
}

void write_back(bool* name, bool* reg_out, bool* reg_in1, bool* reg_in2, bool* imm, bool* output, bool* input1, bool* input2)
{
    bool rtype = is_rtype(name);
    if (rtype)
        setRegistryValue(reg_out, output); // how to handle mult
}

////////////////////////////////////// PROBLEM 7 Assigned
void tick() {
    bool* name = expand_bool(0);
    bool* reg_out = expand_bool(0); //hold index in registry: registry[reg_out]
    bool* reg_in1 = expand_bool(0);
    bool* reg_in2 = expand_bool(0);
    bool* imm = new bool[16];
    
    bool* output = new bool[8]; //??? 8b or 16b esp for mult
    bool* input1 = new bool[8];
    bool* input2 = new bool[8];
    
    fetch_instruction(name,  reg_out,  reg_in1,  reg_in2,  imm,  output,  input1,  input2);
    instruction_decode(name,  reg_out,  reg_in1,  reg_in2,  imm,  output,  input1,  input2);
    execute(name,  reg_out,  reg_in1,  reg_in2,  imm,  output,  input1,  input2);
    run_memory(name,  reg_out,  reg_in1,  reg_in2,  imm,  output,  input1,  input2);
    write_back(name,  reg_out,  reg_in1,  reg_in2,  imm,  output,  input1,  input2);
    /*
    ////////////////// IF
    instructionFetch(); // load instructionMem[PC] into IR
    incrementPC(); // now that it's loaded, move to next
    ////////////////// ID
    bool* name = expand_bool(0);
    bool* reg_out = expand_bool(0); //hold index in registry: registry[reg_out]
    bool* reg_in1 = expand_bool(0);
    bool* reg_in2 = expand_bool(0);
    bool* imm = new bool[16];
    
    bool* output = new bool[8]; //??? 8b or 16b esp for mult
    bool* input1 = new bool[8];
    bool* input2 = new bool[8];
    
    // if used(!reg_in1, imm) change these arrays to store registry indicies
    parseInstructionInIR(name, reg_out, reg_in1, reg_in2, imm);
    
    ////////////////// EX

    input1 = getRegistryValue(input1, reg_in1);
    input2 = getRegistryValue(input2, reg_in2);
    // how to operate on imm: unrecognized signals doesn't modify output
    output = alu(name, output, input1, input2);
    
    ////////////////// MEM
    //option (write): run_memory(name, reg_out, reg_in1, imm);
    bool rtype = is_rtype(name);
    if (!rtype)
    {
        bool* fourteen = decToBin(14);
        bool* fifteen = decToBin(15);
        bool* thirty = decToBin(30);
        bool is_lw = equal(name, fourteen); // load word
        bool is_li = equal(name, thirty);
        
        bool is_sw = equal(name, fifteen); // store word
        
        mem(reg_out, imm, is_lw, is_sw);
        if (is_li)
        {
            bool* value = new bool[8];
            copy_8bit(value, imm, 8); // convert imm to 8 bits
            setRegistryValue(reg_out, value);
        }
        
    } // end mem operations if
    
    ////////////////// WB
    if (rtype)
        setRegistryValue(reg_out, output); // how to handle mult
     */
}

////////////////////////////////////// PROBLEM 8
////////////////////////////////////// PROBLEM 8 Helpers
void printPipelineStore()
{
    cout<<"Pipeline store:"<<endl;
    cout<<"Name"<<'\t'<<"reg_out"<<'\t'<<"reg_in1"<<'\t'<<"reg_in2"<<'\t'<<"imm1"<<'\t'<<"imm2"<<"\n\t\t"<<"output"<<'\t'<<"input1"<<'\t'<<"input2"<<endl;
    
    int height = 45; int width = 8;
    for(int i=0; i<height; i++)
    {
        if (i%9==0)   cout<< i/9 << ": ";
        for(int j=0; j<width; j++)
        {
            if (j%4==0 )    cout<<' ';
            cout << pipelineStore[i][j];
        }
        if (i%9 == 5)    cout<<"\n\t\t";
        cout<<"  ";
        if (i%9==8)   cout << endl;
    }
    cout<<endl;
}
/*
void assignStore(int index, bool* name, bool* reg_out, bool* reg_in1, bool* reg_in2, bool* imm, bool* output, bool* input1, bool* input2 ) // index is index of command %5, ie which of the 5 logical rows does it go in?
{
    copy_8bit(pipelineStore[9*index+0], name, 0); // deep copy into pipeStore
    copy_8bit(pipelineStore[9*index+1], reg_out, 0);
    copy_8bit(pipelineStore[9*index+2], reg_in1, 0);
    copy_8bit(pipelineStore[9*index+3], reg_in2, 0);
    copy_8bit(pipelineStore[9*index+4], imm, 0); // front half
    copy_8bit(pipelineStore[9*index+5], imm, 8); // later half
    copy_8bit(pipelineStore[9*index+6], output, 0);
    copy_8bit(pipelineStore[9*index+7], input1, 0);
    copy_8bit(pipelineStore[9*index+8], input2, 0);
              
}
 */
////////////////////////////////////// PROBLEM 8 assignment
/*
 build a data structure with
 bool pipelineStore[5*9][8] // 5 command pipeline, each command requires 9 stores of 8bits each
        options for access: for command i, get name at pipe[9*(i%5)+0], get output at pip[9*(i%5)+6]
                         make [5][8*9] write function to get clip
 stores: name, reg_out, reg_in1, reg_in2 (possibly 0), imm (2x8), output, input1, input2
 registry is locked if it is in reg_out slot of n-1 or n-2, n is current command
 write void step(); which moves everything in pipeStore down one position
 or just loop around with fancy math:
 
 */
bool pipelineStore[5*9][8];
void pipeline()
{
    /* indexing explanation:
     pipelineStore = pS; run If on i, ID on i-1 etc .: i-0 for IF
     selecton one of 5 logical rows (for 5 devices/components) (i-0)%5
     translate to actual rows (9 rows per logical row): 9*( (i-0)%5 )
     name = col0, reg_out = col1, ..., input2 = col8: 9*( (i-0)%5 ) +0
     pipelineStore[9*((i-0)%5)+0] = name_column assignment
     */

    // options for using imm: unequivocal: must store in pS as 2 8bits
        //1: all functions (eg tick) call device with 2 imm fields
        //2: combine immediate fields while calling
        //      does this store as 2 bytes in pS?
        //3*: just use adjacent blocks: indexing takes care of overlap
        //      means we don't ever use pS[index+5]


    for (int i =1; i <=64; i+=1) // 64 commands, un-stalled requires 64+4 cycles
    {
        // pipelineStore columns: name, reg_out, reg_in1, reg_in2 (possibly 0), imm_first, imm_second output, input1, input2
        cout<<"command: "<< i <<endl;
        int fetch_index = 9*( (i-0)%5 );
        fetch_instruction(pipelineStore[fetch_index+0], pipelineStore[fetch_index+1], pipelineStore[fetch_index+2], pipelineStore[fetch_index+3], pipelineStore[fetch_index+4], pipelineStore[fetch_index+6], pipelineStore[fetch_index+7], pipelineStore[fetch_index+8]);
        int decode_index = 9*( (i-1)%5 );
        if ((i-1)>=0){ // make sure don't index bad values
            instruction_decode(pipelineStore[decode_index+0], pipelineStore[decode_index+1], pipelineStore[decode_index+2], pipelineStore[decode_index+3], pipelineStore[decode_index+4], pipelineStore[decode_index+6], pipelineStore[decode_index+7], pipelineStore[decode_index+8]);
        }

        
        ////////// HANDLE STALLS
        // if current regin1 or regin2 access regout from 2  logical rows before, stall 1
        int type1_index = 9*( (i-2)%5 );            // compare to one before fetch index, b/c fetch index is working on the next command. Ie before fetch (fetch-1) is this one, but fetch-2 is the issue
        
        bool type1_hazard = equal(pipelineStore[decode_index+2], pipelineStore[type1_index + 1]); //current_reg1 ?= old_reg_out
        bool tmp = equal(pipelineStore[decode_index+3], pipelineStore[type1_index+1]); // current_reg2 ?= old_reg_out
        bool zeros = And(all_zero(pipelineStore[decode_index+2]), all_zero(pipelineStore[decode_index+3]));
        
        type1_hazard = Or(type1_hazard, tmp);
        type1_hazard = And(type1_hazard, Not(zeros));
        
        if (type1_hazard){
            cout<<"type1_hazard\n";
            // push memory and write back through of previous step
            run_memory(pipelineStore[type1_index+0], pipelineStore[type1_index+1], pipelineStore[type1_index+2], pipelineStore[type1_index+3], pipelineStore[type1_index+4], pipelineStore[type1_index+6], pipelineStore[type1_index+7], pipelineStore[type1_index+8]);
            write_back(pipelineStore[type1_index+0],  pipelineStore[type1_index+1], pipelineStore[type1_index+2],  pipelineStore[type1_index+3], pipelineStore[type1_index+4],  pipelineStore[type1_index+6], pipelineStore[type1_index+7],  pipelineStore[type1_index+8]);
        }
        
        // if current reg_in1 or reg_in2 access regout from 1 row before stall 2
        int type2_index = 9*( (i-3)%5 );
        bool type2_hazard = equal(pipelineStore[decode_index+2], pipelineStore[type2_index + 1]); // fetch index with 0 >> -1
        tmp = equal(pipelineStore[decode_index+3], pipelineStore[type2_index + 1]);
        
        type2_hazard = Or(type2_hazard, tmp);
        type2_hazard = And(type2_hazard, Not(all_zero(pipelineStore[decode_index +3])));

        // if both type1 and type2, correct for both
        if (type2_hazard){
            cout<<"type2_hazard\n";
            // push write back through of 2 commands back
            write_back(pipelineStore[type2_index+0],  pipelineStore[type2_index+1], pipelineStore[type2_index+2],  pipelineStore[type2_index+3], pipelineStore[type2_index+4],  pipelineStore[type2_index+6], pipelineStore[type2_index+7],  pipelineStore[type2_index+8]);
        }

    
        //bool write_back_hazard = equal( pipelineStore[decode_index+1]);
        
        int exec_index = 9*( (i-2)%5 );
        if ((i-2) >=0){

            execute(pipelineStore[exec_index+0], pipelineStore[exec_index+1], pipelineStore[exec_index+2], pipelineStore[exec_index+3], pipelineStore[exec_index+4], pipelineStore[exec_index+6], pipelineStore[exec_index+7], pipelineStore[exec_index+8]);
        }
        
        int mem_index = 9*( (i-3)%5 );
        if ((i-3) >=0){
            run_memory(pipelineStore[mem_index+0], pipelineStore[mem_index+1], pipelineStore[mem_index+2], pipelineStore[mem_index+3], pipelineStore[mem_index+4], pipelineStore[mem_index+6], pipelineStore[mem_index+7], pipelineStore[mem_index+8]);
        }
        
        int wb_index = 9*( (i-4)%5 );
        if ((i-4) >=0){
            write_back(pipelineStore[wb_index+0],  pipelineStore[wb_index+1], pipelineStore[wb_index+2],  pipelineStore[wb_index+3], pipelineStore[wb_index+4],  pipelineStore[wb_index+6], pipelineStore[wb_index+7],  pipelineStore[wb_index+8]);
        }
    }
    cout<<" luck winner is "; printValueInDecimal(registry[1]);
    /*
     assign command i a place (math) in pipeStore
     consider i<5 and i>59 specially : only running some commands
     let i track IF .: cycle = run ID on i-1, EX on i-2, MEM on i-3, WB on i-4
                            after running everything for cycle i, put instruction i+1 info into i%5-1
     
     cycle()
     { //cyle = run ID on i-1, EX on i-2, MEM on i-3, WB on i-4
     IF with pS[i%5] = pipelineStore[i%5]; ID with pS[i-1%5] (if i-1>=0); EX with pS[(i-2)%5] ... so on //pS[i%5] takes care of pS[i-5] (command which finishes executing)
    }
     */
}


////////////////////////////////////// MAIN
// WORKING ON: figure out why command 1 not executing, note we changed beginning index of for loop to 1 to read in command to pipelineStore

#include "test_utils.cpp"
using namespace std;
int main()
{
    initialize();
    ifstream ifs_test_program("test_program.s");
    initializeinstructionMemory(ifs_test_program);
    pipeline();

    printRegistry();
    
    // SW 4, 10
    /*
    // LI 4, 11
    to_bits8(instructionMemory[0], 30);
    to_bits8(instructionMemory[1], 4);
    to_bits8(instructionMemory[2], 0);
    to_bits8(instructionMemory[3], 11);
    // LI 5, 13
    to_bits8(instructionMemory[4], 30);
    to_bits8(instructionMemory[5], 5);
    to_bits8(instructionMemory[6], 0);
    to_bits8(instructionMemory[7], 13);
    // ADDU 6, 4, 5
    to_bits8(instructionMemory[8], 16);
    to_bits8(instructionMemory[9], 6);
    to_bits8(instructionMemory[10], 4);
    to_bits8(instructionMemory[11], 5);
    // SW 6, 10
    to_bits8(instructionMemory[12], 15);
    to_bits8(instructionMemory[13], 6);
    to_bits8(instructionMemory[14], 0);
    to_bits8(instructionMemory[15], 10);
    
    to_bits8(PC, 0);
    tick();
    cout<<"11 = "; printValueInDecimal(registry[4]);
    tick();
    cout<<"13 = "; printValueInDecimal(registry[5]);
    tick();
    cout<<"24 = "; printValueInDecimal(registry[6]);
    tick();
    cout<<"24 = "; printValueInDecimal(dataMemory[10]);
    */
    
    return 1;
}
