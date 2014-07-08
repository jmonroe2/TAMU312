#include "basic_functions.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"
#include "p4.h"
#include "p5.h"
#include <iostream>

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
    
    // DEFINE DECODER FOr SIGNAL INTERPRETATION
    ////////////////////////////////////
    // let signal be deNoted 01234567
    // only one of sig1-18 will be 1111,1111 all others 0000,0000
    bool fhb = Or(Or(i[0],i[1]),Or(i[2],i[3])); //0*1*2*3*4 //First half byte
    
    //sig0
    bool tmp = Or(i[4],i[5]); //4,5
    tmp = Or(tmp,i[6]) ; //4,5,6
    tmp = Or(tmp,i[7]); //4,5,6,7
    bool* sig0 = expand_bool(And(Not(tmp),Not(fhb))); //NOR(0-7)
    
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
    if (all_one(sig0))      std::cout<<"add \n";
    if (all_one(sig1))      std::cout<<"sub \n";
    if (all_one(sig2))		std::cout<<"negate \n";
	if (all_one(sig3)) 		std::cout<<"equal \n";
    if (all_one(sig4)) 		std::cout<<"less than \n";
    if (all_one(sig5)) 		std::cout<<"greater than \n";
    if (all_one(sig6)) 		std::cout<<"and \n";
    if (all_one(sig7)) 		std::cout<<"or \n";
    if (all_one(sig8)) 		std::cout<<"sll \n";
    if (all_one(sig9)) 		std::cout<<"srl \n";
    if (all_one(sig10)) 	std::cout<<"multu \n";
    if (all_one(sig11)) 	std::cout<<"mult \n";
    if (all_one(sig12)) 	std::cout<<"divu \n";
    if (all_one(sig13)) 	std::cout<<"div \n";
    if (all_one(sig14)) 	std::cout<<"sig14 \n";
    if (all_one(sig15))		std::cout<<"sig15  \n";
    if (all_one(sig16))		std::cout<<"addu \n";
    if (all_one(sig17))		std::cout<<"subu \n";
    
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
    neg_out = negate(   neg_out,    input1); //correct assumption?
    sll_out = shiftLeft( sll_out, input1);  //correct assumption?
    srl_out = shiftRight( srl_out, input1); //correct assumption?
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
