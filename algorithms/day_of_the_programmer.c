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

void print_full_date(int year)
{
    printf("This is full date\n");
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
    
    /* output */
    print_full_date(y);

    return 0;
}
