#include <stdio.h>

int main(void)
{
    //1st line: 3 space-separated integers a0, a1, a2
    //2nd line: 3 space-separated integers b0, b1, b2
    //output: 2 space-separted integers Alice Bob (1 2)
    int a[3];
    int b[3];
    int i;
    int Alice_Score = 0;
    int Bob_Score = 0;

    scanf("%d %d %d", &a[0], &a[1], &a[2]);
    scanf("%d %d %d", &b[0], &b[1], &b[2]);

    while (a[0] > 100 || b[0] > 100
        || a[1] > 100 || b[1] > 100
        || a[2] > 100 || b[2] > 100
        || a[0] < 1   || b[0] < 1
        || a[1] < 1   || b[1] < 1
        || a[2] < 1   || b[2] < 1)
    {
        scanf("%d %d %d", &a[0], &a[1], &a[2]);
        scanf("%d %d %d", &b[0], &b[1], &b[2]);
    }

    for (i = 0; i < 3; i++)
    {
        if (a[i] > b[i])
        {
            /* alice is awarded 1 point */
            Alice_Score++;
        }
        if (a[i] < b[i])
        {
            /* bob is awarded 1 point */
            Bob_Score++;
        }
        if (a[i] == b[i])
        {
            /* neither person receives a point */
        }
    }
    
    printf("%d %d\n", Alice_Score, Bob_Score);
    
    return 0;
}
