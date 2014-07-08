#include "basic_functions.h"
#include "p1.h"
#include "p2.h"
#include "p3.h" // I need helper functions from p3
#include "p6.h"
#include <iostream>

#include <vector>
using namespace std;

bool registry[16][8];
bool instructionMemory[256][8];
bool dataMemory[16][8];
bool PC[8];
bool IR[32];

void initialize() {// please excuse the for loops: they're only to save space
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

    // initialize IR
    for (int i=0; i<32; i+=1)
        IR[i] = 0;
}

bool* getRegistryValue(bool* output, bool registerNum[8]) {
    int indexDec = toDecimal(registerNum);
    //output = registry[indexDec]; // if I don't know size of output, is this acceptable? --seems to temporary: if I change registry whatever calls getReg (lw) also changes
    copy_8bit(output, registry[indexDec], 0 );
    return output;
}

void setRegistryValue(bool registerNum[8], bool value[8]) {
    //check index less than max
    int registrySize = 16;
    bool* max_reg = new bool[8];
    max_reg = decToBin(registrySize - 1); // subtract 1 for indexing
    bool exception;
    exception = lessthan(max_reg, registerNum);
    if (exception){
        cout<< toDecimal(registerNum) <<" ---REGISTRY DOES NOT EXIST"<<endl;
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

int toDecimal(bool registerNum[8]) {
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
}

void incrementPC() {
    // function to set PC = PC +4
    bool* step = new bool[8];
    step = decToBin(4);
    bool* PC_addition = new bool[8];
    PC_addition = addu(PC_addition, &PC[0], step);
    // I don't fully understAnd why this assignment is necessary. In other words, why would fix of second argument Not wOrk for everything?
    assignPC(PC_addition);
}

void addPC(bool addressOffset[8]) {
    bool* PC_addition = new bool[8];
    PC_addition = addu(PC_addition, &PC[0], addressOffset);
    assignPC(PC_addition);
}

void instructionFetch() {
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

void parseInstructionInIR(bool* name,
                          bool* reg_out,
                          bool* reg_in1,
                          bool* reg_in2,
                          bool* imm16) {
    // get instruction from IR, split into 4 Or 3 parts, stOre in respective inputs
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
    
    // if name ==0 then IR is R-type: if R-type: use new input (from IR) else use a copy of Original (ie don't change it)
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

void initializeInstructionMemory(std::ifstream& fp) {
    // function loads <64 lines of *fp into instructionMemory
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
            
            first = atoi(parts[0].c_str());
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

bool* getInstructionValue(bool* output, const std::string& instructionName) {
    // assume name is upper case
    bool* value = new bool[8];
    if (instructionName=="ADD")     value = decToBin(0);
    if (instructionName=="SUB")     value = decToBin(1);
    if (instructionName=="NEG")     value = decToBin(2);
    if (instructionName=="EQUAL")   value = decToBin(3);
    if (instructionName=="LTHAN") value = decToBin(4); // CORRECT?
    if (instructionName=="GTHAN")   value = decToBin(5); // CORRECT?
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

void mem(bool registerNum[8], bool memlocation[16], bool read, bool write) {
    if (read)
        lw(registerNum, memlocation);
    else //(write)
        sw(registerNum, memlocation);
}

void lw(bool registerNum[8], bool memlocation[16]) {
    bool* value = new bool[8]; // populate new array with memory value
    readMem(value, memlocation);
    setRegistryValue(registerNum, value);
}

void sw(bool registerNum[8], bool memlocation[16]) {
    bool* value = new bool[8];
    value = getRegistryValue( value, registerNum);
    writeMem(value, memlocation);
    cout<<"Mem(" << toDecimal(memlocation) << ") = ";
    printValue(value);
    cout<<endl;
}

void readOrWriteMem(bool value[8], bool memlocation[8], bool read, bool write) {
    int mem_dec = toDecimal(memlocation);
    bool* memloc_16b = decToBin_16b(mem_dec);
    
    if (read)
        readMem(value, memloc_16b);
    else
        writeMem(value, memloc_16b);

}

void readMem(bool value[8], bool memlocation[16]) {
    // reads array at memlocation into value
    // ignore first 8 bits of memlocation
    bool* memloc_8b = new bool[8];
    copy_8bit(memloc_8b, memlocation,8);
    
    int memInt = toDecimal(memloc_8b);
    copy_8bit(value, dataMemory[memInt],0);
}

void writeMem(bool value[8], bool memlocation[16]) {
    // ignore first 8 bits of memlocation
    bool* memloc_8b = new bool[8];
    copy_8bit(memloc_8b, memlocation,8);
    
    int memInt = toDecimal(memloc_8b);
    copy_8bit(dataMemory[memInt], value,0);
}

/////////////////////////////////////// Problem 6 helper functions

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
    int height = 32; int width = 8;
    for(int i=0; i<height; i++)
	{
        if (i%4==0) cout<< i/4+1 << ": ";
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