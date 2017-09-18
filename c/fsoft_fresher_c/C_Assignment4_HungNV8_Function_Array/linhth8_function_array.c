/*******************************************************************************
 * Description:
 * FR_EMB_HN17_01
 * mentor: @hungnv8
 * Function and Array (16-Jan-2017)
 * Deadline: 17:00 25-Jan-2017
 * dev: @linhth8
 ******************************************************************************/
#include <stdio.h>
#include <math.h>
#include "header.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
int g_A[MAX][MAX];
int g_B[MAX][MAX];
int g_rowA=1;
int g_rowB=1;
int g_colA=1;
int g_colB=1;

/*******************************************************************************
 * Code
 ******************************************************************************/
float rectangle_area(float perimeter, float diagonal)
{
    /*
    Calculate area of rectangle, with known perimeter and diagonal.
    P = 2 * (a + b);
    D = sqrt(a^2 + b^2);
    S = P^2 / 8 - D^2 / 2; // Tinh den truong hop < 0
    */

    return(pow(perimeter, 2) /8 - pow(diagonal, 2)/2);
}

int isRectangle(float perimeter, float diagonal)
{
    if ((perimeter <= 2*diagonal) || (diagonal <= 0))
    {
        return(0);
    }
    else
    {
        return(1);
    }
}

void matrix_input_row_col(void)
{
    /*Input no of row and column of two matrices*/
    printf("Input number of row and column of two matrices: \n");

    do {
        printf("g_rowA = ");
        scanf("%d", &g_rowA);
        printf("g_colA = ");
        scanf("%d", &g_colA);

        printf("g_rowB = ");
        scanf("%d", &g_rowB);
        printf("g_colB = ");
        scanf("%d", &g_colB);
    } while((g_rowA<=0) || (g_colA<=0) || (g_rowB<=0) || (g_colB<=0) || (g_rowA > MAX) || (g_rowB > MAX) || (g_colA > MAX) || (g_colB > MAX));

}

void matrix_input_elements(void)
{
    int i;
    int j;

    /*Nhap cac phan tu cua hai ma tran*/
    printf("Input elements of matrix A: \n");
    for (i=0; i<g_rowA; i++)
    {
        for (j=0; j<g_colA; j++)
        {
            scanf("%d", &g_A[i][j]);
        }
    }

    printf("You entered matrix A: \n");
    matrix_display(g_rowA, g_colA, g_A);

    printf("Input elements of matrix B: \n");
    for (i=0; i<g_rowB; i++)
    {
        for (j=0; j<g_colB; j++)
        {
            scanf("%d", &g_B[i][j]);
        }
    }

    printf("You entered matrix B: \n");
    matrix_display(g_rowB, g_colB, g_B);
}

int matrix_check_add_condition(void)
{
    if ((g_rowA!=g_rowB) || (g_colA!=g_colB))
    {
        return(0); // cannot add
    }
    else
    {
        return(1); // can add
    }
}

int matrix_check_mul_condition(void)
{
    if (g_colA==g_rowB)
    {
        return(1); // can multiply
    }
    else
    {
        return(0); //cannot multiply
    }
}

void matrix_display(int row, int col, int a[MAX][MAX])
{
    int i;
    int j;
    printf("Size: [%d, %d]\n", row, col);

    for (i= 0;i<row;i++) {
      for (j=0;j<col;j++) {
         printf("%d\t", a[i][j]);
      }
      printf("\n");
   }
}

void matrix_add(int a[MAX][MAX], int b[MAX][MAX])
{
    int i;
    int j;
    int sum[MAX][MAX];

    /*Tinh tong 2 ma tran a va b*/

    printf("Matrix summation result = \n");
    for (i= 0;i<g_rowA;i++) {
      for (j=0;j<g_colA;j++) {
         sum[i][j] = a[i][j] + b[i][j];
         printf("%d\t", sum[i][j]);
      }
      printf("\n");
    }

}

void matrix_multiply(int a[MAX][MAX], int b[MAX][MAX])
{
    /*Tinh tich 2 ma tran a va b*/
    int i;
    int j;
    int k;
    int tmp;
    int multiply[MAX][MAX];

    for (i = 0; i < g_rowA; i++) {
      for (j = 0; j < g_colB; j++) {
        for (k = 0; k < g_rowB; k++) {
          tmp = tmp + a[i][k]*b[k][j];
        }

        multiply[i][j] = tmp;
        tmp = 0;
      }
    }

    printf("Matrix multiplication result = \n");
    matrix_display(g_rowA, g_colB, multiply);
}
/*******************************************************************************
 * Main Function
 ******************************************************************************/
int main(void)
{
    float p; // perimeter
    float d; // diagonal

    /************************************************************************************
    Phan 1: Nhap vao chu vi (p), duong cheo (d) --> Tinh dien tich hinh chu nhat.
    *************************************************************************************/
    printf("-------------------------------------------------------------------------\n");
    printf("Section 1: Input perimeter and diagonal: (p > 2d > 0) \n");
    scanf("%f%f", &p, &d);
    /*Kiem tra dieu kien, p > 2d > 0 thi moi tiep tuc tinh*/
    while (isRectangle(p, d)==0)
    {
    printf("Please re-input p and d, note the condition (p > 2d > 0):\n");
    scanf("%f%f", &p, &d);
    }

    /*In ra gia tri dien tich*/
    printf("Rectangle Area (Peri = %.2f, Diag = %.2f) = %.2f\n", p, d, rectangle_area(p,d));

    /************************************************************************************
    Phan 2: Nhap vao 2 ma tran, tinh tong/tich. (Dung array)
    *************************************************************************************/
    printf("-------------------------------------------------------------------------\n");
    printf("Section 2: Matrix Addition and Multiplication\n");

    /*
    B1: Nhap so row/col tu ban phim
    B2: Kiem tra dieu kien nhan 2 ma tran
    B3: Kiem tra dieu kien cong 2 ma tran
    B4: Ra quyet dinh nhan hay cong, continue() or return(1);
    B5: Nhap tung phan tu cua 2 ma tran
    B6: Hien thi 2 ma tran da nhap
    B7: Thuc hien phep cong hoac nhan neu thoa man yeu cau.
    */

    matrix_input_row_col();

    while ((matrix_check_add_condition()!=1) && (matrix_check_mul_condition()!=1))
    {
        printf("Cannot add or multiply the 2 matrices with the above sizes.\n");
        printf("Please re-input row and column\n");
        matrix_input_row_col();
    }

    matrix_input_elements();

    if (matrix_check_add_condition()==1)
    {
        printf("We can add the two matrices\n");
        matrix_add(g_A, g_B);
    }

    if (matrix_check_mul_condition()==1)
    {
        printf("We can multiply the two matrices\n");
        matrix_multiply(g_A, g_B);
    }

    printf("--------------------------------------------------------------------------\n");
    getchar(); /*wait*/
    return 0;
}
