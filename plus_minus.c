/* plus-minus */
#include <stdio.h>

typedef enum
{
    ANFC_SNEP_CONN_DISC = 0U,
    ANFC_SNEP_CONN_WAIT,
    ANFC_SNEP_CONN_IDLE,
    ANFC_SNEP_CONN_RCV_RESPONSE,
    ANFC_SNEP_CONN_SEND_FRAGMENTS,
    ANFC_SNEP_CONN_RCV_FRAGMENTS,
    ANFC_SNEP_CONN_ERROR
}Anfc_SNEP_ConnState_Type;

int main(void)
{
    printf("Plus-Minus\n");

    Anfc_SNEP_ConnState_Type CONN_State;
    
    CONN_State = ANFC_SNEP_CONN_RCV_RESPONSE;
    
    printf("%d", CONN_State);
    
    int a;

    scanf("%d", &a);

    while (a != 1);
    
    printf("%d",a);
    
    return 0;
}
