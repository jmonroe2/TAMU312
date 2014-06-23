#include <iostream>
#include "basic_functions.h"

using namespace std;

int functionCount;

bool And(bool a, bool b) {
	functionCount+=1;
	if (a && b) return true;
	else return false;
}

bool Or(bool a, bool b) {
	functionCount+=1;
	return (a || b);
}

bool Not(bool a) {
	functionCount+=1;
	return  !(a);
}

void printFunctionCount() {
	std::cout<< "Functions run: "<<functionCount <<'\n';
    return;
}

void print(bool a) {
	if (a)  std::cout<< "true" <<'\n';
	else std::cout<< "false" <<'\n';
}

void resetFunctionCount() {
	functionCount = 0;
	std::cout<<"Reseting function count\n";
    return;
}

bool getValue(bool byte[8], int offset) {
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

