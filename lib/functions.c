/*  functions.c -- Calculate factorials and compare strings

    Author:     Diogo Correia
    Creation:   02-01-2021
    Last edit:  19-01-2021                                            */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

/*  Find factorial value  */
double
fact(double x)
{
    double tot = 1;
    for (size_t i = x; i > 0; i--)
        tot *= i;
    
    return tot;
}	// fact()


/*  Find double factorial value  */
double
dfact(double x)
{
    double tot = 1; 
    for (int i=x; i>=0; i=i-2) 
    { 
        if (i==0 || i==1) 
            return tot; 
        else
            tot *= i; 
    } 
}	// dfact()


/*  Compare two char arrays with diferent allocation size  */
int
compstr(const char *str1, const char *str2)
{
    // Check wich one is bigger
    if (strlen(str1) < strlen(str2))
    {
        for (size_t i = 0; i < strlen(str1); i++)
        {
            if (str1[i] != str2[i])
                return 1;
        }
    }
    else
    {
        for (size_t i = 0; i < strlen(str2); i++)
        {
            if (str1[i] != str2[i])
                return 1;
        }
    }
    
    return 0;
}	// compsrt()
