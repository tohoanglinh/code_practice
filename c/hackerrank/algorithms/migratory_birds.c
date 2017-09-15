#include <stdio.h>
#include <stdlib.h>

int count_bird(int type, int *bird_arr, int total_bird)
{
    int i;
    int cnt;
    cnt = 0;
    for (i = 0; i < total_bird; i++)
    {
        if (*(bird_arr+i) == type)
        {
            cnt++;
        }
    }
    return cnt;
}

int main(void)
{
    /* n: number of birds */
    int n;
    scanf("%d", &n);

    /* n integers, each describes the respective type number of each bird */
    int i;
    int *bird;
    bird = malloc(n*sizeof(int));
    if (NULL == bird)
    {
        return (-1);
    }
    for (i = 0; i < n; i++)
    {
        scanf(" %d", bird+i);
    }

    int cnt_max;
    int type;
    cnt_max = 0;
    int cnt_max_type;
    cnt_max_type = 0;
    /* count frequency occurrence */
    for (type = 1; type <= 5; type++)
    {
        //printf("frequency of bird type %d is %d\n", type, count_bird(type,bird,n));
        if (count_bird(type,bird,n) > cnt_max)
        {
            cnt_max = count_bird(type,bird,n);
            cnt_max_type = type;
        }
    }

    //printf("cnt_max      = %d\n", cnt_max);
    //printf("cnt_max_type = %d\n", cnt_max_type);
    printf("%d\n", cnt_max_type);

    free(bird);
    return 0;
}
