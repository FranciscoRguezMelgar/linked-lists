#if !defined(_FRM_SRC_LINKED_LIST_LINKED_LIST_ALLOCATOR_H_)
#define _FRM_SRC_LINKED_LIST_LINKED_LIST_ALLOCATOR_H_
#include <linked_list_allocator.h>
#include <stddef.h>

void*
linked_list_allocator_constructor(linked_list_allocator_t* alloc, void* constructor_args);

void*
linked_list_allocator_alloc(linked_list_allocator_t* alloc, size_t size);

void
linked_list_allocator_destructor(linked_list_allocator_t* alloc, void* object);

void
linked_list_allocator_free(linked_list_allocator_t* alloc, void* ptr);

#endif
