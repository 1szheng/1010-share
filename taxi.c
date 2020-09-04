/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Taxi
 *
 * Read in four positive integer corresponding to the day of the week,
 * the hour and minute of boarding, and the distance travelled.  Print
 * to the standard output, the fare of the taxi.
 *
 * @file: taxi.c
 * @author: Wan Si Zheng (Group D05)
 */

#include "cs1010.h"
#include <stdbool.h>

// returns true if it is a weekday
bool is_weekday(long day)
{
    if ((day >= 1) && (day <= 5))
    {
        return true;
    }
    return false;
}

// returns true if boarding time falls under morning peak hours
// morning peak 6:00 to 9:29
bool is_morning_peak(long hrs, long mins)
{
    if ((hrs >= 6) && (hrs <= 9))
    {
        // past 9:29
        if ((hrs == 9) && (mins > 29))
        {
            return false;
        }
        return true;
    }
    return false;
}

// returns true if boarding time falls under evening peak hours
// evening peak 18:00 to 23:59
bool is_evening_peak(long hrs)
{
    if ((hrs >= 18) && (hrs < 24))
    {
        return true;
    }
    return false;
}

// returns true if boarding time falls under midnight peak hours
// mightnight peak 0:00 to 5:59
bool is_midnight_peak(long hrs)
{
    if ((hrs >= 0) && (hrs < 6))
    {
        return true;
    }
    return false;
}

// returns the maximum amount of times the distance can be divded by the respective per meter
// returned counter is multiplied by the applicable fare
// first 1km, if any, subtracted in calc_fare before distance_counter is called
long distance_counter(long dist)
{
    if (dist <= 9000)
    {
        // if distance is exactly divisible by 400m
        if ((dist % 400) == 0)
        {
            return (dist / 400);
        }
        // if not exactly divisible, add 1 to deal with additional distance travelled
        return ((dist / 400) + 1);
    }
    else
    {
        // 9km is subtracted from distance
        // 9km will be added back to the return value as 23 == ((9000/400) + 1)
        dist = dist - 9000;

        //if remaining distance is exactly divisible by 350m
        if ((dist % 350) == 0)
        {
            return ((dist / 350) + 23);
        }
        // if not exactly divisible, add 1 to deal with additional distance travelled
        return ((dist / 350) + 1 + 23);
    }
}

// returns the metered fare, excludes any surcharge
double calc_metered_fare(long dist)
{
    if (dist <= 1000)
    {
        return 3.20;
    }
    return (3.20 + (0.22 * distance_counter(dist - 1000)));
}


// returns the cost of the fare in dollars
double calc_surcharge(double fare, long day, long hrs, long mins)
{
    // check for evening peak
    // 25% surcharge, returns fare multiplied 0.25
    if (is_evening_peak(hrs))
    {
        return (fare * 0.25);
    }

    // check for midnight peak
    // 50% surcharge, returns fare multiplied by 0.5
    else if (is_midnight_peak(hrs))
    {
        return (fare * 0.5);
    }

    // check for weekday
    else if (is_weekday(day))
    {
        // if is weekday then check for morning peak
        // 25% surcharge, returns fare multiplied by 0.25
        if (is_morning_peak(hrs, mins))
        {
            return (fare * 0.25);
        }
    }

    // no surcharge
    return 0;
}

// returns the total fare of the journey
double calc_total_fare(long day, long hrs, long mins, long dist)
{
    double metered_fare = calc_metered_fare(dist);
    return (metered_fare + calc_surcharge(metered_fare, day, hrs, mins));
}

int main()
{
    long* values = cs1010_read_long_array(4);       // store values for day, hours, minutes and distance 
    if (values != NULL)
    {
        long day, hrs, mins, dist;                  // variables for calculation

        day = values[0];
        hrs = values[1];
        mins = values[2];
        dist = values[3];

        // filter illogical inputs, assuming only positive inputs are provided
        if ((day > 0) && (day <= 7) && (hrs >= 0) && (hrs < 24) && (mins >= 0) && (mins < 60))
        {
            double total_fare = calc_total_fare(day, hrs, mins, dist);
            cs1010_println_double(total_fare);
        }
    }
    free(values);
    return 0;
}
