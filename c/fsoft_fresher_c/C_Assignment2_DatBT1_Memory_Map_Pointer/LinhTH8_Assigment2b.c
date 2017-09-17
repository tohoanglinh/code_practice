/*******************************************************************************
 * Fresher Embedded HN17_01
 * Date: 12-1-2017
 * Mentor: DatBT1
 * Dev: LinhTH8
 * Assignment 2: Memory Management and Pointer
 * 2b. Pointer and Multidimension Array
 * Cong 2 ma tran (2x2)
 * Nhap so phan tu cua 2 ma tran va cac phan tu cua ma tran
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/******************************************************************************* /
/*Prototypes*/
static void nhap_ma_tran(int row, int col);
static void cong_ma_tran(int **A, int **B);
void free_pointers(int **p, int row);

/*Global Vars*/
int g_row;
int g_col;
int **A;
int **B;
int **SUM;
 /******************************************************************************/
 /*Procedure*/
static void nhap_ma_tran(int row, int col)
{
    int i, j;
    
    /*Cap phat bo nho cho hai ma tran A va B*/
    A = (int**)malloc(row*sizeof(int));
    for (i=0;i<row;i++)
    {
        *(A+i) = (int*)malloc(col*sizeof(int));
    }
    
    B = (int**)malloc(row*sizeof(int));
    for (i=0;i<row;i++)
    {
        *(B+i) = (int*)malloc(col*sizeof(int));
    }
    
    /*Nhap cac phan tu cua 2 ma tran*/
    printf("Enter elements of the 1st matrix \n");
    for (i=0;i<row;i++)
       for (j=0;j<col;j++)
       {
        scanf("%d",&*(*(A+i)+j));
       }
    
    printf("Enter elements of the 2nd matrix \n");
    for (i=0;i<row;i++)
    {
       for (j=0;j<col;j++)
       {
        scanf("%d",&*(*(B+i)+j));
       }
   }
}

static void cong_ma_tran(int **A, int **B)
{
    int i, j;
    printf("Sum of entered matrices:-\n");

    SUM = (int**)malloc(g_row*sizeof(int));
    for (i=0;i<g_row;i++)
    {
        SUM[i] = (int*)malloc(g_col*sizeof(int));
    }
    
    for (i= 0;i<g_row;i++) {
      for (j=0;j<g_col;j++) {
         *(*(SUM+i)+j)=*(*(A+i)+j)+*(*(B+i)+j);
         printf("%d\t", *(*(SUM+i)+j));
      }
      printf("\n");
   }
}

void free_pointers(int **p, int row)
{
    int i;
    for (i=0; i<row; i++)
    {
        free(p[i]);
    }
    free(p);
}

int main(void)
{
    /*Nhap so phan tu cua 2 ma tran*/
    printf("Enter no of rows and columns of two matrices : \n");
    scanf("%d", &g_row);
    scanf("%d", &g_col);
    
    nhap_ma_tran(g_row, g_col);
    cong_ma_tran(A, B);
    
    free_pointers(A,g_row);
    free_pointers(B,g_row);
    free_pointers(SUM,g_row);
    
    return 0;
}
