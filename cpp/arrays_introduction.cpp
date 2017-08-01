/**
 * File   : arrays_introduction.cpp
 * Author : To Hoang Linh
 * Date   : 2017-07-25
 * ForWhat: An array is a series of elements of the same type placed in contiguous
 * memory locations that can be individually referenced by adding an index to a unique
 * identifier.
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
int main(void)
{
    /* N: number of intergers */
    int N;
    cin >> N;
    
    int i;
    int *A = new int [N];
    
    for (i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    
    for (i = N-1; i >= 0; i--)
    {
        cout << A[i] << " ";
    }
    
    delete[]A;
    return 0;
}
