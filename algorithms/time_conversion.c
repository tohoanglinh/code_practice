/*Time Conversion*/
#include <stdio.h>
#include <stdlib.h>

int char_to_num(char ch);
char num_to_char(int n);
int convert_hour(char *s);
int length(char *s);

int main(void)
{
    /*input: 12-hour AM/PM format*/
    char *s;
    s = malloc(512000*sizeof(char));
    if (NULL == s)
    {
        return (-1);
    }
    scanf("%s", s);

    /*output: 24-hour military format*/ 
    int new_hour;
    
    int len = length(s);
    
    /* AM */
    if ('A'==s[len-2])
    {
        if (convert_hour(s) == 12)
        {
            new_hour = convert_hour(s) - 12;
        }
        else
        {
            new_hour = convert_hour(s);
        }
    }

    /* PM */
    if ('P'==s[len-2])
    {
        if (convert_hour(s) == 12)
        {
            new_hour = convert_hour(s);
        }
        else
        {
            new_hour = convert_hour(s) + 12;
        }
    }
    
    char *s1 = (char *)malloc(512000*sizeof(char));
    s1[0] = num_to_char(new_hour/10);
    s1[1] = num_to_char(new_hour%10);

    int i;
    for (i = 2; i <= (len-2); i++)
    {
        s1[i] = s[i];
        if (i == (len - 2))
        {
            s1[i] = '\0';
        }
    }
    printf("%s", s1);
    
    free(s);
    return 0;
}

int length(char *s)
{
    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

int convert_hour(char *s)
{
    return (10*char_to_num(s[0]) + char_to_num(s[1]));
}

int char_to_num(char ch)
{
    /*'6' --> 6*/
    return (ch-48);
}
char num_to_char(int n)
{
    /*6 --> '6'*/
    return (n+48);
}
