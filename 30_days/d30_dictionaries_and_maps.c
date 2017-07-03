#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_DATABASE_ENTRIES 100000
#define MIN_DATABASE_ENTRIES 1
#define MAX_NAME_LENGTH 100

typedef struct
{
    char name[100];
    long phone;         /* 8-digit phone number */
} phonebook_t;

void query(char input_name[], phonebook_t pb[], long len_pb);

void query(char input_name[], phonebook_t pb[], long len_pb)
{
    unsigned short found = 0;
    long i;
    
    for (i = 0; i < len_pb; i++)
    {
        if (strcmp(input_name, pb[i].name)==0)
        {
            /* display sam=phone */
            found = 1;
            printf("%s=%li\n", pb[i].name, pb[i].phone);
        }
    }

    if (found == 0)
    {
        printf("Not found\n");
    }
}

/* Dictionaries and maps */
int main(void)
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    long i;         /* tmp counter */
    long n;         /* number of database entries */

    /* allocate pointer in heap (big size, slow access, have to free) --> suitable for unpredictable or big size array */
    phonebook_t *pb;
    pb = (phonebook_t *) malloc (MAX_DATABASE_ENTRIES);
        
    scanf("%li", &n);

    if ((n>=MIN_DATABASE_ENTRIES) && (n<=MAX_DATABASE_ENTRIES))
    {
        /* input database members */
        for (i = 0; i < n; i++)
        {
            scanf("%s %li", pb[i].name, &pb[i].phone);
        }
    }
    else
    {
        /* re-enter n */
        scanf("%li", &n);
    }
    
    /* queries */
    char input_name[100];
    //input_name = (char *) malloc (MAX_NAME_LENGTH);
    int n1;
    do
    {
        n1 = scanf("%s", input_name);
        /* EOF = -1, defined in stdio.h */
        if (n1 == EOF)
        {
            break;
        }
        query(input_name, pb, n);
    } while (n1 != EOF);
    
    /* free memory allocated to pointers */
    free(pb);
    
    return 0;
}
