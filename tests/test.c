#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../lexer.h"

static char *read_file(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (!file)
    {
        fprintf(stderr, "Unable to open file '%s'\n", path);
        exit(74); /* IO error */
    }

    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    rewind(file);

    char *buffer = malloc(fsize + 1);
    size_t bytes = fread(buffer, sizeof(char), fsize, file);

    if (bytes < fsize)
    {
        fprintf(stderr, "Unable to read file '%s'\n", path);
        exit(74);
    }

    buffer[bytes] = '\0';
    fclose(file);

    return buffer;
}

static void print_error(const char *expected, const char *result)
{
    printf("Expected:\t%s\n", expected);
    printf("Actual result:\t%s\n", result);
}

static void print_test_result(const char *name, int result)
{
    printf("[ %s " ANSI_COLOUR_RESET "] %s\n" ANSI_COLOUR_RESET, (result ? ANSI_COLOUR_GREEN "Pass" : ANSI_COLOUR_RED "Fail"), name);
}

static void print_test_name(const char *test_name)
{
    printf("Starting test [%s]\n", test_name);
}

static int test_lexer(void)
{
    const char *test_name = "Lexer keywords";

    /* Test keywords */
    print_test_name(test_name);

    char *input = read_file("tests/tokens.ptn");


    if (!input)
    {
        fprintf(stderr, ANSI_COLOUR_RED "Error unable to read input for test: [%s]\n" ANSI_COLOUR_RESET, test_name);
        print_test_result(test_name, 0);
    }

    lexer_t *l = lexer_init(input);


    unit_test_t tests[] = {
        DEFINE_TEST("IDENT")
        DEFINE_TEST("ASSIGN")
        DEFINE_TEST("INT")
        DEFINE_TEST("FLOAT")
        DEFINE_TEST("STRING")

        DEFINE_TEST("PLUS")
        DEFINE_TEST("MINUS")
        DEFINE_TEST("DIVIDE")
        DEFINE_TEST("MULTIPLY")
        DEFINE_TEST("MODULO")

        DEFINE_TEST("BANG")
        DEFINE_TEST("AND")
        DEFINE_TEST("OR")
        DEFINE_TEST("INCREMENT")
        DEFINE_TEST("DECREMENT")

        DEFINE_TEST("LT")
        DEFINE_TEST("GT")
        DEFINE_TEST("NE")
        DEFINE_TEST("EQ")
        DEFINE_TEST("LT_EQ")
        DEFINE_TEST("GT_EQ")

        DEFINE_TEST("COMMA")
        DEFINE_TEST("SEMICOLON")

        DEFINE_TEST("LPAREN")
        DEFINE_TEST("RPAREN")
        DEFINE_TEST("LBRACE")
        DEFINE_TEST("RBRACE")
        DEFINE_TEST("LBRACKET")
        DEFINE_TEST("RBRACKET")

        DEFINE_TEST("VAR")
        DEFINE_TEST("IF")
        DEFINE_TEST("ELSE")
        DEFINE_TEST("LOOP")
        DEFINE_TEST("FUNC")
        DEFINE_TEST("RETURN")
        DEFINE_TEST("BREAK")
        DEFINE_TEST("CONTINUE")
        DEFINE_TEST("TRUE")
        DEFINE_TEST("FALSE")
    };

    token_t tok;
    unsigned i = 0;
    unsigned result = 0;
    unsigned has_errored = 0;

    while ( (tok = lexer_next(l)).type != TOK_EOF )
    {
        tests[i].result = token_get_type_literal(tok.type);

        if (strcmp(tests[i].expected, tests[i].result) != 0)
        {
            result = 0;
            has_errored = 1;
            print_test_result(test_name, result);
            print_error(tests[i].expected, tests[i].result);
        }


        i++;
    }

    if (!has_errored)
        print_test_result(test_name, 1);

    lexer_free(l);

    free(input);
    input = NULL;

    return has_errored;
}

int main(int argc, char **argv)
{
    test_lexer();

    return 0;
}

