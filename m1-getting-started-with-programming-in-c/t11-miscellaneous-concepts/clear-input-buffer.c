/*
 Author: Internshala
 Module: Getting Started with Programming in C
 Topic: Miscellaneous Concepts

 Demonstrates clearing the remainder of a numeric input line safely.
*/

#include <stdio.h>
#include <string.h>

static int read_name(char *name, size_t capacity)
{
    if (fgets(name, (int)capacity, stdin) == NULL) {
        return 0;
    }

    size_t length = strcspn(name, "\n");
    if (name[length] == '\n') {
        name[length] = '\0';
        if (length > 0 && name[length - 1] == '\r') {
            name[length - 1] = '\0';
        }
    } else {
        int ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Discard the rest of an overlong name. */
            }
            return 0;
        }
    }

    return name[0] != '\0';
}

static int clear_input_buffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Discard characters left on the current input line. */
    }

    return ch != EOF;
}

int main(void)
{
    char name[40];
    char gender;
    int age;
    int id;

    printf("Enter name: ");
    if (!read_name(name, sizeof name)) {
        fprintf(stderr, "Name must contain between 1 and 39 characters.\n");
        return 1;
    }
    printf("%s", name);

    printf("\nEnter id: ");
    if (scanf("%d", &id) != 1) {
        fprintf(stderr, "Invalid id. Enter a whole number.\n");
        return 1;
    }
    printf("%d", id);

    /* Clear the rest of the id line before reading the next character. */
    if (!clear_input_buffer()) {
        fprintf(stderr, "Unexpected end of input after id.\n");
        return 1;
    }

    printf("\nEnter gender: 'M' or 'F': ");
    if (scanf(" %c", &gender) != 1 || (gender != 'M' && gender != 'F')) {
        fprintf(stderr, "Invalid gender. Enter M or F.\n");
        return 1;
    }
    printf("%c", gender);

    printf("\nEnter age: ");
    if (scanf("%d", &age) != 1 || age < 0) {
        fprintf(stderr, "Invalid age. Enter a non-negative whole number.\n");
        return 1;
    }
    printf("%d\n", age);

    return 0;
}
