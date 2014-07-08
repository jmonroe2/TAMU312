#include <algorithm>
#include "basic_functions.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"
#include "p6.h"
#include "p7.h"

void tick() {
    ////////////////// IF
    instructionFetch(); // load instructionMem[PC] into IR
    incrementPC(); // now that it's loaded, move to next
    ////////////////// ID
    bool* name = expand_bool(0);
    bool* reg_out = expand_bool(0); //hold index in registry: registry[reg_out]
    bool* reg_in1 = expand_bool(0);
    bool* reg_in2 = expand_bool(0);
    bool* imm = new bool[16];
    // if used(!reg_in1, imm) change these arrays to store registry indicies
    parseInstructionInIR(name, reg_out, reg_in1, reg_in2, imm);
    
    ////////////////// EX
    bool* output = new bool[8]; //??? 8b or 16b esp for mult
    bool* input1 = new bool[8];
    bool* input2 = new bool[8];
    input1 = getRegistryValue(input1, reg_in1);
    input2 = getRegistryValue(input2, reg_in2);
    // how to operate on imm: unrecognized signals doesn't modify output
    output = alu(name, output, input1, input2);
    
    ////////////////// MEM
    //option (write): run_mem(name, reg_out, reg_in1, imm);
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
        setRegistryValue(reg_out, output);
}

