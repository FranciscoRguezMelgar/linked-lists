#if !defined(_FRM_LINKED_LIST_TEST_FRAMEWORK_H_)
#define _FRM_LINKED_LIST_TEST_FRAMEWORK_H_

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(array) ((int64_t)(sizeof((array)) / sizeof((array)[0])))

typedef struct linked_list linked_list_t;
struct timespec;

typedef struct test {
    void (*test)(void);
    const char* test_name;
} test_t;

#define TEST_ELEMENT(foo)                                                                          \
    {                                                                                              \
        .test = foo, .test_name = #foo                                                             \
    }

double
timespec_to_double(const struct timespec* tm);

void
et_assert_eq_int(int a, int b);

void
et_assert_eq_double(double a, double b);

void
et_assert(bool condition);

void
print_int(void* int_ptr, void* args_ptr);

void
print_linked_list_int(linked_list_t* ll);

void
printf_pass();

bool
compare_double_with_confidence(double a, double b, double confidence);

#endif
