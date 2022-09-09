#ifndef _DISJOINT_H_
#define _DISJOINT_H_

typedef struct disjoint
{
    struct disjoint* p;
    int rank;
    char value;
} disjoint;

void make_set(disjoint* const);
void union_set(disjoint* const, disjoint* const);
disjoint* find_set(disjoint* const);
static void link(disjoint* const, disjoint* const);

#endif // _DISJOINT_H_