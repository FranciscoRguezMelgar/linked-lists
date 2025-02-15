#include "framework.h"
#include <linked_list.h>
#include <linked_list_allocator.h>
#include <linked_list_iterator.h>
#include <time.h>

static void
benchmark_test()
{
    linked_list_t* ll = linked_list_create(linked_list_basic_allocator_double);

    enum : int { LIST_SIZE = 1 << 16 };
    struct timespec start = {}, end = {};
    double          start_d = .0, end_d = .0, duration;
    double          vector[LIST_SIZE];
    double*         vector_ptr[LIST_SIZE];

    for (int i = 0; i < LIST_SIZE; ++i) {
        vector[i]     = (double)i;
        vector_ptr[i] = vector + i;
    }

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < LIST_SIZE; ++i) {
        linked_list_append(ll, &vector[i]);
    }
    clock_gettime(CLOCK_REALTIME, &end);

    start_d                         = timespec_to_double(&start);
    end_d                           = timespec_to_double(&end);
    duration                        = end_d - start_d;
    const double time_for_appending = 9.366554;

    et_assert(compare_double_with_confidence(duration, time_for_appending, 0.001));
    printf("It took %lf seconds to append %d doubles one at a time.\n", duration, LIST_SIZE);
    linked_list_clear(ll);

    clock_gettime(CLOCK_REALTIME, &start);
    linked_list_append_n(ll, (void**)vector_ptr, LIST_SIZE);
    clock_gettime(CLOCK_REALTIME, &end);

    start_d                           = timespec_to_double(&start);
    end_d                             = timespec_to_double(&end);
    duration                          = end_d - start_d;
    const double time_for_appending_n = 0.002356;

    et_assert(compare_double_with_confidence(duration, time_for_appending_n, 0.00001));
    printf("It took %lf seconds to append %d doubles all at once.\n", duration, LIST_SIZE);

    et_assert_eq_int(linked_list_size(ll), LIST_SIZE);

    linked_list_iterator_t* it;
    int                     counter = 0;
    clock_gettime(CLOCK_REALTIME, &start);
    for (it = linked_list_begin(ll); !linked_list_iterator_is_end(it);
         linked_list_iterator_advance(it)) {
        const double value = *(double*)linked_list_iterator_get(it);
        et_assert_eq_double(value, counter++);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    et_assert_eq_int(counter, LIST_SIZE);
    linked_list_iterator_destroy(it);
    start_d                        = timespec_to_double(&start);
    end_d                          = timespec_to_double(&end);
    duration                       = end_d - start_d;
    const double time_for_checking = 0.000722;
    et_assert(compare_double_with_confidence(duration, time_for_checking, 0.00001));
    printf("It took %lf seconds to check a %d elements vector.\n", duration, LIST_SIZE);
    linked_list_destroy(ll);
}

int
main()
{
    test_t tests[] = {TEST_ELEMENT(benchmark_test)};
    for (int i = 0; i < ARRAY_SIZE(tests); ++i) {
        tests[i].test();
    }
}
