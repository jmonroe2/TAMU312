#include "basic_functions.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"
#include "p6.h"
#include "p7.h"
#include "p8.h"

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
    for (int i =1; i <=64; i+=1) // 64 commands, un-stalled requires 64+4 cycles
    {
        // pipelineStore columns: name, reg_out, reg_in1, reg_in2 (possibly 0), imm_first, imm_second output, input1, input2
        int fetch_index = 9*( (i-0)%5 );
        fetch_instruction(pipelineStore[fetch_index+0], pipelineStore[fetch_index+1], pipelineStore[fetch_index+2], pipelineStore[fetch_index+3], pipelineStore[fetch_index+4], pipelineStore[fetch_index+6], pipelineStore[fetch_index+7], pipelineStore[fetch_index+8]);
        int decode_index = 9*( (i-1)%5 );
        if ((i-1)>=0){ // make sure don't index bad values
            instruction_decode(pipelineStore[decode_index+0], pipelineStore[decode_index+1], pipelineStore[decode_index+2], pipelineStore[decode_index+3], pipelineStore[decode_index+4], pipelineStore[decode_index+6], pipelineStore[decode_index+7], pipelineStore[decode_index+8]);
        }

        
        ////////// HANDLE STALLS
        // if current regin1 or regin2 access regout from 2  logical rows before, stall 1
        int type1_index = 9*( (i-2)%5 );
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
