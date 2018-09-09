#include "header_a6.h"

void allocate_pointer(int **p, int n)
{
    *p = (int*)malloc(n*sizeof(int));
}
