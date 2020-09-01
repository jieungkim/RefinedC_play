
This file includes modified versions for examples that exist in RefinedC or newly added functions to test RefinedC.


#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "../inc/refinedc.h"
// copied from the [tutorials] directory
#include "alloc.h"
#include "list.h"

// realted to [tutorials/t3_list.c].
typedef struct [[rc::refined_by("l: {list type}")]]
               [[rc::ptr_type("list_t : {maybe2 cons l} @ optionalO<λ (ty, l). &own<...>>")]]
list {
    [[rc::field("&own<ty>")]]
    void *head;

    [[rc::field("l @ list_t")]]
    struct list *tail;
} *list_t;

[[rc::parameters("p : loc", "l : {list type}")]]
[[rc::args("p @ &own<l @ list_t>")]]
// [[rc::returns("{bool_decide (l = [])} @ boolean<bool_it>")]]
[[rc::exists("b : bool")]] // added (1)
[[rc::returns("b @ boolean<bool_it>")]] // added (2)
[[rc::ensures("{if (bool_decide (l = [])) then b = true else b = false}")]] // added (3)
[[rc::ensures("{True}")]] // added (4)
[[rc::ensures("True")]] // added (5)
[[rc::ensures("p @ &own<l @ list_t>")]]
bool is_empty (list_t *l) {
    return *l == NUL
}
