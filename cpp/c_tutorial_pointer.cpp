/**
 * File   : c_tutorial_pointer.cpp
 * Author : To Hoang Linh
 * Date   : 2017-07-24
 * ForWhat: A pointer in C is a way to share a memory address among different contexts
 * (primarily functions). They are primarily used whenever a function needs to modify
 * the content of a variable, of which it doesn't have ownership. In order to access
 * the memory address of a variable, val, we need to prepend it with & sign. E.g.,
 * &val returns the memory address of val. This memory address is assigned to a
 * pointer and can be shared among various functions. E.g. int *p = &val will assign
 * the memory address of val to pointer p. To access the content of the memory to
 * which the pointer points, prepend it with a *. For example, *p will return the
 * value reflected by val and any modification to it will be reflected at the source (val).
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
using namespace std;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MACRO1 2

/*******************************************************************************
 * Code
 ******************************************************************************/
void update(int *a, int *b)
{
    /* complete this function */
    int tmp_a;
    int tmp_b;
    tmp_a = *a;
    tmp_b = *b;
    *a = tmp_a + tmp_b;
    if (tmp_a > tmp_b)
    {
        *b = tmp_a - tmp_b;
    }
    else
    {
        *b = tmp_b - tmp_a;
    }
}

int main(void)
{
    int a, b;

    cin >> a >> b;

    update(&a, &b);

    cout << a << "\n" << b;

    return 0;
}
