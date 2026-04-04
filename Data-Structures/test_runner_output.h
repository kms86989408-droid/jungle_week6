#ifndef DATA_STRUCTURES_TEST_RUNNER_OUTPUT_H
#define DATA_STRUCTURES_TEST_RUNNER_OUTPUT_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef void (*capture_output_fn)(void *);

static int capture_output(capture_output_fn fn, void *ctx, char *buffer, size_t size)
{
    FILE *temp;
    int saved_stdout;
    int temp_fd;
    size_t bytes_read;

    if (size == 0) {
        return -1;
    }

    temp = tmpfile();
    if (temp == NULL) {
        buffer[0] = '\0';
        return -1;
    }

    fflush(stdout);
    saved_stdout = dup(STDOUT_FILENO);
    temp_fd = fileno(temp);
    dup2(temp_fd, STDOUT_FILENO);

    fn(ctx);

    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    rewind(temp);
    bytes_read = fread(buffer, 1, size - 1, temp);
    buffer[bytes_read] = '\0';
    fclose(temp);
    return 0;
}

static int expect_string(const char *label, const char *actual, const char *expected)
{
    if (strcmp(actual, expected) != 0) {
        printf("[FAIL] %s\n", label);
        printf("  expected: \"%s\"\n", expected);
        printf("  actual:   \"%s\"\n", actual);
        return 1;
    }

    printf("[PASS] %s\n", label);
    return 0;
}

static int expect_int_value(const char *label, int actual, int expected)
{
    if (actual != expected) {
        printf("[FAIL] %s: expected %d, got %d\n", label, expected, actual);
        return 1;
    }

    printf("[PASS] %s\n", label);
    return 0;
}

#endif
