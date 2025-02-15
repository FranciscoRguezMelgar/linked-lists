#include "linked_list.h"
#include "linked_list_allocator.h"
#include "linked_list_iterator.h"
#include "linked_list_node.h"

#include <stdbool.h>

struct linked_list {
    linked_list_node_t*      first;
    linked_list_size_t       size;
    linked_list_allocator_t* allocator;
};

typedef struct linked_list_accessor {
    union {
        linked_list_node_t* node;
        linked_list_t*      list;
    };

    bool root;
} linked_list_accessor_t;

static linked_list_node_t*
linked_list_get_node_at(linked_list_t* list, linked_list_size_t pos)
{
    linked_list_node_t* node = list->first;
    for (linked_list_size_t i = 0; i < pos; ++i) {
        node = linked_list_node_get_next(node);
    }
    return node;
}

static linked_list_accessor_t
linked_list_get_accessor_to_before(linked_list_t* list, linked_list_size_t position)
{
    linked_list_accessor_t accessor;
    if ((accessor.root = !position)) {
        accessor.list = list;
    } else {
        accessor.node = linked_list_get_node_at(list, position - 1);
    }
    return accessor;
}

static void
linked_list_accessor_set_next(linked_list_accessor_t accessor, linked_list_node_t* next)
{
    if (accessor.root) {
        accessor.list->first = next;
    } else {
        linked_list_node_set_next(accessor.node, next);
    }
}

static void
linked_list_accessor_advance(linked_list_accessor_t* accessor)
{
    if (accessor->root) {
        accessor->node = accessor->list->first;
    } else {
        accessor->node = linked_list_node_get_next(accessor->node);
    }
    accessor->root = false;
}

static linked_list_node_t*
linked_list_accessor_get_next(linked_list_accessor_t list)
{
    return list.root ? list.list->first : linked_list_node_get_next(list.node);
}

linked_list_size_t
linked_list_size(linked_list_t* list)
{
    return list->size;
}

linked_list_t*
linked_list_create(linked_list_allocator_t* allocator)
{
    linked_list_t* res = linked_list_allocator_alloc(allocator, sizeof *res);
    *res               = (linked_list_t){
                      .allocator = allocator,
                      .size      = 0,
                      .first     = nullptr,
    };
    return res;
}

void
linked_list_insert_at(linked_list_t* list, linked_list_size_t position, void* constructor_args)
{
    void* new_element = linked_list_allocator_constructor(list->allocator, constructor_args);
    linked_list_node_t*    new_node = linked_list_node_create(list->allocator, new_element);
    linked_list_accessor_t accessor = linked_list_get_accessor_to_before(list, position);
    linked_list_node_set_next(new_node, linked_list_accessor_get_next(accessor));
    linked_list_accessor_set_next(accessor, new_node);
    ++list->size;
}

void
linked_list_remove_at(linked_list_t* list, linked_list_size_t position)
{
    linked_list_accessor_t accessor = linked_list_get_accessor_to_before(list, position);
    linked_list_node_t*    next     = linked_list_accessor_get_next(accessor);
    linked_list_accessor_set_next(accessor, linked_list_node_get_next(next));
    linked_list_node_destroy(next, list->allocator);
    --list->size;
}

void
linked_list_append(linked_list_t* list, void* constructor_args)
{
    linked_list_insert_at(list, list->size, constructor_args);
}

void
linked_list_shrink(linked_list_t* list, linked_list_size_t new_size)
{
    linked_list_accessor_t accessor       = linked_list_get_accessor_to_before(list, new_size);
    linked_list_node_t*    node_to_delete = linked_list_accessor_get_next(accessor);
    linked_list_accessor_set_next(accessor, nullptr);
    while (node_to_delete) {
        linked_list_node_t* next = linked_list_node_get_next(node_to_delete);
        linked_list_node_destroy(node_to_delete, list->allocator);
        node_to_delete = next;
        --list->size;
    }
}

void
linked_list_clear(linked_list_t* list)
{
    linked_list_shrink(list, 0);
}

void
linked_list_destroy(linked_list_t* list)
{
    linked_list_clear(list);
    linked_list_allocator_free(list->allocator, list);
}

void
linked_list_foreach(linked_list_t* list, linked_list_apply_fn_t fn, void* fn_args)
{
    for (linked_list_node_t* node = list->first; node; node = linked_list_node_get_next(node)) {
        fn(linked_list_node_get_content(node), fn_args);
    }
}

void*
linked_list_at(linked_list_t* list, linked_list_size_t position)
{
    return linked_list_node_get_content(linked_list_get_node_at(list, position));
}

linked_list_iterator_t*
linked_list_begin(linked_list_t* list)
{
    return linked_list_iterator_create(linked_list_get_node_at(list, 0), list->allocator);
}

void
linked_list_append_n(linked_list_t* list, void* constructor_args_array[],
                     linked_list_size_t elements)
{
    linked_list_accessor_t accessor =
        linked_list_get_accessor_to_before(list, linked_list_size(list));
    for (linked_list_size_t i = 0; i < elements; ++i) {
        linked_list_node_t* new_node = linked_list_node_create(
            list->allocator,
            linked_list_allocator_constructor(list->allocator, constructor_args_array[i]));
        linked_list_accessor_set_next(accessor, new_node);
        linked_list_accessor_advance(&accessor);
        ++list->size;
    }
}

void
linked_list_filter(linked_list_t* list, linked_list_filter_fn_t filter_fn, void* filter_fn_arg)
{
    linked_list_node_t *last_valid_node = nullptr, *next = nullptr;
    for (linked_list_node_t* node = list->first; node; node = next) {
        next = linked_list_node_get_next(node);
        linked_list_node_set_next(node, nullptr);
        if (filter_fn(linked_list_node_get_content(node), filter_fn_arg)) {
            if (last_valid_node) {
                linked_list_node_set_next(last_valid_node, node);
            } else {
                list->first = node;
            }
            last_valid_node = node;
        } else {
            linked_list_node_destroy(node, list->allocator);
            --list->size;
        }
    }
    list->first = last_valid_node ? list->first : nullptr;
}

bool
linked_list_equals(linked_list_t* lhs, linked_list_t* rhs, linked_list_equals_fn_t fn)
{
    if (lhs == rhs) {
        return true;
    }
    if (!lhs || !rhs) {
        return lhs == rhs;
    }
    if (lhs->size != rhs->size) {
        return false;
    }
    linked_list_node_t *node_lhs = lhs->first, *node_rhs = rhs->first;
    bool                equals = true;
    while (equals && node_lhs && node_rhs) {
        equals = fn(linked_list_node_get_content(node_lhs), linked_list_node_get_content(node_rhs));
        node_lhs = linked_list_node_get_next(node_lhs);
        node_rhs = linked_list_node_get_next(node_rhs);
    }
    return equals;
}
