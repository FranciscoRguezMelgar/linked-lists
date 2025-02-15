#include "framework.h"
#include "linked_list.h"

double
timespec_to_double(const struct timespec* tm)
{
    return tm->tv_sec + tm->tv_nsec / 1'000'000'000.;
}

void
et_assert_eq_int(int a, int b)
{
    if (a == b) {
        return;
    }
    printf("Expected that a (%d) is equal to b (%d) but not true.\n", a, b);
    abort();
}

void
et_assert_eq_double(double a, double b)
{
    if (a == b) {
        return;
    }
    printf("Expected that a (%lf) is equal to b (%lf) but not true.\n", a, b);
    abort();
}

void
et_assert(bool condition) {
    if (condition){
        return;
    }
    printf("Expected that a condition was true but it's false.\n");
    abort();
}

void
printf_pass()
{
    printf("\033[92;1mPASS\033[0m\n");
}

typedef struct print_int_args {
    char*  buffer;
    size_t pos;
    char*  separator;
} print_int_args_t;

void
print_int(void* int_ptr, void* args_ptr)
{
    print_int_args_t* args = args_ptr;
    args->pos += sprintf(args->buffer + args->pos, "%d%s", *(int*)int_ptr, args->separator);
}

void
print_linked_list_int(linked_list_t* ll)
{
    enum : int { BUFFER_SIZE = 65536 };

    char             buffer[BUFFER_SIZE] = {"{"};
    print_int_args_t args                = {
                       .buffer    = buffer,
                       .pos       = 1,
                       .separator = ", ",
    };
    linked_list_foreach(ll, print_int, &args);
    et_assert(args.pos < BUFFER_SIZE);
    buffer[args.pos - 2] = '}';
    buffer[args.pos - 1] = '\0';
    printf("%s\n", args.buffer);
}

#define ABS(num) ((num) < 0 ? (num) : -(num))

bool
compare_double_with_confidence(double a, double b, double confidence)
{
    return ABS(a - b) < confidence;
}
