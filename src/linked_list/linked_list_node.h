#if !defined(_FRM_LIKED_LIST_SRC_LINKED_LIST_NODE_H_)
#define _FRM_LIKED_LIST_SRC_LINKED_LIST_NODE_H_

typedef struct linked_list_node      linked_list_node_t;
typedef struct linked_list_allocator linked_list_allocator_t;

linked_list_node_t*
linked_list_node_create(linked_list_allocator_t* allocator, void* content);

linked_list_node_t*
linked_list_node_get_next(linked_list_node_t* node);

void
linked_list_node_set_next(linked_list_node_t* node, linked_list_node_t* next);

void*
linked_list_node_get_content(linked_list_node_t* node);

void
linked_list_node_destroy(linked_list_node_t* node, linked_list_allocator_t* allocator);

#endif
