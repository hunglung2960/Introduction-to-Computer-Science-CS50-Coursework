/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"


bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    int lower = 0;
    int upper = (n-1);
    int mid = ((lower + upper)/2);
    // TODO: implement a searching algorithm
    while (upper - lower > 1)
    {
        //find the mid-point while needle is on the left.
        if (value < values[mid])
        {
            upper = mid;
            mid = ((lower + upper)/2);
        }
        //find the mid-point while needle is on the right.
        if (value > values[mid])
        {
            lower = mid;
            mid = ((lower + upper)/2);

        }
        if (value == values[mid] || (value == values[upper] && upper - lower == 1))
        {
            return true;
        }
    }

    if (value != values[mid])
    {
        return false;
    }
}



void sort(int values[], int n)
{
    int array[65536];
    int i;
    int j;
    // TODO: implement a sorting algorithm
    //To store the values in array--values to array[MAX].
    for (j = 0; j < 65536; j++)
    {
        array[j] = 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 65536; j++)
        {
            if (values[i] == j)
            {

                array[j] = array[j] + 1;
            }
        }
    }
    //To put back the values in array--values from array[MAX] in order.
    i = 0;
    for (j = 0; j < 65536; j++)
    {
        if (array[j] != 0)
        {
            int Sum = array[j];
            for (int S = 0; S < Sum; S++)
            {
                values[i] = j;
                if (array[j] > 0)
                {
                    array[j] = array[j] - 1;
                }
                i = i + 1;
            }
        }
    }


}
