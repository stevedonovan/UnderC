/* Whole-object copies.
 *
 * Assigning one plain struct to another, and returning a plain struct by
 * value, both compile to the COPY opcode.  COPY takes its destination from
 * the top of the stack, so the operands have to be emitted in that order;
 * with them reversed the copy ran backwards and the destination kept its
 * original contents.
 */
#include <stdio.h>

struct Pair {
    int a;
    int b;
};

struct Counted {
    int a;
    int b;
    Counted() : a(0), b(0) {}
};

static Pair make_pair(int x, int y)
{
    Pair value;
    value.a = x;
    value.b = y;
    return value;
}

static Counted make_counted(int x, int y)
{
    Counted value;
    value.a = x;
    value.b = y;
    return value;
}

static Pair global_pair;

int main()
{
    Pair source;
    Pair target;
    Pair returned;
    Counted counted;
    int used;

    source.a = 5;
    source.b = 6;
    target = source;
    if (target.a != 5 || target.b != 6) return 1;

    /* the assignment must not disturb its right-hand side */
    if (source.a != 5 || source.b != 6) return 2;

    returned = make_pair(11,13);
    if (returned.a != 11 || returned.b != 13) return 3;

    global_pair = make_pair(21,23);
    if (global_pair.a != 21 || global_pair.b != 23) return 4;

    counted = make_counted(31,33);
    if (counted.a != 31 || counted.b != 33) return 5;

    /* an assignment used as a value yields the assigned object */
    used = (target = make_pair(41,43)).a;
    if (used != 41 || target.a != 41 || target.b != 43) return 6;

    printf("object-value-semantics-ok\n");
    return 0;
}
