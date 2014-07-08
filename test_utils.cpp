// Implementations of test util functions.
// TA: Yin Qu (me.yin.qu@gmail.com)
/* Compatibility changes:
 to_uint (line 13) change a[i] to a[len-1-i]
 to_bits (line 45, 47) change output[i] to output[len-1-i]
 str_to_bits (line 65, 67) change output[i] output[7-i]
 to_str (line 85) change v[i] to v[len-1-i]
 to_int change regurn a[len-1] a[0]
 */

#include <sstream>
#include "test_utils.h"

using namespace std;

int to_uint(bool* a, int len) {
  int n = 0;
  int d = 1;
  for (int i = 0; i <len; ++i) {
    if (a[len-1 - i]) {
      n += d;
    }
    d = d << 1;
  }
  return n;
} 

int to_int(bool* a, int len) {
  int n = to_uint(a, len);
  return a[0] ? (n - (1 << len)) : n;
} 

int to_uint8(bool* a) {
  return to_uint(a, 8);
}

int to_uint16(bool* a) {
  return to_uint(a, 16);
}

int to_int8(bool* a) {
  return to_int(a, 8);
}

int to_int16(bool* a) {
  return to_int(a, 16);
}

bool* to_bits(bool* output, int num, int len) {
  for (int i = 0; i < len; ++i) {
    if (num & 1) {
      output[len-1 - i] = true;
    } else {
      output[len-1 - i] = false;
    }
    num = num >> 1;
  }
  return output;
}

bool* to_bits8(bool* output, int num) {
  return to_bits(output, num, 8);
}

bool* to_bits16(bool* output, int num) {
  return to_bits(output, num, 16);
}

bool* str_to_bits8(bool* output, const char* num) {
  for (int i = 0; i < 8; ++i) {
    if (num[7 - i] == '1') {
      output[7 - i] = true;
    } else {
      output[7 - i] = false;
    }
  }
  return output;
}

bool bitwise_eq(bool* v1, bool* v2, int len) {
  for (int i = 0; i < len; ++i) {
    if (v1[i] != v2[i]) {
      return false;
    }
  }
  return true;
}

string to_str(bool* v, int len) {
  string s;
  for (int i = 0; i < len; ++i) {
    s = (v[len-1 - i] ? '1' : '0') + s;
  }
  int uint = to_uint(v, len);
  int sint = to_int(v, len);

  ostringstream oss;
  oss << s << " = " << sint << " = " << uint << "U";
  return oss.str();
}

