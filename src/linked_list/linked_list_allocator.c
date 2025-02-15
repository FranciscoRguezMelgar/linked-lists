#include "linked_list_allocator.h"
#include <stdlib.h>

struct linked_list_allocator {
    linked_list_constructor_fn_t constructor;
    linked_list_destructor_fn_t  destructor;
    linked_list_alloc_fn_t       alloc;
    linked_list_free_fn_t        free;
};

#define BASIC_TYPE_CONSTRUCTOR(type)                                                               \
    static void* allocate_##type(void* arg)                                                        \
    {                                                                                              \
        type* res = malloc(sizeof *res);                                                           \
        *res      = *(type*)arg;                                                                   \
        return res;                                                                                \
    }

#define BASIC_TYPE_ALLOCATOR(type)                                                                 \
    linked_list_allocator_t basic_allocator_##type = {                                             \
        .alloc       = malloc,                                                                     \
        .constructor = allocate_##type,                                                            \
        .destructor  = free,                                                                       \
        .free        = free,                                                                       \
    };

#define BASIC_TYPE_ALLOCATOR_INITIALIZATION(type)                                                  \
    linked_list_allocator_t* const linked_list_basic_allocator_##type = &basic_allocator_##type;

#define BASIC_TYPE_ALLOCATOR_CREATION(type)                                                        \
    BASIC_TYPE_CONSTRUCTOR(type)                                                                   \
    BASIC_TYPE_ALLOCATOR(type)                                                                     \
    BASIC_TYPE_ALLOCATOR_INITIALIZATION(type)

typedef void* ptr_t;
BASIC_TYPE_ALLOCATOR_CREATION(int)
BASIC_TYPE_ALLOCATOR_CREATION(bool)
BASIC_TYPE_ALLOCATOR_CREATION(double)
BASIC_TYPE_ALLOCATOR_CREATION(float)
BASIC_TYPE_ALLOCATOR_CREATION(ptr_t)

linked_list_allocator_t*
linked_list_allocator_create(linked_list_constructor_fn_t constructor,
                             linked_list_destructor_fn_t destructor, linked_list_alloc_fn_t alloc,
                             linked_list_free_fn_t free)
{
    linked_list_allocator_t* res = alloc(sizeof *res);
    *res                         = (linked_list_allocator_t){
                                .constructor = constructor,
                                .destructor  = destructor,
                                .alloc       = alloc,
                                .free        = free,
    };
    return res;
}

void*
linked_list_allocator_constructor(linked_list_allocator_t* alloc, void* constructor_args)
{
    return alloc->constructor(constructor_args);
}

void*
linked_list_allocator_alloc(linked_list_allocator_t* alloc, size_t size)
{
    return alloc->alloc(size);
}

void
linked_list_allocator_destructor(linked_list_allocator_t* alloc, void* object)
{
    alloc->destructor(object);
}

void
linked_list_allocator_free(linked_list_allocator_t* alloc, void* ptr)
{
    alloc->free(ptr);
}

void
linked_list_allocator_destroy(linked_list_allocator_t* alloc)
{
    alloc->free(alloc);
}
