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
    char name[MAX_NAME_LENGTH];
    uint32_t phone;         /* 8-digit phone number */
} phonebook_t;

FILE *g_fp;

void query(char input_name[], phonebook_t *pb, uint32_t len_pb);
void list_all(phonebook_t *pb, uint32_t len_pb);

void query(char input_name[], phonebook_t *pb, uint32_t len_pb)
{
    uint8_t found = 0;
    uint32_t i;

    for (i = 0; i < len_pb; i++)
    {
        if (strcmp(input_name, pb[i].name) == 0)
        {
            /* display sam=phone */
            found = 1;
            fprintf(g_fp, "%s=%d\n", pb[i].name, pb[i].phone);
            //printf("%s=%d\n", pb[i].name, pb[i].phone);
        }
    }
    
    if (found == 0)
    {
        fprintf(g_fp, "Not found\n");
        //printf("Not found\n");
    }
}

void list_all(phonebook_t *pb, uint32_t len_pb)
{
    uint32_t i;
    for (i = 0; i < len_pb; i++)
    {
        printf("member %d has name (%s) and phone (%d)\n", i, pb[i].name, pb[i].phone);
    }
}

/* Dictionaries and maps */
int main(void)
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    uint32_t i;         /* tmp counter */
    uint32_t n;         /* number of database entries */

    g_fp = fopen ("out.txt", "w+");
    
    /* allocate array in stack (small size, fast access) --> suitable for known small size array */
    //phonebook_t pb[n];

    /* allocate pointer in heap (big size, slow access, have to free) --> suitable for unpredictable or big size array */
    phonebook_t *pb;
    pb = (phonebook_t *) malloc (MAX_DATABASE_ENTRIES);

    scanf("%d", &n);

    if ((n>=MIN_DATABASE_ENTRIES) && (n<=MAX_DATABASE_ENTRIES))
    {
        /* input database members */
        for (i = 0; i < n; i++)
        {
            scanf("%s %d", pb[i].name, &pb[i].phone);
        }
    }
    else
    {
        /* re-enter n */
        scanf("%d", &n);
    }

    /* list all */
    //list_all(pb, n);

    /* queries */
    char input_name[MAX_NAME_LENGTH];
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

    fclose(g_fp);
    free(pb);

    return 0;
}
