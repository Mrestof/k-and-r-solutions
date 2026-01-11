#include <stdio.h>

/* daytab: days in each month */
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;
    char *days;

    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    days = *(daytab + leap) +1;  // +1 to skip "0"
    for (i = 1; i < month; i++)
        day += *days++;
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    char *days;

    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    days = *(daytab + leap) +1;  // +1 to skip "0"
    for (i = 1; yearday > *days; i++, days++)
        yearday -= *days;
    *pmonth = i;
    *pday = yearday;
}

int main(void)
{
    int year, month, day, yearday;
    int result_month, result_day;

    /* Test day_of_year function */
    year = 2024; month = 2; day = 29;  /* Leap year test */
    printf("Date: %d-%d-%d\n", year, month, day);
    printf("Day of year: %d\n", day_of_year(year, month, day));

    year = 2023; month = 3; day = 1;   /* Non-leap year test */
    printf("Date: %d-%d-%d\n", year, month, day);
    printf("Day of year: %d\n", day_of_year(year, month, day));

    year = 2024; month = 12; day = 31;  /* End of year test */
    printf("Date: %d-%d-%d\n", year, month, day);
    printf("Day of year: %d\n", day_of_year(year, month, day));

    printf("\n");

    /* Test month_day function */
    year = 2024; yearday = 60;  /* Should be Feb 29 in leap year */
    month_day(year, yearday, &result_month, &result_day);
    printf("Year: %d, Day: %d -> Month: %d, Day: %d\n", 
           year, yearday, result_month, result_day);

    year = 2023; yearday = 60;  /* Should be Feb 28 in non-leap year */
    month_day(year, yearday, &result_month, &result_day);
    printf("Year: %d, Day: %d -> Month: %d, Day: %d\n", 
           year, yearday, result_month, result_day);

    year = 2024; yearday = 366;  /* Last day of leap year */
    month_day(year, yearday, &result_month, &result_day);
    printf("Year: %d, Day: %d -> Month: %d, Day: %d\n", 
           year, yearday, result_month, result_day);

    return 0;
}
