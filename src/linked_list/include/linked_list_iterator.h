#if !defined(_FRM_LINKED_LIST_INCLUDE_LINKED_LIST_ITERATOR_H_)
#define _FRM_LINKED_LIST_INCLUDE_LINKED_LIST_ITERATOR_H_

#include <stddef.h>
#include <stdint.h>

typedef struct linked_list_allocator linked_list_allocator_t;
typedef struct linked_list_iterator  linked_list_iterator_t;
typedef int64_t                      linked_list_size_t;

void*
linked_list_iterator_get(linked_list_iterator_t* it);

void
linked_list_iterator_advance(linked_list_iterator_t* it);

void
linked_list_iterator_advance_n(linked_list_iterator_t* it, linked_list_size_t n);

bool
linked_list_iterator_equals(const linked_list_iterator_t* it, const linked_list_iterator_t* it2);

bool
linked_list_iterator_is_end(const linked_list_iterator_t*);

void
linked_list_iterator_destroy(linked_list_iterator_t* it);

#endif
