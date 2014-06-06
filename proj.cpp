#include <iostream>
/*
g++ proj.cpp -o run
*/
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
}

//////////////////////////////////////PROBLEM 2

////////////////////////////////////// MAIN
int main()
{
	bool a,b,c;
	std::cin>>a>>b>>c;
    
    
    std::cout<< "Sum 3\t";
    print(Sum(a,b,c));
	//print_function_count();// sum 3
    //reset_function_count();
    
    std::cout<< "Carrry out\t";
    print(CarryOut(a,b,c));
	//print_function_count(); //carrout
    //reset_function_count();

	
    
    return 1;
}

