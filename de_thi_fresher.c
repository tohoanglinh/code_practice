/* De thi dau vao Fresher FGA.S16
 * Cho 1 mang chua 1 day cap so cong, thieu 1 phan tu.
 * Tim phan tu bi thieu trong day.
 * VD: array[] = {2,4,8,10,12}: cong 2, thieu 6 --> ket qua la 6
 * VD: array[] = {4,12,16,20,24}: cong 4, thieu 8 --> ket qua la 8
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
//    int array[] = {2,4,8,10,12};
    int array[] = {4,12,16,20,24};
    int *diff;
    int index;
    int size;

    printf("==============\n");
    printf("De thi Fresher\n");
    printf("==============\n");

    /* verification the input array */
    size = sizeof(array)/sizeof(int);
    diff = (int *) malloc((size - 1)* sizeof(int));
//    printf("Input array size: %d\n", size);
    printf("Input array  : ");
    for (index = 0; index < size; index++)
    {
        printf("%d,", array[index]);
    }

    /* displaying the rule of the input array */
    for (index = 0; index < size; index++)
    {
        if (index == (size - 1))
        {
            break;
        }
        diff[index] = array[index+1] - array[index];
//        printf("\ndiff[%d]=%d", index, diff[index]);
    }

    /* find the missing diff element position */
    int start = diff[0];
    int diff_position, same_position;
    int size_diff = size - 1;
    for (index = 1; index < size_diff; index++)
    {
        if (index == (size_diff - 1) && diff[index] != start)
        {
            diff_position = index;
            same_position = index - 1;
            break;
        }
        if ((diff[index] != start) && (diff[index+1] == start))
        {
            diff_position = index;
            same_position = index+1;
            break;
        }
        if ((diff[index] != start) && (diff[index+1] != start))
        {
            diff_position = 0;
            same_position = index;
            break;
        }
    }

//    printf("\nSame Position: %d", same_position);
    printf("\nAdd coeff    : %d", diff[same_position]);
//    printf("\nDiff Position: %d", diff_position);
//    printf("\nHe so khac   : %d", diff[diff_position]);

    int missing_element;
    missing_element = diff[same_position] + array[diff_position];
    printf("\nMissing elem : %d", missing_element);

    free(diff);

    return 0;
}
