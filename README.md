# for-each-macro

C preprocessor hack for "for_each" __VA_ARGS__ expension

## What ?

This repo is a single-file header-only (no sh*t) preprocessor va_args expansion implementation.

This enables the use of a FOR_EACH macro that will apply the first argument to all the other ones.

Please see the [How ?](#how-) tab for more details on the usage.

## Why ?

I needed this type of stuff for a project ([ld-spy](https://github.com/Tech0ne/ld-spy/)), and decided to search the entire internet for ideas.

A lot of the time, I ended up on some tricks to make "macro overloading", where the macro would be changed depending on the number of arguments.

While this allows for some cool tricks, this is limited to the ammount of time you want to copy a line.

And this can often become reeeeally big.

That implementation does NOT limit you to a number of arguments.

## How ?

To use this tool, simply copy the [for-each-macro.h](https://github.com/Tech0ne/for-each-macro/blob/main/for-each-macro.h) file into your headers, and start using it.

Here is a sample example:

```c
#include "for-each-macro.h"
#include <stdio.h>

#define PRINT_THEIR_ADDRESS(x) printf("%p\n", &x);

int main()
{
    int a, b, c, d, e, f, g, h, i, j;
    FOR_EACH(PRINT_THEIR_ADDRESS, a, b, c, d, e, f, g, h, i, j); // the semicolon is not necessary here
}
```

You could also use it to automate the collection of cool infos about some variables.

This comes really usefull when used on debug-oriented projects:

```c
#include "for-each-macro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VARIABLE_TYPE_INT,
    VARIABLE_TYPE_STRING,
    VARIABLE_TYPE_CHAR,
    VARIABLE_TYPE_UNDEFINED,
} variable_type;

typedef struct {
    char* name;
    variable_type type;
    void* value;
} variable;

variable* get_variable_from_argument(const char* name, variable_type type, void* value)
{
    variable* object = (variable*)malloc(sizeof(variable));
    object->name = strdup(name);
    object->type = type;
    object->value = value;

    return object;
}

void debug_print_and_free_variable(variable* object)
{
    printf("Variable %s of type ", object->name);

    switch (object->type) {
        case VARIABLE_TYPE_INT:
            printf("INT: %i\n", *(int*)object->value);
            break;

        case VARIABLE_TYPE_STRING:
            printf("STRING: %s\n", *(char**)object->value);
            break;

        case VARIABLE_TYPE_CHAR:
            printf("CHAR: %c\n", *(char*)object->value);
            break;

        default:
            printf("UNDEFINED: %p\n", object->value);
            break;
    }

    free(object->name);
    free(object);
}

#define TYPEOF(x) _Generic(x,           \
    int: VARIABLE_TYPE_INT,             \
    char*: VARIABLE_TYPE_STRING,        \
    char: VARIABLE_TYPE_CHAR,           \
    default: VARIABLE_TYPE_UNDEFINED)

#define SETUP_VARIABLE(x) debug_print_and_free_variable(get_variable_from_argument(#x, TYPEOF(x), &x));

void random_function(int i, char* s, char c, long l)
{
    FOR_EACH(SETUP_VARIABLE, i, s, c, l);
}

int main()
{
    random_function(12, "hello", 'k', 14);
}
```

![Output of code](images/cool_output.png Output of the code)

## Notes

This tool was made more for the PoC than to be explicitly usefull.

For that reason, and others (including "I don't know how to fix that 'problem'" and "I'm lazy"), if you misspell something, the compilation process will give a reeeeally long output.

![Misspell error](images/misspell_error.png This is caused by a misspell)

Be carefull of that when using this implementation.

## Thanks

I won't be able to note all the websites / StackOverflow questions I viewed, sry :|

## Final words

Enjoy it guys :D

Please paste the file as-is, as implied in the LICENSE file.

Thanks <3
