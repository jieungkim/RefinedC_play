#include <stdint.h>
#include "../inc/refinedc.h"

struct [[rc::refined_by("r : nat", "g : nat", "b : nat")]] color {
  [[rc::field("r @ int<u8>")]]
  uint8_t r;

  [[rc::field("g @ int<u8>")]]
  uint8_t g;

  [[rc::field("b @ int<u8>")]]
  uint8_t b;
};

struct [[rc::refined_by("val : nat")]] wrap {
  [[rc::field("val @ int<u32>")]]
  unsigned int val;
};

[[rc::parameters("b : loc", "val : nat")]]
[[rc::args("b @ &own<{val} @ wrap>")]]
[[rc::ensures("b @ &own<{0%nat} @ wrap>")]]
void init(struct wrap *b) {
    b->val = 0;
}

[[rc::parameters("b : loc", "val : nat")]]
[[rc::args("b @ &own<{val} @ wrap>")]]
[[rc::returns("{val} @ wrap")]]
struct wrap copy(struct wrap *b) {
    struct wrap copied;
    copied.val = b->val;
    return copied;
}


[[rc::parameters("pc : loc", "r : nat", "g : nat", "b : nat")]]
[[rc::args("pc @ &own<{r, g, b} @ color>")]]
[[rc::returns("{(r, g, b)} @ color")]]
struct color color_copy(struct color *b) {
    struct color copied;
    copied.r = b->r;
    copied.g = b->g;
    copied.b = b->b;
    
    return copied;
}

[[rc::parameters("ar : loc", "elts : {list (nat * nat * nat)%type}", "size : nat")]]
[[rc::args("ar @&own<array<{(mk_layout 3 0)}, {elts `at_type` color}>>")]]
[[rc::args("size @ int<i32>")]]
[[rc::requires("{(size ≤ length elts)%nat}")]]
[[rc::requires("{(O < size)%nat}")]]
[[rc::ensures("ar @&own<array<{(mk_layout 3 0)}, {<[O:=(O, O, O)]>elts `at_type` (color)}>>")]]
void init_one(struct color *ar, int size){
    ar[0].r = 0;
    ar[0].g = 0;
    ar[0].b = 0;
}

[[rc::parameters("ar : loc", "elts : {list (nat * nat * nat)%type}", "size : nat", "i : nat")]]
[[rc::args("ar @&own<array<{((mk_layout 3 0)}, {elts `at_type` color}>>")]]
[[rc::args("size @ int<i32>")]]
[[rc::args("i @ int<i32>")]]
[[rc::requires("{(size ≤ length elts)%nat}")]]
[[rc::requires("{(i < size)%nat}")]]
[[rc::ensures("ar @&own<array<{(mk_layout 3 0)}, {<[i:=(O, O, O)]>elts `at_type` (color)}>>")]]
void init_i(struct color *ar, int size, int i){
    ar[i].r = 0;
    ar[i].g = 0;
    ar[i].b = 0;
}


/* TODO: make this thing works: Do we need to add additional lemmas and tactics?
#define DATA_SIZE 100
static struct color colorpool[DATA_SIZE];

[[rc::requires("[global_with_type \"colorpool\" Own (uninit (mk_layout (Z.to_nat 100) 3))]")]]
void global_initialize(){
    int i = 0;
    [[rc::exists("index : nat")]]
    [[rc::inv_vars("i : index @ int<i32>")]]
    [[rc::constraints("{(index ≤ 100)%nat}")]]
    while (i < 100) {
        colorpool[i].r = 0;
        colorpool[i].g = 0;
        colorpool[i].b = 0;
        i++;
    }
}
*/

// TODO: make this thing works: Do we need to add additional lemmas and tactics?
[[rc::parameters("ar : loc", "elts : {list (nat * nat * nat)%type}", "size : nat")]]
[[rc::args("ar @&own<array<{(mk_layout 3 0)}, {elts `at_type` color}>>")]]
[[rc::args("size @ int<i32>")]]
[[rc::requires("{(size ≤ length elts)%nat}")]]
// This one looks quite correct with the [constraints] stated as loop invariants, but it cannot be discharged automatically.
// [[rc::ensures("{(∀ k, (k < size)%nat → elts !! k = Some (O, O, O))}")]]
void initialize(struct color *ar, int size){

    [[rc::exists("i : nat")]]
    [[rc::inv_vars("i : i @ int<i32>")]]
    [[rc::constraints("{(i ≤ length elts)%nat}")]]
    // This one looks quite correct, but it cannot be discharged automatically.
    // [[rc::constraints("{(∀ k, (k < i)%nat → elts !! k = Some (O, O, O))}")]]
    for(int i = 0; i < size; i++){
      // Enabling this line causes error even if we do not add additional [ensures] and/or [constraints].
      //  init_i(ar, size, i);
        
      // Enabling the following lines also causes errors even if we do not add additional [ensures] and/or [constraints].
      // ar[i].r = 0;
      // ar[i].g = 0;
      // ar[i].b = 0;
    }
}
