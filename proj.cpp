#include <iostream>
#include <string.h>
using namespace std;
/*
g++ proj.cpp -o run
*/

// what prevents me from not assigning anything to internal output? in negate?
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
bool AND(bool a, bool b)
{
	function_count+=1;
	if (a && b) return true;
	else return false;
}

bool OR(bool a, bool b)
{
	function_count+=1;
	return (a || b);
}

bool NOT(bool a)
{
	function_count+=1;
	return  !(a);
}
////////////////////////////////////// PROBLEM 1

bool XOR(bool a, bool b)
{
    // (~A)*B + A*(~B)
    //function count 5
    bool nab = AND(NOT(a),b);
    bool anb = AND(a,NOT(b));
    return OR(nab, anb);
}

bool Mux(bool operation, bool output_if_true, bool output_if_false)
{
    // let c = op, a = ifTrue; b = ifFalse;
    // return ca + ~cb
    // fun count 4
    bool if_true = AND(operation,output_if_true);
    bool if_false = AND(NOT(operation), output_if_false);
    return OR(if_true, if_false);
}

bool Sum(bool a, bool b)
{
    //fun count 5
    return XOR(a,b);
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
    bool ab = AND(a,b);
    bool bc = AND(b,c);
    bool ac = AND(a,c);
    bool first = OR(ab,bc);
    return OR(first,ac);
}

bool Equal(bool a, bool b)
//(Returns 1 if two values are equal)
{
    // fun count 6
    return NOT(Sum(a,b));
    
    /* ? fun count 5:
    ab = AND(a,b);
    na = NOT(a);
    nb = NOT(b);
    nanb = AND(na,nb);
    return OR(ab,nanb);
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
    
    cout<<"The value is " << value <<'\n';

}

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
    result = OR(result,input[index]); // 1s permeate result
    
    index = 5;
    result = OR(result,input[index]);
    index = 4;
    result = OR(result,input[index]);
    index = 3;
    result = OR(result,input[index]);
    index = 2;
    result = OR(result,input[index]);
    index = 1;
    result = OR(result,input[index]);
    index = 0;
    result = OR(result,input[index]);
    
    return NOT(result);
}

bool all_one (bool input[8] )
{
    // if any value is 0 this returns 0
    // AKA, returns 1 for all 1
    
    int index = 7;
    bool result = input[index];
    
    index = 6;
    result = AND(result,input[index]); // 0s permeate result
    
    index = 5;
    result = AND(result,input[index]);
    index = 4;
    result = AND(result,input[index]);
    index = 3;
    result = AND(result,input[index]);
    index = 2;
    result = AND(result,input[index]);
    index = 1;
    result = AND(result,input[index]);
    index = 0;
    result = AND(result,input[index]);

    return result;
}
////////////////////////////////////// PROBLEM 2

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


bool* Negate(bool* output, bool input[8])
//(create the 2's complement version of this number - make sure that a value negated twice is itself)
{
    // fun count 8 + 115(addu) = 123
    // flip all bits
    bool* temp = new bool[8];
    int index = 7;
    temp[index] = NOT(input[index]);
    
    //REPEAT FOR ALL INDICES
    index = 6;
    temp[index] = NOT(input[index]);
    index = 5;
    temp[index] = NOT(input[index]);
    index = 4;
    temp[index] = NOT(input[index]);
    index = 3;
    temp[index] = NOT(input[index]);
    index = 2;
    temp[index] = NOT(input[index]);
    index = 1;
    temp[index] = NOT(input[index]);
    index = 0;
    temp[index] = NOT(input[index]);

    bool* one = populate_new_array(0,0,0,0, 0,0,0,1);
    
    output = addu(output,temp,one); //add 1 to flipped bits
    return output; // what prevents me from not assigning anything to internal output?
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

bool* equal_fullout(bool* output, bool input1[8], bool input2[8])
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

bool* lessthan_fullout(bool* output, bool input1[8], bool input2[8])
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

bool* greaterthan_fullout(bool* output, bool input1[8], bool input2[8])
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

bool* and_bitwise(bool* output, bool input1[8], bool input2[8])
// (bitwise and)
{
    // fun count 8
    int index = 7;
    output[index] = AND(input1[index],input2[index]);
    
    index = 6;
    output[index] = AND(input1[index],input2[index]);
    index = 5;
    output[index] = AND(input1[index],input2[index]);
    index = 4;
    output[index] = AND(input1[index],input2[index]);
    index = 3;
    output[index] = AND(input1[index],input2[index]);
    index = 2;
    output[index] = AND(input1[index],input2[index]);
    index = 1;
    output[index] = AND(input1[index],input2[index]);
    index = 0;
    output[index] = AND(input1[index],input2[index]);
    
    return output;
}

bool* or_bitwise(bool* output, bool input1[8], bool input2[8])
// (bitwise or)
{
    // fun count 8
    int index = 7;
    output[index] = OR(input1[index],input1[index]);
    
    index = 6;
    output[index] = OR(input1[index],input2[index]);
    index = 5;
    output[index] = OR(input1[index],input2[index]);
    index = 4;
    output[index] = OR(input1[index],input2[index]);
    index = 3;
    output[index] = OR(input1[index],input2[index]);
    index = 2;
    output[index] = OR(input1[index],input2[index]);
    index = 1;
    output[index] = OR(input1[index],input2[index]);
    index = 0;
    output[index] = OR(input1[index],input2[index]);
    
    return output;
}

bool* shiftLeft(bool* output, bool input[8])
// (shift left all bits, equivalent to multiplication with 2)
{
    // think of this as all pull start from most significant and pull value into promoted position
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
    // starting from right, copy value from left into current and move to more significant index (decrease sequentially)
    
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
int main()
{
    // HOW TO RUN:
    // compiled w/ g++ version 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)

    //      see function list for available options (*some name changes applied*)
    //      use populate_new_array() with arguments as left to right values (as you would read them)- returns pointer to new array
    //      see example which runs shiftRight for more detail
    
    // code split into 4 sections in addition to main: base, problem 1, problem 2 helper, problem 2
    /*
      bool AND(bool a, bool b)
      bool OR(bool a, bool b)
      bool NOT(bool a)
     
      bool XOR(bool a, bool b)
      bool Mux(bool operation, bool output_if_true, bool output_if_false)
      bool Sum(bool a, bool b)
      bool Sum(bool a bool b, bool c)
      bool CarryOut(bool a, bool b, bool c)
      bool Equal(bool a, bool b)
     
      bool getValue(bool byte[8], int offset)
      void writeValue(bool* byte, int offset, bool value)
      void printValue(bool byte[8])
      void printValueInDecimal(bool byte[8])
      bool* populate_new_array( bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8)
     
      bool* mux(bool* output, bool operation, bool input1[8], bool input2[8])
      bool* addu(bool* output, bool input1[8], bool input2[8]);
      bool* negate(bool* output, bool input[8]) (create the 2's complement version of this number - make sure that a value negated twice is itself)
      bool* subu(bool* output, bool input1[8], bool input2[8]);
      bool  equal(bool input1[8], bool input2[8]); (return 0 if two values are different)
      bool  lessthan(bool input1[8], bool input2[8]); (return 0 if false)
      bool  greaterthan(bool input1[8], bool input2[8]); (return 0 if false)
      bool* equal_fullout(bool* output, bool input1[8], bool input2[8]); (return 00000000 if two values are different)
      bool* lessthan_fullout(bool* output, bool input1[8], bool input2[8]); (return 00000000 if false)
      bool* greaterthan_fullout(bool* output, bool input1[8], bool input2[8])(return 00000000 if false)
      bool* and_bitwise(bool* output, bool input1[8], bool input2[8]); (bitwise and)
      bool* or_bitwise(bool* output, bool input1[8], bool input2[8])
      bool* shiftLeft(bool* output, bool input[8])
      bool* shiftRight(bool* output, bool input[8])
     
     */
	bool a,b,c,d,e,f,g,h;
    //bool s,t,u,v,w,x,y,z; //for optional test2
	cin>>a>>b>>c>>d>>e>>f>>g>>h;
    //cin>>s>>t>>u>>v>>w>>x>>y>>z;
    
    // eg to copy into command line
    // 1 0 1 0  1 0 1 1
    
    // could just populate this with arbitrary values
    bool* test1 = populate_new_array (a,b,c,d,e,f,g,h);
    //bool* test2 = populate_new_array (s,t,u,v,w,x,y,z);
    
    bool* out = new bool[8];
    out = shiftRight(out,test1);
    
    printValue(test1);
    printValue(out);
    printValueInDecimal(test1);
    printValueInDecimal(out);
    
    print_function_count();
    
    return 1;
}

// 0 0 0 0  1 1 1 1      0 1 1 1  0 0 0 0