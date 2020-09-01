#pragma once
#include "../inc/spinlock.h"
#include "alloc.h"

typedef struct [[rc::refined_by("sizes : {list nat}")]]
               [[rc::ptr_type("alloc_entry_t : {maybe2 cons sizes} @ optionalO<λ (size, l) : {(nat * _)}. &own<...>>")]]
               [[rc::size("{mk_layout size 3}")]]
               [[rc::constraints("{(8 | size)}")]] alloc_entry {
    [[rc::field("size @ int<size_t>")]]
    size_t size;

    [[rc::field("l @ alloc_entry_t")]]
    struct alloc_entry *next;
}* alloc_entry_t;

struct [[rc::refined_by("n : unit")]]
       [[rc::exists("lid: lock_id")]] alloc_state {
    [[rc::field("spinlock<lid>")]]
    struct spinlock lock;

    [[rc::field("spinlocked<lid, {\"data\"}, alloc_entry_t>")]]
    alloc_entry_t data;
};

[[rc::requires("[global_with_type \"allocator_state\" Own (uninit struct_alloc_state)]")]]
[[rc::ensures("[alloc_initialized]")]]
void init_alloc();
