/* Grading Students */
#include <stdio.h>
#include <stdlib.h>

int func_next_mul_5(int grade);
int func_round(int grade);

int func_next_mul_5(int grade)
{
    /* 
     * 0 < next - grade < 5
     * next % 5 == 0
     * ? next
     */
    int next;
    for (next = grade; next < grade + 5; next++)
    {
        if (next % 5 == 0)
        {
            return next;
        }
    }
    return grade;
}

int func_round(int grade)
{
    int result;
    int next_5;
    
    if (grade < 38)
    {
        result = grade;
    }
    else
    {
        if (grade % 5 == 0)
        {
            result = grade;
        }
        else
        {
            /* find the next multiplier of 5 */
            next_5 = func_next_mul_5(grade);
            if ((next_5 - grade) < 3)
            {
                result = next_5;
            }
            else
            {
                result = grade;
            }
        }
    }
    return result;
}

int main(void)
{
    int n;
    n = 0;
//    printf("1. Enter number of students n = ");
    while ((n < 1) || (n > 60))
    {
        scanf("%d", &n);
    }
    
//    printf("2. Enter grade for each student:\n");
    int i;
    int *grade;
    grade = (int*) malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
    {
        scanf("%d", &grade[i]);
        while ((grade[i] < 0) || (grade[i] > 100))
        {
            scanf("%d", &grade[i]);
        }
    }
    
//    printf("3. Output: \n");
    for (i = 0; i < n; i++)
    {
        printf("%d\n", func_round(grade[i]));
    }
    
    free(grade);
    return 0;
}
