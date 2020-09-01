This file includes modified versions for examples that exist in RefinedC or newly added functions to test RefinedC.


#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "../inc/refinedc.h"
// copied from the [tutorials] directory
#include "alloc.h"
#include "list.h"

// realted to [tutorials/t3_list.c].
// list: int version
typedef struct [[rc::refined_by("l: {list Z}")]]
[[rc::ptr_type("list_t : {maybe2 cons l} @ optionalO<λ (val, l). &own<...>>")]]
list {
    [[rc::field("val @ int<i32>")]]
    int val;
    [[rc::field("l @ list_t")]]
    struct list *tail;
} *list_t;


[[rc::returns("{[]} @ list_t")]]
list_t init () {
    return NULL;
}

[[rc::parameters("p : loc", "l : {list Z}")]]
[[rc::args("p @ &own<l @ list_t>")]]
[[rc::returns("{bool_decide (l = [])} @ boolean<bool_it>")]]
[[rc::ensures("p @ &own<l @ list_t>")]]
bool is_empty (list_t *l) {
    return *l == NULL;
}

[[rc::parameters("l : {list Z}", "val : Z")]]
[[rc::args("l @ list_t", "val @ int<i32>")]]
[[rc::requires("[alloc_initialized]")]]
[[rc::returns("{val :: l} @ list_t")]]
list_t push (list_t p, int e) {
    struct list *node = alloc(sizeof(struct list));
    node->val = e;
    node->tail = p;
    return node;
}

[[rc::parameters("l : {list Z}")]]
[[rc::args("l @ list_t")]]
[[rc::returns("{rev l} @ list_t")]]
list_t reverse (list_t p) {
    list_t w, t;
    w = NULL;
    [[rc::exists("l1 : {list Z}", "l2 : {list Z}")]]
    [[rc::inv_vars("w : l1 @ list_t", "p : l2 @ list_t")]]
    [[rc::constraints("{l = rev l1 ++ l2}")]]
    while (p != NULL) {
        t = p->tail;
        p->tail = w;
        w = p;
        p = t;
    }
    return w;
}

[[rc::parameters("p : loc", "l1 : {list Z}", "l2 : {list Z}")]]
[[rc::args("p @ &own<l1 @ list_t>", "l2 @ list_t")]]
[[rc::ensures("p @ &own<{l1 ++ l2} @ list_t>")]]
void append(list_t *l1, list_t l2) {
  list_t *end = &*l1;
  [[rc::exists("pl : loc", "l1_suffix : {list Z}")]]
  [[rc::inv_vars("end : pl @ &own<l1_suffix @ list_t>")]]
  [[rc::inv_vars("l1 : p @ &own<wand<{pl ◁ₗ (l1_suffix ++ l2) @ list_t}, {l1 ++ l2} @ list_t>>")]]
  while(*end != NULL){
    end = &((*end)->tail);
  }
  *end = l2;
}

[[rc::parameters("l : {list Z}", "p : loc", "n : Z" )]]
[[rc::args("p @ &own<l @ list_t>", "n @ int<i32>")]]
[[rc::exists("b : bool")]]
[[rc::returns("b @ boolean<bool_it>")]]
[[rc::ensures("p @ &own<l @ list_t>", "{b ↔ n ∈ l}")]]
 [[rc::tactics("all: try set_unfold; refined_solver.")]]
bool member (list_t *p, int k) {
    list_t *prev = &*p;
    [[rc::exists("l1 : {list Z}", "pc : loc")]]
    [[rc::inv_vars("prev : pc @ &own<l1 @ list_t>")]]
    [[rc::inv_vars("p : p @ &own<wand<{pc ◁ₗ l1 @ list_t}, l @ list_t>>")]]
    [[rc::constraints("{n ∈ l ↔ n ∈ l1}")]]
    while(*prev != NULL) {
        list_t cur = *prev;

        int head = cur->val;
        if(head == k) {
            return 1;
        }

        prev = &cur->tail;
    }
    return 0;
}

/* TODO: find out the invaraint of this function
[[rc::parameters("l : {list Z}", "p : loc", "n : Z" )]]
[[rc::args("p @ &own<l @ list_t>", "n @ int<i32>")]]
[[rc::exists("b : bool")]]
[[rc::returns("b @ boolean<bool_it>")]]
[[rc::ensures("p @ &own<l @ list_t>", "{b ↔ n ∈ l}")]]
*/
bool member_simple (list_t p, int k) {
    while(p != NULL) {
        if(p->val == k) {
            return 1;
        }
        p = p->tail;
    }
    return 0;
}

