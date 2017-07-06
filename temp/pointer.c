#include <stdio.h>

/* Pointer */

int main(void)
{
    int *ptr;
    
    int a[2] = {20, 21, 22};
    
    ptr = &a;
    
    printf("Pointer point to the address at ptr = %d\n", ptr);
    
    printf("Pointer point to the value of *ptr = %d\n", *ptr);
    
    ptr++;
    
    printf("ptr++ = %d\n", ptr);
    
    printf("*ptr++ = %d\n", *ptr);
    
    return 0;
}
