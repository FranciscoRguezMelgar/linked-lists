#include "linked_list_node.h"
#include "linked_list_allocator.h"

typedef struct linked_list linked_list_t;

struct linked_list_node {
    linked_list_node_t* next;
    void*               content;
};

linked_list_node_t*
linked_list_node_create(linked_list_allocator_t* allocator, void* content)
{
    linked_list_node_t* res = linked_list_allocator_alloc(allocator, sizeof *res);
    *res                    = (linked_list_node_t){
                           .content = content,
                           .next    = nullptr,
    };
    return res;
}

linked_list_node_t*
linked_list_node_get_next(linked_list_node_t* node)
{
    return node->next;
}

void
linked_list_node_set_next(linked_list_node_t* node, linked_list_node_t* next)
{
    node->next = next;
}

void*
linked_list_node_get_content(linked_list_node_t* node)
{
    return node->content;
}

void
linked_list_node_destroy(linked_list_node_t* node, linked_list_allocator_t* allocator)
{
    linked_list_allocator_destructor(allocator, node->content);
    linked_list_allocator_free(allocator, node);
}

