#ifndef TEST_H
#define TEST_H

#define ANSI_COLOUR_RED   "\x1b[31m"
#define ANSI_COLOUR_GREEN "\x1b[32m"
#define ANSI_COLOUR_RESET "\x1b[0m"

#define DEFINE_TEST(exp) { .expected = exp, .result = NULL },
#define RELEASE(ptr) free(ptr); ptr = NULL;

typedef struct {
    const char *expected;
    const char *result;
} unit_test_t;

#endif //TEST_H

