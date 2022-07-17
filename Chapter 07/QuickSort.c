#define swap(a, b)  \
typeof((a)) c;      \
c = (a);            \
(a) = (b);          \
(b) = (c)           \


int partition(int* A, int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j)
    {
        if (A[j] <= x)
        {
            i += 1;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void quicksort(int* A, int p, int r)
{
    if (p < r)
    {
        int q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

void do_quiksort(int* A, int size)
{
    quicksort(A, 0, size - 1);
}

extern void test_assending(void (*)(int*, int));

int main(void)
{
    test_assending(do_quiksort);
    return 0;
}