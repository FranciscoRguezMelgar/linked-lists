#if !defined(_FRM_LINKED_LIST_SRC_LINKED_LIST_ITERATOR_H_)
#define _FRM_LINKED_LIST_SRC_LINKED_LIST_ITERATOR_H_

#include <linked_list_iterator.h>

typedef struct linked_list_node      linked_list_node_t;
typedef struct linked_list_allocator linked_list_allocator_t;

linked_list_iterator_t*
linked_list_iterator_create(linked_list_node_t* node, linked_list_allocator_t* allocator);

#endif
