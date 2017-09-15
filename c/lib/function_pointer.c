/**
 * Callback, event handlers
 * Menu, store an array of functions, call dynamically (Reduce code)
 */

#include <stdio.h>

typedef void(*pFunction)(int i);	/* typedef a function pointer, input int, return void*/

int i = 0;

void func(int i)
{
	printf("in pfunc %d\n", i);
}

void test_pFunc(pFunction pfunc, int i)
{
	pfunc(i);
}

int main(int arg, char const *argv[])
{
	test_pFunc(func, 1234);
	return 0;
}