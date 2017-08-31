/* file: day_of_the_programmer.c
 * author: To Hoang Linh
 * date: 15.Jul.2017
 * content: Marie invented a Time Machine and wants to test it by time-traveling
 * to visit Russia on the Day of the Programmer (the 256th day of the year)
 * during a year in the inclusive range from 1700 to 2700
 * From 1700 to 1917, Russia's official calendar was the Julian,
 * Since 1919, they used the Gregorian.
 * The transition from Julian to Gregorian occured in 1918, when the next day
 * after Jan 31st was Feb 14th. This means that in 1918, Feb 14th was the 32nd
 * day of the year in Russia.
 * In both calendar systems, Feb is the only month with a variable amount of
 * days; it has 29 days during a leap year, and 28 days during all other years.
 * In the Julian calendar, leap years are divisible by 4; in the Gregorian calendar,
 * leap years are either of the following
 * */

#include <stdio.h>
#include <stdbool.h>

#define JANUARY 31
#define MARCH   31
#define APRIL   30
#define MAY     31
#define JUNE    30
#define JULY    31
#define AUGUST  31

void printFullDate(int date, int month, int year)
{
    printf("%02d.%02d.%04d\n", date, month, year);
}

bool isLeapYear(int year)
{
    if (year >= 1700 && year <= 1917)
    {
        /* Julian calendar */
        if (year % 4 == 0)
        {
            return true;
        }
    }
    else if (year >= 1919)
    {
        /* Gregorian calendar */
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        {
            return true;
        }
    }
    else
    {
        /* transition from Julian to Gregorian: 1918 */
        return false;
    }
    return false;
}

int sumDate(int year)
{
    int february;
    if (year != 1918)
    {
        if (true == isLeapYear(year))
        {
            february = 29;
        }
        else
        {
            february = 28;
        }
    }
    else
    {
        /* in 1918, february only has 15 days */
        february = 28 - 14 + 1;
    }
    return (JANUARY+february+MARCH+APRIL+MAY+JUNE+JULY+AUGUST);
}

/* find 256th date of the year */
int findDate(int year)
{
    return (256-sumDate(year));
}

int findMonth(int year)
{
    return 9;
}

int main(void)
{
    /* input: year y */
    int y;
    y = 0;
    while (y < 1700 || y > 2700)
    {
        scanf("%d", &y);
    }

    /* output : find the day of the programmer during year y, dd.mm.yyyy */
    printFullDate(findDate(y), findMonth(y), y);

    return 0;
}
