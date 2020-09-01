
This file includes modified versions for examples that exist in RefinedC or newly added functions to test RefinedC.


#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "../inc/refinedc.h"
// copied from the [tutorials] directory
#include "alloc.h"
#include "list.h"

// related to [tutorials/t1_basic.c].
[[rc::args("struct<struct_basic, {0} @ int<i32>, {0} @ int<i32>>")]]
[[rc::returns("struct<struct_basic, {1} @ int<i32>, {1} @ int<i32>>")]]
struct basic struct_test1(struct basic out) {
    assert (out.a == 0);
    assert (out.b == 0);
    out.a = 1;
    out.b = 1;
    assert (out.a == 1);
    assert (out.b == 1);
    return out;
}
