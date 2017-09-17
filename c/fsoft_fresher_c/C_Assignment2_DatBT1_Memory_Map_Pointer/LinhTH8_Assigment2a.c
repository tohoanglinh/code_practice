/*******************************************************************************
 * Fresher Embedded HN17_01
 * Date: 12-1-2017
 * Mentor: DatBT1
 * Dev: LinhTH8
 * Assignment 2: Memory Management and Pointer
 2a. Viết một chương trình C để đảo một mảng ký tự bằng cách sử dụng con trỏ và 
 hàm cấp phát bộ nhớ động. Cho phép người dùng nhập số phần tử của mảng và các 
 phần tử của mảng. Tổ chức chương trình thành các chương trình con.
 ******************************************************************************/
 
 /*******************************************************************************
 * Coding Conventions
 * Không tab, trailing space
 * Các hàm phải có prototype
 * Các tên biến, hàm phải có nghĩa
 * Không khai báo biến giữa hàm
 ******************************************************************************/
#include <stdio.h>
#include <malloc.h>

 /*******************************************************************************
 * Program Flow
 2.1. Mang 1 chieu (array)
 Input: User inputs no of elements of the array and elements.
 Output: dao 1 mang ky tu
 Requirement: 
     + Su dung pointer va dynamic memory allocation functions (malloc, calloc)
     + Viet thanh cac chuong trinh con (function)
 No of elements = 5;
 Element 1 = a;
 Element 2 = b;
 .
 .
 Element 5 = e;
 --> Mảng đó là abcde --> Đảo ngược lại là edcba
 ******************************************************************************/
 
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX 100 /*So luong phan tu toi da co the nhap*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void input(void); /*Nhap mang ky tu va luu vao con tro p*/
static void reverse(void); /*Ham dao nguoc chuoi ky tu(so)*/
static void swap(int *a, int *b); /*Doi cho 2 so cho nhau*/

/*******************************************************************************
 * Variables (Global)
 ******************************************************************************/  
    int g_num; /*so luong phan tu cua chuoi ky tu*/
    int *p; /*con tro de quan ly truy cap den tung phan tu trong chuoi ky tu*/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void swap(int *a, int *b)
{
    int tmp;
    
    tmp = *b;
    *b  = *a;
    *a  = tmp;
}
 
static void reverse(void)
{
    char i;
    int tmp;
    
    printf("Before reversing...\n");
    for ( i = 0; i < g_num; i++ ) 
    {
      printf("%c ", *(p+i) );
    }
    
    printf("\nAfter reversing...\n");
    
    /*Tim kiem tu dau day --> 1/2 day, dao so dau voi so cuoi*/
    for ( i = 0; i < g_num/2; i++)
    {
        swap(p+i, p+g_num-i-1);
    }
    
    /*Output to screen*/
    for ( i = 0; i < g_num; i++ ) 
    {
      printf("%c ", *(p+i) );
    }
}

static void input(void)
{
    int i;
    
    do{
    printf("Input no of elements: ");
    scanf("%d",&g_num);   
    } while((g_num>MAX) || (g_num<=0));

    p = (int*)malloc(g_num*sizeof(int));
      
    printf("Input each element value: \n");
    for (i=0;i<g_num;i++)
    {
        scanf(" %c",p+i);
    }
}

int main(void)
{       
    input();
    reverse();

    return 0;
}
