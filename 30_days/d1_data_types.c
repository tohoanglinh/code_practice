#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i = 4;
    double d = 4.0;
    char s[] = "HackerRank ";
    // Declare second integer, double, and String variables.
    int i2;
    double d2;
    char *s2 = malloc (256);
    if (s2 == NULL)
        {
        printf ("No memory\n");
        return 1;
    }

/*
For C programmers::
(this is not the comment.this is the solution of facing prob in reading input).
Now I think all c programmers facing the problem(in this question) that either they are unable to get proper input or how to take input till end line(new line).
For solution I need to ask u something.
Do u know why we use spaces between scanf()?
Ans: we use spaces because spaces inside scanf() make scanf() to take input skipping the spaces of given input by user.
Given question will give us a new line after the double input.
So if we use scanf("%[^\n]"), we will not get the line we wanted because it will stop taking new line as it got earlier.So we need to skip the new line before taking input of string till new line.
As I said earlier we can use \n inside scanf() to skip that new line
so, our code might look like this:
scanf(" %d %lf\n%[^\n]", &[int variable], &[double variable],[your string]);
now the scanf() will work and u will be happy getting 30 marks.
Note:this can be done by assingnment supperssion or many other ways.Oh!yes, the gets() is banned coz it may make Buffer Overflow(security threat).You may use fgets().
*/

    // Read and save an integer, double, and String to your variables.
//    scanf("%d", &i2);
//    scanf("%lf", &d2);
//    fgets(s2, 256, stdin);
    scanf(" %d %lf\n%[^\n]", &i2, &d2,s2);

    // Print the sum of both integer variables on a new line.
    printf("%d\n", i+i2);

    // Print the sum of the double variables on a new line.
    printf("%.1lf\n", d+d2);

    // Concatenate and print the String variables on a new line
    // The 's' variable above should be printed first.
    printf("%s%s", s,s2);

    return 0;
}
