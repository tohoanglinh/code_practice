#include <stdio.h>

int main(void)
{
    printf("hello\n");
    
    int i;
    i = 5;
    printf("i = %d\n", i);
    
    int a,b;
    a = 2;
//    b = ++a + (2*a);
    b = a++ + (2*a);
    printf("b=%d",b);

    return 0;
}
