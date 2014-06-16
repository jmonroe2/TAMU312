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

bool Xor(bool a, bool b)
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
    return Xor(a,b);
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
    
    cout<<"The value is " << value <<'\n';

}

bool* populate_new_array( bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8)
{
    bool* new_array = new bool[8];
    // bit of confusing Notation: b_i goes in new_array[i-1] (fOr indexing)
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
    // returns true (1) fOr all 0
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
    // AKA, returns 1 fOr all 1
    
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
    
    //REPEAT FOr ALL INDICES
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
// return 1 fOr input1 < input2
{
    // fun count 238
    // fOr a false result we need the sign bit to be 0 .: subtract in reverse
    //ie supposed_less (input1) - supposed_great(input 2); if s_less > s_great sign bit 0 >> return all zeros
    bool* diff = new bool[8];
    diff = subu(diff, input1, input2);
    
    return diff[0];  // return sign bit
}

bool greaterthan(bool input1[8], bool input2[8])
// (return 0 if false)
// return 1 fOr input1 > input2
{
    // fun count 238
    // fOr a true result we want 1 as sign bit .: need negative answer .: reverse expected
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
// return 1111 1111 fOr input1 < input2
{
    // fun count 238
    // fOr a false result we need the sign bit to be 0 .: subtract in reverse
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
// return 1111 1111 fOr input1 > input2
{
    // fun count 238
    // fOr a true result we want 1 as sign bit .: need negative answer .: reverse expected
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
////////////////////////////////////// PROBLEM 3 HELPER
bool* expand_bool(bool input){
    
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
////////////////////////////////////// PROBLEM 3
bool* alu(bool instruction[8], bool input1[8], bool input2[8])
{
    
    //bool* i = new bool[8];
    bool* i = instruction; // redefine fOr code clarity
    
    // DEFINE DECODER FOr SIGNAL INTERPRETATION
    ////////////////////////////////////
    // let signal be deNoted 01234567
    // only one of sig1-18 will be 1111,1111 all others 0000,0000
    bool fhb = Or(Or(i[0],i[1]),Or(i[2],i[3])); //0*1*2*3*4 //First half byte
    
    // sig1
    bool tmp = Or(i[4],i[5]); //4,5
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
    if (all_one(sig1))       cout<<"sig1 \n";
    if (all_one(sig2))		cout<<"negate \n";
	if (all_one(sig3)) 		cout<<"equal \n";
    if (all_one(sig4)) 		cout<<"less than \n";
    if (all_one(sig5)) 		cout<<"greater than \n";
    if (all_one(sig6)) 		cout<<"and \n";
    if (all_one(sig7)) 		cout<<"or \n";
    if (all_one(sig8)) 		cout<<"sll \n";
    if (all_one(sig9)) 		cout<<"srl \n";
    if (all_one(sig10)) 	cout<<"sig10 \n";
    if (all_one(sig11)) 	cout<<"sig11 \n";
    if (all_one(sig12)) 	cout<<"sig12 \n";
    if (all_one(sig13)) 	cout<<"sig13 \n";
    if (all_one(sig14)) 	cout<<"sig14 \n";
    if (all_one(sig15))		cout<<"sig15  \n";
    if (all_one(sig16))		cout<<"addu \n";
    if (all_one(sig17))		cout<<"subu \n";
    
    
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
    
    addu_out = addu(    addu_out,   input1,  input2);
    neg_out = Negate(   neg_out,    input1); //correct assumption?
    sll_out = shiftLeft( sll_out, input1);  //correct assumption?
    srl_out = shiftRight( srl_out, input1); //correct assumption?
    subu_out = subu(    subu_out,   input1,  input2);
    equal_out = equal(  equal_out,  input1,  input2);
    lessthan_out = lessthan(   lessthan_out,  input1,  input2);
    greaterthan_out = greaterthan(  greaterthan_out,  input1,  input2);
    and_out = and8(     and_out,    input1,  input2);
    or_out = or8(       or_out,     input1,  input2);
    
    
    // SELECT OUTPUT
    ////////////////////////////////////
    // and8 with signals (either all 0 or all 1) copies all *_outs to *_option (for code/logic clarity)
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
    
    //// SELECT OUTPUT
    ////////////////////////////////////
    bool* output = new bool[8]; //what about when I add multiply?
    output = or8(output, addu_option, subu_option);
    output = or8(output, output, neg_option); //~ output+=neg_option
    output = or8(output, output, equal_option);
    output = or8(output, output, lessthan_option);
    output = or8(output, output, greaterthan_option);
    output = or8(output, output, and_option);
    output = or8(output, output, or_option);
    output = or8(output, output, sll_option);
    output = or8(output, output, srl_option);
    
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
    bool exception = Xor(carry,carry_out); // carry_out or     carry_in != carry out
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
    negative = Negate(negative, input2);
    
    output = add(output, input1,negative); // add takes care of excpetion
    return output;
}

////////////////////////////////////// PROBLEM 5
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
    bool exception = Xor(carry,carry_out); // carry_out or     carry_in != carry out
    exception = Or(exception,carry_out);
    
    
    if (exception){
        throw "\n";
    }
    
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

bool* mux16b(bool* output, bool operation, bool input1[16], bool input2[16])
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
    // define usefule arrays:
    bool* one = new bool[8];
    one[7] = 1;
    one[6] = 0;
    one[5] = 0;
    one[4] = 0;
    one[3] = 0;
    one[2] = 0;
    one[1] = 0;
    one[0] = 0;
    bool* zero = new bool[8];
    zero = expand_bool(0);

    
    bool* remainder = new bool[8];
    remainder[7] = input1[7];
    remainder[6] = input1[6];
    remainder[5] = input1[5];
    remainder[4] = input1[4];
    remainder[3] = input1[3];
    remainder[2] = input1[2];
    remainder[1] = input1[1];
    remainder[0] = input1[0];
    
    //bool* divisor = new bool[8];
    bool* remove = new bool[8];
    bool* addition = new bool[8];
    bool gthan;
    
    
    for (int i =0; i<8; i+=1) {

    
        input2 = shiftRight(input2, input2);
        output = shiftLeft(output, output); // always begin with zero
        
        gthan = greaterthan(remainder, input2);
        remove = mux(remove, gthan, input2, zero); // remove divisor if > (else 0)
        remainder = subu(remainder, remainder, remove);
        addition = mux(addition, gthan, one, zero); //  if > add 1 ,else add 0

        cout<<gthan <<" therefore use "; printValue(remainder);
        output = addu(output, output, addition); // output+= addition
        
        // v 0 0 1 0  1 0 0 0   0 0 0 0  0 1 0 1
    }
    
    
    return output;
    
}

//bool* div(bool* output, bool input1[8], bool input2[8]);


////////////////////////////////////// MAIN
// should all functions which take output as arugment return void- needless reassignment..?



int main()
{
    // HOW TO RUN:
    // compiled w/ g++ version 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)

    //      see function list fOr available options (*some name changes applied*)
    //      use populate_new_array() with arguments as left to right values (as you would read them)- returns pointer to new array
    //      see example which runs shiftRight fOr mOre detail
    
    // code split into 4 sections in addition to main: base, problem 1, problem 2 helper, problem 2
   	bool a,b,c,d,e,f,g,h;
    bool s,t,u,v,w,x,y,z; //fOr optional test2
	cin>>a>>b>>c>>d>>e>>f>>g>>h;
    cin>>s>>t>>u>>v>>w>>x>>y>>z;
    
    // eg to copy into commAnd line
    // 1 0 1 0  1 0 1 1
    
    // could just populate this with arbitrary values
    bool* test1 = populate_new_array (a,b,c,d,e,f,g,h);
    bool* test2 = populate_new_array (s,t,u,v,w,x,y,z); //instruction
    
    printValueInDecimal(test1);
    printValueInDecimal(test2);
    
    bool* out = new bool[8];
    out = divu(out,test1,test2);
    printValueInDecimal(out);
    //print16bDecimal(out);
    
    //print_function_count();
    //reset_function_count();
    
    return 1;
}

// 0 0 1 0  1 0 0 0   0 0 0 0  0 1 0 1