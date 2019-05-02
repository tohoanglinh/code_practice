/*
 * File   : small_triangles_large_triangles.c
 * Author : To Hoang Linh
 * Date   : 2019-04-30
 * ForWhat: You are given n triangles, specifically, their sides a,b,c.
 * Print them in the same style but sorted by their areas from the smallest
 * to largest. It is guaranteed that all the areas are different.
 * Calculate area of triangle using Heron's formula.
 */

/**
 * INCLUDES
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * DEFINES & MACROS
 */
typedef struct triangle
{
    int a;
    int b;
    int c;
} triangle_t;

/**
 * FUNCTIONS
 */
double area_triangle(triangle_t triangle)
{
    double perimeter;

    perimeter = (double)(triangle.a + triangle.b + triangle.c)/2;
    return sqrt(perimeter * (perimeter - triangle.a) * (perimeter - triangle.b) * (perimeter - triangle.c));
}

void sort_array(triangle_t *array, int array_size)
{
    int i, j;
    triangle_t temp;
    double *area = malloc(sizeof(double)*array_size);
    double temp_area;

    for (i = 0; i < array_size; i++)
    {
        area[i] = area_triangle(array[i]);
    }

    for (i = 0; i < array_size; i++)
    {
        for (j = i+1; j < array_size; j++)
        {
            if (area[i] > area[j])
            {
                temp = array[i];
                temp_area = area[i];
                array[i] = array[j];
                area[i] = area[j];
                array[j] = temp;
                area[j] = temp_area;
            }
        }
    }
}

int main(void)
{
    /* n: number of triangles */
    int n;
    int i;

    scanf("%d", &n);

    triangle_t *tri = malloc(sizeof(triangle_t)*n);

    for (i = 0; i < n; i++)
    {
        scanf(" %d %d %d", &tri[i].a, &tri[i].b, &tri[i].c);
    }

    /* sort by areas */
    sort_array(&tri, n);

    /* print back */
    for (i = 0; i < n; i++)
    {
        printf("%d %d %d \n", tri[i].a, tri[i].b, tri[i].c);
    }

    free(tri);

    return 0;
}
