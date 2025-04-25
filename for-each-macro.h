/*************
 *
 *     @
 *       @
 *   @ @ @
 *
 *************/
// Made by Tech0ne on https://github.com/Tech0ne/for-each-macro
// Take a look at the repo for usage

// Token pasting
#define FE_CAT(a, b) FE_CAT_I(a, b)
#define FE_CAT_I(a, b) a##b

// Stringify
#define FE_STR(x) #x

// Boolean logic
#define FE_NOT(x) FE_CAT(_FE_NOT_, x)
#define _FE_NOT_0 1
#define _FE_NOT_1 0

#define FE_BOOL(x) FE_NOT(FE_NOT(x))

#define FE_IF(c) CAT(_FE_IF_, BOOL(c))
#define _FE_IF_1(t, f) t
#define _FE_IF_0(t, f) f

// Defer + Obstruct
#define FE_EMPTY()
#define FE_DEFER(id) id FE_EMPTY()
#define FE_OBSTRUCT(...) __VA_ARGS__ FE_DEFER(FE_EMPTY)()

// Recursive expansion booster
#define FE_EVAL(...) FE_EVAL1(FE_EVAL1(FE_EVAL1(__VA_ARGS__)))
#define FE_EVAL1(...) FE_EVAL2(FE_EVAL2(__VA_ARGS__))
#define FE_EVAL2(...) FE_EVAL3(FE_EVAL3(__VA_ARGS__))
#define FE_EVAL3(...) __VA_ARGS__

// Detect if __VA_ARGS__ is empty
#define FE_FIRST(a, ...) a
#define FE_HAS_ARGS(...) FE_BOOL(FE_FIRST(__VA_ARGS__ __VA_OPT__(,) 0))

// === MAPPING ===

// Recursive macro map
#define _FE_MAP(m, x, ...) m(x) __VA_OPT__(FE_OBSTRUCT(_FE_MAP_INDIRECT)()(m, __VA_ARGS__))
#define _FE_MAP_INDIRECT() _FE_MAP

// === API ===

/*
#Usage

The action argument should be direct: The macro expand to action(x) (for each x in the va_args)

## Sample exmple

```c
#define ACTION(x) printf("%p\n", &x);
FOR_EACH(ACTION, a, b, c, d)

// This will expand to
printf("%p\n", &a);printf("%p\n", &b);printf("%p\n", &c);printf("%p\n", &d);
```

## Another example, demonstrating the use inside of an array

The goal being to retreive the address of each input

```c
#define GET_ADDRESS(x) &x,
void* addresses[] = {FOR_EACH(GET_ADDRESS, a, b, c, d) NULL};
//This will expand to
void* addresses[] = {&a,&b,&c,&d,NULL};
```
*/
#define FOR_EACH(action, ...) FE_EVAL(_FE_MAP(action, __VA_ARGS__))
