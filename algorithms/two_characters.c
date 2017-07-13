#include <stdio.h>

int main(void)
{
    /* s_len: length of s */
    int s_len;
    scanf("%d", &s_len);

    char *s;
    s = malloc(s_len*sizeof(char));
    if (NULL == s)
    {
        return (-1);
    }
    

    
    free(s);
    return 0;
}
