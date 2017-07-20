/*
 * File   : test_standard_functions.c
 * Author : To Hoang Linh
 * Date   : 2017-07-10
 * ForWhat: to create a generic template for C source coding.
 */

/**
 * INCLUDES
 */
/* printf, scanf */
#include <stdio.h>
/* malloc, free */
#include <stdlib.h>
/* strlen, strcat, strcpy, strcmp, memset, memcpy, strtol, strtoul*/
#include <string.h>
/* C99: uint8_t, uint16_t, uint32_t */
#include <stdint.h>
/* C99: bool, true, false */
#include <stdbool.h>

/**
 * DEFINES & MACROS
 */
#define LED_ON 1

/**
 * NOTES: string declaration
char* str1="string";
>> This creates a pointer to a literal string that will be located on either .data or .text segments and is accessible at all times.
>> Whenever you do something like that, be sure to declare it const, because if you try to modify it, nasty things might happen.

char str2[7]="string";
>> This creates a local buffer on the stack with a copy of the literal string. It becomes unavailable once the function returns.
>> That explains the weird result you're getting.

char* str3=(char)malloc(sizeof(char)*7);
>> This creates a buffer on the heap (uninitialized) that will be available until you free it.
>> And free it you must, or you will get a memory leak.
 */

int main(void)
{
    /* stdio */
//    int i;
//    scanf("%d", &i);
//    printf("Test i = %d\n", i);

    /* stdlib */
//    int *ptr;
//    ptr = malloc(10*sizeof(int));
//    if (NULL == ptr)
//    {
//        printf("ptr == NULL, malloc is failed\n");
//        return (-1);
//    }
//    else
//    {
//        printf("ptr != NULL, malloc is succeeded\n");
//    }
//    free(ptr);

    /* stdbool */
//    bool test;
//    test = false;
//    printf("%d", test);

    /* string */
    char name[] = "To Hoang Linh";
    printf("%d", strlen(name));
    return 0;
}
