#if !defined(_FRM_SRC_LINKED_LIST_INCLUDE_LINKED_LIST_H_)
#define _FRM_SRC_LINKED_LIST_INCLUDE_LINKED_LIST_H_
#include <stdint.h>

typedef struct linked_list_allocator linked_list_allocator_t;
typedef struct linked_list_iterator  linked_list_iterator_t;
typedef struct linked_list           linked_list_t;
typedef int64_t                      linked_list_size_t;
typedef void (*linked_list_apply_fn_t)(void*, void*);
typedef bool (*linked_list_filter_fn_t) (const void*, void*);
typedef bool (*linked_list_equals_fn_t)(const void*, const void*);

linked_list_size_t
linked_list_size(linked_list_t* list);

linked_list_t*
linked_list_create(linked_list_allocator_t* allocator);

void
linked_list_insert_at(linked_list_t* list, linked_list_size_t position, void* constructor_args);

void*
linked_list_at(linked_list_t* list, linked_list_size_t position);

void
linked_list_append(linked_list_t* list, void* constructor_args);

void
linked_list_append_n(linked_list_t* list, void** constructor_args_array,
                     linked_list_size_t elements);

void
linked_list_remove_at(linked_list_t* list, linked_list_size_t position);

void
linked_list_shrink(linked_list_t* list, linked_list_size_t new_size);

void
linked_list_clear(linked_list_t* list);

void
linked_list_destroy(linked_list_t* list);

void
linked_list_foreach(linked_list_t* list, linked_list_apply_fn_t fn, void* fn_args);

linked_list_iterator_t*
linked_list_begin(linked_list_t* list);

void
linked_list_filter(linked_list_t* list, linked_list_filter_fn_t fn, void* filter_fn_arg);

bool
linked_list_equals(linked_list_t* lhs, linked_list_t* rhs, linked_list_equals_fn_t fn);

#endif
