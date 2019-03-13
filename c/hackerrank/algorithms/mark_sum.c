/* Students Marks Sum */

#include <stdio.h>
#include <stdlib.h>

int marks_summation(int *marks, char gender, int number_of_students)
{
    int sum = 0;
    int index;

    if (gender == 'b')
    {
        /* marks of boys */
        for (index = 0; index < number_of_students; index += 2)
        {
            sum += *(marks+index);
        }
    }
    else if (gender == 'g')
    {
        /* marks of girls */
        for (index = 1; index < number_of_students; index += 2)
        {
            sum += *(marks+index);
        }
    }

    return sum;
}

int main(void)
{
    int number_of_students;
    int *marks;
    char gender;
    int index;

    scanf("%d", &number_of_students);

    marks = (int *)malloc(number_of_students*sizeof(int));
    if (marks == NULL)
    {
        return 1;
    }

    for (index = 0; index < number_of_students; index++)
    {
        scanf("%d ", &marks[index]);
    }

    scanf("%c", &gender);

    printf("number_of_students = %d\n", number_of_students);
    for (index = 0; index < number_of_students; index++)
    {
        printf("mark of %d = %d\n", index, marks[index]);
    }
    printf("gender = %c\n", gender);

    printf("%d", marks_summation(marks, gender, number_of_students));

    free(marks);

    return 0;
}
