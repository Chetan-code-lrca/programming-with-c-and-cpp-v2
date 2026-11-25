/*
 Author: Internshala
 Module: Getting Started with Programming in C
 Topic: Miscellaneous Concepts

 Demonstrates clearing the remainder of an overlong input line safely.
*/

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void clear_input_buffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Discard characters left on the current input line. */
    }
}

static int read_line(char *buffer, size_t capacity)
{
    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    size_t length = strcspn(buffer, "\n");
    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[length - 1] = '\0';
        }
        return 1;
    }

    int ch = getchar();
    if (ch == '\n' || ch == EOF) {
        return 1;
    }

    clear_input_buffer();
    return 0;
}

static int read_integer(int *value)
{
    char line[64];
    char *end;
    long parsed;

    if (!read_line(line, sizeof line)) {
        return 0;
    }

    errno = 0;
    parsed = strtol(line, &end, 10);
    if (end == line || errno == ERANGE || parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }
    if (*end != '\0') {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int read_gender(char *gender)
{
    char line[16];
    char *cursor;

    if (!read_line(line, sizeof line)) {
        return 0;
    }

    cursor = line;
    while (isspace((unsigned char)*cursor)) {
        cursor++;
    }
    if (*cursor != 'M' && *cursor != 'F') {
        return 0;
    }

    *gender = *cursor++;
    while (isspace((unsigned char)*cursor)) {
        cursor++;
    }
    return *cursor == '\0';
}

int main(void)
{
    char name[40];
    char gender;
    int age;
    int id;

    printf("Enter name: ");
    if (!read_line(name, sizeof name) || name[0] == '\0') {
        fprintf(stderr, "Name must contain between 1 and 39 characters.\n");
        return 1;
    }
    printf("%s", name);

    printf("\nEnter id: ");
    if (!read_integer(&id)) {
        fprintf(stderr, "Invalid id. Enter an in-range whole number.\n");
        return 1;
    }
    printf("%d", id);

    printf("\nEnter gender: 'M' or 'F': ");
    if (!read_gender(&gender)) {
        fprintf(stderr, "Invalid gender. Enter M or F.\n");
        return 1;
    }
    printf("%c", gender);

    printf("\nEnter age: ");
    if (!read_integer(&age) || age < 0) {
        fprintf(stderr, "Invalid age. Enter a non-negative in-range whole number.\n");
        return 1;
    }
    printf("%d\n", age);

    return 0;
}
