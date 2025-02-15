#if !defined(_FRM_SRC_LINKED_LIST_INCLUDE_LINKED_LIST_ALLOCATOR_H_)
#define _FRM_SRC_LINKED_LIST_INCLUDE_LINKED_LIST_ALLOCATOR_H_
#include <stddef.h>

typedef struct linked_list_allocator linked_list_allocator_t;
typedef void* (*linked_list_constructor_fn_t)(void*);
typedef void (*linked_list_destructor_fn_t)(void*);
typedef void* (*linked_list_alloc_fn_t)(size_t);
typedef linked_list_destructor_fn_t linked_list_free_fn_t;

#define BASIC_ALLOCATOR_PTR_DECLARATION(type)                                                      \
    extern linked_list_allocator_t* const linked_list_basic_allocator_##type;

BASIC_ALLOCATOR_PTR_DECLARATION(int)
BASIC_ALLOCATOR_PTR_DECLARATION(bool)
BASIC_ALLOCATOR_PTR_DECLARATION(double)
BASIC_ALLOCATOR_PTR_DECLARATION(float)
BASIC_ALLOCATOR_PTR_DECLARATION(ptr_t)

linked_list_allocator_t*
linked_list_allocator_create(linked_list_constructor_fn_t constructor,
                             linked_list_destructor_fn_t  destructor,
                             linked_list_alloc_fn_t allocator, linked_list_free_fn_t deallocator);

void
linked_list_allocator_destroy(linked_list_allocator_t* alloc);

#endif
