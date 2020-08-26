#include <limits.h>
#include "../inc/refinedc.h"

[[rc::args("int<u32>")]]
[[rc::returns("int<u64>")]]
unsigned long uint64_casting(unsigned int a) {
  unsigned long r = (unsigned long) a;
  return r;
}

[[rc::parameters("a : Z", "b : Z")]]
[[rc::args("a @ int<u32>", "b @ int<u32>")]]
[[rc::returns("int<u32>")]]
unsigned long wrap_add32(unsigned int a, unsigned int b) {
  unsigned long r1 = (unsigned long) a + (unsigned long) b;

  if (r1 <= (unsigned long) UINT_MAX){
    return (unsigned int) r1;
  } else {
    return (unsigned int) (r1 - (unsigned long) UINT_MAX - (unsigned long) 1);
  }
}

[[rc::parameters("x : Z", "y : Z")]]
[[rc::args("x @ int<u32>", "y @ int<u32>")]]
[[rc::returns("int<u32>")]]
unsigned int wrap_sub64(unsigned int x, unsigned int y) {
	if (x >= y) {
		return x - y;
	}
  
  if (y <= (unsigned int) INT_MAX) { // y <= INT_MAX && x < y
    unsigned int y1 = ((UINT_MAX / (unsigned int) 2) - y) + 1;
    return (x + y1);
	}
  
  if (x > (unsigned int) INT_MAX) { // x > INT_MAX && y > INT_MAX && x < y
    return (x - (y - (UINT_MAX / (unsigned int) 2))) + (UINT_MAX / (unsigned int) 2);
	}
 
  // x <= INT_MAX && y > INT_MAX && x > y
  return (x + (UINT_MAX / 2) ) - (y - (UINT_MAX / 2));
}
