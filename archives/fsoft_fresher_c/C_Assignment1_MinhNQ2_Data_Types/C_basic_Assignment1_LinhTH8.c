/*******************************************************************************
Date: 11-1-2017
Mentor: MinhNQ2
Programmer: LinhTH8
C_Basic
-----------------------------------------------------------------------
Assignment 1:
- Viet 1 chuong trinh cho phep user nhap vao toi da 20 so nguyen (integers).
In ra ket qua gom so trung binh cua cac so nhap vao va so luong so co
gia tri nho hon gia tri trung binh nay.
- Viet 1 ham chuyen cac gia tri chan ve ben phai, le ve ben trai cua
mang do. Yeu cau: dung mang cac so nguyen de xu ly ket qua.
 ******************************************************************************/

/*******************************************************************************
1.a
input:
20 integers.

output:
-average of 20 integers.
-number of numbers that are less than average.

Thinking Flow
B1: Nhap tat ca so nguyen, luu vao array co dung luong x[20]
B2: Dem so luong so nguyen (k<20)
B3: Tinh avg, in ra avg.
B4: Duyet so tu 1-->k, x(1)-->x(k), neu x(k)<avg thi count++
B5: in ra count.
 ******************************************************************************/

/*******************************************************************************
1.b
Viet 1 ham chuyen cac gia tri chan ve ben phai, le ve ben trai cua
mang do. Yeu cau: dung mang cac so nguyen de xu ly ket qua.

Input: Day so chua duoc sap xep
Output: Day so da duoc sap xep lai, chan fai - le trai
 ******************************************************************************/
#include <stdio.h> /*This form is used for system header files*/
#include "LinhTH8.h" /*This form is used for header files of your own program*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
//#define MACRO1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void sap_xep(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
int g_x[20]; /*Mang luu gia tri cac phan tu*/
int g_k; /*Bien dem so luong phan tu da nhap*/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void sap_xep(void)
{
    /*Giai thuat 2:
    - Tim tat ca so chan, luu vao 1 mang chan[];
    - Tim tat ca so le, luu vao 1 mang le[];
    - Hien thi day so le - chan.
    */
    int chan[20];
    int le[20];
    int i;
    int j=0;
    int m=0;
    int j_max;
    int m_max;

    for (i=1; i<=g_k; i++)
    {
        if (g_x[i]%2==0)
        {
            j++;
            chan[j] = g_x[i];
        }
        if (g_x[i]%2==1)
        {
            m++;
            le[m] = g_x[i];
        }
        if (i==g_k)
        {
            j_max = j;
            m_max = m;
        }
    }

    for (m=1;m<=m_max;m++)
    {
        printf("%d  ", le[m]);
    }
    for (j=1;j<=j_max;j++)
    {
        printf("%d  ", chan[j]);
    }

}

int main(void)
{
    /*Local variable declaration*/
    int i; /*Bien chay*/
    int sum;
    float avg;
    int count=0;

    /*Input day so dau vao*/
    printf("Nhap so luong so cua day so (mang) = ");
    scanf("%d", &g_k);
    if(g_k>20)
    {
        printf("So luong toi da la 20");
        return 1; /*error warning*/
    }
    for (i=1;i<=g_k;i++)
    {
        scanf("%d",&g_x[i]);
    }

    /*Tinh avg*/
    sum = 0;
    for (i=1;i<=g_k;i++)
    {
        sum = sum + g_x[i];
    }
    avg = (float) sum / g_k;
    printf("Gia tri trung binh cua cac so da nhap la: %.3f \n", avg);

    /*Duyet so tu 1 den k, tim so < avg, count++*/
    for (i=1;i<=g_k;i++)
    {
        if (g_x[i]<avg)
        {
            count++;
        }
    }
    printf("So luong cac so nho hon gia tri trung binh la: %d \n", count);

    printf("Day so sau khi duoc sap xep Chan Phai - Le Trai: \n");
    sap_xep();

    return 0;
}
