#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_STRING_SIZE 10000
#define MIN_STRING_SIZE 2
#define MAX_TC 10
#define MIN_TC 1

uint16_t length (char tmp_str[]);
void process(char tmp_str[], uint16_t tmp_len);

uint16_t length (char tmp_str[])
{
    uint16_t len;

    len = 0;

    while (tmp_str[len] != '\0')
    {
        len++;
    }
    
    return len;
}

void process(char tmp_str[], uint16_t tmp_len)
{
    uint16_t i;
    uint16_t j;
    uint16_t k;
    
    char *even_str = NULL;
    char *odd_str = NULL;
    
    even_str = malloc(sizeof(char)*tmp_len);
    odd_str = malloc(sizeof(char)*tmp_len);

    i = 0;
    j = 0;
    k = 0;

    while (tmp_str[i] != '\0')
    {
        if (i % 2 == 0)
        {
            even_str[j] = tmp_str[i];
            j++;
        }
        else
        {
            odd_str[k] = tmp_str[i];
            k++;
        }
        i++;
    }

    even_str[j] = '\0';
    odd_str[k] = '\0';

    printf("%s %s\n", even_str, odd_str);
    
    free(even_str);
    free(odd_str);
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int TC;
    
    char input_str[MAX_STRING_SIZE];

    scanf("%d", &TC);

    if ((TC >= 1) && (TC <= 10))
    {
        while (TC > 0)
        {
            scanf (" %s", input_str);
            uint16_t cal_len = length(input_str);
            if ((cal_len >= MIN_STRING_SIZE) && (cal_len <= MAX_STRING_SIZE))
            {
                process(input_str, cal_len);
            }
            else
            {
                printf("pls input another string\n");
            }
            TC--;
        }
    }
    return 0;
}
