TAMU312
=======
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
      bool* negate(bool* output, bool input[8])
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
