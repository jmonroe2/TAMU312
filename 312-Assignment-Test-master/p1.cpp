#include "basic_functions.h"
#include "p1.h"
//#include <stdio>


bool XOR(bool a, bool b)
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
