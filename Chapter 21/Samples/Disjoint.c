#include "Disjoint.h"

void make_set(disjoint* const x)
{
    x->p = x;
    x->rank = 0;
}

void union_set(disjoint* const x, disjoint* const y)
{
    link(find_set(x), find_set(y));
}

static void link(disjoint* const x, disjoint* const y)
{
    if (x->rank > y->rank)
        y->p = x;
    else
    {
        x->p = y;
        if (x->rank == y->rank)
            y->rank += 1;
    }
}

disjoint* find_set(disjoint* const x)
{
    if (x != x->p)
        x->p = find_set(x->p);
    return x->p;
}