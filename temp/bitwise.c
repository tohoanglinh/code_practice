#include <stdio.h>
#include <stdint.h>

int main(void)
{
    printf("bitwise\n");
    
    uint8_t n = 0b1001;
    
    printf("Before: %d\n", n);
    
    n |= 1 << 1;
    
    printf("After: %d\n", n);
    
    long a[17];
    
    printf("Size of a: %d\n", sizeof(a)/sizeof(uint8_t));
    
    uint8_t led[8] = {4, 5, 6, 7, 8, 9, 10, 11};
    
    printf("Size of led: %d\n", sizeof(led)/sizeof(led[0]));
    
    return 0;
}
