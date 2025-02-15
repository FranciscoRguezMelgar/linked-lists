
#include "linked_list_iterator.h"
#include "linked_list_allocator.h"
#include "linked_list_node.h"

typedef struct linked_list_iterator {
    linked_list_node_t*      node;
    linked_list_allocator_t* allocator;
} linked_list_iterator_t;

linked_list_iterator_t*
linked_list_iterator_create(linked_list_node_t* node, linked_list_allocator_t* allocator)
{
    linked_list_iterator_t* res = linked_list_allocator_alloc(allocator, sizeof *res);
    *res                        = (linked_list_iterator_t){
                               .node      = node,
                               .allocator = allocator,
    };
    return res;
}

void*
linked_list_iterator_get(linked_list_iterator_t* it)
{
    return linked_list_node_get_content(it->node);
}

void
linked_list_iterator_advance(linked_list_iterator_t* it)
{
    it->node = linked_list_node_get_next(it->node);
}

void
linked_list_iterator_advance_n(linked_list_iterator_t* it, linked_list_size_t n)
{
    for (linked_list_size_t i = 0; i < n; ++i) {
        linked_list_iterator_advance(it);
    }
}

bool
linked_list_iterator_equals(const linked_list_iterator_t* it, const linked_list_iterator_t* it2)
{
    return it->node == it2->node;
}

bool
linked_list_iterator_is_end(const linked_list_iterator_t* it)
{
    return !(it->node);
}

void
linked_list_iterator_destroy(linked_list_iterator_t* it)
{
    linked_list_allocator_free(it->allocator, it);
}
