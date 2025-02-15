#include <limits.h>
#include <stdio.h>

#include "framework.h"
#include "linked_list.h"
#include "linked_list_allocator.h"
#include "linked_list_iterator.h"

static linked_list_t*
test_create_linked_list_element_equals_index(linked_list_size_t initial_list_size)
{
    linked_list_size_t expected_list_size = 0;
    linked_list_t*     ll                 = linked_list_create(linked_list_basic_allocator_int);

    et_assert_eq_int(linked_list_size(ll), expected_list_size);
    for (linked_list_size_t i = 0; i < initial_list_size; ++i) {
        linked_list_append(ll, &i);
        ++expected_list_size;
        et_assert_eq_int(linked_list_size(ll), expected_list_size);
    }
    return ll;
}

static void
test_int_list()
{
    const linked_list_size_t initial_list_size  = 10;
    linked_list_size_t       expected_list_size = initial_list_size;
    linked_list_t*           ll = test_create_linked_list_element_equals_index(initial_list_size);

    for (linked_list_size_t i = 0; i < linked_list_size(ll); ++i) {
        const int value = *(int*)linked_list_at(ll, i);
        et_assert_eq_int(value, i);
    }

    linked_list_remove_at(ll, 3);
    --expected_list_size;
    et_assert_eq_int(linked_list_size(ll), expected_list_size);

    for (linked_list_size_t i = 0; i < expected_list_size; ++i) {
        const int increment = i >= 3 ? 1 : 0;
        const int value     = *(int*)linked_list_at(ll, i);
        et_assert_eq_int(value, i + increment);
    }

    linked_list_insert_at(ll, 3, (int[]){3});
    ++expected_list_size;
    et_assert_eq_int(linked_list_size(ll), expected_list_size);

    for (linked_list_size_t i = 0; i < expected_list_size; ++i) {
        const int value = *(int*)linked_list_at(ll, i);
        et_assert_eq_int(value, i);
    }

    linked_list_remove_at(ll, 0);
    --expected_list_size;
    et_assert_eq_int(linked_list_size(ll), expected_list_size);

    for (linked_list_size_t i = 0; i < expected_list_size; ++i) {
        const int value = *(int*)linked_list_at(ll, i);
        et_assert_eq_int(value, i + 1);
    }

    linked_list_insert_at(ll, 0, (int[]){0});
    ++expected_list_size;
    et_assert_eq_int(linked_list_size(ll), expected_list_size);

    for (linked_list_size_t i = 0; i < expected_list_size; ++i) {
        const int value = *(int*)linked_list_at(ll, i);
        et_assert_eq_int(value, i);
    }

    linked_list_shrink(ll, 5);
    expected_list_size = 5;
    et_assert_eq_int(linked_list_size(ll), expected_list_size);

    for (linked_list_size_t i = 0; i < expected_list_size; ++i) {
        const int value = *(int*)linked_list_at(ll, i);
        et_assert_eq_int(value, i);
    }

    for (linked_list_size_t i = 0; i < linked_list_size(ll); ++i) {
        ++*(int*)linked_list_at(ll, i);
    }

    for (linked_list_size_t i = 0; i < expected_list_size; ++i) {
        const int value = *(int*)linked_list_at(ll, i);
        et_assert_eq_int(value, i + 1);
    }

    linked_list_clear(ll);
    et_assert_eq_int(0, linked_list_size(ll));
    linked_list_destroy(ll);
}

static void
test_int_iterator()
{
    const linked_list_size_t initial_list_size = 10;
    linked_list_t*           ll = test_create_linked_list_element_equals_index(initial_list_size);
    int                      counter = 0;

    linked_list_iterator_t* it = nullptr;
    for (it = linked_list_begin(ll); !linked_list_iterator_is_end(it);
         linked_list_iterator_advance(it)) {
        const int value = *(int*)linked_list_iterator_get(it);
        et_assert_eq_int(value, counter);
        counter++;
    }
    linked_list_iterator_destroy(it);
    et_assert_eq_int(counter, linked_list_size(ll));
    linked_list_destroy(ll);
}

static bool
int_module(const void* a, void* arg)
{
    return *(const int*)a % *(int*)arg == 0;
}

static bool
int_odd(const void* a, void* arg)
{
    (void)arg;
    return *(const int*)a % 2;
}

static bool
int_gt(const void* a, void* arg)
{
    return *(const int*)a > *(const int*)arg;
}

static bool
return_true(const void* a, void* arg)
{
    (void)a;
    (void)arg;
    return true;
}

static void
test_filter_list_none()
{
    const linked_list_size_t initial_list_size = 10;
    linked_list_t*           ll = test_create_linked_list_element_equals_index(initial_list_size);

    linked_list_filter(ll, int_gt, (int[]){10});
    et_assert_eq_int(linked_list_size(ll), 0);
    linked_list_destroy(ll);
}

static void
test_filter_list_evens()
{
    const linked_list_size_t initial_list_size = 10;
    linked_list_t*           ll = test_create_linked_list_element_equals_index(initial_list_size);

    linked_list_filter(ll, int_module, (int[]){2});
    et_assert_eq_int(linked_list_size(ll), 5);
    linked_list_iterator_t* it;
    for (it = linked_list_begin(ll); !linked_list_iterator_is_end(it);
         linked_list_iterator_advance(it)) {
        const int value = *(int*)linked_list_iterator_get(it);
        et_assert(value % 2 == 0);
    }
    linked_list_iterator_destroy(it);
    linked_list_destroy(ll);
}

static void
test_filter_list_odds()
{
    const linked_list_size_t initial_list_size = 10;
    linked_list_t*           ll = test_create_linked_list_element_equals_index(initial_list_size);

    linked_list_filter(ll, int_odd, nullptr);
    et_assert_eq_int(linked_list_size(ll), 5);
    linked_list_iterator_t* it;
    for (it = linked_list_begin(ll); !linked_list_iterator_is_end(it);
         linked_list_iterator_advance(it)) {
        const int value = *(int*)linked_list_iterator_get(it);
        et_assert(!!(value % 2));
    }
    linked_list_iterator_destroy(it);
    linked_list_destroy(ll);
}

static void
test_filter_list_all()
{
    const linked_list_size_t initial_list_size = 10;
    linked_list_t*           ll = test_create_linked_list_element_equals_index(initial_list_size);

    linked_list_filter(ll, return_true, nullptr);
    et_assert_eq_int(linked_list_size(ll), 10);
    int                     counter = 0;
    linked_list_iterator_t* it;
    for (it = linked_list_begin(ll); !linked_list_iterator_is_end(it);
         linked_list_iterator_advance(it)) {
        const int value = *(int*)linked_list_iterator_get(it);
        et_assert_eq_int(counter, value);
        counter++;
    }
    linked_list_iterator_destroy(it);
    linked_list_destroy(ll);
}

static void
compare_with_counter(void* elem, void* args)
{
    const int element     = *(int*)elem;
    int*      counter_ptr = args;
    et_assert_eq_int(element, (*counter_ptr)++);
}

static void
test_append_n()
{
    linked_list_t* ll = linked_list_create(linked_list_basic_allocator_int);

    enum : linked_list_size_t { LIST_SIZE = 10 };

    int  elements[LIST_SIZE]     = {};
    int* elements_ptr[LIST_SIZE] = {};
    for (linked_list_size_t i = 0; i < LIST_SIZE; ++i) {
        elements[i]     = i;
        elements_ptr[i] = elements + i;
    }

    linked_list_append_n(ll, (void**)elements_ptr, LIST_SIZE);
    et_assert_eq_int(LIST_SIZE, linked_list_size(ll));
    int counter = 0;
    linked_list_foreach(ll, compare_with_counter, &counter);
    et_assert_eq_int(counter, LIST_SIZE);
    linked_list_destroy(ll);
}

static bool
int_equals(const void* lhs, const void* rhs)
{
    return *(const int*)lhs == *(const int*)rhs;
}

void
test_equals_1()
{
    linked_list_t* ll = linked_list_create(linked_list_basic_allocator_int);
    linked_list_t* lk = nullptr;
    et_assert(!linked_list_equals(ll, lk, int_equals));
    lk = ll;
    et_assert(linked_list_equals(ll, lk, int_equals));
    lk = linked_list_create(linked_list_basic_allocator_int);
    et_assert(linked_list_equals(ll, lk, int_equals));
    linked_list_append(ll, (int[]){0});
    et_assert(!linked_list_equals(ll, lk, int_equals));
    linked_list_append(lk, (int[]){0});
    et_assert(linked_list_equals(ll, lk, int_equals));
    linked_list_remove_at(ll, 0);
    linked_list_append(ll, (int[]){1});
    et_assert(!linked_list_equals(ll, lk, int_equals));
    linked_list_destroy(ll);
    linked_list_destroy(lk);
}

void
test_equals_2()
{
    linked_list_t* ll         = linked_list_create(linked_list_basic_allocator_int);
    linked_list_t* lk         = linked_list_create(linked_list_basic_allocator_int);
    int            elements[] = {1, 2, 3, 4, 5, 6};
    int*           elements_ptr[ARRAY_SIZE(elements)];
    for (int i = 0; i < ARRAY_SIZE(elements); ++i) {
        elements_ptr[i] = &elements[i];
    }
    linked_list_append_n(ll, (void**)elements_ptr, ARRAY_SIZE(elements));
    linked_list_append_n(lk, (void**)elements_ptr, ARRAY_SIZE(elements));
    et_assert(linked_list_equals(ll, lk, int_equals));
    linked_list_shrink(lk, linked_list_size(lk) - 1);
    linked_list_append(lk, (int[]){1});
    et_assert(!linked_list_equals(ll, lk, int_equals));
    linked_list_shrink(lk, linked_list_size(lk) - 1);
    linked_list_append(lk, (int[]){6});
    linked_list_remove_at(ll, 0);
    linked_list_insert_at(ll, 0, (int[]){6});
    et_assert(!linked_list_equals(ll, lk, int_equals));
    linked_list_remove_at(ll, 0);
    linked_list_insert_at(ll, 0, (int[]){1});
    linked_list_remove_at(ll, 2);
    linked_list_insert_at(ll, 0, (int[]){7});
    et_assert(!linked_list_equals(ll, lk, int_equals));
    linked_list_destroy(ll);
    linked_list_destroy(lk);

}

int
main()
{
    test_t tests[] = {
        TEST_ELEMENT(test_int_list),          TEST_ELEMENT(test_int_iterator),
        TEST_ELEMENT(test_filter_list_none),  TEST_ELEMENT(test_filter_list_all),
        TEST_ELEMENT(test_filter_list_evens), TEST_ELEMENT(test_filter_list_odds),
        TEST_ELEMENT(test_append_n),          TEST_ELEMENT(test_equals_1),
        TEST_ELEMENT(test_equals_2),
    };
    for (int i = 0; i < ARRAY_SIZE(tests); ++i) {
        printf("%-30s", tests[i].test_name);
        fflush(NULL);
        tests[i].test();
        printf_pass();
    }
}
