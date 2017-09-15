#include <stdio.h>
#include <malloc.h>
#include "header_a6.h"

/* function pointer */
//int (*func)(void);

/* return is a pointer */
//int *func(void);

int (*functionPtr)(int,int);

int addInt(int n, int m) {
    return n+m;
}

int main()
{
    printf("size of char = %d bytes\n", sizeof(char));
    printf("size of short = %d bytes\n", sizeof(short));
    printf("size of int = %d bytes\n", sizeof(int));
    printf("size of long = %d bytes\n", sizeof(long));
    printf("size of double = %d bytes\n", sizeof(double));
    
    functionPtr = &addInt;
    int sum = (*functionPtr)(1,2);
    printf("sum = %d\n", sum);
    
    printf("Pointer learning...\n");
    
    /* declare a pointer p, data type is integer */
    /* pointer with data type integer, that means p points to an integer memory space (2 bytes)*/
    int *p1;
    int **p2;
    int a = 4;
    
    char name[]="Bill";
    char *p_name;
    p_name = name;
    /* name is address constant, save the address where B - i - l - l starts */
    printf("name = %X\n",name);
    int i=0;
    while (*(p_name+i)!='\0'){
        printf("name[%d] = %c\n",i,*(p_name+i));    
        i++;
    }
    
    /* save address of a into p 
     * set the pointer point to integer a 
     * the value of the variable p is assigned the address
     * of the variable a */
     
    /* *p: give me the object value at the following address (p) 
     * &a: tell me the address where the following object starts
     */
    p1 = &a;
    p2 = &p1;
    
    printf("p2 = %d\n", **p2);
    
    /* value of p1 pointed to a */
    *p1 = a;

    /* access value of a --> using *p1 */
    printf("Value of p1 is p1 = %d\n", *p1);
    
    printf("Before malloc: Address of p1 is &p1 = %X\n", &p1);
    
    allocate_pointer(&p1, 2);
    
    /* access address of p1 --> using &p1 */
    printf("After malloc:  Address of p1 is &p1 = %X", &p1);
    
    return(0);
}
